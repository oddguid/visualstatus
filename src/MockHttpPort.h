#ifndef VST_MOCKHTTPPORT_H
#define VST_MOCKHTTPPORT_H

#include <QObject>
#include <QtScript/QScriptEngine>
#include "BaseHttpPort.h"

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
  Q_INVOKABLE void data(const QString &data);

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
};

/// Custom constructor function for a MockHttpPort object. This function
/// makes it possible to create a MockHttpPort object in a script:
///
/// var port = new MockHttpPort;
///
/// \param[in] context Script context for the MockHttpPort object. The
/// first argument of the script context is the parent of the new
/// MockHttpPort object.
/// \param[in] engine Script engine which will take ownership of the new
/// MockHttpPort object.
/// \return The new MockHttpPort object wrapped in a script object.
QScriptValue mockHttpPortConstructor(QScriptContext *context,
                                     QScriptEngine *engine);

#endif
