// simulated build server data
var httpData =
  '{' +
  ' "assignedLabels":[{}],' +
  ' "mode":"NORMAL",' +
  ' "nodeDescription":"the master Jenkins node",' +
  ' "nodeName":"",' +
  ' "numExecutors":2,' +
  ' "description":null,' +
  ' "jobs":[' +
  '   {"name":"job1","url":"http://example.com/jenkins/job/job1/","color":"disabled"},' +
  '   {"name":"job2","url":"http://example.com/jenkins/job/job2/","color":"blue"}' +
  '  ],' +
  ' "overallLoad":{},' +
  ' "primaryView":{"name":"All","url":"http://example.com/jenkins/"},' +
  ' "quietingDown":false,' +
  ' "slaveAgentPort":0,' +
  ' "useCrumbs":false,' +
  ' "useSecurity":false,' +
  ' "views":[' +
  '   {"name":"All","url":"http://example.com/jenkins/"}' +
  ' ]' +
  '}';

// serial device settings
var serialDevice = "/dev/tty.usbserial-A6004op2";
var baudrate = 9600;

// url of build server
var url = "http://example.com/jenkins/";

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

  // create jenkins manager with mock http port
  var port = new MockHttpPort;
  var jenkins = new JenkinsManager;

  jenkins.setHttpPort(port);

  // set mock data
  port.data(httpData);

  // get status of jobs on build server
  if (jenkins.getStatus(url))
  {
    // get color of a job
    var color = jenkins.jobColor("job2");

    // blue indicates successful build
    if ((color === "blue") || (color === "blue_anime"))
    {
      led.setColor(1, colorOk);
    }
    else
    {
      led.setColor(1, colorError);
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
