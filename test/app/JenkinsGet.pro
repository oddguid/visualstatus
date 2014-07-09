#
# Application test for JenkinsManager
#

TARGET = jenkinsget 

HEADERS = ../../src/JenkinsJob.h \
          ../../src/BaseJenkinsManager.h \
          ../../src/JenkinsManager.h \
          ../../src/BaseHttpPort.h \
          ../../src/HttpPort.h

SOURCES = JenkinsGet.cpp \
          ../../src/JenkinsJob.cpp \
          ../../src/BaseJenkinsManager.cpp \
          ../../src/JenkinsManager.cpp \
          ../../src/BaseHttpPort.cpp \
          ../../src/HttpPort.cpp

include(apptest.pri)
