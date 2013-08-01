#ifndef VST_TESTJENKINSMANAGER_H
#define VST_TESTJENKINSMANAGER_H

#include <QtTest/QtTest>

namespace unittest
{

/// Unit tests for JenkinsMaganer class.
class TestJenkinsManager : public QObject
{
  Q_OBJECT

private slots:
  /// Tests the default constructor.
  void defaultConstructor();

  /// Tests the jobNames function.
  void jobNames();

  /// Tests the jobUrl function.
  void jobUrl();

  /// Tests the jobColor function.
  void jobColor();

  /// Tests the jobs function.
  void jobs();

  /// Tests the job function.
  void job();

  /// Tests the global function jenkinsManagerConstructor.
  void jenkinsManagerConstructor();
};

} // unittest
#endif
