#include "SerialLed.h"

SerialLed::SerialLed(QObject *parent)
  : BaseSerialObject(parent)
{
}

SerialLed::~SerialLed()
{
}

bool SerialLed::setSolid(unsigned char led, const Color &color)
{
  return setToggled(led, color, color);
}

bool SerialLed::setToggled(unsigned char led, const Color &color1,
  const Color &color2)
{
  QChar padChar('0');

  QString colorString = QString("w%1-%2%3%4-%5%6%7\012")
                        .arg(led, 3, 10, padChar)
                        .arg(color1.r(), 3, 10, padChar)
                        .arg(color1.g(), 3, 10, padChar)
                        .arg(color1.b(), 3, 10, padChar)
                        .arg(color2.r(), 3, 10, padChar)
                        .arg(color2.g(), 3, 10, padChar)
                        .arg(color2.b(), 3, 10, padChar);

  return write(colorString);
}

bool SerialLed::setToggleDelay(unsigned short delay)
{
  QChar padChar('0');

  QString delayString = QString("d%1\012").arg(delay, 5, 10, padChar);

  return write(delayString);
}

bool SerialLed::clear(unsigned char led)
{
  // clear color by setting it to black
  Color black(0, 0, 0);

  return setToggled(led, black, black);
}

bool SerialLed::clearAll()
{
  QString clearString("c\012");

  return write(clearString);
}

QScriptValue serialLedConstructor(QScriptContext *context,
  QScriptEngine *engine)
{
  // parent of new object is in context
  QObject *parent = context->argument(0).toQObject();

  // create new SerialLed object
  QObject *object = new SerialLed(parent);

  // pass object to script
  return engine->newQObject(object, QScriptEngine::ScriptOwnership);
}
