#include "TestMockJenkinsManager.h"

namespace unittest
{

void TestMockJenkinsManager::defaultConstructor()
{
  DummyJenkinsManager manager;

  QVERIFY(manager.jobNames().size() == 0);
}

void TestMockJenkinsManager::parseJobBufferEmpty()
{
  DummyJenkinsManager manager;

  // no buffer
  manager.parseJobBuffer(NULL);

  QVERIFY(manager.jobNames().size() == 0);
}

void TestMockJenkinsManager::parseJobBuffer()
{
  QByteArray jobArray(
        "job1|http://example.com/job1|red\n"
        "job2|http://example.com/job2|yellow\n"
        "job1|http://example.com/job1|blue\n");

  QBuffer jobBuffer(&jobArray);
  DummyJenkinsManager manager;

  // use buffer
  if (jobBuffer.open(QIODevice::ReadOnly))
  {
    manager.parseJobBuffer(&jobBuffer);

    jobBuffer.close();

    QStringList jobNames = manager.jobNames();

    QVERIFY(jobNames.size() == 2);
    QVERIFY(jobNames.contains("job1") == true);
    QVERIFY(jobNames.contains("job2") == true);

    // job1 should be last instance
    QCOMPARE(manager.jobColor("job1"), QString("blue"));
  }
  else
  {
    QFAIL("Cannot open buffer!");
  }
}

void TestMockJenkinsManager::parseJobBufferError()
{
  QByteArray jobArray(
        "job1|http://example.com/job1|red\n"
        "job2|http://example.com/job2|yellow\n"
        "job3|blue\n");

  QBuffer jobBuffer(&jobArray);
  DummyJenkinsManager manager;

  // use buffer
  if (jobBuffer.open(QIODevice::ReadOnly))
  {
    manager.parseJobBuffer(&jobBuffer);

    jobBuffer.close();

    QStringList jobNames = manager.jobNames();

    QVERIFY(jobNames.size() == 2);
    QVERIFY(jobNames.contains("job1") == true);
    QVERIFY(jobNames.contains("job2") == true);
    QVERIFY(jobNames.contains("job3") == false);
  }
  else
  {
    QFAIL("Cannot open buffer!");
  }
}

} // unittest

QTEST_MAIN(unittest::TestMockJenkinsManager)
