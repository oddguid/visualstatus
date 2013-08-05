#ifndef VST_BASESERIALPORT_H
#define VST_BASESERIALPORT_H

#include <QObject>

namespace core
{

/// Base class for classes that work with a serial port.
class BaseSerialPort : public QObject
{
  Q_OBJECT

public:
  /// Constructor.
  ///
  /// \param[in] parent Parent of this object.
  explicit BaseSerialPort(QObject *parent = 0);

  /// Destructor.
  virtual ~BaseSerialPort();

signals:
  /// Signal to indicate an error has occurred.
  ///
  /// \param[in] error Error message.
  void error(QString &error);

public slots:
  /// Opens the serial port.
  ///
  /// \param[in] deviceName Name of the serial port.
  /// \param[in] baudrate Baudrate for serial port.
  /// \param[in] timeoutSecs Timeout for serial port in seconds.
  /// \return True if successful, false on error.
  virtual bool open(const QString &deviceName,
                    unsigned int baudrate,
                    unsigned int timeoutSecs) = 0;

  /// Indicates whether serial port is open or not.
  ///
  /// \return True if serial port is open, false otherwise.
  virtual bool isOpen() = 0;

  /// Closes the serial port.
  ///
  /// \return True if successful, false on error.
  virtual bool close() = 0;

  /// Sets the timeout of the serial port.
  ///
  /// \param[in] timeoutSecs Timeout for serial port in seconds.
  /// \return True is successful, false on error.
  virtual bool setTimeout(unsigned int timeoutSecs) = 0;

  /// Write the string data to the serial port.
  ///
  /// \param[in] data String data to write.
  /// \return True if successful, false on error.
  virtual bool write(const QString &data) = 0;
};

} // core

#endif
