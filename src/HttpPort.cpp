#include "HttpPort.h"
#include <curl/curl.h>

QByteArray HttpPort::m_curlData = QByteArray();

HttpPort::HttpPort(QObject *parent)
  : BaseHttpPort(parent)
  , m_curl(NULL)
  , m_curlErrorBuffer(CURL_ERROR_SIZE)
  , m_data()
{
  // initial curl settings
  m_curl = curl_easy_init();

  curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, HttpPort::curlWrite);
  curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, &m_curlData);
  curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYPEER, false);
  curl_easy_setopt(m_curl, CURLOPT_FOLLOWLOCATION, 1L);
  curl_easy_setopt(m_curl, CURLOPT_ERRORBUFFER, &m_curlErrorBuffer[0]);
}

HttpPort::~HttpPort()
{
  // cleanup curl
  curl_easy_cleanup(m_curl);
}

bool HttpPort::get(const QString &url)
{
  // clear error
  m_error.clear();

  // clear buffer
  m_curlData.clear();

  // set URL
  CURLcode result = curl_easy_setopt(m_curl, CURLOPT_URL,
                                     url.toStdString().c_str());

  if (result != CURLE_OK)
  {
    // error
    m_error = tr("Error setting URL. %1").arg(curl_easy_strerror(result));

    return false;
  }

  // get data
  result = curl_easy_perform(m_curl);

  if (result == CURLE_OK)
  {
    // get HTTP response code
    long httpCode = 0;

    curl_easy_getinfo(m_curl, CURLINFO_RESPONSE_CODE, &httpCode);

    if (httpCode >= 400)
    {
      // HTTP code 400 or greater is an error
      m_error = tr("HTTP error %1").arg(httpCode);

      return false;
    }
    else
    {
      // get data from global
      m_data = m_curlData;
    }
  }
  else
  {
    // error
    std::string errorMsg(m_curlErrorBuffer.begin(), m_curlErrorBuffer.end());
    m_error = tr("Error getting data. %1").arg(errorMsg.c_str());

    return false;
  }

  return true;
}

QString HttpPort::data()
{
  return QString(m_data);
}

bool HttpPort::setTimeout(unsigned short timeoutSecs)
{
  // clear error
  m_error.clear();

  // set timeout
  CURLcode result = curl_easy_setopt(m_curl, CURLOPT_CONNECTTIMEOUT,
                                     timeoutSecs);

  if (result != CURLE_OK)
  {
    // error
    m_error = tr("Error setting timeout. %1").arg(curl_easy_strerror(result));

    return false;
  }

  return true;
}

bool HttpPort::setAuthentication(const QString &user,
  const QString &password)
{
  // clear error
  m_error.clear();

  // set user
  CURLcode result = curl_easy_setopt(m_curl, CURLOPT_USERNAME,
                                     user.toStdString().c_str());

  if (result != CURLE_OK)
  {
    // error
    m_error = tr("Error setting user.  %1").arg(curl_easy_strerror(result));

    return false;
  }

  // set password
  result = curl_easy_setopt(m_curl, CURLOPT_PASSWORD,
                            password.toStdString().c_str());

  if (result != CURLE_OK)
  {
    // error
    m_error = tr("Error setting password. %1").arg(curl_easy_strerror(result));

    return false;
  }

  return true;
}

bool HttpPort::setProxy(const QString &user, const QString &password,
  const QString &host, unsigned short port)
{
  // clear error
  m_error.clear();

  if (host.isEmpty())
  {
    // no proxy
    CURLcode result = curl_easy_setopt(m_curl, CURLOPT_PROXY, "");

    if (result != CURLE_OK)
    {
      // error
      m_error = tr("Error clearing proxy. %1").arg(curl_easy_strerror(result));

      return false;
    }
  }
  else
  {
    // set proxy
    CURLcode result = curl_easy_setopt(m_curl, CURLOPT_PROXYTYPE,
                                       CURLPROXY_HTTP);

    if (result != CURLE_OK)
    {
      // error
      m_error = tr("Error setting proxy type. %1")
                .arg(curl_easy_strerror(result));

      return false;
    }

    // proxy host
    result = curl_easy_setopt(m_curl, CURLOPT_PROXY,
                              host.toStdString().c_str());

    if (result != CURLE_OK)
    {
      // error
      m_error = tr("Error setting proxy host. %1")
                .arg(curl_easy_strerror(result));

      return false;
    }

    // proxy port
    result = curl_easy_setopt(m_curl, CURLOPT_PROXYPORT, port);

    if (result != CURLE_OK)
    {
      // error
      m_error = tr("Error setting proxy port. %1")
                .arg(curl_easy_strerror(result));

      return false;
    }

    // proxy user
    result = curl_easy_setopt(m_curl, CURLOPT_PROXYUSERNAME,
                              user.toStdString().c_str());

    if (result != CURLE_OK)
    {
      // error
      m_error = tr("Error setting proxy user. %1")
                .arg(curl_easy_strerror(result));

      return false;
    }

    // proxy password
    result = curl_easy_setopt(m_curl, CURLOPT_PROXYPASSWORD,
                              password.toStdString().c_str());

    if (result != CURLE_OK)
    {
      // error
      m_error = tr("Error setting proxy password. %1")
                .arg(curl_easy_strerror(result));

      return false;
    }
  }

  return true;
}

size_t HttpPort::curlWrite(void *ptr, size_t size, size_t nmemb,
  void *userdata)
{
  QByteArray *byteData = (QByteArray*)userdata;
  const char *data = (char*)ptr;

  size_t copySize = size * nmemb;
  size_t bufferSize = byteData->size();

  if ((copySize > INT_MAX) || (bufferSize + copySize > INT_MAX))
  {
    // error, data size beyond capacity of QByteArray
    return 0;
  }

  // append data to global
  byteData->append(data, static_cast<int>(copySize));

  return copySize;
}

QScriptValue httpPortConstructor(QScriptContext *context,
  QScriptEngine *engine)
{
  // parent of new object is in context
  QObject *parent = context->argument(0).toQObject();

  // create new HttpPort object
  QObject *object = new HttpPort(parent);

  // pass object to script
  return engine->newQObject(object, QScriptEngine::ScriptOwnership);
}
