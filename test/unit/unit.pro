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

TestColor.file = TestColor.pro
TestJenkinsJob.file = TestJenkinsJob.pro
TestBaseJenkinsManager.file = TestBaseJenkinsManager.pro
TestJenkinsManager.file = TestJenkinsManager.pro
TestMockJenkinsManager.file = TestMockJenkinsManager.pro
TestLogLevel.file = TestLogLevel.pro
TestLogger.file = TestLogger.pro
TestMockSerialPort.file = TestMockSerialPort.pro
