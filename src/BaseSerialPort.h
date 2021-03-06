#ifndef VST_BASESERIALPORT_H
#define VST_BASESERIALPORT_H

#include <QObject>

/// Base class for classes that work with a serial port.
class BaseSerialPort : public QObject
{
  Q_OBJECT

protected:
  QString m_error;

public:
  /// Constructor.
  ///
  /// \param[in] parent Parent of this object.
  explicit BaseSerialPort(QObject *parent = nullptr);

  /// Destructor.
  virtual ~BaseSerialPort();

  /// Opens the serial port.
  ///
  /// \param[in] deviceName Name of the serial port.
  /// \param[in] baudrate Baudrate for serial port.
  /// \param[in] timeoutSecs Timeout for serial port in seconds, range is
  /// 0 <= timeoutSecs <= 65535.
  /// \return True if successful, false on error.
  Q_INVOKABLE virtual bool open(const QString &deviceName,
                                unsigned int baudrate,
                                unsigned short timeoutSecs) = 0;

  /// Indicates whether serial port is open or not.
  ///
  /// \return True if serial port is open, false otherwise.
  Q_INVOKABLE virtual bool isOpen() = 0;

  /// Closes the serial port.
  ///
  /// \return True if successful, false on error.
  Q_INVOKABLE virtual bool close() = 0;

  /// Sets the timeout of the serial port.
  ///
  /// \param[in] timeoutSecs Timeout for serial port in seconds, range is
  /// 0 <= timeoutSecs <= 65535.
  /// \return True is successful, false on error.
  Q_INVOKABLE virtual bool setTimeout(unsigned short timeoutSecs) = 0;

  /// Write the string data to the serial port.
  ///
  /// \param[in] data String data to write.
  /// \return True if successful, false on error.
  Q_INVOKABLE virtual bool write(const QString &data) = 0;

  /// Write the raw data to the serial port.
  ///
  /// \param[in] data Data to write.
  /// \return True if successfull, false on error.
  Q_INVOKABLE virtual bool writeRaw(const QByteArray &data) = 0;

  /// Returns the last saved error message.
  ///
  /// \return Error message.
  Q_INVOKABLE QString error() const;
};

#endif
