#include "BaseHttpPort.h"

BaseHttpPort::BaseHttpPort(QObject *parent)
  : QObject(parent)
  , m_error()
{
}

BaseHttpPort::~BaseHttpPort()
{
}

QString BaseHttpPort::error() const
{
  return m_error;
}
