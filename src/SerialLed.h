#ifndef VST_SERIALLED_H
#define VST_SERIALLED_H

#include <QObject>
#include "BaseSerialObject.h"
#include "Color.h"

/// Class for LEDs connected to a serial port.
class SerialLed : public BaseSerialObject
{
  Q_OBJECT

public:
  /// Constructor.
  ///
  /// \param[in] parent Parent of this object.
  explicit SerialLed(QObject *parent = nullptr);

  /// Destructor.
  virtual ~SerialLed();

  /// Sets a solid color for the given LED.
  ///
  /// \param[in] led Number of LED to set, range is 0 <= led <= 255.
  /// \param[in] color RGB color for LED.
  /// \return True if successful, false on error.
  Q_INVOKABLE bool setColor(quint8 led,
                            const Color &color);

  /// Makes the given LED toggle between 2 colors. The toggle speed is
  /// set with the function setToggleDelay().
  ///
  /// \param[in] led Number of LED to set, range is 0 <= led <= 255.
  /// \param[in] color1 First RGB color for LED.
  /// \param[in] color2 Second RGB color for LED.
  /// \return True if successful, false on error.
  Q_INVOKABLE bool setToggledColor(quint8 led,
                                   const Color &color1,
                                   const Color &color2);

  /// Sets the delay in milliseconds between color toggles. A delay of 500 ms
  /// will show each color once per second, a delay of 250 ms will show each
  /// color twice per second. The default value and minimal value are set
  /// by the connected hardware.
  ///
  /// \param[in] delay Delay between toggles in milliseconds. Range is 0 <=
  /// delay <= 65535 ms.
  /// \return True if successful, false on error.
  Q_INVOKABLE bool setToggleDelay(quint16 delay);

  /// Clears the color of the given LED.
  ///
  /// \param[in] led Number of LED to clear, range is 0 <= led <= 255.
  /// \return True if successful, false on error.
  Q_INVOKABLE bool clear(quint8 led);

  /// Clears the color of all LEDs.
  ///
  /// \return True if successful, false on error.
  Q_INVOKABLE bool clearAll();

  /// Shows the LEDs. Use true to show the LEDs at the set color, use false
  /// to turn of the LEDs without changing the set colors.
  ///
  /// \param[in] enable True to show LED colors, false to turn off LEDs.
  /// \return True if successful, false on error.
  Q_INVOKABLE bool show(bool enable);
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
