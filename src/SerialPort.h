#ifndef VST_SERIALPORT_H
#define VST_SERIALPORT_H

#include <QObject>
#include "BaseSerialPort.h"
#include "serial/TimeoutSerial.h"

namespace core
{

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
  /// \param[in] timeoutSecs Timeout for serial port in seconds.
  /// \return True if successful, false on error.
  virtual bool open(const QString &deviceName,
                    unsigned int baudrate,
                    unsigned int timeoutSecs);

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
  /// \param[in] timeoutSecs Timeout for serial port in seconds.
  /// \return True is successful, false on error.
  virtual bool setTimeout(unsigned int timeoutSecs);

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

} // core

#endif
