#ifndef VST_LOGGER_H
#define VST_LOGGER_H

#include <QObject>
#include <QString>
#include "LogLevel.h"

namespace script
{

/// Log class for use in scripting. The script engine will make this a global
/// object in the scripting environment.
class Logger : public QObject
{
  Q_OBJECT

private:
  LogLevel::Enum m_logLevel;

public:
  /// Constructor.
  ///
  /// \param[in] parent Parent of this object.
  explicit Logger(QObject *parent = 0);
  
  /// Destructor.
  virtual ~Logger();

signals:
  /// Signal to indicate that the log should be cleared.
  void clearLog();

  /// Signal to indicate that the given text should be appended to the log.
  ///
  /// \param[in] logLevel Log level.
  /// \param[in] text Text to append to log.
  void appendLog(LogLevel::Enum logLevel, const QString &text);

public slots:
  /// Sets the log level. Log messages above this level will be ignored.
  ///
  /// \param[in] logLevel String indicating the log level. Allowed values are
  /// Error, Warning, Info, Debug and Debug2. The default log level is Error.
  void level(const QString &logLevel);

  /// Clears to log.
  void clear();

  /// Appends text to the log by emitting the appendLog() signal using log
  /// level Info.
  ///
  /// \param[in] text Text to log.
  void log(const QString &text);

  /// Appends error text to the log by emitting the appendLog() signal using
  /// log level Error.
  ///
  /// \param[in] text Text to log.
  void logError(const QString &text);

  /// Appends warning text to the log by emitting the appendLog() signal using
  /// log level Warning.
  ///
  /// \param[in] text Text to log.
  void logWarning(const QString &text);

  /// Appends text to the log by emitting the appendLog() signal using log
  /// level Info.
  ///
  /// \param[in] text Text to log.
  void logInfo(const QString &text);

  /// Appends debug text to the log by emitting the appendLog() signal using
  /// log level Debug.
  ///
  /// \param[in] text Text to log
  void logDebug(const QString &text);
};

} // script

#endif
