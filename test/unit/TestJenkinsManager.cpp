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

void TestJenkinsManager::parseJsonData()
{
  QFAIL("TODO: implement function");
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
