HttpPort
========

The _HttpPort_ object is used to retrieve data from a given URL. It is mostly used in conjunction with the _JenkinsManager_ object.

```javascript
// create http port
var port = new HttpPort;

// get data
if (port.get("http://example.com"))
{
  logger.log(port.data());
}
else
{
  // error getting data
  logger.logError(port.error());
}
```

Functions
---------

### HttpPort()

Constructs a new _HttpPort_ object.

```javascript
// create http port
var port = new HttpPort;
```

### string data()

Returns the data that was retrieved by the _get(url)_ call as a string.

```javascript
// create http port
var port = new HttpPort;

// get data
if (port.get("http://example.com"))
{
  var data = port.data();
}
```

### string error()

Returns the last saved error message, which is set when one of the other function returns false.

```javascript
var port = new HttpPort;

// get data
if (!port.get("http://example.com"))
{
  // log error
  logger.logError(port.error());
}
```

### bool get(url)

Retrieves the data at the given URL. Returns true if the data is successfully retrieved and returns false if an error occurred.

```javascript
// create http port
var port = new HttpPort;

// get data
var success = port.get("http://example.com");
```

### bool setAuthentication(user, password)

Sets the basic authentication properties for the HTTP connection and must be called before _get(url)_. The authentication properties are the user name and password. 
Returns true if the properties are successfully set and returns false if an error occurred.

```javascript
// set authentication
port.setAuthentication("user", "password");
```

### bool setProxy(user, password, host, port)

Sets the proxy properties for the HTTP connection and must be called before _get(url)_. The proxy properties are the user name, password, host and port. Use an empty host to disable the proxy properties.
Returns true if the properties are successfully set and returns false if an error occurred.

```javascript
// set proxy
port.setProxy("user", "password", "host", 8080);
```

### bool setTimeout(timeoutSecs)

Sets the timeout on the HTTP port in seconds. Returns true if the timeout is successfully set and returns false if an error occurred.

```javascript
// set timeout
port.setTimeout(5);
```
