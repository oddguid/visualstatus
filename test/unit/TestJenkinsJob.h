#ifndef VST_TESTJENKINSJOB_H
#define VST_TESTJENKINSJOB_H

#include <QtTest/QtTest>

namespace unittest
{

/// Unit tests for JenkinsJob class.
class TestJenkinsJob : public QObject
{
  Q_OBJECT

private slots:
  /// Tests the default constructor.
  void defaultConstructor();

  /// Tests the getter and setter functions for the name of the job.
  void name();

  /// Tests the getter and setter functions for the url of the job.
  void url();

  /// Tests the getter and setter functions for the color of the job.
  void color();
};

} // unittest

#endif
