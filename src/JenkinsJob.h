#ifndef VST_JENKINSJOB_H
#define VST_JENKINSJOB_H

#include <QObject>

/// Class for a Jenkins/Hudson job. Contains the job name, job url and color.
class JenkinsJob : public QObject
{
  Q_OBJECT

  Q_PROPERTY(QString name READ name WRITE name)
  Q_PROPERTY(QString url READ url WRITE url)
  Q_PROPERTY(QString color READ color WRITE color)

private:
  QString m_name;
  QString m_url;
  QString m_color;

public:
  /// Constructor.
  ///
  /// \param[in] parent Parent of his object.
  explicit JenkinsJob(QObject *parent = nullptr);
  
  /// Destructor.
  virtual ~JenkinsJob();

  /// Returns the name of the job.
  ///
  /// \return Name of the job.
  QString name() const;

  /// Sets the name of the job.
  ///
  /// \param[in] name Name of the job.
  void name(const QString &name);

  /// Returns the URL of the job.
  ///
  /// \return URL of the job.
  QString url() const;

  /// Sets the URL of the job.
  ///
  /// \param[in] url URL of the job.
  void url(const QString &url);

  /// Returns the color of the job, indicating the status. Possible values
  /// are (taken from hudson.model.BallColor in schema):
  ///
  /// red            - failed
  /// red_anime      - failed in progress
  /// yellow         - unstable
  /// yellow_anime   - unstable in progress
  /// blue           - success
  /// blue_anime     - success in progress
  /// grey           - pending (disabled, aborted, not built)
  /// grey_anime     - pending in progress
  /// disabled       - disabled
  /// disabled_anime - disabled in progress
  /// aborted        - aborted
  /// aborted_anime  - aborted in progress
  /// notbuilt       - not built
  /// notbuilt_anime - not built in progress
  ///
  /// \return Color.
  QString color() const;

  /// Sets the color of the job.
  ///
  /// \param[in] color Color of the job.
  void color(const QString &color);
};

#endif
