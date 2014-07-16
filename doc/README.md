Documentation
=============

Scripting
---------

The custom scripting objects and functions that visualstatus uses are described in [scripting](scripting.md). Some example scripts can be found in _examples_:

* [http.js](http.js), uses _HttpPort_ to fetch a web page.
* [jenkins_mockhttp.js](jenkins_mockhttp.js), uses _MockHttpPort_ to feed a _JenkinsManager_ prepared JSON data.
* [jenkins.js](jenkins.js), fetches the status of jobs from a build server.
* [led_all.js](led_all.js), sets colors of LEDs using _SerialLed_.
* [led.js](led.js), sets colors of LEDs using _SerialLed_.
* [mockjenkins.js](mockjenkins.js), reads the status of jobs from a file.
* [rainbow.js](rainbow.js), animates a rainbow using _SerialLedBuffered_.
* [timer.js](timer.js), simple timer.

Doxygen
-------

The source documentation can be build using doxygen. Use _doxysrc_ to generate HTML documentation:

```
doxygen doxysrc
```
