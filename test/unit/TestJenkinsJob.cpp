#include "TestJenkinsJob.h"
#include "../../src/JenkinsJob.h"

using namespace script;

namespace unittest
{

void TestJenkinsJob::defaultConstructor()
{
  JenkinsJob job;

  QVERIFY(job.name().isEmpty() == true);
  QVERIFY(job.url().isEmpty() == true);
  QVERIFY(job.color().isEmpty() == true);
}

void TestJenkinsJob::name()
{
  QString nameExp = "JobName";

  JenkinsJob job;
  job.name(nameExp);

  QCOMPARE(job.name(), nameExp);
  QVERIFY(job.url().isEmpty() == true);
  QVERIFY(job.color().isEmpty() == true);
}

void TestJenkinsJob::url()
{
  QString urlExp = "http://example.com";

  JenkinsJob job;
  job.url(urlExp);

  QVERIFY(job.name().isEmpty() == true);
  QCOMPARE(job.url(), urlExp);
  QVERIFY(job.color().isEmpty() == true);
}

void TestJenkinsJob::color()
{
  QString colorExp = "blue";

  JenkinsJob job;
  job.color(colorExp);

  QVERIFY(job.name().isEmpty() == true);
  QVERIFY(job.url().isEmpty() == true);
  QCOMPARE(job.color(), colorExp);
}

} // unittest

QTEST_MAIN(unittest::TestJenkinsJob)
