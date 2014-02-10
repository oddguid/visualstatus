#include "TestSerialLedBuffered.h"

// redefine protected to public to get access to the member variables of the
// SerialLedBuffered class
#define protected public
#include "../../src/SerialLedBuffered.h"
#undef protected

namespace unittest
{

void TestSerialLedBuffered::defaultConstructor()
{
  SerialLedBuffered led;

  QVERIFY(led.error().isEmpty() == true);
}

void TestSerialLedBuffered::initializeBuffer()
{
  SerialLedBuffered led;
  int numLeds = 1;
  int bufferSize = numLeds * 3 + 4;

  // expand the internal buffer and set all bytes to 0
  led.m_numLeds = numLeds;
  led.m_ledBuffer.fill(0, bufferSize);

  // initialize buffer
  led.initializeBuffer();

  // byte should be 0x06
  QCOMPARE(led.m_ledBuffer.at(0), static_cast<char>(0x06));

  // byte should be 0x85
  QCOMPARE(led.m_ledBuffer.at(1), static_cast<char>(0x85));

  // byte should numLeds * 3
  QCOMPARE(led.m_ledBuffer.at(2), static_cast<char>(3));

  // other bytes should be 0
  for (int i = 3; i < led.m_ledBuffer.size(); ++i)
  {
    QCOMPARE(led.m_ledBuffer.at(i), static_cast<char>(0));
  }
}

void TestSerialLedBuffered::numColors()
{
  SerialLedBuffered led;
  int numLeds = 85;
  int bufferSize = numLeds * 3 + 4;

  // should start with 0 LEDs
  QCOMPARE(led.numLeds(), static_cast<quint8>(0));
  QCOMPARE(led.m_numLeds, static_cast<quint8>(0));

  // set number of LEDs
  led.setNumLeds(numLeds);

  QCOMPARE(led.numLeds(), static_cast<quint8>(numLeds));

  // check internal values
  QCOMPARE(led.m_numLeds, static_cast<quint8>(numLeds));
  QCOMPARE(led.m_ledBuffer.size(), bufferSize);

  // set number of LEDs too large, should default to 85
  led.setNumLeds(123);

  QCOMPARE(led.numLeds(), static_cast<quint8>(numLeds));

  // check internal values
  QCOMPARE(led.m_numLeds, static_cast<quint8>(numLeds));
  QCOMPARE(led.m_ledBuffer.size(), bufferSize);
}

void TestSerialLedBuffered::setColor()
{
  SerialLedBuffered led;

  // set number of leds
  led.setNumLeds(3);

  // set colors
  Color color1(1, 2, 3);
  Color color2(253, 254, 255);
  Color color3(127, 128, 129);

  bool ok = led.setColor(0, color1);
  QCOMPARE(ok, true);

  ok = led.setColor(1, color2);
  QCOMPARE(ok, true);

  led.setColor(2, color3);
  QCOMPARE(ok, true);

  // check internal values
  QCOMPARE(led.m_ledBuffer.at(3), static_cast<char>(1));
  QCOMPARE(led.m_ledBuffer.at(4), static_cast<char>(2));
  QCOMPARE(led.m_ledBuffer.at(5), static_cast<char>(3));
  QCOMPARE(led.m_ledBuffer.at(6), static_cast<char>(253));
  QCOMPARE(led.m_ledBuffer.at(7), static_cast<char>(254));
  QCOMPARE(led.m_ledBuffer.at(8), static_cast<char>(255));
  QCOMPARE(led.m_ledBuffer.at(9), static_cast<char>(127));
  QCOMPARE(led.m_ledBuffer.at(10), static_cast<char>(128));
  QCOMPARE(led.m_ledBuffer.at(11), static_cast<char>(129));
}

void TestSerialLedBuffered::clear()
{
  SerialLedBuffered led;

  // set number of leds
  led.setNumLeds(3);

  // set colors
  Color color1(1, 2, 3);
  Color color2(253, 254, 255);
  Color color3(127, 128, 129);

  led.setColor(0, color1);
  led.setColor(1, color2);
  led.setColor(2, color3);

  // clear one led
  bool ok = led.clear(1);
  QCOMPARE(ok, true);

  // check internal values
  QCOMPARE(led.m_ledBuffer.at(3), static_cast<char>(1));
  QCOMPARE(led.m_ledBuffer.at(4), static_cast<char>(2));
  QCOMPARE(led.m_ledBuffer.at(5), static_cast<char>(3));
  QCOMPARE(led.m_ledBuffer.at(6), static_cast<char>(0));
  QCOMPARE(led.m_ledBuffer.at(7), static_cast<char>(0));
  QCOMPARE(led.m_ledBuffer.at(8), static_cast<char>(0));
  QCOMPARE(led.m_ledBuffer.at(9), static_cast<char>(127));
  QCOMPARE(led.m_ledBuffer.at(10), static_cast<char>(128));
  QCOMPARE(led.m_ledBuffer.at(11), static_cast<char>(129));
}

void TestSerialLedBuffered::clearAll()
{
  SerialLedBuffered led;

  // set number of leds
  led.setNumLeds(3);

  // set colors
  Color color1(1, 2, 3);
  Color color2(253, 254, 255);
  Color color3(127, 128, 129);

  led.setColor(0, color1);
  led.setColor(1, color2);
  led.setColor(2, color3);

  // clear all leds
  bool ok = led.clearAll();
  QCOMPARE(ok, true);

  // check internal values
  for (int i = 3; i < led.m_ledBuffer.size() - 1; ++i)
  {
    QCOMPARE(led.m_ledBuffer.at(i), static_cast<char>(0));
  }
}

void TestSerialLedBuffered::setChecksum()
{
  SerialLedBuffered led;

  // checksum should not be set yet
  QCOMPARE(led.m_ledBuffer.at(led.m_ledBuffer.size() - 1),
           static_cast<char>(0));

  // set checksum
  led.setChecksum();

  // expected checksum is based on numColors only
  char expectedCS = 0;

  QCOMPARE(led.m_ledBuffer.at(led.m_ledBuffer.size() - 1), expectedCS);

  // expand buffer
  led.setNumLeds(3);

  // set colors
  Color color1(1, 2, 3);
  Color color2(253, 254, 255);
  Color color3(127, 128, 129);

  led.setColor(0, color1);
  led.setColor(1, color2);
  led.setColor(2, color3);

  // set checksum
  led.setChecksum();

  // expected checksum
  // (3*3) ^ 1 ^ 2 ^ 3 ^ 253 ^ 254 ^ 255 ^ 127 ^ 128 ^ 129
  expectedCS = 139;

  QCOMPARE(led.m_ledBuffer.at(led.m_ledBuffer.size() - 1), expectedCS);
}

void TestSerialLedBuffered::update()
{
  QByteArray expectedData(13, 0);
  expectedData[0] = 0x06;
  expectedData[1] = 0x85;
  expectedData[2] = 9;
  expectedData[3] = 1;
  expectedData[4] = 2;
  expectedData[5] = 3;
  expectedData[6] = 253;
  expectedData[7] = 254;
  expectedData[8] = 255;
  expectedData[9] = 127;
  expectedData[10] = 128;
  expectedData[11] = 129;
  expectedData[12] = 139;

  SerialLedBuffered led(3);
  DummySerialPort port;
  led.setSerialPort(&port);

  // set colors
  Color color1(1, 2, 3);
  Color color2(253, 254, 255);
  Color color3(127, 128, 129);

  led.setColor(0, color1);
  led.setColor(1, color2);
  led.setColor(2, color3);

  // update to serial device
  bool ok = led.update();

  QCOMPARE(ok, true);
  QCOMPARE(port.dataRaw(), expectedData);
}

} // unittest

QTEST_MAIN(unittest::TestSerialLedBuffered)
