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
  unsigned int timeoutSecs)
{
  Q_UNUSED(deviceName);
  Q_UNUSED(baudrate);
  Q_UNUSED(timeoutSecs);

  m_isOpen = true;

  return m_isOpen;
}

bool MockSerialPort::isOpen()
{
  return m_isOpen;
}

bool MockSerialPort::close()
{
  m_isOpen = false;

  return true;
}

bool MockSerialPort::setTimeout(unsigned int timeoutSecs)
{
  Q_UNUSED(timeoutSecs);

  return true;
}

bool MockSerialPort::write(const QString &data)
{
  Q_UNUSED(data);

  if (m_isOpen)
  {
    // emit the data
    emit writtenData(data);

    return true;
  }

  // port not open
  return false;
}

} // core
