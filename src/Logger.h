#ifndef VST_LOGGER_H
#define VST_LOGGER_H

#include <QObject>
#include <QString>
#include "LogLevel.h"

/// Log class for use in scripting. The script engine will make this a global
/// object in the scripting environment.
class Logger : public QObject
{
  Q_OBJECT

protected:
  LogLevel::Enum m_logLevel;

public:
  /// Constructor.
  ///
  /// \param[in] parent Parent of this object.
  explicit Logger(QObject *parent = nullptr);
  
  /// Destructor.
  virtual ~Logger();

  /// Sets the log level. Log messages above this level will be ignored.
  ///
  /// \param[in] logLevel String indicating the log level. Allowed values are
  /// Error, Warning, Info, Debug and Debug2. The default log level is Error.
  Q_INVOKABLE void level(const QString &logLevel);

  /// Clears to log.
  Q_INVOKABLE void clear();

  /// Appends text to the log by emitting the appendLog() signal using log
  /// level Info.
  ///
  /// \param[in] text Text to log.
  Q_INVOKABLE void log(const QString &text);

  /// Appends error text to the log by emitting the appendLog() signal using
  /// log level Error.
  ///
  /// \param[in] text Text to log.
  Q_INVOKABLE void logError(const QString &text);

  /// Appends warning text to the log by emitting the appendLog() signal using
  /// log level Warning.
  ///
  /// \param[in] text Text to log.
  Q_INVOKABLE void logWarning(const QString &text);

  /// Appends text to the log by emitting the appendLog() signal using log
  /// level Info.
  ///
  /// \param[in] text Text to log.
  Q_INVOKABLE void logInfo(const QString &text);

  /// Appends debug text to the log by emitting the appendLog() signal using
  /// log level Debug.
  ///
  /// \param[in] text Text to log
  Q_INVOKABLE void logDebug(const QString &text);

signals:
  /// Signal to indicate that the log should be cleared.
  void clearLog();

  /// Signal to indicate that the given text should be appended to the log.
  ///
  /// \param[in] logLevel Log level.
  /// \param[in] text Text to append to log.
  void appendLog(LogLevel::Enum logLevel, const QString &text);
};

#endif
