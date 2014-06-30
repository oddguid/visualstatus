Logger
======

The _Logger_ object can be used to write log messages to output and supports various log levels. It is a globally available object (_logger_) and does not need to be instantiated or assigned to a variable. It can be called directly in a script:

```javascript
logger.log("a log message");
```

## Functions

### void clear()

Clears the log. This does nothing when logging is done to stdout.

```javascript
logger.clear();
```

### void level(logLevel)

Sets the level of logging, messages above this level will be ignored. The supported log levels are (lowest to highest):

* Error
* Warning
* Info
* Debug

```javascript
logger.level("warning");
```

In this example messages with level _info_ or _debug_ will ignored, while messages with level _error_ or _warning_ will be written to output.

### void log(message)

Logs a message using the log level _info_.

```javascript
logger.log("a log message");
```

### void logDebug(message)

Logs a message using the log level _debug_.

```javascript
logger.logDebug("a debug message");
```

### void logError(message)

Logs a message using the log level _error_.

```javascript
logger.logError("an error message");
```

### void logInfo(message)

Logs a message using the log level _info_.

```javascript
logger.logInfo("an info message");
```

### void logWarning(message)

Logs a message using the log level _warning_.

```javascript
logger.logWarning("a warning message");
```
