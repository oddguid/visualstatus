#include "TestMockSerialPort.h"

// redefine private to public to get access to the member variables of the
// MockSerialPort class
#define private public
#include "../../src/MockSerialPort.h"
#undef private

namespace unittest
{

void TestMockSerialPort::defaultConstructor()
{
  MockSerialPort port;

  QCOMPARE(port.m_isOpen, false);
}

void TestMockSerialPort::open()
{
  MockSerialPort port;

  // open port
  QVERIFY(port.open("device", 0, 0) == true);

  QCOMPARE(port.m_isOpen, true);
}

void TestMockSerialPort::isOpen()
{
  MockSerialPort port;

  QVERIFY(port.isOpen() == false);

  port.m_isOpen = true;

  QVERIFY(port.isOpen() == true);
}

void TestMockSerialPort::close()
{
  MockSerialPort port;

  // close a closed port
  port.close();

  QCOMPARE(port.m_isOpen, false);

  port.m_isOpen = true;

  // close an opened port
  port.close();

  QCOMPARE(port.m_isOpen, false);
}

void TestMockSerialPort::setTimeout()
{
  MockSerialPort port;

  QVERIFY(port.setTimeout(100) == true);
}

void TestMockSerialPort::write()
{
  MockSerialPort port;
  DummyLog log;

  connect(&port, SIGNAL(writtenData(QString)),
          &log, SLOT(writtenData(QString)));

  connect(&port, SIGNAL(writtenRawData(QByteArray)),
          &log, SLOT(writtenDataRaw(QByteArray)));

  // write when port is closed
  QVERIFY(port.write("test") == false);
  QVERIFY(log.m_writtenData.isEmpty() == true);
  QVERIFY(log.m_writtenDataRaw.isEmpty() == true);

  // open port and write again
  if (port.open("device", 0, 0))
  {
    QString data = "test again";

    QVERIFY(port.write(data) == true);

    QCOMPARE(log.m_writtenData, data);
    QVERIFY(log.m_writtenDataRaw.isEmpty() == true);
  }
  else
  {
    QFAIL("Cannot open port!");
  }
}

void TestMockSerialPort::writeRaw()
{
  MockSerialPort port;
  DummyLog log;

  connect(&port, SIGNAL(writtenData(QString)),
          &log, SLOT(writtenData(QString)));

  connect(&port, SIGNAL(writtenRawData(QByteArray)),
          &log, SLOT(writtenDataRaw(QByteArray)));

  // write when port is closed
  QVERIFY(port.writeRaw("test") == false);
  QVERIFY(log.m_writtenData.isEmpty() == true);
  QVERIFY(log.m_writtenDataRaw.isEmpty() == true);

  // open port and write again
  if (port.open("device", 0, 0))
  {
    QByteArray data = "test again";

    QVERIFY(port.writeRaw(data) == true);

    QVERIFY(log.m_writtenData.isEmpty() == true);
    QCOMPARE(log.m_writtenDataRaw, data);
  }
  else
  {
    QFAIL("Cannot open port!");
  }
}

} // unittest

QTEST_MAIN(unittest::TestMockSerialPort)
