#include "TestBaseSerialPort.h"

namespace unittest
{

void TestBaseSerialPort::defaultConstructor()
{
  DummySerialPort port;

  QVERIFY(port.refError().isEmpty() == true);
}

void TestBaseSerialPort::error()
{
  DummySerialPort port;
  QString errorText = "error text";
  port.refError() = errorText;

  QCOMPARE(port.error(), errorText);
}

} // unittest

QTEST_MAIN(unittest::TestBaseSerialPort)
