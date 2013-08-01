#include "TestJenkinsManager.h"

// redefine private to public to get access to the member variables of the
// JenkinsManager class
#define private public
#include "../../src/JenkinsManager.h"
#undef private

using namespace script;

namespace unittest
{

void TestJenkinsManager::defaultConstructor()
{
  JenkinsManager manager;

  QVERIFY(manager.jobNames().size() == 0);
}

void TestJenkinsManager::jobNames()
{
  JenkinsManager manager;

  // setup test data
  JenkinsJob *job1 = new JenkinsJob;
  job1->name("job1");
  job1->url("http://example.com/job1");
  job1->color("red");

  JenkinsJob *job2 = new JenkinsJob;
  job2->name("job2");
  job2->url("http://example.com/job2");
  job2->color("yellow_anime");

  manager.m_jobStatus[job1->name()] = job1;
  manager.m_jobStatus[job2->name()] = job2;

  // get job names
  QStringList jobNames = manager.jobNames();

  QVERIFY(jobNames.size() == 2);
  QVERIFY(jobNames.contains(job1->name()) == true);
  QVERIFY(jobNames.contains(job2->name()) == true);
}

void TestJenkinsManager::jobUrl()
{
  JenkinsManager manager;

  // setup test data
  JenkinsJob *job1 = new JenkinsJob;
  job1->name("job1");
  job1->url("http://example.com/job1");
  job1->color("red");

  JenkinsJob *job2 = new JenkinsJob;
  job2->name("job2");
  job2->url("http://example.com/job2");
  job2->color("yellow_anime");

  manager.m_jobStatus[job1->name()] = job1;
  manager.m_jobStatus[job2->name()] = job2;

  // get job url
  QCOMPARE(manager.jobUrl("job2"), job2->url());
  QCOMPARE(manager.jobUrl("job3"), QString());
}

void TestJenkinsManager::jobColor()
{
  JenkinsManager manager;

  // setup test data
  JenkinsJob *job1 = new JenkinsJob;
  job1->name("job1");
  job1->url("http://example.com/job1");
  job1->color("red");

  JenkinsJob *job2 = new JenkinsJob;
  job2->name("job2");
  job2->url("http://example.com/job2");
  job2->color("yellow_anime");

  manager.m_jobStatus[job1->name()] = job1;
  manager.m_jobStatus[job2->name()] = job2;

  // get job color
  QCOMPARE(manager.jobColor("job1"), job1->color());
  QCOMPARE(manager.jobColor("job3"), QString());
}

void TestJenkinsManager::jobs()
{
  JenkinsManager manager;

  // setup test data
  JenkinsJob *job1 = new JenkinsJob;
  job1->name("job1");
  job1->url("http://example.com/job1");
  job1->color("red");

  JenkinsJob *job2 = new JenkinsJob;
  job2->name("job2");
  job2->url("http://example.com/job2");
  job2->color("yellow_anime");

  JenkinsJob *job3 = new JenkinsJob;
  job3->name("job3");

  manager.m_jobStatus[job1->name()] = job1;
  manager.m_jobStatus[job2->name()] = job2;

  // get jobs
  QObjectList jobs = manager.jobs();

  QVERIFY(jobs.size() == 2);
  QVERIFY(jobs.contains(job1) == true);
  QVERIFY(jobs.contains(job2) == true);
  QVERIFY(jobs.contains(job3) == false);

  // clean up
  delete job3;
}

void TestJenkinsManager::job()
{
  JenkinsManager manager;

  // setup test data
  JenkinsJob *job1 = new JenkinsJob;
  job1->name("job1");
  job1->url("http://example.com/job1");
  job1->color("red");

  JenkinsJob *job2 = new JenkinsJob;
  job2->name("job2");
  job2->url("http://example.com/job2");
  job2->color("yellow_anime");

  manager.m_jobStatus[job1->name()] = job1;
  manager.m_jobStatus[job2->name()] = job2;

  // get job
  QObject *job = manager.job("job1");

  QVERIFY(job != NULL);

  JenkinsJob *jenkinsJob = static_cast<JenkinsJob *>(job);

  QCOMPARE(jenkinsJob->name(), job1->name());
  QCOMPARE(jenkinsJob->url(), job1->url());
  QCOMPARE(jenkinsJob->color(), job1->color());

  job = manager.job("job3");

  QVERIFY(job == NULL);
}

void TestJenkinsManager::jenkinsManagerConstructor()
{
  QScriptEngine *scriptEngine = new QScriptEngine();
  scriptEngine->setProcessEventsInterval(100);

  QScriptContext *scriptContext = scriptEngine->currentContext();

  // add this-object and activation-object to fake a script function call
  QScriptValue thisObject;
  QScriptValue activationObject;

  scriptContext->setThisObject(thisObject);
  scriptContext->setActivationObject(activationObject);

  // ask for new script jenkinsmanager object
  QScriptValue scriptJenkinsManager =
      ::jenkinsManagerConstructor(scriptContext, scriptEngine);

  QFAIL("TODOD: call script function");
//  scriptJenkinsManager
}

} // unittest

QTEST_MAIN(unittest::TestJenkinsManager);
