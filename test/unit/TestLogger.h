#ifndef VST_TESTLOGGER_H
#define VST_TESTLOGGER_H

#include <QtTest/QtTest>
#include "../../src/LogLevel.h"
#include "../../src/Logger.h"

namespace unittest
{

/// Unit tests for Logger class.
class TestLogger : public QObject
{
  Q_OBJECT

private slots:
  /// Tests the level function of the logger.
  void level();

  /// Tests the clear function of the logger.
  void clear();

  /// Tests the log function of the logger.
  void log();

  /// Tests the logError function of the logger.
  void logError();

  /// Tests the logWarning function of the logger.
  void logWarning();

  /// Tests the logInfo function of the logger.
  void logInfo();

  /// Tests the logDebug function of the logger.
  void logDebug();
};

// Dummy class for testing of Logger, makes internals accessible.
class DummyLogger : public Logger
{
  Q_OBJECT

public:
  DummyLogger(QObject *parent = nullptr)
    : Logger(parent)
  {
  }

  ~DummyLogger()
  {
  }

  // make m_logLevel accessible
  LogLevel::Enum &refLogLevel()
  {
    return m_logLevel;
  }
};

// Dummy class for testing the signals of the Logger class.
class DummyLog : public QObject
{
  Q_OBJECT

public:
  LogLevel::Enum m_logLevel;
  QString m_logText;
  bool m_clearCalled;

  explicit DummyLog(QObject *parent = nullptr)
    : QObject(parent)
    , m_logLevel(LogLevel::Info)
    , m_logText()
    , m_clearCalled(false)
  {
  }

  virtual ~DummyLog()
  {
  }

public slots:
  void clearLog()
  {
    m_clearCalled = true;
  }

  void appendLog(LogLevel::Enum logLevel, const QString &text)
  {
    m_logLevel = logLevel;
    m_logText = text;
  }
};

} // unittest

#endif

