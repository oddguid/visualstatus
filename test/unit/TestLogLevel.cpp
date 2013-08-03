#include "TestLogLevel.h"
#include "../../src/LogLevel.h"

namespace unittest
{

void TestLogLevel::toString()
{
  QString errorExp("error");
  QString warningExp("warning");
  QString infoExp("info");
  QString debugExp("debug");

  // error
  LogLevel::Enum level(LogLevel::Error);
  QCOMPARE(LogLevel::toString(level), errorExp);

  // warning
  level = LogLevel::Warning;
  QCOMPARE(LogLevel::toString(level), warningExp);

  // info
  level = LogLevel::Info;
  QCOMPARE(LogLevel::toString(level), infoExp);

  // debug
  level = LogLevel::Debug;
  QCOMPARE(LogLevel::toString(level), debugExp);

  // illegal value, should return info
  level = static_cast<LogLevel::Enum>(100);
  QCOMPARE(LogLevel::toString(level), infoExp);
}

void TestLogLevel::fromString()
{
  LogLevel::Enum errorExp(LogLevel::Error);
  LogLevel::Enum warningExp(LogLevel::Warning);
  LogLevel::Enum infoExp(LogLevel::Info);
  LogLevel::Enum debugExp(LogLevel::Debug);

  // error
  QCOMPARE(LogLevel::fromString("ERROR"), errorExp);
  QCOMPARE(LogLevel::fromString(" ErrOr "), errorExp);

  // warning
  QCOMPARE(LogLevel::fromString("warning"), warningExp);
  QCOMPARE(LogLevel::fromString("warNing "), warningExp);

  // info
  QCOMPARE(LogLevel::fromString("info"), infoExp);
  QCOMPARE(LogLevel::fromString(" InFo"), infoExp);

  // debug
  QCOMPARE(LogLevel::fromString("DEBUG"), debugExp);
  QCOMPARE(LogLevel::fromString(" debug "), debugExp);

  // unknow value, should return log level Info
  QCOMPARE(LogLevel::fromString("unknown"), infoExp);
}

} // unittest

QTEST_MAIN(unittest::TestLogLevel)
