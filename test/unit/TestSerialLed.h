#ifndef VST_TESTSERIALLED_H
#define VST_TESTSERIALLED_H

#include <QtTest/QtTest>
#include "../../src/BaseSerialPort.h"
#include "../../src/SerialLed.h"

namespace unittest
{

/// Unit tests for SerialLed class.
class TestSerialLed : public QObject
{
  Q_OBJECT

private slots:
  /// Tests the default constructor.
  void defaultConstructor();

  /// Tests the setSolid function.
  void setSolid();

  /// Tests the setToggled function.
  void setToggled();

  /// Tests the setToggleDelay function.
  void setToggleDelay();

  /// Tests the clear function.
  void clear();

  /// Tests the clearAll function.
  void clearAll();
};

// Dummy class for testing of SerialLed, implements the pure virtual
// functions of BaseSerialPort.
class DummySerialPort : public BaseSerialPort
{
  Q_OBJECT

protected:
  QString m_data;

public:  
  DummySerialPort(QObject *parent = 0)
    : BaseSerialPort(parent)
    , m_data()
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
    m_data = data;

    return true;
  }

  QString data() const
  {
    return m_data;
  }
};

} // unittest

#endif
