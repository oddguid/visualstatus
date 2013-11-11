#ifndef VST_MOCKHTTPPORT_H
#define VST_MOCKHTTPPORT_H

#include <QObject>
#include "BaseHttpPort.h"

namespace core
{

/// Mock class for HTTP operations.
class MockHttpPort : public BaseHttpPort
{
  Q_OBJECT

private:
  QString m_data;

public:
  /// Constructor.
  ///
  /// \param[in] parent Parent of this object.
  explicit MockHttpPort(QObject *parent = 0);

  /// Destructor.
  virtual ~MockHttpPort();

  /// Sets the mock received data. Will be returned by the function data().
  ///
  /// \param[in] data Mock received data.
  void data(const QString &data);

public slots:
  /// Gets the data at the given url.
  ///
  /// \param[in] url Url to get data from.
  /// \return True if successful, false if error occurred.
  virtual bool get(const QUrl &url);

  /// Returns the received data. Can be called after get() is successfully
  /// called.
  ///
  /// \return Received data, empty if no data is available.
  virtual QString data();

  /// Sets the connection timeout in seconds.
  ///
  /// \param[in] timeout Timeout in seconds, range is 1 <= timout <= 65535.
  /// \return True if successful, false if error occurred.
  virtual bool setTimeout(unsigned short timeout);

  /// Sets the basic authentication properties. This function must be called
  /// before get().
  ///
  /// \param[in] user User name.
  /// \param[in] password Password of user.
  /// \return True if successful, false if error occurred.
  virtual bool setAuthentication(const QString &user,
                                 const QString &password);

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
                        unsigned short port);
};

} // core

#endif