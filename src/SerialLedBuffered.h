#ifndef VST_SERIALLEDBUFFERED_H
#define VST_SERIALLEDBUFFERED_H

#include <QObject>
#include "BaseSerialObject.h"
#include "Color.h"

/// Class for LEDs connected to a serial port. This class uses a buffer and
/// binary transport to update the color of the LEDs on the serial device. A
/// maximum of 85 LEDs is supported.
///
/// The binary transport is based on the EasyTransfer Arduino library by
/// Bill Porter:
///
/// http://www.billporter.info/2011/05/30/easytransfer-arduino-library/
///
/// Bytes in buffer:
///
/// +-------------------+
/// | 0x06              |
/// +-------------------+
/// | 0x85              |
/// +-------------------+
/// | numLeds           |
/// +-------------------+
/// | RGB triplets      |
/// |   (numLeds * 3)   |
/// +-------------------+
/// | checksum          |
/// +-------------------+
class SerialLedBuffered : public BaseSerialObject
{
  Q_OBJECT

protected:
  quint8 m_numLeds;
  QByteArray m_ledBuffer;

public:
  /// Constructor.
  ///
  /// \param[in] parent Parent of this object.
  explicit SerialLedBuffered(QObject *parent = nullptr);

  /// Constructor.
  ///
  /// \param[in] numLeds Number of LEDs to use, range is 0 <= size <= 85.
  /// \param[in] parent Parent of this object.
  SerialLedBuffered(quint8 numLeds, QObject *parent = nullptr);

  /// Destructor.
  virtual ~SerialLedBuffered();

  /// Gives the number of LEDs available in the buffer.
  ///
  /// \return Number of supported LEDs.
  Q_INVOKABLE quint8 numLeds() const;

  /// Sets the number of LEDs available in the buffer. After resizing of the
  /// buffer all colors are set to black.
  ///
  /// \param[in] numLeds Number of LEDs to use, range is 0 <= size <= 85.
  /// \return True if successful, false on error.
  Q_INVOKABLE void setNumLeds(quint8 numLeds);

  /// Sets a color for the given LED.
  ///
  /// \param[in] led Number of LED to set, range is 0 <= led <= numLeds().
  /// \param[in] color RGB color for LED.
  /// \return True if successful, false on error.
  Q_INVOKABLE bool setColor(quint8 led,
                            const Color &color);

  /// Clears the color of the given LED.
  ///
  /// \param[in] led Number of LED to clear, range is 0 <= led <= numLeds().
  /// \return True if successful, false on error.
  Q_INVOKABLE bool clear(quint8 led);

  /// Clears the color of all LEDs.
  ///
  /// \return True if successful, false on error.
  Q_INVOKABLE bool clearAll();

  /// Updates the color of the LEDs by pushing the buffer to the attached
  /// serial device. The buffer is not cleared afterwards.
  ///
  /// \return True if successful, false on error.
  Q_INVOKABLE bool update();

protected:
  /// Adds the header and size information to the buffer.
  void initializeBuffer();

  /// Sets the checksum byte in the buffer
  void setChecksum();
};

/// Custom constructor function for a SerialLedBuffered object. This function
/// makes it possible to create a SerialLedBuffered object in a script:
///
/// var led = new SerialLedBuffered;
///
/// \param[in] context Script context for the SerialLedBuffered object. The
/// first argument of the script context is the parent of the new
/// SerialLedBuffered object.
/// \param[in] engine Script engine which will take ownership of the new
/// SerialLedBuffered object.
/// \return The new SerialLedBuffered object wrapped in a script object.
QScriptValue serialLedBufferedConstructor(QScriptContext *context,
                                          QScriptEngine *engine);

#endif
