#include "SerialLedBuffered.h"

#define MAX_NUM_LEDS          85
#define NUM_COLOR_COMPONENTS  3
#define NUM_EXTRA_BYTES       4
#define DATA_START_INDEX      3

SerialLedBuffered::SerialLedBuffered(QObject *parent)
  : BaseSerialObject(parent)
  , m_numLeds(0)
  , m_ledBuffer(NUM_EXTRA_BYTES, 0)
{
  initializeBuffer();
}

SerialLedBuffered::SerialLedBuffered(quint8 numLeds, QObject *parent)
  : BaseSerialObject(parent)
  , m_numLeds(0)
  , m_ledBuffer()
{
  // set buffer size
  setNumLeds(numLeds);
}

SerialLedBuffered::~SerialLedBuffered()
{
}

quint8 SerialLedBuffered::numLeds() const
{
  return m_numLeds;
}

void SerialLedBuffered::setNumLeds(quint8 numLeds)
{
  // limit number of LEDs
  if (numLeds > MAX_NUM_LEDS)
  {
    m_numLeds = MAX_NUM_LEDS;
  }
  else
  {
    m_numLeds = numLeds;
  }

  // resize buffer and set all LEDs to black
  m_ledBuffer.fill(0, m_numLeds * NUM_COLOR_COMPONENTS + NUM_EXTRA_BYTES);

  initializeBuffer();
}

bool SerialLedBuffered::setColor(quint8 led, const Color &color)
{
  if (led >= m_numLeds)
  {
    // LED number is beyond buffer capacity
    return false;
  }

  quint16 index = DATA_START_INDEX + led * NUM_COLOR_COMPONENTS;

  m_ledBuffer[index++] = color.r();
  m_ledBuffer[index++] = color.g();
  m_ledBuffer[index]   = color.b();

  return true;
}

bool SerialLedBuffered::clear(quint8 led)
{
  if (led >= m_numLeds)
  {
    // LED number is beyond buffer capacity
    return false;
  }

  quint16 index = DATA_START_INDEX + led * NUM_COLOR_COMPONENTS;

  m_ledBuffer[index++] = 0;
  m_ledBuffer[index++] = 0;
  m_ledBuffer[index]   = 0;

  return true;
}

bool SerialLedBuffered::clearAll()
{
  m_ledBuffer.fill(0);
  initializeBuffer();

  return true;
}

bool SerialLedBuffered::update()
{
  return writeRaw(m_ledBuffer);
}

void SerialLedBuffered::initializeBuffer()
{
  m_ledBuffer[0] = 0x06;
  m_ledBuffer[1] = 0x85;
  m_ledBuffer[2] = m_numLeds * NUM_COLOR_COMPONENTS;
}

void SerialLedBuffered::setChecksum()
{
  // start checksum with size field
  quint8 checksum = m_ledBuffer[2];

  // loop all color data
  for (quint16 i = DATA_START_INDEX; i < m_ledBuffer.size() - 1; ++i)
  {
    checksum ^= m_ledBuffer[i];
  }

  m_ledBuffer[m_ledBuffer.size() - 1] = checksum;
}

QScriptValue serialLedBufferedConstructor(QScriptContext *context,
  QScriptEngine *engine)
{
  // parent of new object is in context
  QObject *parent = context->argument(0).toQObject();

  // create new SerialLedBuffered object
  QObject *object = new SerialLedBuffered(parent);

  // pass object to script
  return engine->newQObject(object, QScriptEngine::ScriptOwnership);
}
