#include "TestBaseSerialPort.h"

namespace unittest
{

void TestBaseSerialPort::defaultConstructor()
{
  DummySerialPort port;

  QVERIFY(port.m_error.isEmpty() == true);
}

void TestBaseSerialPort::error()
{
  DummySerialPort port;
  QString errorText = "error text";
  port.m_error = errorText;

  QCOMPARE(port.error(), errorText);
}

} // unittest

QTEST_MAIN(unittest::TestBaseSerialPort)
