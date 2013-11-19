#include "JenkinsManager.h"
#include <qjson/parser.h>
#include <qjson/qobjecthelper.h>
#include "HttpPort.h"

JenkinsManager::JenkinsManager(BaseHttpPort *httpPort, QObject *parent)
  : BaseJenkinsManager(parent)
  , m_httpPort(httpPort)
{
  if (m_httpPort != NULL)
  {
    m_httpPort->setParent(this);
  }
}

JenkinsManager::~JenkinsManager()
{
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
  QJson::Parser parser;
  bool ok;

  QVariantMap result = parser.parse(data, &ok).toMap();

  if (!ok)
  {
    // parse error
    return false;
  }

  // convert to jobs and add to list
  QList<QVariant> jobList = result["jobs"].toList();

  for (int i=0; i<jobList.size(); ++i)
  {
    QVariantMap jobMap = jobList.at(i).toMap();

    JenkinsJob *job = new JenkinsJob;

    QJson::QObjectHelper::qvariant2qobject(jobMap, job);

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
    m_error = QString("No HTTP port set");

    return false;
  }

  // make JSON url
  QString jsonUrl = makeJsonUrl(url);

  // get data
  bool getOk = m_httpPort->get(QUrl(jsonUrl));

  if (getOk)
  {
    // get data and parse
    QByteArray jsonData = m_httpPort->data().toUtf8();

    // parse JSON data
    bool parseOk = parseJsonData(jsonData);

    if (!parseOk)
    {
      // parsing failed
      m_error = QString("Cannot parse JSON data");

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

QScriptValue jenkinsManagerConstructor(QScriptContext *context,
  QScriptEngine *engine)
{
  // parent of new object is in context
  QObject *parent = context->argument(0).toQObject();

  // create new JenkinsManager object
  HttpPort *port = new HttpPort;
  QObject *object = new JenkinsManager(port, parent);

  // pass object to script
  return engine->newQObject(object, QScriptEngine::ScriptOwnership);
}
