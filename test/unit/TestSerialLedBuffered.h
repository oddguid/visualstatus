#ifndef VST_TESTSERIALLEDBUFFERED_H
#define VST_TESTSERIALLEDBUFFERED_H

#include <QtTest/QtTest>
#include "../../src/BaseSerialPort.h"

namespace unittest
{

/// Unit tests for SerialLedBuffered class.
class TestSerialLedBuffered : public QObject
{
  Q_OBJECT

private slots:
  /// Tests the default constructor.
  void defaultConstructor();

  /// Tests the initializeBuffer function.
  void initializeBuffer();

  /// Tests the numColors function.
  void numColors();

  /// Tests the setColor function.
  void setColor();

  /// Tests the setChecksum function.
  void setChecksum();

  /// Tests the clear function.
  void clear();

  /// Tests the clearAll function.
  void clearAll();

  /// Tests the update function.
  void update();
};

// Dummy class for testing of SerialLedBuffered, implements the pure virtual
// functions of BaseSerialPort.
class DummySerialPort : public BaseSerialPort
{
  Q_OBJECT

protected:
  QByteArray m_dataRaw;

public:  
  DummySerialPort(QObject *parent = 0)
    : BaseSerialPort(parent)
    , m_dataRaw()
  {
  }

  ~DummySerialPort()
  {
  }

  virtual bool open(const QString &deviceName,
                    unsigned int baudrate,
                    unsigned short timeoutSecs)
  {
    Q_UNUSED(deviceName)
    Q_UNUSED(baudrate)
    Q_UNUSED(timeoutSecs)

    return true;
  }

  virtual bool isOpen()
  {
    return true;
  }

  virtual bool close()
  {
    return true;
  }

  virtual bool setTimeout(unsigned short timeoutSecs)
  {
    Q_UNUSED(timeoutSecs)

    return true;
  }

  virtual bool write(const QString &data)
  {
    Q_UNUSED(data)

    // SerialLedBuffered does not use write, always return error
    return false;
  }

  virtual bool writeRaw(const QByteArray &data)
  {
    m_dataRaw = data;

    return true;
  }

  QByteArray dataRaw() const
  {
    return m_dataRaw;
  }
};

} // unittest

#endif
