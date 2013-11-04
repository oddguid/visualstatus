#include "JenkinsManager.h"
#include <qjson/parser.h>
#include <qjson/qobjecthelper.h>

namespace script
{

JenkinsManager::JenkinsManager(QObject *parent)
  : BaseJenkinsManager(parent)
  , m_manager()
  , m_reply(NULL)
{
  connect(&m_manager, SIGNAL(finished(QNetworkReply*)),
          this, SLOT(downloadFinished(QNetworkReply*)));
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

void JenkinsManager::getStatus(const QString &url)
{
  // clear job list
  clearJobs();

  if (url.isEmpty())
  {
    // nothing to do
    return;
  }

  // make JSON url
  QString jsonUrl = makeJsonUrl(url);

  // download JSON data
  QNetworkRequest request(jsonUrl);
  m_reply = m_manager.get(request);

  connect(m_reply, SIGNAL(sslErrors(QList<QSslError>)),
          SLOT(sslErrors(QList<QSslError>)));
}

void JenkinsManager::downloadFinished(QNetworkReply *reply)
{
  if (reply->error())
  {
    // error occurred during transfer.
    emit error(reply->errorString());
  }
  else
  {
    // get all received data
    QByteArray data = reply->readAll();

    // parse JSON data
    bool ok = parseJsonData(data);

    if (!ok)
    {
      // parsing failed
      emit error("Cannot parse JSON data");
    }
    else
    {
      // parsing succeeded, indicate job status available
      emit statusAvailable();
    }

    m_reply->deleteLater();
  }
}

void JenkinsManager::sslErrors(const QList<QSslError> &errors)
{
#ifndef QT_NO_OPENSSL
  QString errorString;

  foreach (const QSslError &error, errors)
  {
    // concatenate errors
    errorString += QString("SSL error: %1\n").arg(error.errorString());
  }

  // signal new error message
  emit error(errorString);
#endif
}

} // script

QScriptValue jenkinsManagerConstructor(QScriptContext *context,
  QScriptEngine *engine)
{
  // parent of new object is in context
  QObject *parent = context->argument(0).toQObject();

  // create new JenkinsManager object
  QObject *object = new script::JenkinsManager(parent);

  // pass object to script
  return engine->newQObject(object, QScriptEngine::ScriptOwnership);
}
