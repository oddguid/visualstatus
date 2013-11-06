#include "TestJenkinsManager.h"

// redefine protected to public to get access to the member variables of the
// JenkinsManager class
#define protected public
#include "../../src/JenkinsManager.h"
#undef protected

using namespace script;

namespace unittest
{

void TestJenkinsManager::defaultConstructor()
{
  JenkinsManager manager;

  QVERIFY(manager.jobNames().size() == 0);
}

void TestJenkinsManager::makeJsonUrl()
{
  JenkinsManager manager;
  QString expectedUrl = "http://example.com/api/json";
  QString inputUrl = "http://example.com";

  // base address
  QString outputUrl = manager.makeJsonUrl(inputUrl);
  QCOMPARE(outputUrl, expectedUrl);

  // base address with trailing slash
  inputUrl += "/";
  outputUrl = manager.makeJsonUrl(inputUrl);
  QCOMPARE(outputUrl, expectedUrl);

  // json address
  outputUrl = manager.makeJsonUrl(expectedUrl);
  QCOMPARE(outputUrl, expectedUrl);
}

void TestJenkinsManager::parseJsonDataEmpty()
{
  JenkinsManager manager;
  QByteArray data;

  bool ok = manager.parseJsonData(data);

  QCOMPARE(ok, true);
  QVERIFY(manager.jobNames().isEmpty() == true);
}

void TestJenkinsManager::parseJsonDataError()
{
  JenkinsManager manager;

  // error data: ] is missing in first line
  QByteArray data =
      "{\"assignedLabels\":[{},"
      "\"mode\":\"NORMAL\","
      "\"nodeDescription\":\"master Jenkins node\","
      "\"nodeName\":\"\","
      "\"numExecutors\":3,"
      "\"description\":null,"
      "\"jobs\":["
      "{\"name\":\"job1\",\"url\":\"http://example.com/job/job1/\",\"color\":\"yellow\"},"
      "{\"name\":\"job2\",\"url\":\"http://example.com/job/job2/\",\"color\":\"disabled\"},"
      "{\"name\":\"job3\",\"url\":\"http://example.com/job/job3/\",\"color\":\"blue\"}]"
      ",\"overallLoad\":{},\"primaryView\":{\"name\":\"All\",\"url\":\"http://example.com/\"},"
      "\"quietingDown\":false,"
      "\"slaveAgentPort\":32323,"
      "\"unlabeledLoad\":{},"
      "\"useCrumbs\":false,"
      "\"useSecurity\":true,"
      "\"views\":[{\"name\":\"All\",\"url\":\"http://example.com/\"}]}";

  bool ok = manager.parseJsonData(data);

  QCOMPARE(ok, false);
  QVERIFY(manager.jobNames().isEmpty() == true);
}

void TestJenkinsManager::parseJsonData()
{
  JenkinsManager manager;

  QByteArray data =
      "{\"assignedLabels\":[{}],"
      "\"mode\":\"NORMAL\","
      "\"nodeDescription\":\"master Jenkins node\","
      "\"nodeName\":\"\","
      "\"numExecutors\":3,"
      "\"description\":null,"
      "\"jobs\":["
      "{\"name\":\"job1\",\"url\":\"http://example.com/job/job1/\",\"color\":\"yellow\"},"
      "{\"name\":\"job2\",\"url\":\"http://example.com/job/job2/\",\"color\":\"disabled\"},"
      "{\"name\":\"job3\",\"url\":\"http://example.com/job/job3/\",\"color\":\"blue\"}]"
      ",\"overallLoad\":{},\"primaryView\":{\"name\":\"All\",\"url\":\"http://example.com/\"},"
      "\"quietingDown\":false,"
      "\"slaveAgentPort\":32323,"
      "\"unlabeledLoad\":{},"
      "\"useCrumbs\":false,"
      "\"useSecurity\":true,"
      "\"views\":[{\"name\":\"All\",\"url\":\"http://example.com/\"}]}";

  bool ok = manager.parseJsonData(data);

  QCOMPARE(ok, true);

  // list should have 3 jobs
  QCOMPARE(manager.jobNames().size(), 3);

  QVERIFY(manager.jobNames().contains("job1") == true);
  QVERIFY(manager.jobNames().contains("job2") == true);
  QVERIFY(manager.jobNames().contains("job3") == true);
}

void TestJenkinsManager::parseJsonDataDouble()
{
  JenkinsManager manager;

  QByteArray data =
      "{\"assignedLabels\":[{}],"
      "\"mode\":\"NORMAL\","
      "\"nodeDescription\":\"master Jenkins node\","
      "\"nodeName\":\"\","
      "\"numExecutors\":3,"
      "\"description\":null,"
      "\"jobs\":["
      "{\"name\":\"job1\",\"url\":\"http://example.com/job/job1/\",\"color\":\"yellow\"},"
      "{\"name\":\"job2\",\"url\":\"http://example.com/job/job2/\",\"color\":\"disabled\"},"
      "{\"name\":\"job2\",\"url\":\"http://example.com/job/job3/\",\"color\":\"blue\"}]"
      ",\"overallLoad\":{},\"primaryView\":{\"name\":\"All\",\"url\":\"http://example.com/\"},"
      "\"quietingDown\":false,"
      "\"slaveAgentPort\":32323,"
      "\"unlabeledLoad\":{},"
      "\"useCrumbs\":false,"
      "\"useSecurity\":true,"
      "\"views\":[{\"name\":\"All\",\"url\":\"http://example.com/\"}]}";

  bool ok = manager.parseJsonData(data);

  QCOMPARE(ok, true);

  // list should have 2 jobs
  QCOMPARE(manager.jobNames().size(), 2);

  QVERIFY(manager.jobNames().contains("job1") == true);
  QVERIFY(manager.jobNames().contains("job2") == true);
  QCOMPARE(manager.jobColor("job2"), QString("blue"));
}

void TestJenkinsManager::parseJsonDataTwice()
{
  JenkinsManager manager;

  QByteArray data =
      "{\"assignedLabels\":[{}],"
      "\"mode\":\"NORMAL\","
      "\"nodeDescription\":\"master Jenkins node\","
      "\"nodeName\":\"\","
      "\"numExecutors\":3,"
      "\"description\":null,"
      "\"jobs\":["
      "{\"name\":\"job1\",\"url\":\"http://example.com/job/job1/\",\"color\":\"yellow\"},"
      "{\"name\":\"job2\",\"url\":\"http://example.com/job/job2/\",\"color\":\"disabled\"},"
      "{\"name\":\"job3\",\"url\":\"http://example.com/job/job3/\",\"color\":\"blue\"}]"
      ",\"overallLoad\":{},\"primaryView\":{\"name\":\"All\",\"url\":\"http://example.com/\"},"
      "\"quietingDown\":false,"
      "\"slaveAgentPort\":32323,"
      "\"unlabeledLoad\":{},"
      "\"useCrumbs\":false,"
      "\"useSecurity\":true,"
      "\"views\":[{\"name\":\"All\",\"url\":\"http://example.com/\"}]}";

  QByteArray data2 =
      "{\"assignedLabels\":[{}],"
      "\"mode\":\"NORMAL\","
      "\"nodeDescription\":\"master Jenkins node\","
      "\"nodeName\":\"\","
      "\"numExecutors\":3,"
      "\"description\":null,"
      "\"jobs\":["
      "{\"name\":\"job11\",\"url\":\"http://example.com/job/job11/\",\"color\":\"yellow\"},"
      "{\"name\":\"job12\",\"url\":\"http://example.com/job/job12/\",\"color\":\"disabled\"},"
      "{\"name\":\"job13\",\"url\":\"http://example.com/job/job13/\",\"color\":\"blue\"}]"
      ",\"overallLoad\":{},\"primaryView\":{\"name\":\"All\",\"url\":\"http://example.com/\"},"
      "\"quietingDown\":false,"
      "\"slaveAgentPort\":32323,"
      "\"unlabeledLoad\":{},"
      "\"useCrumbs\":false,"
      "\"useSecurity\":true,"
      "\"views\":[{\"name\":\"All\",\"url\":\"http://example.com/\"}]}";

  bool ok = manager.parseJsonData(data);

  QCOMPARE(ok, true);

  ok = manager.parseJsonData(data2);

  QCOMPARE(ok, true);

  // list should have 6 jobs
  QCOMPARE(manager.jobNames().size(), 6);

  QVERIFY(manager.jobNames().contains("job1") == true);
  QVERIFY(manager.jobNames().contains("job2") == true);
  QVERIFY(manager.jobNames().contains("job3") == true);
  QVERIFY(manager.jobNames().contains("job11") == true);
  QVERIFY(manager.jobNames().contains("job12") == true);
  QVERIFY(manager.jobNames().contains("job13") == true);
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

  QFAIL("TODO: call script function");
//  scriptJenkinsManager
}

} // unittest

QTEST_MAIN(unittest::TestJenkinsManager)
