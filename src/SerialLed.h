#ifndef VST_SERIALLED_H
#define VST_SERIALLED_H

#include <QObject>
#include "BaseSerialObject.h"
#include "Color.h"

/// Class for a LED connected to a serial port.
class SerialLed : public BaseSerialObject
{
  Q_OBJECT

public:
  /// Constructor.
  ///
  /// \param[in] parent Parent of this object.
  explicit SerialLed(QObject *parent = 0);

  /// Destructor.
  ~SerialLed();

  /// Sets a solid color for the given LED.
  ///
  /// \param[in] led Number of LED to set, range is 0 <= led <= 255.
  /// \param[in] color RGB color for LED.
  /// \return True if successful, false on error.
  Q_INVOKABLE bool setSolid(unsigned char led,
                           const Color &color);

  /// Makes the given LED transition between 2 colors.
  ///
  /// \param[in] led Number of LED to set, range is 0 <= led <= 255.
  /// \param[in] startColor First RGB color for LED.
  /// \param[in] endColor Second RGB color for LED.
  /// \param[in] riseTime Time in milliseconds to transition from the first
  /// color to the second color. Range is 0 <= riseTime <= 65535 ms.
  /// \param[in] fallTime Time in milliseconds to transition from the second
  /// color to the first color. Range is 0 <= fallTime <= 65535 ms.
  /// \return True if successful, false on error.
  Q_INVOKABLE bool setSawtooth(unsigned char led,
                               const Color &startColor,
                               const Color &endColor,
                               unsigned short riseTime,
                               unsigned short fallTime);
};

/// Custom constructor function for a SerialLed object. This function
/// makes it possible to create a SerialLed object in a script:
///
/// var led = new SerialLed;
///
/// \param[in] context Script context for the SerialLed object. The
/// first argument of the script context is the parent of the new
/// SerialLed object.
/// \param[in] engine Script engine which will take ownership of the new
/// SerialLed object.
/// \return The new SerialLed object wrapped in a script object.
QScriptValue serialLedConstructor(QScriptContext *context,
                                  QScriptEngine *engine);

#endif
