#ifndef VST_TESTMOCKJENKINSMANAGER_H
#define VST_TESTMOCKJENKINSMANAGER_H

#include <QtTest/QtTest>

namespace unittest
{

/// Unit tests for MockJenkinsManager class.
class TestMockJenkinsManager : public QObject
{
  Q_OBJECT

private slots:
  /// Tests the default constructor.
  void defaultConstructor();

  /// Tests the parseJobBuffer function with empty argument.
  void parseJobBufferEmpty();

  /// Tests the parseJobBuffer function with a buffer.
  void parseJobBuffer();

  /// Tests the parseJobBuffer function with a buffer containing an error.
  void parseJobBufferError();
};

} // unittest

#endif
