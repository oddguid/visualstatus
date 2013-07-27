#include "Color.h"

#define MAX_COLOR_VALUE 255

namespace script
{

Color::Color(QObject *parent)
  : QObject(parent)
  , m_r(0)
  , m_g(0)
  , m_b(0)
{
}

Color::~Color()
{
}

Color::Color(const Color &that)
{
  m_r = that.m_r;
  m_g = that.m_g;
  m_b = that.m_b;
}

Color &Color::operator=(const Color &that)
{
  if (this != &that)
  {
    m_r = that.m_r;
    m_g = that.m_g;
    m_b = that.m_b;
  }

  return *this;
}

quint8 Color::r() const
{
  return m_r;
}

void Color::r(quint8 r)
{
  m_r = r;
}

quint8 Color::g() const
{
  return m_g;
}

void Color::g(quint8 g)
{
  m_g = g;
}

quint8 Color::b() const
{
  return m_b;
}

void Color::b(quint8 b)
{
  m_b = b;
}

QScriptValue Color::toScriptValue(QScriptEngine *engine) const
{
  QScriptValue object = engine->newObject();

  object.setProperty("r", m_r);
  object.setProperty("g", m_g);
  object.setProperty("b", m_b);

  return object;
}

void Color::fromScriptValue(const QScriptValue &object)
{
  // red component
  QScriptValue value = object.property("r");
  
  // TODO: test isValid() ??
  // TODO: what should we test if the property is not in the object ??
  
  if (value.isUndefined())
  {
    // property is Undefined. set to 0, not the default NaN
    m_r = 0;
  }
  else
  {
    // convert to unsigned integer
    quint32 r = value.toUInt32();
    
    if (r > MAX_COLOR_VALUE)
    {
      // clip value
      m_r = MAX_COLOR_VALUE;
    }
    else
    {
      m_r = r;
    }
  }
  
  // green component
  value = object.property("g");
  
  if (value.isUndefined())
  {
    // property is Undefined. set to 0, not the default NaN
    m_g = 0;
  }
  else
  {
    // convert to unsigned integer
    quint32 g = value.toUInt16();
    
    if (g > MAX_COLOR_VALUE)
    {
      // clip value
      m_g = MAX_COLOR_VALUE;
    }
    else
    {
      m_g = g;
    }
  }
  
  // blue component
  value = object.property("b");
  
  if (value.isUndefined())
  {
    // property is Undefined. set to 0, not the default NaN
    m_b = 0;
  }
  else
  {
    // convert to unsigned integer
    quint32 b = value.toUInt16();
    
    if (b > MAX_COLOR_VALUE)
    {
      // clip value
      m_b = MAX_COLOR_VALUE;
    }
    else
    {
      m_b = b;
    }
  }
}

} // script

QScriptValue colorConstructor(QScriptContext *context,
  QScriptEngine *engine)
{
  // parent of new object is in context
  QObject *parent = context->argument(0).toQObject();

  // create new Color object
  QObject *object = new script::Color(parent);

  // pass object to script
  return engine->newQObject(object, QScriptEngine::ScriptOwnership);
}

QScriptValue colorToScriptValue(QScriptEngine *engine, 
  const script::Color &color)
{
  // create and set new object
  QScriptValue object = color.toScriptValue(engine);

  return object;
}

void colorFromScriptValue(const QScriptValue &object, 
  script::Color &color)
{
  // set from object
  color.fromScriptValue(object);
}
