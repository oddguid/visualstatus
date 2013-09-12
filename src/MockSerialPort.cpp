#include "MockSerialPort.h"

namespace core
{

MockSerialPort::MockSerialPort(QObject *parent)
  : BaseSerialPort(parent)
  , m_isOpen(false)
{
}

MockSerialPort::~MockSerialPort()
{
}

bool MockSerialPort::open(const QString &deviceName, unsigned int baudrate,
  unsigned short timeoutSecs)
{
  Q_UNUSED(deviceName);
  Q_UNUSED(baudrate);
  Q_UNUSED(timeoutSecs);

  m_error.clear();

  m_isOpen = true;

  return m_isOpen;
}

bool MockSerialPort::isOpen()
{
  return m_isOpen;
}

bool MockSerialPort::close()
{
  m_error.clear();

  m_isOpen = false;

  return true;
}

bool MockSerialPort::setTimeout(unsigned short timeoutSecs)
{
  Q_UNUSED(timeoutSecs);

  m_error.clear();

  return true;
}

bool MockSerialPort::write(const QString &data)
{
  Q_UNUSED(data);

  m_error.clear();

  if (m_isOpen)
  {
    // emit the data
    emit writtenData(data);

    return true;
  }

  // port not open
  m_error = tr("Cannot write data, serial port is closed.");

  return false;
}

} // core
