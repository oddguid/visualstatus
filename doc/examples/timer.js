var counter = 0;
var timer = new QTimer;

// called by timer
function timeout()
{
  logger.log("timeout!");

  if (++counter >= 10) 
  {
    logger.log("done!");
    exit();
  }
}

// connect function and start
timer.timeout.connect(timeout);
timer.start(500);
