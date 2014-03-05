visualstatus
============

Visualstatus is a project that makes it possible to output the status of jobs on a build server (Hudson, Jenkins) to serially attached LEDs.

Though it's primary focus is build jobs and LEDs, other inputs and outputs are also supported. This is made possible by using Javascript files combined with custom objects.

Simple example
--------------

Here is a simple Javascript file that retrieves the status of a build job and outputs this to a LED:

```javascript
// serial device settings
var serialDevice = "/dev/tty.usbserial-A6004op2";
var baudrate = 9600;

// url of hudson build server
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

  // create jenkins/hudson manager
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
}
```

This script can be executed with the following command:

```
visualstatus script.js
```

Building
--------

Visualstatus depends on the following software:

* [Qt](http://qt-project.org), version 4.8.5 is used for development.
* [qjson](http://qjson.sourceforge.net)
* [boost](http://www.boost.org), for ASIO
* [libcurl](http://curl.haxx.se/libcurl)
* [curlpp](http://code.google.com/p/curlpp)
* [TimeoutSerial](https://gitorious.org/serial-port), a copy is included in this repository.

Build steps, assuming all dependencies are available:

1. qmake
2. make or nmake

