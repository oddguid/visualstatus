#include "BaseSerialObject.h"
#include "BaseSerialPort.h"

BaseSerialObject::BaseSerialObject(QObject *parent)
  : QObject(parent)
  , m_error()
  , m_serialPort(NULL)
{
}

BaseSerialObject::~BaseSerialObject()
{
}

bool BaseSerialObject::write(const QString &data)
{
  m_error.clear();

  if (m_serialPort == NULL)
  {
    // no serial port set
    m_error = tr("No serial port set");

    return false;
  }

  if (!m_serialPort->write(data))
  {
    m_error = m_serialPort->error();

    return false;
  }

  return true;
}

void BaseSerialObject::setSerialPort(BaseSerialPort *serialPort)
{
  m_serialPort = serialPort;
}

QString BaseSerialObject::error() const
{
  return m_error;
}