#ifndef VST_TESTBASEJENKINSMANAGER_H
#define VST_TESTBASEJENKINSMANAGER_H

#include <QtTest/QtTest>
#include "../../src/BaseJenkinsManager.h"
#include "../../src/JenkinsJob.h"

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
};

// Dummy class for testing of BaseJenkinsManager, implements the public slot
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
  virtual void getStatus(const QString &url)
  {
    Q_UNUSED(url);
  }
};

} // unittest

#endif
