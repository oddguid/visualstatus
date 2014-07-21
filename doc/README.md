Documentation
=============

Scripting
---------

The custom scripting objects and functions that visualstatus uses are described in [scripting](scripting.md). Some example scripts can be found in _examples_:

* [http.js](examples/http.js), uses _HttpPort_ to fetch a web page.
* [jenkins_mockhttp.js](examples/jenkins_mockhttp.js), uses _MockHttpPort_ to feed a _JenkinsManager_ prepared JSON data.
* [jenkins.js](examples/jenkins.js), fetches the status of jobs from a build server.
* [led_all.js](examples/led_all.js), sets colors of LEDs using _SerialLed_.
* [led.js](examples/led.js), sets colors of LEDs using _SerialLed_.
* [mockjenkins.js](examples/mockjenkins.js), reads the status of jobs from a file.
* [rainbow.js](examples/rainbow.js), animates a rainbow using _SerialLedBuffered_.
* [timer.js](examples/timer.js), simple timer.

Doxygen
-------

The source documentation can be build using doxygen. Use _doxysrc_ to generate HTML documentation:

```
doxygen doxysrc
```
