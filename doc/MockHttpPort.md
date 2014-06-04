MockHttpPort
============

The _MockHttpPort_ object is a mock interface for HTTP connections. It implements the same functions as the _HttpPort_ object, but instead of retrieving the data at the given URL it returns prepared data.

This object can be used in place to fake an HTTP connection, which can be useful while developing scripts. For example, given the following script:

```javascript
// create http port
var port = new HttpPort;

// get data
if (port.get("http://example.com"))
{
  var data = port.data();
}
```

Replacing _HttpPort_ with _MockHttpPort_ requires only a change in the instantiation of the port variable:

```javascript
// create mock http port
var port = new MockHttpPort;

// get data
if (port.get("http://example.com"))
{
  var data = port.data();
}
```

The function _data(data)_ can be used to prepare the data that will be returned:

```javascript
// create mock http port
var port = new MockHttpPort;

// prepare data
port.data("<?xml version=\"1.0\" encoding=\"UTF-8\"?><root><field/></root>");

// get data
if (port.get("http://example.com"))
{
  // returns previously set xml data
  var data = port.data();
}
```

Functions
---------

### MockHttpPort()

Constructs a new _MockHttpPort_ object.

```javascript
// create http port
var port = new MockHttpPort;
```

### string data()

Returns the data that was prepared by the _data(data)_ call as a string.

```javascript
// create http port
var port = new MockHttpPort;

// prepare data
port.data("<?xml version=\"1.0\" encoding=\"UTF-8\"?><root><field/></root>");

// get data
if (port.get("http://example.com"))
{
  var data = port.data();
}
```

### data(data)

Sets the data that will be returned when _data()_ is called.

```javascript
// create http port
var port = MockHttpPort;

// prepare data
port.data("<?xml version=\"1.0\" encoding=\"UTF-8\"?><root><field/></root>");
```

### string error()

Returns the last saved error message, which is set when one of the other function returns false.

```javascript
var port = new MockHttpPort;

// get data
if (!port.get("http://example.com"))
{
  // log error
  logger.logError(port.error());
}
```

### bool get(url)

Retrieves the data at the given URL. The parameter has no effect and the function always returns true.

```javascript
// create http port
var port = new MockHttpPort;

// get data
var success = port.get("http://example.com");
```

### bool setAuthentication(user, password)

Sets the basic authentication properties for the HTTP connection and must be called before _get(url)_. The authentication properties are the user name and password. 
The parameters have no effect and the function always returns true.

```javascript
// set authentication
port.setAuthentication("user", "password");
```

### bool setProxy(user, password, host, port)

Sets the proxy properties for the HTTP connection and must be called before _get(url)_. The proxy properties are the user name, password, host and port. Use an empty host to disable the proxy properties.
The parameters have no effect and the function always returns true.

```javascript
// set proxy
port.setProxy("user", "password", "host", 8080);
```

### bool setTimeout(timeoutSecs)

Sets the timeout on the HTTP port in seconds. The parameter has no effect and the function always returns true.

```javascript
// set timeout
port.setTimeout(5);
```
