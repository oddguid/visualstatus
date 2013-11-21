#ifndef VST_SERIALPORT_H
#define VST_SERIALPORT_H

#include <QObject>
#include <qscriptengine>
#include "BaseSerialPort.h"
#include "serial/TimeoutSerial.h"

/// Class for serial port operations.
class SerialPort : public BaseSerialPort
{
  Q_OBJECT

protected:
  TimeoutSerial m_serialPort;

  static const std::string m_delimiter;
  static const std::string m_expected;

public:
  /// Constructor.
  ///
  /// \param[in] parent Parent of this object.
  explicit SerialPort(QObject *parent = 0);

  /// Destructor.
  virtual ~SerialPort();

public slots:
  /// Opens the serial port.
  ///
  /// \param[in] deviceName Name of the serial port.
  /// \param[in] baudrate Baudrate for serial port.
  /// \param[in] timeoutSecs Timeout for serial port in seconds, range is
  /// 0 <= timeoutSecs <= 65535.
  /// \return True if successful, false on error.
  virtual bool open(const QString &deviceName,
                    unsigned int baudrate,
                    unsigned short timeoutSecs);

  /// Indicates whether serial port is open or not.
  ///
  /// \return True if serial port is open, false otherwise.
  virtual bool isOpen();

  /// Closes the serial port.
  ///
  /// \return True if successful, false on error.
  virtual bool close();

  /// Sets the timeout of the serial port.
  ///
  /// \param[in] timeoutSecs Timeout for serial port in seconds, range is
  /// 0 <= timeoutSecs <= 65535.
  /// \return True is successful, false on error.
  virtual bool setTimeout(unsigned short timeoutSecs);

  /// Write the string data to the serial port.
  ///
  /// \param[in] data String data to write.
  /// \return True if successful, false on error.
  virtual bool write(const QString &data);

protected:
  /// Write the string data to the serial port
  ///
  /// \param[in] data String data to write.
  /// \return True if successful (!\n is returned by serial device), false on
  /// error.
  bool writeString(const QString &data);

  /// Reads from the serial port until the given delimiter is received. Default
  /// delimiter is the line end ('\n').
  ///
  /// \param[in] delimiter Delimiter to use.
  /// \return Received data from the serial port.
  QString readStringUntil(const QString& delimiter = QString("\n"));
};

/// Custom constructor function for a SerialPort object. This function
/// makes it possible to create a SerialPort object in a script:
///
/// var port = new SerialPort;
///
/// \param[in] context Script context for the SerialPort object. The
/// first argument of the script context is the parent of the new
/// SerialPort object.
/// \param[in] engine Script engine which will take ownership of the new
/// SerialPort object.
/// \return The new SerialPort object wrapped in a script object.
QScriptValue serialPortConstructor(QScriptContext *context,
                                   QScriptEngine *engine);

#endif
