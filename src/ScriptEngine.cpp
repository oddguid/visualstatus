#include "ScriptEngine.h"

ScriptEngine::ScriptEngine(QObject *parent)
  : QScriptEngine(parent)
{
  addFunctions();
}

ScriptEngine::~ScriptEngine()
{
}

QScriptValue ScriptEngine::exitScriptFunction(QScriptContext *context,
  QScriptEngine *engine)
{
  Q_UNUSED(context)

  ScriptEngine *scriptEngine = dynamic_cast<ScriptEngine *>(engine);

  if (scriptEngine != nullptr)
  {
    // signal exit
    emit scriptEngine->exitScript();
  }

  return engine->undefinedValue();
}

void ScriptEngine::addFunctions()
{
  // register the exit function
  QScriptValue exitFunction = this->newFunction(exitScriptFunction);
  this->globalObject().setProperty("exit", exitFunction);
}

