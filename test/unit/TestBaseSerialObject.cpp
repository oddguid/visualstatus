#include "TestBaseSerialObject.h"

namespace unittest
{

void TestBaseSerialObject::defaultConstructor()
{
  DummySerialObject object;

  QVERIFY(object.refError().isEmpty() == true);
  QVERIFY(object.refSerialPort() == nullptr);
}

void TestBaseSerialObject::setSerialPort()
{
  DummySerialObject object;
  DummySerialPort port;

  // set error on serial port for verification
  QString errorText = "test error";
  port.setError(errorText);

  QVERIFY(object.refSerialPort() == nullptr);

  object.setSerialPort(&port);

  QVERIFY(object.refSerialPort() == &port);
  QCOMPARE(object.refSerialPort()->error(), errorText);
}

void TestBaseSerialObject::error()
{
  DummySerialObject object;
  QString errorText = "error text";
  object.refError() = errorText;

  QCOMPARE(object.error(), errorText);
}

void TestBaseSerialObject::writeNoSerialPort()
{
  DummySerialObject object;
  QString expectedError = "No serial port set";

  // should return false since no serial port is set
  bool ok = object.write(QString());

  QCOMPARE(ok, false);
  QCOMPARE(object.error(), expectedError);
}

void TestBaseSerialObject::writeSerialPortError()
{
  DummySerialObject object;
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
  DummySerialObject object;
  DummySerialPort port;
  QString data = "data";

  // set serial port, will return success
  object.setSerialPort(&port);

  bool ok = object.write(data);

  QCOMPARE(ok, true);
  QVERIFY(object.error().isEmpty() == true);

  // verify "written" data
  DummySerialPort *objectPort =
      static_cast<DummySerialPort *>(object.refSerialPort());

  QCOMPARE(objectPort->data(), data);
}

void TestBaseSerialObject::writeRawNoSerialPort()
{
  DummySerialObject object;
  QString expectedError = "No serial port set";

  // should return false since no serial port is set
  bool ok = object.writeRaw(QByteArray());

  QCOMPARE(ok, false);
  QCOMPARE(object.error(), expectedError);
}

void TestBaseSerialObject::writeRawSerialPortError()
{
  DummySerialObject object;
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
  DummySerialObject object;
  DummySerialPort port;
  QByteArray data = "data";

  // set serial port, will return success
  object.setSerialPort(&port);

  bool ok = object.writeRaw(data);

  QCOMPARE(ok, true);
  QVERIFY(object.error().isEmpty() == true);

  // verify "written" data
  DummySerialPort *objectPort =
      static_cast<DummySerialPort *>(object.refSerialPort());

  QCOMPARE(objectPort->dataRaw(), data);
}

} // unittest

QTEST_MAIN(unittest::TestBaseSerialObject)
