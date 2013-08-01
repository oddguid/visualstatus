#
# Unit tests
#

TEMPLATE = subdirs

SUBDIRS += TestColor \
           TestJenkinsJob \
           TestJenkinsManager

TestColor.file = TestColor.pro
TestJenkinsJob.file = TestJenkinsJob.pro
TestJenkinsManager.file = TestJenkinsManager.pro
