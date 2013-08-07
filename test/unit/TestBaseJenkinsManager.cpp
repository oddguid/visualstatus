#include "TestBaseJenkinsManager.h"
#include "../../src/JenkinsJob.h"

using namespace script;

namespace unittest
{

void TestBaseJenkinsManager::defaultConstructor()
{
  DummyJenkinsManager manager;

  QVERIFY(manager.jobNames().size() == 0);
}

void TestBaseJenkinsManager::jobNames()
{
  DummyJenkinsManager manager;

  // setup test data
  JenkinsJob *job1 = new JenkinsJob;
  job1->name("job1");
  job1->url("http://example.com/job1");
  job1->color("red");

  JenkinsJob *job2 = new JenkinsJob;
  job2->name("job2");
  job2->url("http://example.com/job2");
  job2->color("yellow_anime");

  manager.jobMap()[job1->name()] = job1;
  manager.jobMap()[job2->name()] = job2;

  // get job names
  QStringList jobNames = manager.jobNames();

  QVERIFY(jobNames.size() == 2);
  QVERIFY(jobNames.contains(job1->name()) == true);
  QVERIFY(jobNames.contains(job2->name()) == true);
}

void TestBaseJenkinsManager::jobUrl()
{
  DummyJenkinsManager manager;

  // setup test data
  JenkinsJob *job1 = new JenkinsJob;
  job1->name("job1");
  job1->url("http://example.com/job1");
  job1->color("red");

  JenkinsJob *job2 = new JenkinsJob;
  job2->name("job2");
  job2->url("http://example.com/job2");
  job2->color("yellow_anime");

  manager.jobMap()[job1->name()] = job1;
  manager.jobMap()[job2->name()] = job2;

  // get job url
  QCOMPARE(manager.jobUrl("job2"), job2->url());
  QCOMPARE(manager.jobUrl("job3"), QString());
}

void TestBaseJenkinsManager::jobColor()
{
  DummyJenkinsManager manager;

  // setup test data
  JenkinsJob *job1 = new JenkinsJob;
  job1->name("job1");
  job1->url("http://example.com/job1");
  job1->color("red");

  JenkinsJob *job2 = new JenkinsJob;
  job2->name("job2");
  job2->url("http://example.com/job2");
  job2->color("yellow_anime");

  manager.jobMap()[job1->name()] = job1;
  manager.jobMap()[job2->name()] = job2;

  // get job color
  QCOMPARE(manager.jobColor("job1"), job1->color());
  QCOMPARE(manager.jobColor("job3"), QString());
}

void TestBaseJenkinsManager::jobs()
{
  DummyJenkinsManager manager;

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

  manager.jobMap()[job1->name()] = job1;
  manager.jobMap()[job2->name()] = job2;

  // get jobs
  QObjectList jobs = manager.jobs();

  QVERIFY(jobs.size() == 2);
  QVERIFY(jobs.contains(job1) == true);
  QVERIFY(jobs.contains(job2) == true);
  QVERIFY(jobs.contains(job3) == false);

  // clean up
  delete job3;
}

void TestBaseJenkinsManager::job()
{
  DummyJenkinsManager manager;

  // setup test data
  JenkinsJob *job1 = new JenkinsJob;
  job1->name("job1");
  job1->url("http://example.com/job1");
  job1->color("red");

  JenkinsJob *job2 = new JenkinsJob;
  job2->name("job2");
  job2->url("http://example.com/job2");
  job2->color("yellow_anime");

  manager.jobMap()[job1->name()] = job1;
  manager.jobMap()[job2->name()] = job2;

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

} // unittest

QTEST_MAIN(unittest::TestBaseJenkinsManager)
