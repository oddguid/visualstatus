#
# Unit test for BaseHttpPort class
#

TARGET = testbasehttpport 

HEADERS = TestBaseHttpPort.h \
          ../../src/BaseHttpPort.h

SOURCES = TestBaseHttpPort.cpp \
          ../../src/BaseHttpPort.cpp

include(unittest.pri)

