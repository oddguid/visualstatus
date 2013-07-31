#
# Unit test for JenkinsJob class
#

TARGET = testjenkinsjob 

HEADERS = TestJenkinsJob.h \
          ../../src/JenkinsJob.h

SOURCES = TestJenkinsJob.cpp \
          ../../src/JenkinsJob.cpp

include(unittest.pri)
