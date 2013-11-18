#include "SerialPort.h"
#include <QDateTime>

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
  unsigned short timeoutSecs)
{
  m_error.clear();

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
        m_error = QString(tr("Received unexpected answer: %1"))
                  .arg(QString::fromStdString(answer));

        return false;
      }
    }
    else
    {
      // empty answer
      m_error = tr("Received empty answer.");

      return false;
    }
  }
  catch (boost::system::system_error &exc)
  {
    m_error = QString(tr("Cannot open serial port. %1 (%2)"))
              .arg(QString(exc.what()))
              .arg(exc.code().value());

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
  m_error.clear();

  try
  {
    m_serialPort.close();
  }
  catch (boost::system::system_error &exc)
  {
    m_error = QString(tr("Cannot close serial port. %1 (%2)"))
              .arg(QString(exc.what()))
              .arg(exc.code().value());

    return false;
  }

  return true;
}

bool SerialPort::setTimeout(unsigned short timeoutSecs)
{
  m_error.clear();

  try
  {
    m_serialPort.setTimeout(boost::posix_time::seconds(timeoutSecs));
  }
  catch (boost::system::system_error &exc)
  {
    m_error = QString(tr("Cannot set serial port timeout. %1 (%2)"))
              .arg(QString(exc.what()))
              .arg(exc.code().value());

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
  m_error.clear();

  try
  {
    m_serialPort.writeString(data.toStdString());
  }
  catch (boost::system::system_error &exc)
  {
    m_error = QString(tr("Cannot write to serial port. %1 (%2)"))
              .arg(QString(exc.what()))
              .arg(exc.code().value());

    return false;
  }

  // serial device should report a !
  std::string answer = m_serialPort.readStringUntil(m_delimiter);

  if (answer != m_expected)
  {
    // unexpected answer
    m_error = QString(tr("Received unexpected answer: %1"))
              .arg(QString::fromStdString(answer));

    return false;
  }

  return true;
}

QString SerialPort::readStringUntil(const QString &delimiter)
{
  m_error.clear();
  std::string value;

  try
  {
    value = m_serialPort.readStringUntil(delimiter.toStdString());
  }
  catch (boost::system::system_error& exc)
  {
    m_error = QString(tr("Cannot read from serial port. %1 (%2)"))
              .arg(QString(exc.what()))
              .arg(exc.code().value());
  }

  return QString::fromStdString(value);
}
