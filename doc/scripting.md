Scripting
=========

Visualstatus uses QtScript as the scripting environment, which is based on ECMA script. 

Custom objects and functions have been added to allow easy communication with external systems like Hudson/Jenkins servers and serial ports.


Custom script objects
---------------------

The following custom objects are available in the scripting environment:

* [Logger](Logger.md), for logging.
* [Color](Color.md), for RGB colors.
* [QTimer](QTimer.md), for repetitive timers.
* [SerialPort](SerialPort.md), for serial port communications.
* [HttpPort](HttpPort.md), for simple HTTP communications.
* [JenkinsManager](JenkinsManager.md), for interfacing with a Hudson/Jenkins build server.
* [SerialLed](SerialLed.md), for LEDs connected to a serial port.
* [SerialLedBuffered](SerialLedBuffered.md), for LEDs connected to a serial port (buffered transfer).
* [MockSerialPort](MockSerialPort.md), for mocking a serial port.
* [MockHttpPort](MockHttpPort.md), for mocking an HTTP port.
* [MockJenkinsManager](MockJenkinsManager.md), for mocking a Hudson/Jenkins build server.

Global functions
----------------

### exit()

Ends the evaluation of the script and closes the application. 

Normally the application will keep running, even when evaluation of a script has ended. This is done to allow serial port connections to remain open, which is especially useful with Arduino ( an Arduino resets itself when the serial connection is closed). Calling the _exit()_ function will close the application and therefore close all serial port connections.

```javascript
var counter = 0;
var timer = new QTimer;

function timeout()
{
  if (++counter >= 10)
  {
    exit();
  }
}

timer.timeout.connect(timeout);
timer.start(500);
```
