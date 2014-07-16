// serial device settings
var serialDevice = "/dev/tty.usbserial-A6004op2";
var baudrate = 9600;

// data file for MockJenkinsManager
var file = "jenkins.dat";

// colors
var colorOk = new Color(0, 0, 64);
var colorError = new Color(64, 0, 0);

// serial port
var serialPort = new SerialPort;

// open serial port
if (serialPort.open(serialDevice, baudrate, 10))
{
  // create serial led
  var led = new SerialLed;

  led.setSerialPort(serialPort);

  // create mock jenkins manager
  var port = new HttpPort;
  var jenkins = new MockJenkinsManager;

  jenkins.setHttpPort(port);
  
  // get status of jobs from file
  if (jenkins.getStatus(file))
  {
    // get color of a job
    var color = jenkins.jobColor("job2");

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
