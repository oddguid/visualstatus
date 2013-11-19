#include "MockJenkinsManager.h"
#include <QStringList>
#include <QFile>

MockJenkinsManager::MockJenkinsManager(QObject *parent)
  : BaseJenkinsManager(parent)
{
}

MockJenkinsManager::~MockJenkinsManager()
{
}

bool MockJenkinsManager::getStatus(const QString &fileName)
{
  m_error.clear();

  // clear job list
  qDeleteAll(m_jobStatus);
  m_jobStatus.clear();

  // open file
  QFile statusFile(fileName);

  if (!statusFile.open(QIODevice::ReadOnly | QIODevice::Text))
  {
    // cannot open file
    m_error = QString(tr("Cannot open file %1")).arg(fileName);

    return false;
  }

  // parse contents
  parseJobBuffer(&statusFile);

  statusFile.close();

  return true;
}

void MockJenkinsManager::parseJobBuffer(QIODevice *jobBuffer)
{
  if (jobBuffer == NULL)
  {
    // nothing to do
    return;
  }

  // read lines
  while (!jobBuffer->atEnd())
  {
    QString statusLine = jobBuffer->readLine();
    QStringList statusItems = statusLine.split("|");

    // must be three items in status
    if (statusItems.size() == 3)
    {
      // create job
      JenkinsJob *job = new JenkinsJob();
      job->name(statusItems.value(0));
      job->url(statusItems.value(1));

      // remove end of line from color
      job->color(statusItems.value(2).simplified());

      if (m_jobStatus.contains(job->name()))
      {
        // key already exists, delete value before replacing
        JenkinsJob *tmp = m_jobStatus.take(job->name());
        delete tmp;
      }

      m_jobStatus[job->name()] = job;
    }
  }
}

QScriptValue mockJenkinsManagerConstructor(QScriptContext *context,
  QScriptEngine *engine)
{
  // parent of new object is in context
  QObject *parent = context->argument(0).toQObject();

  // create new MockJenkinsManager object
  QObject *object = new MockJenkinsManager(parent);

  // pass object to script
  return engine->newQObject(object, QScriptEngine::ScriptOwnership);
}
