#include "TestBaseSerialObject.h"

namespace unittest
{

void TestBaseSerialObject::defaultConstructor()
{
  BaseSerialObject object;

  QVERIFY(object.m_error.isEmpty() == true);
  QVERIFY(object.m_serialPort == NULL);
}

void TestBaseSerialObject::setSerialPort()
{
  BaseSerialObject object;
  DummySerialPort port;

  // set error on serial port for verification
  QString errorText = "test error";
  port.setError(errorText);

  QVERIFY(object.m_serialPort == NULL);

  object.setSerialPort(&port);

  QVERIFY(object.m_serialPort == &port);
  QCOMPARE(object.m_serialPort->error(), errorText);
}

void TestBaseSerialObject::error()
{
  BaseSerialObject object;
  QString errorText = "error text";
  object.m_error = errorText;

  QCOMPARE(object.error(), errorText);
}

void TestBaseSerialObject::writeNoSerialPort()
{
  BaseSerialObject object;
  QString expectedError = "No serial port set";

  // should return false since no serial port is set
  bool ok = object.write(QString());

  QCOMPARE(ok, false);
  QCOMPARE(object.error(), expectedError);
}

void TestBaseSerialObject::writeSerialPortError()
{
  BaseSerialObject object;
  DummySerialPort port;

  // set serial port to return error
  QString errorText = "Write error";
  port.setError(errorText);
  port.setWriteReturnValue(false);

  object.setSerialPort(&port);

  bool ok = object.write(QString());

  QCOMPARE(ok, false);
  QCOMPARE(object.error(), errorText);
}

void TestBaseSerialObject::write()
{
  BaseSerialObject object;
  DummySerialPort port;
  QString data = "data";

  // set serial port, will return success
  object.setSerialPort(&port);

  bool ok = object.write(data);

  QCOMPARE(ok, true);
  QVERIFY(object.error().isEmpty() == true);

  // verify "written" data
  DummySerialPort *objectPort =
      static_cast<DummySerialPort *>(object.m_serialPort);

  QCOMPARE(objectPort->data(), data);
}

void TestBaseSerialObject::writeRawNoSerialPort()
{
  BaseSerialObject object;
  QString expectedError = "No serial port set";

  // should return false since no serial port is set
  bool ok = object.writeRaw(QByteArray());

  QCOMPARE(ok, false);
  QCOMPARE(object.error(), expectedError);
}

void TestBaseSerialObject::writeRawSerialPortError()
{
  BaseSerialObject object;
  DummySerialPort port;

  // set serial port to return error
  QString errorText = "Write error";
  port.setError(errorText);
  port.setWriteReturnValue(false);

  object.setSerialPort(&port);

  bool ok = object.writeRaw(QByteArray());

  QCOMPARE(ok, false);
  QCOMPARE(object.error(), errorText);
}

void TestBaseSerialObject::writeRaw()
{
  BaseSerialObject object;
  DummySerialPort port;
  QByteArray data = "data";

  // set serial port, will return success
  object.setSerialPort(&port);

  bool ok = object.writeRaw(data);

  QCOMPARE(ok, true);
  QVERIFY(object.error().isEmpty() == true);

  // verify "written" data
  DummySerialPort *objectPort =
      static_cast<DummySerialPort *>(object.m_serialPort);

  QCOMPARE(objectPort->dataRaw(), data);
}

} // unittest

QTEST_MAIN(unittest::TestBaseSerialObject)
