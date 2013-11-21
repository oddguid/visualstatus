#ifndef VST_HTTPPORT_H
#define VST_HTTPPORT_H

#include <QObject>
#include <QUrl>
#include <qscriptengine>
#include <sstream>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include "BaseHttpPort.h"

/// Class for HTTP operations, uses curlpp.
class HttpPort : public BaseHttpPort
{
  Q_OBJECT

protected:
  curlpp::Easy m_request;
  std::stringstream m_data;

public:
  /// Constructor.
  ///
  /// \param[in] parent Parent of this object.
  explicit HttpPort(QObject *parent = 0);

  /// Destructor.
  virtual ~HttpPort();

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

/// Custom constructor function for an HttpPort object. This function
/// makes it possible to create an HttpPort object in a script:
///
/// var port = new HttpPort;
///
/// \param[in] context Script context for the HttpPort object. The
/// first argument of the script context is the parent of the new
/// HttpPort object.
/// \param[in] engine Script engine which will take ownership of the new
/// HttpPort object.
/// \return The new HttpPort object wrapped in a script object.
QScriptValue httpPortConstructor(QScriptContext *context,
                                 QScriptEngine *engine);

#endif
