#ifndef VST_TESTMOCKSERIALPORT_H
#define VST_TESTMOCKSERIALPORT_H

#include <QtTest/QtTest>
#include "../../src/MockSerialPort.h"

namespace unittest
{

/// Unit tests for MockSerialPort class.
class TestMockSerialPort : public QObject
{
  Q_OBJECT

private slots:
  /// Tests the default constructor.
  void defaultConstructor();

  /// Tests the open function.
  void open();

  /// Tests the isOpen function.
  void isOpen();

  /// Tests the close function.
  void close();

  /// Tests the setTimeout function.
  void setTimeout();

  /// Tests the write function.
  void write();

  /// Tests the writeRaw function.
  void writeRaw();
};

// Dummy class for testing of MockSerialPort, makes internals accessible.
class DummySerialPort : public MockSerialPort
{
  Q_OBJECT

public:
  explicit DummySerialPort(QObject *parent = nullptr)
    : MockSerialPort(parent)
  {
  }

  virtual ~DummySerialPort()
  {
  }

  // make m_isOpen accessible
  bool &refIsOpen()
  {
    return m_isOpen;
  }
};

// Dummy class for testing the writtenData and writtenRawData signals of the
// MockSerialPort class.
class DummyLog : public QObject
{
  Q_OBJECT

public:
  QString m_writtenData;
  QByteArray m_writtenDataRaw;

  explicit DummyLog(QObject *parent = nullptr)
    : QObject(parent)
    , m_writtenData()
    , m_writtenDataRaw()
  {
  }

  virtual ~DummyLog()
  {
  }

public slots:
  void writtenData(QString data)
  {
    m_writtenData = data;
  }

  void writtenDataRaw(QByteArray data)
  {
    m_writtenDataRaw = data;
  }
};

} // unittest

#endif
