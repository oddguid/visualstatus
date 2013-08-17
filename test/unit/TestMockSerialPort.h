#ifndef VST_TESTMOCKSERIALPORT_H
#define VST_TESTMOCKSERIALPORT_H

#include <QtTest/QtTest>

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
};

// Dummy class for testing the writtenData signal of the MockSerialPort class.
class DummyLog : public QObject
{
  Q_OBJECT

public:
  QString m_writtenData;

  explicit DummyLog(QObject *parent = 0)
    : QObject(parent)
    , m_writtenData()
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
};

} // unittest

#endif
