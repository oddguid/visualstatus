#ifndef VST_MAINCONSOLE_H
#define VST_MAINCONSOLE_H

#include <QObject>
#include <QStringList>
#include <QTextStream>
#include "LogLevel.h"

class ScriptRunner;

/// Class for the console version of the application. Uses commandline
/// arguments as input and runs the given script. Logging is output to stdout.
class MainConsole : public QObject
{
  Q_OBJECT

protected:
  ScriptRunner *m_scriptRunner;
  QTextStream m_log;
  QString m_scriptFileName;

public:
  /// Constructor.
  ///
  /// \param[in] parent Parent of this object.
  explicit MainConsole(QObject *parent = nullptr);

  /// Destructor.
  virtual ~MainConsole();

  /// Prepares the script based on the given arguments. The argument list must
  /// contain the file name of the script to run.
  ///
  /// \param[in] arguments List with arguments to use when running script.
  /// \return True if successful, false on error.
  bool prepareScript(const QStringList &arguments);

protected:
  /// Creates the ScriptRunner object.
  void createScriptRunner();

signals:
  /// Signal to indicate that the application should exit.
  void exit();

public slots:
  /// Writes the given log text to stdout.
  ///
  /// \param[in] logLevel Log level.
  /// \param[in] text Text to write to stdout.
  void log(LogLevel::Enum logLevel, const QString &text);

  /// Runs the prepared script.
  void runScript();
};

#endif
