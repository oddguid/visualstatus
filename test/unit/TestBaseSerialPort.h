#ifndef VST_TESTBASESERIALPORT_H
#define VST_TESTBASESERIALPORT_H

#include <QtTest/QtTest>
#include "../../src/BaseSerialPort.h"

namespace unittest
{

/// Unit tests for BaseSerialPort class.
class TestBaseSerialPort : public QObject
{
  Q_OBJECT

private slots:
  /// Tests the default constructor.
  void defaultConstructor();

  /// Tests the error function.
  void error();
};

// Dummy class for testing of BaseSerialPort, implements the pure virtual
// functions and makes internals accessible.
class DummySerialPort : public BaseSerialPort
{
  Q_OBJECT

public:
  explicit DummySerialPort(QObject *parent = nullptr)
    : BaseSerialPort(parent)
  {
  }

  virtual ~DummySerialPort()
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

    return true;
  }

  virtual bool writeRaw(const QByteArray &data)
  {
    Q_UNUSED(data)

    return true;
  }

  // make m_error accessible
  QString &refError()
  {
    return m_error;
  }
};

} // unittest

#endif
