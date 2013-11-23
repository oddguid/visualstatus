#ifndef VST_BASEJENKINSMANAGER_H
#define VST_BASEJENKINSMANAGER_H

#include <QObject>
#include <QObjectList>
#include <QString>
#include <QStringList>
#include <QMap>

class JenkinsJob;
class BaseHttpPort;

/// Base class for classes retrieving the job status from a Jenkins/Hudson
/// build server.
class BaseJenkinsManager : public QObject
{
  Q_OBJECT

protected:
  QMap<QString, JenkinsJob *> m_jobStatus;
  QString m_error;
  BaseHttpPort *m_httpPort;

public:
  /// Constructor.
  ///
  /// \param[in] parent Parent of this object.
  explicit BaseJenkinsManager(QObject *parent = 0);

  /// Destructor.
  virtual ~BaseJenkinsManager();

  /// Retrieves the status of the jobs from the build server at the given URL.
  ///
  /// \param[in] url URL of build server (main status page).
  /// \return True if successful, false if error occurred.
  Q_INVOKABLE virtual bool getStatus(const QString &url) = 0;

  /// Returns a list with the names of all jobs found on the build server.
  ///
  /// \return List with job names.
  Q_INVOKABLE virtual QStringList jobNames();

  /// Returns the URL of the given job.
  ///
  /// \param[in] jobName Name of job.
  /// \return URL of job, empty if job not found.
  Q_INVOKABLE virtual QString jobUrl(const QString &jobName);

  /// Returns the color (status) of the given job. Possible values
  /// are:
  ///
  /// red           - failed
  /// red_anime     - failed in progress
  /// yellow        - unstable
  /// yellow_anime  - unstable in progress
  /// blue          - success
  /// blue_anime    - success in progress
  /// grey          - pending (disabled, aborted, not built)
  /// grey_anime    - pending in progress
  ///
  /// \param[in] jobName Name of job.
  /// \return Color of job, empty if job not found.
  Q_INVOKABLE virtual QString jobColor(const QString &jobName);

  /// Returns a list with all jobs found on the build server.
  ///
  /// \return List with job objects.
  Q_INVOKABLE virtual QObjectList jobs();

  /// Returns the job of the given name.
  ///
  /// \param[in] jobName Name of job.
  /// \return Job object, NULL if job not found.
  Q_INVOKABLE virtual QObject *job(const QString &jobName);

  /// Sets the HTTP port to use. This object will not become the parent of the
  /// HTTP port and will therefore not clean it up.
  ///
  /// \param[in] httpPort HTTP port to use.
  Q_INVOKABLE void setHttpPort(BaseHttpPort *port);

  /// Returns the last saved error message.
  ///
  /// \return Error message.
  Q_INVOKABLE QString error() const;

protected:
  /// Empties the job list.
  void clearJobs();
};

#endif
