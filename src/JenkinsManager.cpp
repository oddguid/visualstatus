#include "JenkinsManager.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QStringList>
#include <QVariantList>
#include "HttpPort.h"

JenkinsManager::JenkinsManager(QObject *parent)
  : BaseJenkinsManager(parent)
{
}

JenkinsManager::~JenkinsManager()
{
}

bool JenkinsManager::getStatus(const QString &url)
{
  m_error.clear();

  // clear job list
  clearJobs();

  if (url.isEmpty())
  {
    // nothing to do
    return true;
  }

  if (m_httpPort == NULL)
  {
    m_error = tr("No HTTP port set");

    return false;
  }

  // make JSON url
  QString jsonUrl = makeJsonUrl(url);

  // get data
  bool getOk = m_httpPort->get(jsonUrl);

  if (getOk)
  {
    // get data and parse
    QByteArray jsonData = m_httpPort->data().toUtf8();

    // parse JSON data
    bool parseOk = parseJsonData(jsonData);

    if (!parseOk)
    {
      // parsing failed
      m_error = tr("Cannot parse JSON data");

      return false;
    }
  }
  else
  {
    // error getting data
    m_error = m_httpPort->error();

    return false;
  }

  return true;
}

QString JenkinsManager::makeJsonUrl(const QString &url)
{
  // append /api/json to access JSON interface of Jenkins/Hudson
  QString jsonUrl(url);
  QString path = "/api/json";

  if (!url.endsWith(path, Qt::CaseInsensitive))
  {
    if (!url.endsWith("/"))
    {
      jsonUrl += path;
    }
    else
    {
      // append path without first slash
      jsonUrl += path.mid(1);
    }
  }

  return jsonUrl;
}

bool JenkinsManager::parseJsonData(const QByteArray &data)
{
  if (data.isEmpty())
  {
    // no data, done
    return true;
  }

  // parse JSON data
  QJsonParseError parseError;
  QJsonDocument document = QJsonDocument::fromJson(data, &parseError);

  if (parseError.error != QJsonParseError::NoError)
  {
    // parse error
    return false;
  }

  if (!document.isObject())
  {
    // not an object
    return false;
  }

  // convert to map
  const QVariantMap result = document.object().toVariantMap();

  // convert to jobs and add to list
  const QVariantList jobList = result["jobs"].toList();

  for (int i = 0; i < jobList.size(); ++i)
  {
    const QVariantMap jobMap = jobList.at(i).toMap();

    // create job
    JenkinsJob *job = new JenkinsJob;
    job->name(jobMap.value("name").toString());
    job->url(jobMap.value("url").toString());
    job->color(jobMap.value("color").toString());

    if (m_jobStatus.contains(job->name()))
    {
      // delete if key already exists
      JenkinsJob *tmp = m_jobStatus.take(job->name());
      delete tmp;
    }

    m_jobStatus[job->name()] = job;
  }

  // done
  return true;
}

QScriptValue jenkinsManagerConstructor(QScriptContext *context,
  QScriptEngine *engine)
{
  // parent of new object is in context
  QObject *parent = context->argument(0).toQObject();

  // create new JenkinsManager object
  QObject *object = new JenkinsManager(parent);

  // pass object to script
  return engine->newQObject(object, QScriptEngine::ScriptOwnership);
}
