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
  QChar padChar('0');

  QString colorString = QString(":c%1-%2%3%4\012")
                        .arg(led, 3, 10, padChar)
                        .arg(color.r(), 3, 10, padChar)
                        .arg(color.g(), 3, 10, padChar)
                        .arg(color.b(), 3, 10, padChar);

  return write(colorString);
}

bool SerialLed::setSawtooth(unsigned char led, const Color &startColor,
  const Color &endColor, unsigned short riseTime, unsigned short fallTime)
{
  QChar padChar('0');

  QString colorString = QString(":s%1-%2%3%4-%5%6%7-%8-%9\012")
                        .arg(led, 3, 10, padChar)
                        .arg(startColor.r(), 3, 10, padChar)
                        .arg(startColor.g(), 3, 10, padChar)
                        .arg(startColor.b(), 3, 10, padChar)
                        .arg(endColor.r(), 3, 10, padChar)
                        .arg(endColor.g(), 3, 10, padChar)
                        .arg(endColor.b(), 3, 10, padChar)
                        .arg(riseTime, 5, 10, padChar)
                        .arg(fallTime, 5, 10, padChar);

  return write(colorString);
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
