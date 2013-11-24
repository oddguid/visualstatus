#
# Unit tests
#

TEMPLATE = subdirs

SUBDIRS += TestColor \
           TestJenkinsJob \
           TestBaseJenkinsManager \
           TestJenkinsManager \
           TestMockJenkinsManager \
           TestLogLevel \
           TestLogger \
           TestMockSerialPort \
           TestMockHttpPort \
           TestBaseHttpPort \
           TestBaseSerialPort \
           TestBaseSerialObject

TestColor.file = TestColor.pro
TestJenkinsJob.file = TestJenkinsJob.pro
TestBaseJenkinsManager.file = TestBaseJenkinsManager.pro
TestJenkinsManager.file = TestJenkinsManager.pro
TestMockJenkinsManager.file = TestMockJenkinsManager.pro
TestLogLevel.file = TestLogLevel.pro
TestLogger.file = TestLogger.pro
TestMockSerialPort.file = TestMockSerialPort.pro
TestMockHttpPort.file = TestMockHttpPort.pro
TestBaseHttpPort.file = TestBaseHttpPort.pro
TestBaseSerialPort.file = TestBaseSerialPort.pro
TestBaseSerialObject.file = TestBaseSerialObject.pro
