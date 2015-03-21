#include "TestMockSerialPort.h"

namespace unittest
{

void TestMockSerialPort::defaultConstructor()
{
  DummySerialPort port;

  QCOMPARE(port.refIsOpen(), false);
}

void TestMockSerialPort::open()
{
  DummySerialPort port;

  // open port
  QVERIFY(port.open("device", 0, 0) == true);

  QCOMPARE(port.refIsOpen(), true);
}

void TestMockSerialPort::isOpen()
{
  DummySerialPort port;

  QVERIFY(port.isOpen() == false);

  port.refIsOpen() = true;

  QVERIFY(port.isOpen() == true);
}

void TestMockSerialPort::close()
{
  DummySerialPort port;

  // close a closed port
  port.close();

  QCOMPARE(port.refIsOpen(), false);

  port.refIsOpen() = true;

  // close an opened port
  port.close();

  QCOMPARE(port.refIsOpen(), false);
}

void TestMockSerialPort::setTimeout()
{
  DummySerialPort port;

  QVERIFY(port.setTimeout(100) == true);
}

void TestMockSerialPort::write()
{
  DummySerialPort port;
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
  DummySerialPort port;
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
