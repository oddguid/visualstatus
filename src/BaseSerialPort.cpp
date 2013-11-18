#include "BaseSerialPort.h"

BaseSerialPort::BaseSerialPort(QObject *parent)
  : QObject(parent)
  , m_error()
{
}

BaseSerialPort::~BaseSerialPort()
{
}

QString BaseSerialPort::error() const
{
  return m_error;
}
