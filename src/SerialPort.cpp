#include "SerialPort.h"
#include <QDateTime>

const std::string SerialPort::m_delimiter = "\012";
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
      if (answer.compare(0, m_expected.length(), m_expected) != 0)
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
  catch (timeout_exception &exc)
  {
    m_error = QString(tr("Time-out while opening serial port. %1"))
              .arg(QString(exc.what()));

    return false;
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
  catch (timeout_exception &exc)
  {
    m_error = QString(tr("Time-out while closing serial port. %1"))
              .arg(QString(exc.what()));

    return false;
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
  catch (timeout_exception &exc)
  {
    m_error = QString(tr("Time-out while setting serial port time-out. %1"))
              .arg(QString(exc.what()));

    return false;
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
  m_error.clear();

  try
  {
    m_serialPort.writeString(data.toStdString());
  }
  catch (timeout_exception &exc)
  {
    m_error = QString(tr("Time-out while writing to serial port. %1"))
              .arg(QString(exc.what()));

    return false;
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

  if (answer.compare(0, m_expected.length(), m_expected) != 0)
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
  catch (timeout_exception &exc)
  {
    m_error = QString(tr("Time-out while reading from serial port. %1"))
              .arg(QString(exc.what()));
  }
  catch (boost::system::system_error& exc)
  {
    m_error = QString(tr("Cannot read from serial port. %1 (%2)"))
              .arg(QString(exc.what()))
              .arg(exc.code().value());
  }

  return QString::fromStdString(value);
}

QScriptValue serialPortConstructor(QScriptContext *context,
  QScriptEngine *engine)
{
  // parent of new object is in context
  QObject *parent = context->argument(0).toQObject();

  // create new SerialPort object
  QObject *object = new SerialPort(parent);

  // pass object to script
  return engine->newQObject(object, QScriptEngine::ScriptOwnership);
}
