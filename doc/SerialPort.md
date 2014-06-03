SerialPort
==========

The _SerialPort_ object is the interface to connected devices. It has functions to open & close serial ports and to write data to a serial port.

```javascript
// create serial port
var port = new SerialPort;

// open serial port
if (port.open("/dev/tty.usbserial-A6004op2", 9600, 10))
{
  // write
  if (!port.write("message"))
  {
    // error writing
    logger.logError(port.error());
  }
}
else
{
  // error opening port
  logger.logError(port.error());
}

// close port
port.close();
```

Functions
---------

### SerialPort()

Constructs a new _SerialPort_ object.

```javascript
// create serial port
var port = new SerialPort;
```

### bool close()

Closes the serial port. Returns true if the serial port is successfully closed and returns false if an error occurred.

```javascript
// close port
port.close();
```

### string error()

Returns the last saved error message, which is set when one of the other function returns false.

```javascript
var port = new SerialPort;

// open
if (!port.open("/dev/tty.usbserial-A6004op2", 9600, 10))
{
  // log error
  logger.logError(port.error());
}
```

### bool isOpen()

Indicates whether the serial port is opened or not. Returns true if the serial port is open
and returns false if it is not.

```javascript
// create serial port
var port = new SerialPort;

// returns false
var open = port.isOpen();

// open
if (port.open("/dev/tty.usbserial-A6004op2", 9600, 10))
{
  // returns true
  open = port.isOpen();  
}
```

### bool open(deviceName, baudrate, timeoutSecs)

Opens the serial port named _deviceName_ with the given _baudrate_ and _timeout_. Returns true if the serial port is successfully opened and returns false if an error occurred.

```javascript
// create serial port
var port = new SerialPort;

// open
var isOpen = port.open("/dev/tty.usbserial-A6004op2", 9600, 10);
```

### bool setTimeout(timeoutSecs)

Sets the timeout on the serial port in seconds. Returns true if the timeout is successfully set and returns false if an error occurred.

```javascript
// set timeout
port.setTimeout(5);
```

### bool write(data)

Writes a string to the serial port. Returns true if the data is successfully written and returns false if an error occurred.

```javascript
// write
port.write("message");
```
