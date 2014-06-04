MockJenkinsManager
==================

The _MockJenkinsManager_ object is a mock interface for a Jenkins manager. It implements the same functions as the _JenkinsManager_ object, but instead of retrieving the status of jobs from a Jenkins build server it reads the status from a file.

This object can be used in place to fake a Jenkins manager, which can be useful while developing scripts. One change is needed though when using a _MockJenkinsManager_ object: the URL must be changed to point to a local file. For example, given the following script:

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

Replacing _JenkinsManager_ with _MockJenkinsManager_ and changing the URL:

```javascript
// create mock manager
var manager = new MockJenkinsManager;
var port = new HttpPort;

manager.setHttpPort(port);

// get status of jobs
if (manager.get("/tmp/jobstatus.txt"))
{
  // get color of job
  var color = manager.jobColor("job");

  logger.log("color of job 'job' is " + color);
}
```

The file with the status of the jobs should have the following markup:
* one job status per line;
* each line should have the name (mandatory), url (optional), and color (optional) of a job;
* each line must have two separators (|);
* it is possible to define multiple jobs with the same name, but only the last occurrence in the file is used;
* the color should be one of the predefined colors. See the function _jobColor(jobName)_ for an overview.

Example file:

```
job1|http://example.com/job1|red
job2||blue_anime
job3||
```

Functions
---------

### MockJenkinsManager()

Constructs a new _MockJenkinsManager_ object.

```javascript
// create manager
var manager = new MockJenkinsManager;
```

### string error()

Returns the last saved error message, which is set when one of the other function returns false.

```javascript
var port = new HttpPort;
var manager = new MockJenkinsManager;

// set http port
manager.setHttpPort(port);

// get status of jobs
if (!manager.get("/tmp/jobstatus.txt"))
{
  // log error
  logger.logError(manager.error());
}
```

### bool getStatus(fileName)

Retrieves the status of the jobs from the given file. Returns true if the status of the jobs is successfully read and returns false if an error occurred.

```javascript
// create manager
var manager = new MockJenkinsManager;

// get status of jobs
var success = manager.get("/tmp/jobstatus.txt");
```

### Object job(jobName)

Returns the job with the given name. Returns NULL if the job was not found.

```javascript
var manager = new MockJenkinsManager;

if (manager.getStatus("/tmp/jobstatus.txt"))
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

Returns a list with the names of all jobs read when _get(fileName)_ was called.

```javascript
if (manager.get("/tmp/jobstatus.txt"))
{
  var names = manager.jobNames();
}
```

### Objectlist jobs()

Returns a list with all the jobs read when _get(fileName)_ was called.

```javascript
var manager = new MockJenkinsManager;

if (manager.getStatus("/tmp/jobstatus.txt"))
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

Sets the HTTP port to use, which can be an _HttpPort_ object or a _MockHttpPort_ object. The parameter has no effect since the HTTP port is not used.

```javascript
var port = new HttpPort;
var manager = new MockJenkinsManager;

// set http port
manager.setHttpPort(port);
```
