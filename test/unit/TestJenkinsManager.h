#ifndef VST_TESTJENKINSMANAGER_H
#define VST_TESTJENKINSMANAGER_H

#include <QtTest/QtTest>

namespace unittest
{

/// Unit tests for JenkinsManager class.
class TestJenkinsManager : public QObject
{
  Q_OBJECT

private slots:
  /// Tests the default constructor.
  void defaultConstructor();

  /// Tests the makeJsonUrl function.
  void makeJsonUrl();

  /// Tests the global function jenkinsManagerConstructor.
  void jenkinsManagerConstructor();
};

} // unittest

#endif
