#include "TestMockHttpPort.h"

// redefine private to public to get access to the member variables of the
// MockHttpPort class
#define private public
#include "../../src/MockHttpPort.h"
#undef private

namespace unittest
{

void TestMockHttpPort::defaultConstructor()
{
  MockHttpPort port;

  QVERIFY(port.m_data.isEmpty() == true);
}

void TestMockHttpPort::get()
{
  MockHttpPort port;
  QUrl url("http://example.com");

  // get
  QVERIFY(port.get(url) == true);

  QVERIFY(port.m_data.isEmpty() == true);
}

void TestMockHttpPort::data()
{
  MockHttpPort port;
  QString data = "test";

  port.data(data);

  // data
  QCOMPARE(port.data(), data);
}

void TestMockHttpPort::setTimeout()
{
  MockHttpPort port;
  unsigned short timeout = 123;

  QVERIFY(port.setTimeout(timeout) == true);
}

void TestMockHttpPort::setAuthentication()
{
  MockHttpPort port;
  QString user = "user";
  QString password = "password";

  QVERIFY(port.setAuthentication(user, password) == true);
}

void TestMockHttpPort::setProxy()
{
  MockHttpPort port;
  QString proxyUser = "user";
  QString proxyPassword = "password";
  QString proxyHost = "host";
  unsigned short proxyPort = 8080;

  QVERIFY(port.setProxy(proxyUser, proxyPassword,
                        proxyHost, proxyPort) == true);
}

} // unittest

QTEST_MAIN(unittest::TestMockHttpPort)
