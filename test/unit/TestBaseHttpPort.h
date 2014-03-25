#ifndef VST_TESTBASEHTTPPORT_H
#define VST_TESTBASEHTTPPORT_H

#include <QtTest/QtTest>

// redefine protected to public to get access to the member variables of the
// BaseHttpPort class
#define protected public
#include "../../src/BaseHttpPort.h"
#undef protected

namespace unittest
{

/// Unit tests for BaseHttpPort class.
class TestBaseHttpPort : public QObject
{
  Q_OBJECT

private slots:
  /// Tests the default constructor.
  void defaultConstructor();

  /// Tests the error function.
  void error();
};

// Dummy class for testing of BaseHttpPort, implements the pure virtual
// functions.
class DummyHttpPort : public BaseHttpPort
{
  Q_OBJECT

public:
  DummyHttpPort(QObject *parent = 0)
    : BaseHttpPort(parent)
  {
  }

  ~DummyHttpPort()
  {
  }

  virtual bool get(const QString &url)
  {
    Q_UNUSED(url)

    return true;
  }

  virtual QString data()
  {
    return QString();
  }

  virtual bool setTimeout(unsigned short timeout)
  {
    Q_UNUSED(timeout)

    return true;
  }

  virtual bool setAuthentication(const QString &user,
                                 const QString &password)
  {
    Q_UNUSED(user)
    Q_UNUSED(password)

    return true;
  }

  virtual bool setProxy(const QString &user,
                        const QString &password,
                        const QString &host,
                        unsigned short port)
  {
    Q_UNUSED(user)
    Q_UNUSED(password)
    Q_UNUSED(host)
    Q_UNUSED(port)

    return true;
  }
};

} // unittest

#endif
