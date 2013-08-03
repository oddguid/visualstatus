#ifndef VST_TESTLOGLEVEL_H
#define VST_TESTLOGLEVEL_H

#include <QtTest/QtTest>

namespace unittest
{

/// Unit tests for LogLevel functions.
class TestLogLevel : public QObject
{
  Q_OBJECT

private slots:
  /// Tests the toString function of the LogLevel namespace.
  void toString();

  /// Tests the fromString function of the LogLevel namespace.
  void fromString();
};

} // unittest

#endif

