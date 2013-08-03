#
# Unit tests
#

TEMPLATE = subdirs

SUBDIRS += TestColor \
           TestJenkinsJob \
           TestJenkinsManager \
           TestLogLevel \
           TestLogger

TestColor.file = TestColor.pro
TestJenkinsJob.file = TestJenkinsJob.pro
TestJenkinsManager.file = TestJenkinsManager.pro
TestLogLevel.file = TestLogLevel.pro
TestLogger.file = TestLogger.pro
