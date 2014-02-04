#include "SerialLedBuffered.h"

#define NUM_COLOR_COMPONENTS  3
#define NUM_EXTRA_BYTES       5
#define DATA_START_INDEX      4

SerialLedBuffered::SerialLedBuffered(QObject *parent)
  : BaseSerialObject(parent)
  , m_numColors(0)
  , m_colorBuffer(NUM_EXTRA_BYTES, 0)
{
  initializeBuffer();
}

SerialLedBuffered::SerialLedBuffered(quint8 numColors, QObject *parent)
  : BaseSerialObject(parent)
  , m_numColors(numColors)
  , m_colorBuffer(numColors * NUM_COLOR_COMPONENTS + NUM_EXTRA_BYTES, 0)
{
  initializeBuffer();
}

SerialLedBuffered::~SerialLedBuffered()
{
}

quint8 SerialLedBuffered::numColors() const
{
  return m_numColors;
}

void SerialLedBuffered::setNumColors(quint8 numColors)
{
  // resize buffer and set all colors to black
  m_numColors = numColors;
  m_colorBuffer.fill(0, numColors * NUM_COLOR_COMPONENTS + NUM_EXTRA_BYTES);

  initializeBuffer();
}

bool SerialLedBuffered::setColor(quint8 led, const Color &color)
{
  if (led >= m_numColors)
  {
    // LED number is beyond buffer capacity
    return false;
  }

  quint16 index = DATA_START_INDEX + led * NUM_COLOR_COMPONENTS;

  m_colorBuffer[index++] = color.r();
  m_colorBuffer[index++] = color.g();
  m_colorBuffer[index]   = color.b();

  return true;
}

bool SerialLedBuffered::clear(quint8 led)
{
  if (led >= m_numColors)
  {
    // LED number is beyond buffer capacity
    return false;
  }

  quint16 index = DATA_START_INDEX + led * NUM_COLOR_COMPONENTS;

  m_colorBuffer[index++] = 0;
  m_colorBuffer[index++] = 0;
  m_colorBuffer[index]   = 0;

  return true;
}

bool SerialLedBuffered::clearAll()
{
  m_colorBuffer.fill(0);
  initializeBuffer();

  return true;
}

bool SerialLedBuffered::update()
{
  return writeRaw(m_colorBuffer);
}

void SerialLedBuffered::initializeBuffer()
{
  m_colorBuffer[0] = 0x06;
  m_colorBuffer[1] = 0x85;
  m_colorBuffer[2] = static_cast<quint8>((m_numColors >> 8) & 0xFF);
  m_colorBuffer[3] = static_cast<quint8>(m_numColors & 0xFF);
}

void SerialLedBuffered::setChecksum()
{
  // start checksum with size field
  quint8 checksum = m_colorBuffer[2];
  checksum ^= m_colorBuffer[3];

  // loop all color data
  for (quint16 i = DATA_START_INDEX; i < m_colorBuffer.size() - 1; ++i)
  {
    checksum ^= m_colorBuffer[i];
  }

  m_colorBuffer[m_colorBuffer.size() - 1] = checksum;
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
