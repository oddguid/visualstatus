#ifndef VST_TESTBASEHTTPPORT_H
#define VST_TESTBASEHTTPPORT_H

#include <QtTest/QtTest>
#include "../../src/BaseHttpPort.h"

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
// functions and makes the internal data accessible.
class DummyHttpPort : public BaseHttpPort
{
  Q_OBJECT

public:
  explicit DummyHttpPort(QObject *parent = nullptr)
    : BaseHttpPort(parent)
  {
  }

  virtual ~DummyHttpPort()
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

  // make m_error accessible
  QString &refError()
  {
    return m_error;
  }
};

} // unittest

#endif
