#include "TestSerialLed.h"

namespace unittest
{

void TestSerialLed::defaultConstructor()
{
  SerialLed led;

  QVERIFY(led.error().isEmpty() == true);
}

void TestSerialLed::setColor()
{
  unsigned char ledNum = 255;
  unsigned char ledR = 0;
  unsigned char ledG = 128;
  unsigned char ledB = 255;
  QString expectedData("w255-000128255-000128255\012");

  SerialLed led;
  DummySerialPort port;
  led.setSerialPort(&port);

  Color ledColor(ledR, ledG, ledB);

  // set solid color
  bool ok = led.setColor(ledNum, ledColor);

  QCOMPARE(ok, true);
  QCOMPARE(port.data(), expectedData);
}

void TestSerialLed::setToggledColor()
{
  unsigned char ledNum = 255;
  unsigned char ledR1 = 0;
  unsigned char ledG1 = 128;
  unsigned char ledB1 = 255;
  unsigned char ledR2 = 128;
  unsigned char ledG2 = 255;
  unsigned char ledB2 = 0;
  QString expectedData("w255-000128255-128255000\012");

  SerialLed led;
  DummySerialPort port;
  led.setSerialPort(&port);

  Color ledColor1(ledR1, ledG1, ledB1);
  Color ledColor2(ledR2, ledG2, ledB2);

  // set toggled color
  bool ok = led.setToggledColor(ledNum, ledColor1, ledColor2);

  QCOMPARE(ok, true);
  QCOMPARE(port.data(), expectedData);
}

void TestSerialLed::setToggleDelay()
{
  unsigned short delay = 250;
  QString expectedData("d00250\012");

  SerialLed led;
  DummySerialPort port;
  led.setSerialPort(&port);

  // set delay
  bool ok = led.setToggleDelay(delay);

  QCOMPARE(ok, true);
  QCOMPARE(port.data(), expectedData);
}

void TestSerialLed::clear()
{
  unsigned char ledNum = 64;
  QString expectedData("w064-000000000-000000000\012");

  SerialLed led;
  DummySerialPort port;
  led.setSerialPort(&port);

  // clear color
  bool ok = led.clear(ledNum);

  QCOMPARE(ok, true);
  QCOMPARE(port.data(), expectedData);
}

void TestSerialLed::clearAll()
{
  QString expectedData("c\012");

  SerialLed led;
  DummySerialPort port;
  led.setSerialPort(&port);

  // clear all colors
  bool ok = led.clearAll();

  QCOMPARE(ok, true);
  QCOMPARE(port.data(), expectedData);
}

void TestSerialLed::show()
{
  QString expectedDataOn("m1\012");
  QString expectedDataOff("m0\012");

  SerialLed led;
  DummySerialPort port;
  led.setSerialPort(&port);

  // set on
  bool ok = led.show(true);

  QCOMPARE(ok, true);
  QCOMPARE(port.data(), expectedDataOn);

  // set off
  ok = led.show(false);

  QCOMPARE(ok, true);
  QCOMPARE(port.data(), expectedDataOff);
}

} // unittest

QTEST_MAIN(unittest::TestSerialLed)
