#
# Unit test for JenkinsManager class
#

TARGET = testjenkinsmanager 

HEADERS = TestJenkinsManager.h \
          ../../src/JenkinsJob.h \
          ../../src/BaseJenkinsManager.h \
          ../../src/JenkinsManager.h

SOURCES = TestJenkinsManager.cpp \
          ../../src/JenkinsJob.cpp \
          ../../src/BaseJenkinsManager.cpp \
          ../../src/JenkinsManager.cpp

QT += network
include(../../src/macx.pri)

include(unittest.pri)

