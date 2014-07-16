// serial device settings
var serialDevice = "/dev/tty.usbserial-A6004op2";
var baudrate = 9600;

// serial port
var port = new SerialPort;

// open serial port
if (port.open(serialDevice, baudrate, 10))
{
  // create serial led
  var led = new SerialLed;
  led.setSerialPort(port);

  // colors
  var color1 = new Color;
  color1.r = 32;
  color1.g = 0;
  color1.b = 0;

  var color2 = new Color;
  color2.r = 0;
  color2.g = 32;
  color2.b = 32;

  // set colors
  for (var i = 0; i < 40; i++)
  {
    led.setToggledColor(i, color1, color2);
  }

  // change time between toggles
  led.setToggleDelay(100);

  // show colors on serial leds
  led.show(true);
}
else
{
  // error, log and exit
  logger.logError(serialPort.error());
  exit();
}
