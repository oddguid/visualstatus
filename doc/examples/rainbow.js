// serial device settings
var serialDevice = "/dev/tty.usbserial-A6004op2";
var baudrate = 115200;
var numLeds = 40;

// serial port
var serialPort = new SerialPort;

// open serial port
if (serialPort.open(serialDevice, baudrate, 10))
{
  // create buffered serial led
  var led = new SerialLedBuffered;
  
  led.setNumLeds(numLeds);
  led.setSerialPort(serialPort);

  // code below is from the Arduino example sketch 'strandtest', which is
  // part of the Adafruit_Neopixel library. source:
  // https://github.com/adafruit/Adafruit_NeoPixel
  var color = new Color;

  for (var j = 0; j < 256*100; j++)
  {
    for (var i = 0; i < numLeds; i++)
    {
      var wheel = ((i * 256 / numLeds) + j) & 255;

      if (wheel < 85)
      {
        color.r = wheel * 3;
        color.g = 255 - wheel * 3;
        color.b = 0;
      }
      else if (wheel < 170)
      {
        wheel -= 85;
        color.r = 255 - wheel * 3;
        color.g = 0;
        color.b = wheel * 3;
      }
      else
      {
        wheel -= 170;
        color.r = 0;
        color.g = wheel * 3;
        color.b = 255 - wheel * 3;
      }

      // set color
      led.setColor(i, color);
    }

    // update colors
    led.update();
  }

  // close and exit
  serialPort.close();
  exit();
}
else
{
  // error, log and exit
  logger.logError(serialPort.error());
  exit();
}
