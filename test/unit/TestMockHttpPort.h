#ifndef VST_TESTMOCKHTTPPORT_H
#define VST_TESTMOCKHTTPPORT_H

#include <QtTest/QtTest>

namespace unittest
{

/// Unit tests for MockHttpPort class.
class TestMockHttpPort : public QObject
{
  Q_OBJECT

private slots:
  /// Tests the default constructor.
  void defaultConstructor();

  /// Tests the get function.
  void get();

  /// Tests the data function.
  void data();

  /// Tests the setTimeout function.
  void setTimeout();

  /// Tests the setAuthentication function.
  void setAuthentication();

  /// Tests the setProxy function.
  void setProxy();
};

} // unittest

#endif