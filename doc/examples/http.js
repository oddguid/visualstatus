// http port
var port = new HttpPort;

// get page from example.com
if (port.get("http://example.com"))
{
  // log page
  logger.log(port.data());
}
else
{
  // error, log
  logger.logError(port.error());
}

exit();
