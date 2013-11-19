#ifndef VST_JENKINSMANAGER_H
#define VST_JENKINSMANAGER_H

#include <QObject>
#include <qscriptengine>
#include "BaseJenkinsManager.h"
#include "JenkinsJob.h"
#include "BaseHttpPort.h"

/// Class for retrieving the job status from a Jenkins/Hudson build server.
class JenkinsManager : public BaseJenkinsManager
{
  Q_OBJECT

public:
  /// Constructor.
  ///
  /// \param[in] parent Parent of this object.
  JenkinsManager(QObject *parent = 0);
  
  /// Destructor.
  virtual ~JenkinsManager();

protected:
  /// Checks if the given URL ends with /api/json, if it does not the URL
  /// is fixed by appending /api/json.
  QString makeJsonUrl(const QString &url);

  /// Parses the given JSON data and populates the job list. Does not empty
  /// the job list before parsing!
  ///
  /// \param[in] data Byte array with JSON data.
  /// \return True on success, false on error.
  bool parseJsonData(const QByteArray &data);

public slots:
  /// Retrieves the status of the jobs from the build server at the given URL.
  ///
  /// \param[in] url URL of build server (main status page).
  /// \return True if successful, false if error occurred.
  virtual bool getStatus(const QString &url);
};

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
