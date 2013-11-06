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

  /// Tests the parseJsonData function with empty data.
  void parseJsonDataEmpty();

  /// Tests the parseJsonData function with faulty data.
  void parseJsonDataError();

  /// Tests the parseJsonData function with correct data.
  void parseJsonData();

  /// Tests the parseJsonData function with correct data. The data contains
  /// a job twice.
  void parseJsonDataDouble();

  /// Tests the parseJsonData function with 2 correct, different data buffers.
  void parseJsonDataTwice();

  /// Tests the global function jenkinsManagerConstructor.
  void jenkinsManagerConstructor();
};

} // unittest

#endif
