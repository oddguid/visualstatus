#ifndef VST_BASESERIALOBJECT_H
#define VST_BASESERIALOBJECT_H

#include <QObject>
#include <QString>

class BaseSerialPort;

/// Base class for objects that output data to a serial port.
class BaseSerialObject : public QObject
{
  Q_OBJECT

protected:
  QString m_error;
  BaseSerialPort *m_serialPort;

public:
  /// Constructor.
  ///
  /// \param[in] parent Parent of this object.
  explicit BaseSerialObject(QObject *parent = 0);
        
  /// Destructor.
  virtual ~BaseSerialObject();

  /// Sets the serial port to use. This object will not become the parent of the
  /// serial port and will therefore not clean it up.
  ///
  /// \param[in] serialPort serial port to use.
  Q_INVOKABLE void setSerialPort(BaseSerialPort *serialPort);

  /// Returns the last saved error message.
  ///
  /// \return Error message.
  Q_INVOKABLE QString error() const;

protected:
  /// Writes the given data to the serial port.
  ///
  /// \param[in] data Data to write to serial port.
  /// \return True if successful, false on error or if no serial port is set.
  bool write(const QString &data);

  /// Writes the given raw data to the serial port.
  ///
  /// \param[in] data Data to write to serial port.
  /// \return True if successful, false on error or if no serial port is set.
  bool writeRaw(const QByteArray &data);
};

#endif

