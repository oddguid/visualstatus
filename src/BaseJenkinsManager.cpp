#include "BaseJenkinsManager.h"
#include "JenkinsJob.h"
#include "BaseHttpPort.h"

BaseJenkinsManager::BaseJenkinsManager(QObject *parent)
  : QObject(parent)
  , m_jobStatus()
  , m_error()
  , m_httpPort(nullptr)
{
}

BaseJenkinsManager::~BaseJenkinsManager()
{
  clearJobs();
}

QStringList BaseJenkinsManager::jobNames()
{
  return m_jobStatus.keys();
}

QString BaseJenkinsManager::jobUrl(const QString &jobName)
{
  if (m_jobStatus.contains(jobName))
  {
    JenkinsJob *job = m_jobStatus[jobName];

    if (job != nullptr)
    {
      return job->url();
    }
  }

  return QString();
}

QString BaseJenkinsManager::jobColor(const QString &jobName)
{
  if (m_jobStatus.contains(jobName))
  {
    JenkinsJob *job = m_jobStatus[jobName];

    if (job != nullptr)
    {
      return job->color();
    }
  }

  return QString();
}

QObjectList BaseJenkinsManager::jobs()
{
  QObjectList jobs;
  QMap<QString, JenkinsJob *>::iterator iter;

  for (iter = m_jobStatus.begin(); iter != m_jobStatus.end(); ++iter)
  {
    jobs.append(iter.value());
  }

  return jobs;
}

QObject *BaseJenkinsManager::job(const QString &jobName)
{
  if (m_jobStatus.contains(jobName))
  {
    return m_jobStatus[jobName];
  }

  return nullptr;
}

void BaseJenkinsManager::setHttpPort(BaseHttpPort *port)
{
  m_httpPort = port;
}

QString BaseJenkinsManager::error() const
{
  return m_error;
}

void BaseJenkinsManager::clearJobs()
{
  qDeleteAll(m_jobStatus.begin(), m_jobStatus.end());
  m_jobStatus.clear();
}
