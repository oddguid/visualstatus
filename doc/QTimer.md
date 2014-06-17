QTimer
======

The _QTimer_ object exposes the Qt QTimer class to the scripting environment, providing repetitive timers. 

```javascript
// create timer
var timer = new QTimer;

var counter = 0;

// called when timer signals a timeout
function timeoutFunction()
{
  logger.log("timeout!");

  if (++counter >= 10)
  {
    logger.log("done!");

    // stop timer
    timer.stop();
  }
}

// connect timeout signal to function
timer.timeout.connect(timeout);

// start timer with 1 second interval
timer.start(1000);
```

Functions
---------

### QTimer()

Constructs a new QTimer object.

```javascript
// create timer
var timer = new QTimer;
```

### start(timeoutMSecs)

Starts or restarts the timer with a timeout interval of timeoutMSecs milliseconds. If the timer is already running, it will be stopped and restarted.

```javascript
// start timer
timer.start(200);
```

### stop()

Stops the timer.

```javascript
// stop timer
timer.stop();
```

Signals
-------

### timeout()

Signal to indicate a timeout of the timer.

```javascript
// called when timer signals a timeout
function timeoutFunction()
{
  logger.log("timeout!");
}

// create timer
var timer = new QTimer;

// connect timeout signal to function
timer.timeout.connect(timeout);

// start timer with 1 second interval
timer.start(1000);
```
