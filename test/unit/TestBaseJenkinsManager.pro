#
# Unit test for BaseJenkinsManager class
#

TARGET = testbasejenkinsmanager 

HEADERS = TestBaseJenkinsManager.h \
          ../../src/JenkinsJob.h \
          ../../src/BaseJenkinsManager.h

SOURCES = TestBaseJenkinsManager.cpp \
          ../../src/JenkinsJob.cpp \
          ../../src/BaseJenkinsManager.cpp

include(unittest.pri)

