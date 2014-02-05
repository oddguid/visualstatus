#ifndef VST_TESTBASESERIALOBJECT_H
#define VST_TESTBASESERIALOBJECT_H

#include <QtTest/QtTest>
#include "../../src/BaseSerialPort.h"

// redefine protected to public to get access to the member variables of the
// BaseSerialObject class
#define protected public
#include "../../src/BaseSerialObject.h"
#undef protected

namespace unittest
{

/// Unit tests for BaseSerialObject class.
class TestBaseSerialObject : public QObject
{
  Q_OBJECT

private slots:
  /// Tests the default constructor.
  void defaultConstructor();

  /// Tests the setSerialPort function.
  void setSerialPort();

  /// Tests the error function.
  void error();

  /// Tests the write function, no serial port is set.
  void writeNoSerialPort();

  /// Tests the write function, serial port returns error.
  void writeSerialPortError();

  /// Tests the write function, normal operation.
  void write();

  /// Tests the writeRaw function, no serial port is set.
  void writeRawNoSerialPort();

  /// Tests the writeRaw function, serial port returns error.
  void writeRawSerialPortError();

  /// Tests the writeRaw function, normal operation.
  void writeRaw();
};

// Dummy class for testing of BaseSerialObject, implements the pure virtual
// functions of BaseSerialPort.
class DummySerialPort : public BaseSerialPort
{
  Q_OBJECT

protected:
  bool m_writeReturnValue;
  QString m_data;
  QByteArray m_dataRaw;

public:  
  DummySerialPort(QObject *parent = 0)
    : BaseSerialPort(parent)
    , m_writeReturnValue(true)
    , m_data()
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
    m_data = data;

    return m_writeReturnValue;
  }

  virtual bool writeRaw(const QByteArray &data)
  {
    m_dataRaw = data;

    return m_writeReturnValue;
  }

  void setWriteReturnValue(bool value)
  {
    m_writeReturnValue = value;
  }

  void setError(const QString &error)
  {
    m_error = error;
  }

  QString data() const
  {
    return m_data;
  }

  QByteArray dataRaw() const
  {
    return m_dataRaw;
  }
};

} // unittest

#endif
