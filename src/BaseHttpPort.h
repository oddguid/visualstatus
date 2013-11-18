#ifndef VST_BASEHTTPPORT_H
#define VST_BASEHTTPPORT_H

#include <QObject>
#include <QUrl>

/// Base class for classes that use the HTTP protocol.
class BaseHttpPort : public QObject
{
  Q_OBJECT

protected:
  QString m_error;

public:
  /// Constructor.
  ///
  /// \param[in] parent Parent of this object.
  explicit BaseHttpPort(QObject *parent = 0);

  /// Destructor.
  virtual ~BaseHttpPort();

public slots:
  /// Gets the data at the given url.
  ///
  /// \param[in] url Url to get data from.
  /// \return True if successful, false if error occurred.
  virtual bool get(const QUrl &url) = 0;

  /// Returns the received data. Can be called after get() is successfully
  /// called.
  ///
  /// \return Received data, empty if no data is available.
  virtual QString data() = 0;

  /// Sets the connection timeout in seconds.
  ///
  /// \param[in] timeout Timeout in seconds, range is 1 <= timout <= 65535.
  /// \return True if successful, false if error occurred.
  virtual bool setTimeout(unsigned short timeout) = 0;

  /// Sets the basic authentication properties. This function must be called
  /// before get().
  ///
  /// \param[in] user User name.
  /// \param[in] password Password of user.
  /// \return True if successful, false if error occurred.
  virtual bool setAuthentication(const QString &user,
                                 const QString &password) = 0;

  /// Sets the proxy to use. Use an empty host to disable the proxy. This
  /// function must be called before get().
  ///
  /// \param[in] user Proxy user name.
  /// \param[in] password Password of proxy user.
  /// \param[in] host Proxy hostname.
  /// \param[in] port Proxy port number, range is 0 <= port <= 65535.
  /// \return True if successful, false if error occurred.
  virtual bool setProxy(const QString &user,
                        const QString &password,
                        const QString &host,
                        unsigned short port) = 0;

  /// Returns the last saved error message.
  ///
  /// \return Error message.
  QString error() const;
};

#endif
