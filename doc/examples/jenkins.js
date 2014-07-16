// serial device settings
var serialDevice = "/dev/tty.usbserial-A6004op2";
var baudrate = 9600;

// url of build server
var url = "http://ci.jruby.org";

// colors
var colorOk = new Color(0, 64, 0);
var colorError = new Color(64, 0, 0);

// serial port
var serialPort = new SerialPort;

// open serial port
if (serialPort.open(serialDevice, baudrate, 10))
{
  // create serial led
  var led = new SerialLed;

  led.setSerialPort(serialPort);

  // create jenkins manager
  var port = new HttpPort;
  var jenkins = new JenkinsManager;

  jenkins.setHttpPort(port);

  // get status of jobs on build server
  if (jenkins.getStatus(url))
  {
    // get color of a job
    var color = jenkins.jobColor("jruby-dist-master");

    // blue indicates successful build
    if ((color === "blue") || (color === "blue_anime"))
    {
      led.setColor(0, colorOk);
    }
    else
    {
      led.setColor(0, colorError);
    }

    // show colors on serial led
    led.show(true);
  }
  else
  {
    // error, log and exit
    logger.logError(jenkins.error());
    exit();
  }
}
else
{
  // error, log and exit
  logger.logError(serialPort.error());
  exit();
}
