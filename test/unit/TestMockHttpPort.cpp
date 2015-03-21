#include "TestMockHttpPort.h"

namespace unittest
{

void TestMockHttpPort::defaultConstructor()
{
  DummyHttpPort port;

  QVERIFY(port.refData().isEmpty() == true);
}

void TestMockHttpPort::get()
{
  DummyHttpPort port;
  QString url("http://example.com");

  // get
  QVERIFY(port.get(url) == true);

  QVERIFY(port.refData().isEmpty() == true);
}

void TestMockHttpPort::data()
{
  DummyHttpPort port;
  QString data = "test";

  port.data(data);

  // data
  QCOMPARE(port.data(), data);
}

void TestMockHttpPort::setTimeout()
{
  DummyHttpPort port;
  unsigned short timeout = 123;

  QVERIFY(port.setTimeout(timeout) == true);
}

void TestMockHttpPort::setAuthentication()
{
  DummyHttpPort port;
  QString user = "user";
  QString password = "password";

  QVERIFY(port.setAuthentication(user, password) == true);
}

void TestMockHttpPort::setProxy()
{
  DummyHttpPort port;
  QString proxyUser = "user";
  QString proxyPassword = "password";
  QString proxyHost = "host";
  unsigned short proxyPort = 8080;

  QVERIFY(port.setProxy(proxyUser, proxyPassword,
                        proxyHost, proxyPort) == true);
}

} // unittest

QTEST_MAIN(unittest::TestMockHttpPort)
