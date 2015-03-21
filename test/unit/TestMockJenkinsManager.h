#ifndef VST_TESTMOCKJENKINSMANAGER_H
#define VST_TESTMOCKJENKINSMANAGER_H

#include <QtTest/QtTest>
#include "../../src/MockJenkinsManager.h"

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

// Dummy class for testing of MockJenkinsManager, makes internals accessible.
class DummyJenkinsManager : public MockJenkinsManager
{
  Q_OBJECT

public:
  DummyJenkinsManager(QObject *parent = nullptr)
    : MockJenkinsManager(parent)
  {
  }

  ~DummyJenkinsManager()
  {
  }

  // make parseJobBuffer accessible
  using MockJenkinsManager::parseJobBuffer;
};

} // unittest

#endif
