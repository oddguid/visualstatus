#ifndef VST_TESTBASEJENKINSMANAGER_H
#define VST_TESTBASEJENKINSMANAGER_H

#include <QtTest/QtTest>
#include "../../src/JenkinsJob.h"
#include "../../src/BaseJenkinsManager.h"

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
// getStatus(const QString &url) and makes internals accessible.
class DummyJenkinsManager : public BaseJenkinsManager
{
  Q_OBJECT

public:
  explicit DummyJenkinsManager(QObject *parent = nullptr)
    : BaseJenkinsManager(parent)
  {
  }

  virtual ~DummyJenkinsManager()
  {
  }

  QMap<QString, JenkinsJob *> &jobMap()
  {
    return m_jobStatus;
  }

  // make m_error accessible
  QString &refError()
  {
    return m_error;
  }

  // make clearJobs accessible
  using BaseJenkinsManager::clearJobs;

public slots:
  virtual bool getStatus(const QString &url)
  {
    Q_UNUSED(url);

    return true;
  }
};

} // unittest

#endif
