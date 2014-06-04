SerialLed
=========

The _SerialLed_ object sets the color of LEDs which are connected through a serial port. It has functions to set and clear colors of individual LEDs. 

```javascript
// create serial port
var port = new SerialPort;

// open serial port
if (port.open("/dev/tty.usbserial-A6004op2", 9600, 10))
{
  // LED
  var led = new SerialLed;
  led.setSerialPort(port);

  // color red
  var red = new Color(255, 0, 0);

  // color green
  var green = new Color(0, 255, 0);

  // set toggled color on first LED
  led.setToggled(0, red, green);

  // set toggle time
  led.setToggleDelay(500);

  // set color on second LED
  led.setColor(1, green);

  // turn LEDs on
  led.show(true);
}
```

A description of the protocol that is used can be found here(TODO).

Functions
---------

### SerialLed()

Constructs a new _SerialLed_ object.

```javascript
// create serial LED
var led = new SerialLed;
```

### bool clear(led)

Clears the color for the LED with the given number. The parameter _led_ indicates which LED to clear and it's value must be in the range [0, 255]. Returns true if the color is successfully cleared and returns false if an error occurred.

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
var led = new SerialLed;

// color white
var color = new Color(255, 255, 255);

// set color
if (!led.setColor(0, color))
{
  // log error
  logger.logError(led.error());
}
```

### bool setColor(led, color)

Sets a solid color for the LED with the given number. The parameter _led_ indicates which LED to set and its value must be in the range [0, 255]. The parameter _color_ is a _Color_ object. Returns true if the color is successfully set and returns false if an error occurred.

```javascript
// LED
var led = new SerialLed;

// color green
var green = new Color(0, 255, 0);

// set solid color on third LED
led.setColor(2, green);
```

### setSerialPort(port)

Sets the serial port to use, which can be a _SerialPort_ object or a _MockSerialPort_ object.

```javascript
var port = new SerialPort;
var led = new SerialLed;

// set serial port
led.setSerialPort(port);
```

### bool setToggledColor(led, color1, color2)

Sets a toggled color for the LED with the given number. When set the LED will toggle between the two colors at the interval set by the function _setToggleDelay_. The parameter _led_ indicates which LED to set and its value must be in the range [0, 255]. The parameters _color1_ and _color2_ are _Color_ objects. Returns true if the colors are successfully set and returns false if an error occurred.

```javascript
// LED
var led = new SerialLed;

// color blue
var blue = new Color(0, 0, 255);

// color white
var white = new Color(25, 255, 255);

// set toggled color on first LED
led.setToggledColor(1, white, blue);
```

### bool setToggleDelay(delay)

Sets the delay in milliseconds between color toggles. A delay of 500ms will show each color once per second, a delay of 250ms will show each color twice per second. The default value and minimal value are set by the connected hardware. The parameter _delay_ must be in the range [0, 65535]. Returns true if the delay is successfully set and returns false if an error occurred.

```javascript
// LED
var led = new SerialLed;

// set toggle delay
led.setToggleDelay(100);
```

### bool show(enable)

Turns the LEDs on or off. Use true to show the LEDs at the set colors and use false to turn the LEDs off. Turning the LEDs off will not change the set colors. Returns true if the colors are successfully set on or off and returns false if an error occurred.

```javascript
// turn LEDs on
led.show(true);

// turn LEDs off
led.show(false);
```
