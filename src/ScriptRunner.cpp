#include "ScriptRunner.h"
#include "Logger.h"
#include "MockSerialPort.h"
#include "SerialPort.h"
#include "MockHttpPort.h"
#include "HttpPort.h"
#include "MockJenkinsManager.h"
#include "JenkinsManager.h"
#include "SerialLed.h"

ScriptRunner::ScriptRunner(QObject *parent)
  : QObject(parent)
  , m_scriptEngine(NULL)
{
  // create script engine
  createScriptEngine();
}

ScriptRunner::~ScriptRunner()
{
}

void ScriptRunner::createScriptEngine()
{
  m_scriptEngine = new ScriptEngine(this);
  m_scriptEngine->setProcessEventsInterval(100);

  // add script objects
  addLogger();
  addColor();
  addMockSerialPort();
  addSerialPort();
  addMockHttpPort();
  addHttpPort();
  addMockJenkinsManager();
  addJenkinsManager();
  addSerialLed();

  // connect script engine signals
  connect(m_scriptEngine, SIGNAL(exitScript()), this, SLOT(exitScript()));
}

void ScriptRunner::addLogger()
{
  // create logger object
  Logger *logger = new Logger;

  // connect signals
  connect(logger, SIGNAL(appendLog(LogLevel::Enum, QString)),
          this, SIGNAL(appendLog(LogLevel::Enum, QString)));

  connect(logger, SIGNAL(clearLog()), this, SIGNAL(clearLog()));

  // add logger object to script environment
  QScriptValue objectValue = m_scriptEngine->newQObject(logger);
  m_scriptEngine->globalObject().setProperty("logger", objectValue);
}

void ScriptRunner::addColor()
{
  // register Color conversion functions
  qScriptRegisterMetaType(m_scriptEngine,
                          colorToScriptValue,
                          colorFromScriptValue);

  // register the custom constructor function
  QScriptValue ctor = m_scriptEngine->newFunction(colorConstructor);

  QScriptValue metaObject =
    m_scriptEngine->newQMetaObject(&QObject::staticMetaObject, ctor);

  m_scriptEngine->globalObject().setProperty("Color", metaObject);
}

void ScriptRunner::addMockSerialPort()
{
  // register the custom constructor function
  QScriptValue ctor = m_scriptEngine->newFunction(mockSerialPortConstructor);

  QScriptValue metaObject =
      m_scriptEngine->newQMetaObject(&QObject::staticMetaObject, ctor);

  m_scriptEngine->globalObject().setProperty("MockSerialPort", metaObject);
}

void ScriptRunner::addSerialPort()
{
  // register the custom constructor function
  QScriptValue ctor = m_scriptEngine->newFunction(serialPortConstructor);

  QScriptValue metaObject =
    m_scriptEngine->newQMetaObject(&QObject::staticMetaObject, ctor);

  m_scriptEngine->globalObject().setProperty("SerialPort", metaObject);
}

void ScriptRunner::addMockHttpPort()
{
  // register the custom constructor function
  QScriptValue ctor = m_scriptEngine->newFunction(mockHttpPortConstructor);

  QScriptValue metaObject =
      m_scriptEngine->newQMetaObject(&QObject::staticMetaObject, ctor);

  m_scriptEngine->globalObject().setProperty("MockHttpPort", metaObject);
}

void ScriptRunner::addHttpPort()
{
  // register the custom constructor function
  QScriptValue ctor = m_scriptEngine->newFunction(httpPortConstructor);

  QScriptValue metaObject =
    m_scriptEngine->newQMetaObject(&QObject::staticMetaObject, ctor);

  m_scriptEngine->globalObject().setProperty("HttpPort", metaObject);
}

void ScriptRunner::addMockJenkinsManager()
{
  // register the custom constructor function
  QScriptValue ctor =
      m_scriptEngine->newFunction(mockJenkinsManagerConstructor);

  QScriptValue metaObject =
      m_scriptEngine->newQMetaObject(&QObject::staticMetaObject, ctor);

  m_scriptEngine->globalObject().setProperty("MockJenkinsManager", metaObject);
}

void ScriptRunner::addJenkinsManager()
{
  // register the custom constructor function
  QScriptValue ctor =
      m_scriptEngine->newFunction(jenkinsManagerConstructor);

  QScriptValue metaObject =
      m_scriptEngine->newQMetaObject(&QObject::staticMetaObject, ctor);

  m_scriptEngine->globalObject().setProperty("JenkinsManager", metaObject);
}

void ScriptRunner::addSerialLed()
{
  // register the custom constructor function
  QScriptValue ctor = m_scriptEngine->newFunction(serialLedConstructor);

  QScriptValue metaObject =
    m_scriptEngine->newQMetaObject(&QObject::staticMetaObject, ctor);

  m_scriptEngine->globalObject().setProperty("SerialLed", metaObject);
}

void ScriptRunner::runScript(const QString &script, const QString &fileName)
{
  // clear exceptions
  m_scriptEngine->clearExceptions();

  // evaluate script
  m_scriptEngine->evaluate(script, fileName);

  if (m_scriptEngine->hasUncaughtException())
  {
    QScriptValue error = m_scriptEngine->uncaughtException();
    int lineNumber = m_scriptEngine->uncaughtExceptionLineNumber();

    // emit errors
    emit appendLog(LogLevel::Error,
                   QString(tr("Error in script, line %1:")).arg(lineNumber));

    emit appendLog(LogLevel::Error, QString("%1").arg(error.toString()));
  }
}

void ScriptRunner::exitScript()
{
  if (m_scriptEngine->isEvaluating())
  {
    // abort evaluation of script
    m_scriptEngine->abortEvaluation();
  }

  emit exit();
}
