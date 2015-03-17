#include "TestBaseHttpPort.h"

namespace unittest
{

void TestBaseHttpPort::defaultConstructor()
{
  DummyHttpPort port;

  QVERIFY(port.refError().isEmpty() == true);
}

void TestBaseHttpPort::error()
{
  DummyHttpPort port;
  QString errorText = "error text";
  port.refError() = errorText;

  QCOMPARE(port.error(), errorText);
}

} // unittest

QTEST_MAIN(unittest::TestBaseHttpPort)
