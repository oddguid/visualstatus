#include "HttpPort.h"
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>

namespace core
{

HttpPort::HttpPort(QObject *parent)
  : BaseHttpPort(parent)
  , m_request()
  , m_data()
{
  // set output stream
  curlpp::options::WriteStream writeStream(&m_data);
  m_request.setOpt(writeStream);
}

HttpPort::~HttpPort()
{
}

bool HttpPort::get(const QUrl &url)
{
  // clear error
  m_error.clear();

  // clear buffer
  m_data.str(std::string());
  m_data.clear();

  try
  {
    // set URL
    curlpp::options::Url urlOption(url.toString().toStdString());
    m_request.setOpt(urlOption);

    // get data
    m_request.perform();
  }
  catch (curlpp::RuntimeError &rExc)
  {
    m_error = QString(rExc.what());

    return false;
  }
  catch (curlpp::LogicError &lExc)
  {
    m_error = QString(lExc.what());

    return false;
  }

  return true;
}

QString HttpPort::data()
{
  return QString::fromStdString(m_data.str());
}

bool HttpPort::setTimeout(unsigned short timeout)
{
  // clear error
  m_error.clear();

  try
  {
    // set timeout
    curlpp::options::Timeout timeoutOption(timeout);
    m_request.setOpt(timeoutOption);
  }
  catch (curlpp::RuntimeError &rExc)
  {
    m_error = QString(rExc.what());

    return false;
  }
  catch (curlpp::LogicError &lExc)
  {
    m_error = QString(lExc.what());

    return false;
  }

  return true;
}

bool HttpPort::setAuthentication(const QString &user,
  const QString &password)
{
  // clear error
  m_error.clear();

  try
  {
    // set user and password
    QString userPwd = QString("%1:%2").arg(user).arg(password);
    curlpp::options::UserPwd userPwdOption(userPwd.toStdString());

    m_request.setOpt(userPwdOption);
  }
  catch (curlpp::RuntimeError &rExc)
  {
    m_error = QString(rExc.what());

    return false;
  }
  catch (curlpp::LogicError &lExc)
  {
    m_error = QString(lExc.what());

    return false;
  }

  return true;
}

bool HttpPort::setProxy(const QString &user, const QString &password,
  const QString &host, unsigned short port)
{
  // clear error
  m_error.clear();

  try
  {
    if (host.isEmpty())
    {
      // no proxy
      curlpp::options::Proxy hostOption("");
      m_request.setOpt(hostOption);
    }
    else
    {
      // proxy host
      curlpp::options::Proxy hostOption(host.toStdString());
      m_request.setOpt(hostOption);

      // proxy port
      curlpp::options::ProxyPort portOption(port);
      m_request.setOpt(portOption);

      // proxy user and password
      QString userPwd = QString("%1:%2").arg(user).arg(password);
      curlpp::options::ProxyUserPwd userPwdOption(userPwd.toStdString());

      m_request.setOpt(userPwdOption);
    }
  }
  catch (curlpp::RuntimeError &rExc)
  {
    m_error = QString(rExc.what());

    return false;
  }
  catch (curlpp::LogicError &lExc)
  {
    m_error = QString(lExc.what());

    return false;
  }

  return true;
}

} // core
