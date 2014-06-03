MockSerialPort
==============

The _MockSerialPort_ object is a mock interface for the serial port. It implements the same functions as the _SerialPort_ object, but instead of outputting the data to a physically connected device it outputs the data via a Qt signal.

This object can be used in place to fake a serial device, which can be useful while developing scripts. For example, given the following script:

```javascript
// create serial port
var port = new SerialPort;

// open serial port
if (port.open("/dev/tty.usbserial-A6004op2", 9600, 10))
{
  port.write("testdata");
}

port.close();
```

Replacing _SerialPort_ with _MockSerialPort_ requires only a change in the instantiation of the port variable:

```javascript
// create mock serial port
var port = new MockSerialPort;

// open serial port
if (port.open("/dev/tty.usbserial-A6004op2", 9600, 10))
{
  port.write("testdata");
}

port.close();
```

The Qt signal _writtenData_ can be used to get the written data:

```javascript
// function to receive data from MockSerialPort
function logSerialOutput(data)
{
  logger.log("serial port output:");
  logger.log(data);
}

// create mock serial port
var port = new MockSerialPort;

// open serial port
if (port.open("/dev/tty.usbserial-A6004op2", 9600, 10))
{
  // connect writtenData signal to function
  port.writtenData.connect(logSerialOutput);

  port.write("testdata");
}

port.close();
```

Functions
---------

### MockSerialPort()

Constructs a new _MockSerialPort_ object.

```javascript
// create serial port
var port = new MockSerialPort;
```

### bool close()

Closes the serial port. Always returns true.

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
var port = new MockSerialPort;

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

Opens the serial port named _deviceName_ with the given _baudrate_ and _timeout_. The parameters have no effect and the function always returns true.

```javascript
// create serial port
var port = new MockSerialPort;

// open
var isOpen = port.open("/dev/tty.usbserial-A6004op2", 9600, 10);
```

### bool setTimeout(timeoutSecs)

Sets the timeout on the serial port in seconds. The parameters have no effect and the function always returns true.

```javascript
// set timeout
port.setTimeout(5);
```

### bool write(data)

Emulates writing a string to the serial port and emits the signal _writtenData_. Returns true if the data is successfully written and returns false if an error occurred.

```javascript
// write
port.write("message");
```

Signals
-------

### writtenData(data)

Signal with the data that was written when the function _write(data)_ was successfully called.

```javascript
// function to receive data from MockSerialPort
function logSerialOutput(data)
{
  logger.log("serial port output:");
  logger.log(data);
}

// create mock serial port
var port = new MockSerialPort;

// open serial port
if (port.open("/dev/tty.usbserial-A6004op2", 9600, 10))
{
  // connect writtenData signal to function
  port.writtenData.connect(logSerialOutput);

  port.write("testdata");
}

port.close();
```
