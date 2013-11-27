#include "TestSerialLed.h"

namespace unittest
{

void TestSerialLed::defaultConstructor()
{
  SerialLed led;

  QVERIFY(led.error().isEmpty() == true);
}

void TestSerialLed::setSolid()
{
  unsigned char ledNum = 255;
  unsigned char ledR = 0;
  unsigned char ledG = 128;
  unsigned char ledB = 255;
  QString expectedData("c255-000128255\n");

  SerialLed led;
  DummySerialPort port;
  led.setSerialPort(&port);

  Color ledColor;
  ledColor.r(ledR);
  ledColor.g(ledG);
  ledColor.b(ledB);

  // set solid color
  bool ok = led.setSolid(ledNum, ledColor);

  QCOMPARE(ok, true);
  QCOMPARE(port.data(), expectedData);
}

void TestSerialLed::setSawtooth()
{
  unsigned char ledNum = 255;
  unsigned char ledR1 = 0;
  unsigned char ledG1 = 128;
  unsigned char ledB1 = 255;
  unsigned char ledR2 = 128;
  unsigned char ledG2 = 255;
  unsigned char ledB2 = 0;
  unsigned short riseTime = 500;
  unsigned short fallTime = 1234;

  QString expectedData("s255-000128255-128255000-00500-01234\n");

  SerialLed led;
  DummySerialPort port;
  led.setSerialPort(&port);

  Color ledColor1;
  ledColor1.r(ledR1);
  ledColor1.g(ledG1);
  ledColor1.b(ledB1);

  Color ledColor2;
  ledColor2.r(ledR2);
  ledColor2.g(ledG2);
  ledColor2.b(ledB2);

  // set sawtooth color
  bool ok = led.setSawtooth(ledNum, ledColor1, ledColor2, riseTime, fallTime);

  QCOMPARE(ok, true);
  QCOMPARE(port.data(), expectedData);
}

} // unittest

QTEST_MAIN(unittest::TestSerialLed)
