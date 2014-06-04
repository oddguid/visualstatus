SerialLedBuffered
=================

The _SerialLedBuffered_ object sets the color of LEDs which are connected through a serial port. This object differs from the _SerialLed_ object in that it uses a buffer and binary transport to set the color of multiple LEDs with a single function call.

```javascript
// create serial port
var port = new SerialPort;

// open serial port
if (port.open("/dev/tty.usbserial-A6004op2", 9600, 10))
{
  // LED buffer
  var led = new SerialLedBuffered;
  led.setNumLeds(2);
  led.setSerialPort(port);

  // color red
  var red = new Color(255, 0, 0);

  // color green
  var green = new Color(0, 255, 0);

  // set color on first LED
  led.setColor(0, red);

  // set color on second LED
  led.setColor(1, green);

  // update LEDs
  led.udpate();
}
```

A description of the protocol that is used can be found here(TODO).

Functions
---------

### SerialLedBuffered()

Constructs a new _SerialLedBuffered_ object.

```javascript
// create serial LED buffer
var led = new SerialLedBuffered;
```

### SerialLedBuffered(numLeds)

Constructs a new _SerialLedBuffered_ object and initializes the buffer to hold _numLeds_ LEDs. The parameter _numLeds_ must be in the range [0, 85].

```javascript
// create serial LED buffer for 80 LEDs
var led = new SerialLedBuffered(80);
```

### bool clear(led)

Clears the color for the LED with the given number. The parameter _led_ indicates which LED to clear and it's value must be in the range [0, numLeds() - 1]. Returns true if the color is successfully cleared and returns false if an error occurred.

```javascript
// clear color of fifth LED
led.clear(4);
```

### bool clearAll()

Clears the color of all LEDs. Returns true if the colors are successfully cleared and returns false if an error occurred.

```javascript
// clear color of all LEDs
led.clearAll();
```

### string error()

Returns the last saved error message, which is set when one of the other function returns false.

```javascript
// LED
var led = new SerialLedBuffered;

// color white
var color = new Color(255, 255, 255);

// set color
if (!led.setColor(0, color))
{
  // log error
  logger.logError(led.error());
}
```

### unsigned short numLeds()

Returns the number of LEDs that the buffer can hold.

```javascript
// create serial LED buffer
var led = new SerialLedBuffered(27);

// get number of LEDs in buffer
var num = led.numLeds();
```

### bool setColor(led, color)

Sets a color for the LED with the given number. The parameter _led_ indicates which LED to set and its value must be in the range [0, numLeds() - 1]. The parameter _color_ is a _Color_ object. Returns true if the color is successfully set and returns false if an error occurred.

```javascript
// LED
var led = new SerialLedBuffered(5);

// color green
var green = new Color(0, 255, 0);

// set color on third LED
led.setColor(2, green);
```

### setNumLeds(numLeds)

Sets the number of LEDs that the buffer must hold. The parameter _numLeds_ must be in the range [0, 85] and after resizing of the buffer all colors are set to black.

```javascript
// create serial LED buffer
var led = new SerialLedBuffer;

// set number of LEDs in buffer
led.setNumLeds(11);
```

### setSerialPort(port)

Sets the serial port to use, which can be a _SerialPort_ object or a _MockSerialPort_ object.

```javascript
var port = new SerialPort;
var led = new SerialLedBuffered;

// set serial port
led.setSerialPort(port);
```

### bool update()

Updates the color of the LEDs by pushing the buffer to the attached serial device. The buffer is not cleared afterwards. Returns true if the update was successful and returns false if an error occurred.

```javascript
// update LEDs
led.update();
```
