#ifndef VST_JENKINSMANAGER_H
#define VST_JENKINSMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QSslError>
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
