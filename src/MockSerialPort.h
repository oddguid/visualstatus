#ifndef VST_MOCKSERIALPORT_H
#define VST_MOCKSERIALPORT_H

#include <QObject>
#include <qscriptengine>
#include "BaseSerialPort.h"

/// Mock class for serial port operations.
class MockSerialPort : public BaseSerialPort
{
  Q_OBJECT

private:
  bool m_isOpen;

public:
  /// Constructor.
  ///
  /// \param[in] parent Parent of this object.
  explicit MockSerialPort(QObject *parent = 0);

  /// Destructor.
  virtual ~MockSerialPort();

  /// Opens the serial port.
  ///
  /// \param[in] deviceName Name of the serial port.
  /// \param[in] baudrate Baudrate for serial port.
  /// \param[in] timeoutSecs Timeout for serial port in seconds, range is
  /// 0 <= timeoutSecs <= 65535.
  /// \return True if successful, false on error.
  Q_INVOKABLE virtual bool open(const QString &deviceName,
                                unsigned int baudrate,
                                unsigned short timeoutSecs);

  /// Indicates whether serial port is open or not.
  ///
  /// \return True if serial port is open, false otherwise.
  Q_INVOKABLE virtual bool isOpen();

  /// Closes the serial port.
  ///
  /// \return True if successful, false on error.
  Q_INVOKABLE virtual bool close();

  /// Sets the timeout of the serial port.
  ///
  /// \param[in] timeoutSecs Timeout for serial port in seconds., range is
  /// 0 <= timeoutSecs <= 65535
  /// \return True is successful, false on error.
  Q_INVOKABLE virtual bool setTimeout(unsigned short timeoutSecs);

  /// Write the string data to the serial port.
  ///
  /// \param[in] data String data to write.
  /// \return True if successful, false on error.
  Q_INVOKABLE virtual bool write(const QString &data);

  /// Write the raw data to the serial port.
  ///
  /// \param[in] data Data to write.
  /// \return True if successfull, false on error.
  Q_INVOKABLE virtual bool writeRaw(const QByteArray &data);

signals:
  /// Signal that emits the data from the write function.
  void writtenData(QString data);

  /// Signal that emits the data from the writeRaw function.
  void writtenRawData(QByteArray data);
};

/// Custom constructor function for a MockSerialPort object. This function
/// makes it possible to create a MockSerialPort object in a script:
///
/// var port = new MockSerialPort;
///
/// \param[in] context Script context for the MockSerialPort object. The
/// first argument of the script context is the parent of the new
/// MockSerialPort object.
/// \param[in] engine Script engine which will take ownership of the new
/// MockSerialPort object.
/// \return The new MockSerialPort object wrapped in a script object.
QScriptValue mockSerialPortConstructor(QScriptContext *context,
                                       QScriptEngine *engine);

#endif
