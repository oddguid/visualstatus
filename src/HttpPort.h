#ifndef VST_HTTPPORT_H
#define VST_HTTPPORT_H

#include <QObject>
#include <QUrl>
#include <QtScript/QScriptEngine>
#include <sstream>
#include <vector>
#include <curl/curl.h>
#include "BaseHttpPort.h"

/// Class for HTTP operations, uses curlpp.
class HttpPort : public BaseHttpPort
{
  Q_OBJECT

protected:
  CURL *m_curl;
  std::vector<unsigned char> m_curlErrorBuffer;
  QByteArray m_data;
  static QByteArray m_curlData;

public:
  /// Constructor.
  ///
  /// \param[in] parent Parent of this object.
  explicit HttpPort(QObject *parent = 0);

  /// Destructor.
  virtual ~HttpPort();

  /// Gets the data at the given url.
  ///
  /// \param[in] url Url to get data from.
  /// \return True if successful, false if error occurred.
  Q_INVOKABLE virtual bool get(const QString &url);

  /// Returns the received data. Can be called after get() is successfully
  /// called.
  ///
  /// \return Received data, empty if no data is available.
  Q_INVOKABLE virtual QString data();

  /// Sets the connection timeout in seconds.
  ///
  /// \param[in] timeoutSecs Timeout in seconds, range is
  /// 1 <= timeoutSecs <= 65535.
  /// \return True if successful, false if error occurred.
  Q_INVOKABLE virtual bool setTimeout(unsigned short timeoutSecs);

  /// Sets the basic authentication properties. This function must be called
  /// before get().
  ///
  /// \param[in] user User name.
  /// \param[in] password Password of user.
  /// \return True if successful, false if error occurred.
  Q_INVOKABLE virtual bool setAuthentication(const QString &user,
                                             const QString &password);

  /// Sets the proxy to use. Use an empty host to disable the proxy. This
  /// function must be called before get().
  ///
  /// \param[in] user Proxy user name.
  /// \param[in] password Password of proxy user.
  /// \param[in] host Proxy hostname.
  /// \param[in] port Proxy port number, range is 0 <= port <= 65535.
  /// \return True if successful, false if error occurred.
  Q_INVOKABLE virtual bool setProxy(const QString &user,
                                    const QString &password,
                                    const QString &host,
                                    unsigned short port);

protected:
  /// Helper function to collect the data that libCurl receives.
  ///
  /// \param[in] ptr Data chunk that was received.
  /// \param[in] size Number of data tokens that was received.
  /// \param[in] nmemb Size of a data token in bytes.
  /// \param[in,out] userdata Structure to which the received data will be
  /// appended. In this case a static QByteArray will be used.
  /// \return Number of bytes that was processed, which is normally size *
  /// nmemb. A different value signals an error.
  static size_t curlWrite(void *ptr,
                          size_t size,
                          size_t nmemb,
                          void *userdata);
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
