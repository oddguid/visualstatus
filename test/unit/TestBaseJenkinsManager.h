#ifndef VST_TESTBASEJENKINSMANAGER_H
#define VST_TESTBASEJENKINSMANAGER_H

#include <QtTest/QtTest>
#include "../../src/JenkinsJob.h"

// redefine protected to public to get access to the member variables of the
// BaseJenkinsManager class
#define protected public
#include "../../src/BaseJenkinsManager.h"
#undef protected

namespace unittest
{

/// Unit tests for BaseJenkinsManager class.
class TestBaseJenkinsManager : public QObject
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

  /// Tests the error function.
  void error();

  /// Tests the clearJobs function.
  void clearJobs();
};

// Dummy class for testing of BaseJenkinsManager, implements function
// getStatus(const QString &url).
class DummyJenkinsManager : public script::BaseJenkinsManager
{
  Q_OBJECT

public:
  DummyJenkinsManager(QObject *parent = 0)
    : BaseJenkinsManager(parent)
  {
  }

  ~DummyJenkinsManager()
  {
  }

  QMap<QString, script::JenkinsJob *> &jobMap()
  {
    return m_jobStatus;
  }

public slots:
  virtual bool getStatus(const QString &url)
  {
    Q_UNUSED(url);

    return true;
  }
};

} // unittest

#endif
