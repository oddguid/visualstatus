#include "TestLogger.h"
#include <QString>
#include <QList>

// redefine private to public to get access to the member variables of the
// Logger class
#define private public
#include "../../src/Logger.h"
#undef private

using namespace script;

namespace unittest
{

void TestLogger::level()
{
  Logger logger;

  // default level should be info
  QVERIFY(logger.m_logLevel == LogLevel::Info);

  // error
  logger.level("error");
  QCOMPARE(logger.m_logLevel, LogLevel::Error);

  // info
  logger.level(" Info ");
  QCOMPARE(logger.m_logLevel, LogLevel::Info);

  // debug
  logger.level(" DEBUG");
  QCOMPARE(logger.m_logLevel, LogLevel::Debug);

  // unknown value
  logger.level("verbose");
  QCOMPARE(logger.m_logLevel, LogLevel::Info);
}

void TestLogger::clear()
{
  Logger logger;
  DummyLog log;

  log.connect(&logger, SIGNAL(clearLog()), SLOT(clearLog()));
  log.connect(&logger, SIGNAL(appendLog(LogLevel::Enum, const QString &)),
              SLOT(appendLog(LogLevel::Enum, const QString &)));

  QVERIFY(log.m_clearCalled == false);

  // call clear
  logger.clear();

  QVERIFY(log.m_clearCalled == true);
}

void TestLogger::log()
{
  QString textExp = "Test message";
  LogLevel::Enum levelExp = LogLevel::Info;

  Logger logger;
  DummyLog log;

  log.connect(&logger, SIGNAL(clearLog()), SLOT(clearLog()));
  log.connect(&logger, SIGNAL(appendLog(LogLevel::Enum, const QString &)),
              SLOT(appendLog(LogLevel::Enum, const QString &)));

  QVERIFY(log.m_clearCalled == false);

  // set log level
  logger.m_logLevel = LogLevel::Error;

  // log
  logger.log(textExp);

  // log should be empty
  QVERIFY(log.m_logText.isEmpty() == true);

  // increase log level
  logger.m_logLevel = LogLevel::Info;

  // log
  logger.log(textExp);

  // look for entry in dummy log
  QCOMPARE(log.m_logLevel, levelExp);
  QCOMPARE(log.m_logText, textExp);
}

void TestLogger::logError()
{
  QString textExp = "Test message";
  LogLevel::Enum levelExp = LogLevel::Error;

  Logger logger;
  DummyLog log;

  log.connect(&logger, SIGNAL(clearLog()), SLOT(clearLog()));
  log.connect(&logger, SIGNAL(appendLog(LogLevel::Enum, const QString &)),
              SLOT(appendLog(LogLevel::Enum, const QString &)));

  QVERIFY(log.m_clearCalled == false);

  // log error
  logger.logError(textExp);

  // look for entry in dummy log
  QCOMPARE(log.m_logLevel, levelExp);
  QCOMPARE(log.m_logText, textExp);
}

void TestLogger::logWarning()
{
  QString textExp = "Test message";
  LogLevel::Enum levelExp = LogLevel::Warning;

  Logger logger;
  DummyLog log;

  log.connect(&logger, SIGNAL(clearLog()), SLOT(clearLog()));
  log.connect(&logger, SIGNAL(appendLog(LogLevel::Enum, const QString &)),
              SLOT(appendLog(LogLevel::Enum, const QString &)));

  QVERIFY(log.m_clearCalled == false);

  // set log level
  logger.m_logLevel = LogLevel::Error;

  // log warning
  logger.logWarning(textExp);

  // log should be empty
  QVERIFY(log.m_logText.isEmpty() == true);

  // increase log level
  logger.m_logLevel = LogLevel::Warning;

  // log warning
  logger.logWarning(textExp);

  // look for entry in dummy log
  QCOMPARE(log.m_logLevel, levelExp);
  QCOMPARE(log.m_logText, textExp);
}

void TestLogger::logInfo()
{
  QString textExp = "Test message";
  LogLevel::Enum levelExp = LogLevel::Info;

  Logger logger;
  DummyLog log;

  log.connect(&logger, SIGNAL(clearLog()), SLOT(clearLog()));
  log.connect(&logger, SIGNAL(appendLog(LogLevel::Enum, const QString &)),
              SLOT(appendLog(LogLevel::Enum, const QString &)));

  QVERIFY(log.m_clearCalled == false);

  // set log level
  logger.m_logLevel = LogLevel::Error;

  // log info
  logger.logInfo(textExp);

  // log should be empty
  QVERIFY(log.m_logText.isEmpty() == true);

  // increase log level
  logger.m_logLevel = LogLevel::Info;

  // log info
  logger.logInfo(textExp);

  // look for entry in dummy log
  QCOMPARE(log.m_logLevel, levelExp);
  QCOMPARE(log.m_logText, textExp);
}

void TestLogger::logDebug()
{
  QString textExp = "Test message";
  LogLevel::Enum levelExp = LogLevel::Debug;

  Logger logger;
  DummyLog log;

  log.connect(&logger, SIGNAL(clearLog()), SLOT(clearLog()));
  log.connect(&logger, SIGNAL(appendLog(LogLevel::Enum, const QString &)),
              SLOT(appendLog(LogLevel::Enum, const QString &)));

  QVERIFY(log.m_clearCalled == false);

  // set log level
  logger.m_logLevel = LogLevel::Error;

  // log debug
  logger.logDebug(textExp);

  // log should be empty
  QVERIFY(log.m_logText.isEmpty() == true);

  // increase log level
  logger.m_logLevel = LogLevel::Debug;

  // log debug
  logger.logDebug(textExp);

  // look for entry in dummy log
  QCOMPARE(log.m_logLevel, levelExp);
  QCOMPARE(log.m_logText, textExp);
}

} // unittest

QTEST_MAIN(unittest::TestLogger)
