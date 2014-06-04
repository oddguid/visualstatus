JenkinsManager
==============

The _JenkinsManager_ object is used to retrieve the status of jobs on a Hudson or Jenkins build server using the JSON interface. It uses an _HttpPort_ (or _MockHttpPort_) object for HTTP communications.

```javascript
// create manager
var manager = new JenkinsManager;
var port = new HttpPort;

manager.setHttpPort(port);

// get status of jobs
if (manager.get("http://example.com/jenkins/"))
{
  // get color of job
  var color = manager.jobColor("job");

  logger.log("color of job 'job' is " + color);
}
```

Functions
---------

### JenkinsManager()

Constructs a new _JenkinsManager_ object.

```javascript
// create manager
var manager = new JenkinsManager;
```

### string error()

Returns the last saved error message, which is set when one of the other function returns false.

```javascript
var port = new HttpPort;
var manager = new JenkinsManager;

// set http port
manager.setHttpPort(port);

// get status of jobs
if (!manager.get("http://example.com/jenkins/"))
{
  // log error
  logger.logError(manager.error());
}
```

### bool getStatus(url)

Retrieves the status of the jobs from the build server at the given URL. Returns true if the status of the jobs is successfully retrieved and returns false if an error occurred.

The URL should point to the main page of the Jenkins build server and may include the path to it's JSON interface. For example, if the main page of Jenkins is at http://example.com/jenkins then either http://example.com/jenkins or http://example.com/jenkins/api/json can be used as the URL.

```javascript
// create manager
var manager = new JenkinsManager;
var port = new HttpPort;

manager.setHttpPort(port);

// get status of jobs
var success = manager.get("http://example.com:8080/jenkins/");
```

### Object job(jobName)

Returns the job with the given name. Returns NULL if the job was not found.

```javascript
var port = new HttpPort;
var manager = new JenkinsManager;

manager.setHttpPort(port);

if (manager.getStatus("http://example.com/jenkins/"))
{
  // get job
  var job = manager.job("job");

  // log name and color
  logger.log(job.name);
  logger.log(job.color)
}
```

### string jobColor(jobName)

Returns the color of the job with the given name. Returns an emptry string if the job was not found.

The color is not an actual RGB color, but rather a description of the orb as shown on the Jenkins main page. Possible values for the color are (taken from Jenkins XSD):

* red (failed)
* red_anime (failed in progress)
* yellow (unstable)
* yellow_anime (unstable in progress)
* blue (success)
* blue_anime (success in progress)
* grey (pending)
* grey_anime (pending in progress)
* disabled (disabled)
* disabled_anime (disabled in progress)
* aborted (aborted)
* aborted_anime (aborted in progress)
* notbuilt (not built)
* notbuilt_anime (not built in progress)

```javascript
var color = manager.jobColor("job");
```

### stringlist jobNames()

Returns a list with the names of all jobs retrieved from the build server when _get(url)_ was called.

```javascript
if (manager.get("http://example.com/jenkins/"))
{
  var names = manager.jobNames();
}
```

### Objectlist jobs()

Returns a list with all the jobs retrieved from the build server when _get(url)_ was called.

```javascript
var port = new HttpPort;
var manager = new JenkinsManager;

manager.setHttpPort(port);

if (manager.getStatus("http://example.com/jenkins/"))
{
  var jobs = manager.jobs();

  for (var i = 0; i < jobs.length; i++)
  {
    // log names and colors
    logger.log(jobs[i].name);
    logger.log(jobs[i].color);
  }
}
```

### string jobUrl(jobName)

Returns the URL of the job with the given name. Returns an empty string if the job was not found.

```javascript
var url = manager.jobUrl("job");
```

### setHttpPort(port)

Sets the HTTP port to use, which can be an _HttpPort_ object or a _MockHttpPort_ object.

```javascript
var port = new HttpPort;
var manager = new JenkinsManager;

// set http port
manager.setHttpPort(port);
```

