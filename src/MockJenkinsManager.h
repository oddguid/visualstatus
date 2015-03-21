#ifndef VST_MOCKJENKINSMANAGER_H
#define VST_MOCKJENKINSMANAGER_H

#include <QIODevice>
#include <QtScript/QScriptEngine>
#include "BaseJenkinsManager.h"
#include "JenkinsJob.h"

/// Mock class for retrieving the job status from a Jenkins/Hudson build
/// server.
///
/// The job status is read from a file and this file should have the following
/// markup:
/// - one job status per line;
/// - each line should have the name (mandatory), url (optional) and color
/// (optional);
/// - each line must have two separators (|);
/// - it is possible to define multiple jobs with the same name, but only the
/// last occurrence in the file is used.
///
/// For example:
/// job1|http://example.com|red
/// job2||blue_anime
/// job3||
class MockJenkinsManager : public BaseJenkinsManager
{
  Q_OBJECT

public:
  /// Constructor.
  ///
  /// \param[in] parent Parent of this object.
  explicit MockJenkinsManager(QObject *parent = nullptr);

  /// Destructor.
  virtual ~MockJenkinsManager();

  /// Retrieves the status of the jobs from a file.
  ///
  /// \param[in] fileName Name of the job status file.
  /// \return True if successful, false if error occurred.
  Q_INVOKABLE virtual bool getStatus(const QString &fileName);

protected:
  /// Parses the job status data in the given buffer. Every line is split on
  /// on the separator (|) into three parts and stored in a JenkinsJob.
  ///
  /// \param[in] jobBuffer Buffer with job status data.
  void parseJobBuffer(QIODevice *jobBuffer);
};

/// Custom constructor function for a MockJenkinsManager object. This function
/// makes it possible to create a MockJenkinsManager object in a script:
///
/// var manager = new MockJenkinsManager;
///
/// \param[in] context Script context for the MockJenkinsManager object. The
/// first argument of the script context is the parent of the new
/// MockJenkinsManager object.
/// \param[in] engine Script engine which will take ownership of the new
/// MockJenkinsManager object.
/// \return The new MockJenkinsManager object wrapped in a script object.
QScriptValue mockJenkinsManagerConstructor(QScriptContext *context,
                                           QScriptEngine *engine);

#endif
