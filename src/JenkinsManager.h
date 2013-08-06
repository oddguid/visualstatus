#ifndef VST_JENKINSMANAGER_H
#define VST_JENKINSMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QSslError>
#include <QMap>
#include <QStringList>
#include <qscriptengine>
#include "BaseJenkinsManager.h"
#include "JenkinsJob.h"

namespace script
{

/// Class for retrieving the job status from a Jenkins/Hudson build server.
class JenkinsManager : public BaseJenkinsManager
{
  Q_OBJECT

private:
  QNetworkAccessManager m_manager;
  QNetworkReply *m_reply;
  QMap<QString, JenkinsJob *> m_jobStatus;

public:
  /// Constructor.
  ///
  /// \param[in] parent Parent of this object.
  explicit JenkinsManager(QObject *parent = 0);
  
  /// Destructor.
  virtual ~JenkinsManager();

public slots:
  /// Retrieves the status of the jobs from the build server at the given URL.
  ///
  /// \param[in] url URL of build server (main status page).
  virtual void getStatus(const QString &url);

  /// Returns a list with the names of all jobs found on the build server.
  ///
  /// \return List with job names.
  virtual QStringList jobNames();

  /// Returns the URL of the given job.
  ///
  /// \param[in] jobName Name of job.
  /// \return URL of job, empty if job not found.
  virtual QString jobUrl(const QString &jobName);

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
  virtual QString jobColor(const QString &jobName);

  /// Returns a list with all jobs found on the build server.
  ///
  /// \return List with job objects.
  virtual QObjectList jobs();

  /// Returns the job of the given name.
  ///
  /// \param[in] jobName Name of job.
  /// \return Job object, NULL if job not found.
  virtual QObject *job(const QString &jobName);

protected slots:
  /// Processes the received job information.
  ///
  /// \param[in] reply HTTP reply with job information.
  void downloadFinished(QNetworkReply *reply);

  /// Handles SSL errors.
  ///
  /// \param[in] errors List of SSL errors.
  void sslErrors(const QList<QSslError> &errors);
};

} // script

/// Custom constructor function for a JenkinsManager object. This function 
/// makes it possible to create a JenkinsManager object in a script:
///
/// var manager = new JenkinsManager;
///
/// \param[in] context Script context for the JenkinsManager object. The first 
/// argument of the script context is the parent of the new JenkinsManager 
/// object.
/// \param[in] engine Script engine which will take ownership of the new 
/// JenkinsManager object.
/// \return The new JenkinsManager object wrapped in a script object.
QScriptValue jenkinsManagerConstructor(QScriptContext *context, 
                                       QScriptEngine *engine);

#endif
