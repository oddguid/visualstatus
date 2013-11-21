#include "TestBaseHttpPort.h"

namespace unittest
{

void TestBaseHttpPort::defaultConstructor()
{
  DummyHttpPort port;

  QVERIFY(port.m_error.isEmpty() == true);
}

void TestBaseHttpPort::error()
{
  DummyHttpPort port;
  QString errorText = "error text";
  port.m_error = errorText;

  QCOMPARE(port.error(), errorText);
}

} // unittest

QTEST_MAIN(unittest::TestBaseHttpPort)
