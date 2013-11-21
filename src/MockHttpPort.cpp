#include "MockHttpPort.h"

MockHttpPort::MockHttpPort(QObject *parent)
  : BaseHttpPort(parent)
  , m_data()
{
}

MockHttpPort::~MockHttpPort()
{
}

void MockHttpPort::data(const QString &data)
{
  m_data = data;
}

bool MockHttpPort::get(const QUrl &url)
{
  Q_UNUSED(url);

  return true;
}

QString MockHttpPort::data()
{
  return m_data;
}

bool MockHttpPort::setTimeout(unsigned short timeout)
{
  Q_UNUSED(timeout);

  return true;
}

bool MockHttpPort::setAuthentication(const QString &user,
  const QString &password)
{
  Q_UNUSED(user);
  Q_UNUSED(password);

  return true;
}

bool MockHttpPort::setProxy(const QString &user, const QString &password,
  const QString &host, unsigned short port)
{
  Q_UNUSED(user);
  Q_UNUSED(password);
  Q_UNUSED(host);
  Q_UNUSED(port);

  return true;
}

QScriptValue mockHttpPortConstructor(QScriptContext *context,
  QScriptEngine *engine)
{
  // parent of new object is in context
  QObject *parent = context->argument(0).toQObject();

  // create new MockHttpPort object
  QObject *object = new MockHttpPort(parent);

  // pass object to script
  return engine->newQObject(object, QScriptEngine::ScriptOwnership);
}
