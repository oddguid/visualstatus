#ifndef VST_MOCKSERIALPORT_H
#define VST_MOCKSERIALPORT_H

#include <QObject>
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

signals:
  /// Signal that emits the data from the write function.
  void writtenData(QString data);

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
  /// \param[in] timeoutSecs Timeout for serial port in seconds., range is
  /// 0 <= timeoutSecs <= 65535
  /// \return True is successful, false on error.
  virtual bool setTimeout(unsigned short timeoutSecs);

  /// Write the string data to the serial port.
  ///
  /// \param[in] data String data to write.
  /// \return True if successful, false on error.
  virtual bool write(const QString &data);
};

#endif
