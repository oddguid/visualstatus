#ifndef VST_BASEJENKINSMANAGER_H
#define VST_BASEJENKINSMANAGER_H

#include <QObject>
#include <QObjectList>
#include <QString>
#include <QStringList>

namespace script
{

class JenkinsJob;
    
/// Base class for classes retrieving the job status from a Jenkins/Hudson
/// build server.
class BaseJenkinsManager : public QObject
{
  Q_OBJECT

public:
  /// Constructor.
  ///
  /// \param[in] parent Parent of this object.
  explicit BaseJenkinsManager(QObject *parent = 0);

  /// Destructor.
  virtual ~BaseJenkinsManager();

signals:
  /// Signal to indicate that the status of the jobs has been retrieved from 
  /// the build server.
  void statusAvailable();

  /// Signal to indicate an error has occurred.
  ///
  /// \param[in] error Error message.
  void error(QString error);

public slots:
  /// Retrieves the status of the jobs from the build server at the given URL.
  ///
  /// \param[in] url URL of build server (main status page).
  virtual void getStatus(const QString &url) = 0;

  /// Returns a list with the names of all jobs found on the build server.
  ///
  /// \return List with job names.
  virtual QStringList jobNames() = 0;

  /// Returns the URL of the given job.
  ///
  /// \param[in] jobName Name of job.
  /// \return URL of job, empty if job not found.
  virtual QString jobUrl(const QString &jobName) = 0;

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
  virtual QString jobColor(const QString &jobName) = 0;

  /// Returns a list with all jobs found on the build server.
  ///
  /// \return List with job objects.
  virtual QObjectList jobs() = 0;

  /// Returns the job of the given name.
  ///
  /// \param[in] jobName Name of job.
  /// \return Job object, NULL if job not found.
  virtual QObject *job(const QString &jobName) = 0;
};

} // script

#endif
