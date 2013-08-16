#
# Unit test for MockJenkinsManager class
#

TARGET = testmockjenkinsmanager 

HEADERS = TestMockJenkinsManager.h \
          ../../src/JenkinsJob.h \
          ../../src/BaseJenkinsManager.h \
          ../../src/MockJenkinsManager.h

SOURCES = TestMockJenkinsManager.cpp \
          ../../src/JenkinsJob.cpp \
          ../../src/BaseJenkinsManager.cpp \
          ../../src/MockJenkinsManager.cpp

QT += network
include(../../src/common.pri)

include(unittest.pri)

