#include "TestMockJenkinsManager.h"

// redefine protected to public to get access to the member variables of the
// MockJenkinsManager class
#define protected public
#include "../../src/MockJenkinsManager.h"
#undef protected

namespace unittest
{

void TestMockJenkinsManager::defaultConstructor()
{
  MockJenkinsManager manager;

  QVERIFY(manager.jobNames().size() == 0);
}

void TestMockJenkinsManager::parseJobBufferEmpty()
{
  MockJenkinsManager manager;

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
  MockJenkinsManager manager;

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
  MockJenkinsManager manager;

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

void TestMockJenkinsManager::mockJenkinsManagerConstructor()
{
  QScriptEngine *scriptEngine = new QScriptEngine();
  scriptEngine->setProcessEventsInterval(100);

  QScriptContext *scriptContext = scriptEngine->currentContext();

  // add this-object and activation-object to fake a script function call
  QScriptValue thisObject;
  QScriptValue activationObject;

  scriptContext->setThisObject(thisObject);
  scriptContext->setActivationObject(activationObject);

  // ask for new script mockjenkinsmanager object
  QScriptValue scriptMockJenkinsManager =
      ::mockJenkinsManagerConstructor(scriptContext, scriptEngine);

  QFAIL("TODO: call script function");
//  scriptMockJenkinsManager
}

} // unittest

QTEST_MAIN(unittest::TestMockJenkinsManager)
