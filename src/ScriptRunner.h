#ifndef VST_SCRIPTRUNNER_H
#define VST_SCRIPTRUNNER_H

#include <QObject>
#include <QScriptEngine>
#include "LogLevel.h"

/// Class for running status scripts. Uses QtScriptEngine for script
/// evaluation.
class ScriptRunner : public QObject
{
  Q_OBJECT

protected:
  QScriptEngine *m_scriptEngine;

public:
  /// Constructor.
  ///
  /// \parent[in] parent Parent of this object.
  explicit ScriptRunner(QObject *parent = 0);

  /// Destructor.
  ~ScriptRunner();

protected:
  /// Creates the script engine.
  void createScriptEngine();

  /// Adds the Logger object to the script engine.
  void addLogger();

  /// Adds the Color object to the script engine.
  void addColor();

  /// Adds the MockSerialPort object to the script engine.
  void addMockSerialPort();

  /// Adds the SerialPort object to the script engine.
  void addSerialPort();

  /// Adds the MockHttpPort object to the script engine.
  void addMockHttpPort();

  /// Adds the HttpPort object to the script engine.
  void addHttpPort();

  /// Adds the MockJenkinsManager object to the script engine.
  void addMockJenkinsManager();

  /// Adds the JenkinsManager object to the script engine.
  void addJenkinsManager();

  /// Adds the SerialLed object to the script engine.
  void addSerialLed();

signals:
  /// Signal to indicate that the log should be cleared.
  void clearLog();

  /// Signal to indicate that the given text should be appended to the log.
  ///
  /// \param[in] logLevel Log level.
  /// \param[in] text Text to append to log.
  void appendLog(LogLevel::Enum logLevel, const QString &text);

public slots:
  /// Evaluates the given script. Errors are emitted using the appendLog()
  /// signal.
  ///
  /// \param[in] script Script to evaluate.
  /// \param[in] fileName Name of script file, used in error reporting.
  void runScript(const QString &script, const QString &fileName);
};

#endif
