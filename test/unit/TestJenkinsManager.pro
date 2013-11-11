#
# Unit test for JenkinsManager class
#

TARGET = testjenkinsmanager 

HEADERS = TestJenkinsManager.h \
          ../../src/JenkinsJob.h \
          ../../src/BaseJenkinsManager.h \
          ../../src/JenkinsManager.h \
          ../../src/BaseHttpPort.h \
          ../../src/HttpPort.h \
          ../../src/MockHttpPort.h

SOURCES = TestJenkinsManager.cpp \
          ../../src/JenkinsJob.cpp \
          ../../src/BaseJenkinsManager.cpp \
          ../../src/JenkinsManager.cpp \
          ../../src/BaseHttpPort.cpp \
          ../../src/HttpPort.cpp \
          ../../src/MockHttpPort.cpp

include(../../src/common.pri)

include(unittest.pri)

