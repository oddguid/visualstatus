#include "Color.h"

#define MAX_COLOR_VALUE 255

Color::Color(QObject *parent)
  : QObject(parent)
  , m_r(0)
  , m_g(0)
  , m_b(0)
{
}

Color::Color(quint8 r, quint8 g, quint8 b, QObject *parent)
  : QObject(parent)
  , m_r(r)
  , m_g(g)
  , m_b(b)
{
}

Color::~Color()
{
}

Color::Color(const Color &that)
  : QObject()
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

void Color::set(quint8 r, quint8 g, quint8 b)
{
  m_r = r;
  m_g = g;
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
  
  if ((!value.isValid()) || (value.isUndefined()))
  {
    // property is not valid or Undefined. set to 0, not the default NaN
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
  
  if ((!value.isValid()) || (value.isUndefined()))
  {
    // property is not valid or Undefined. set to 0, not the default NaN
    m_g = 0;
  }
  else
  {
    // convert to unsigned integer
    quint32 g = value.toUInt32();
    
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
  
  if ((!value.isValid()) || (value.isUndefined()))
  {
    // property is Undefined. set to 0, not the default NaN
    m_b = 0;
  }
  else
  {
    // convert to unsigned integer
    quint32 b = value.toUInt32();
    
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

QScriptValue colorConstructor(QScriptContext *context,
  QScriptEngine *engine)
{
  QObject *object = NULL;

  if ((context->argumentCount() == 3)
    || (context->argumentCount() == 4))
  {
    // red component
    quint32 r = context->argument(0).toUInt32();

    if (r > MAX_COLOR_VALUE)
    {
      // clip value
      r = MAX_COLOR_VALUE;
    }

    // green component
    quint32 g = context->argument(1).toUInt32();

    if (g > MAX_COLOR_VALUE)
    {
      // clip value
      g = MAX_COLOR_VALUE;
    }

    // blue component
    quint32 b = context->argument(2).toUInt32();

    if (b > MAX_COLOR_VALUE)
    {
      // clip value
      b = MAX_COLOR_VALUE;
    }

    if (context->argumentCount() == 3)
    {
      // create new color object
      object = new Color(static_cast<quint8>(r),
                         static_cast<quint8>(g),
                         static_cast<quint8>(b));
    }
    else
    {
      // parent of new object is last argument in context
      QObject *parent = context->argument(3).toQObject();

      // create new color object
      object = new Color(static_cast<quint8>(r),
                         static_cast<quint8>(g),
                         static_cast<quint8>(b),
                         parent);
    }
  }
  else
  {
    // parent of new object is in context
    QObject *parent = context->argument(0).toQObject();

    // create new Color object
    object = new Color(parent);
  }

  // pass object to script
  return engine->newQObject(object, QScriptEngine::ScriptOwnership);
}

QScriptValue colorToScriptValue(QScriptEngine *engine, 
  const Color &color)
{
  // create and set new object
  QScriptValue object = color.toScriptValue(engine);

  return object;
}

void colorFromScriptValue(const QScriptValue &object, 
  Color &color)
{
  // set from object
  color.fromScriptValue(object);
}
