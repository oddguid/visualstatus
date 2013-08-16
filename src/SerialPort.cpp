#include "SerialPort.h"
#include <QDateTime>

namespace core
{

const std::string SerialPort::m_delimiter = "\n";
const std::string SerialPort::m_expected = "!";

SerialPort::SerialPort(QObject *parent)
  : BaseSerialPort(parent)
  , m_serialPort()
{
}

SerialPort::~SerialPort()
{
  if (m_serialPort.isOpen())
  {
    m_serialPort.close();
  }
}

bool SerialPort::open(const QString &deviceName, unsigned int baudrate,
  unsigned int timeoutSecs)
{
  try
  {
    m_serialPort.open(deviceName.toStdString(), baudrate);
    m_serialPort.setTimeout(boost::posix_time::seconds(timeoutSecs));

    // serial device should report a !\n
    std::string answer = m_serialPort.readStringUntil(m_delimiter);

    if (answer.length() > 0)
    {
      if (answer != m_expected)
      {
        // unexpected answer
        return false;
      }
    }
    else
    {
      // empty answer
      return false;
    }
  }
  catch (boost::system::system_error &exc)
  {
    QString errorMsg = QString("Cannot open serial port. %1 (%2)")
                       .arg(QString(exc.what()))
                       .arg(exc.code().value());

    emit error(errorMsg);

    return false;
  }

  return true;
}

bool SerialPort::isOpen()
{
  return m_serialPort.isOpen();
}

bool SerialPort::close()
{
  try
  {
    m_serialPort.close();
  }
  catch (boost::system::system_error &exc)
  {
    QString errorMsg = QString("Cannot close serial port. %1 (%2)")
                       .arg(QString(exc.what()))
                       .arg(exc.code().value());

    emit error(errorMsg);

    return false;
  }

  return true;
}

bool SerialPort::setTimeout(unsigned int timeoutSecs)
{
  try
  {
    m_serialPort.setTimeout(boost::posix_time::seconds(timeoutSecs));
  }
  catch (boost::system::system_error &exc)
  {
    QString errorMsg = QString("Cannot set serial port timeout. %1 (%2)")
                       .arg(QString(exc.what()))
                       .arg(exc.code().value());

    emit error(errorMsg);

    return false;
  }

  return true;
}

bool SerialPort::write(const QString &data)
{
  return writeString(data);
}

bool SerialPort::writeString(const QString &data)
{
  try
  {
    m_serialPort.writeString(data.toStdString());
  }
  catch (boost::system::system_error &exc)
  {
    QString errorMsg = QString("Cannot write to serial port. %1 (%2)")
                       .arg(QString(exc.what()))
                       .arg(exc.code().value());

    emit error(errorMsg);

    return false;
  }

  // serial device should report a !
  std::string answer = m_serialPort.readStringUntil(m_delimiter);

  if (answer != m_expected)
  {
    // unexpected answer
    return false;
  }

  return true;
}

QString SerialPort::readStringUntil(const QString &delimiter)
{
  std::string value;

  try
  {
    value = m_serialPort.readStringUntil(delimiter.toStdString());
  }
  catch (boost::system::system_error& exc)
  {
    QString errorMsg = QString("Cannot read from serial port. %1 (%2)")
                       .arg(QString(exc.what()))
                       .arg(exc.code().value());

    emit error(errorMsg);
  }

  return QString::fromStdString(value);
}

} // core
