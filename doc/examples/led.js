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
  var red = new Color(255, 0, 0);
  var green = new Color(0, 255, 0);

  // set toggled color on first led
  led.setToggledColor(0, red, green);

  // change time between toggles
  led.setToggleDelay(500);

  // set color on second led
  led.setColor(1, green);

  // show colors on serial leds
  led.show(true);
}
else
{
  // error, log and exit
  logger.logError(serialPort.error());
  exit();
}
