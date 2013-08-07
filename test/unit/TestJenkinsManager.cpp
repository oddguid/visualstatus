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

QTEST_MAIN(unittest::TestJenkinsManager)
