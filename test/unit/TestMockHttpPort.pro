#
# Unit test for MockHttpPort class
#

TARGET = testmockhttpport 

HEADERS = TestMockHttpPort.h \
          ../../src/BaseHttpPort.h \
          ../../src/MockHttpPort.h

SOURCES = TestMockHttpPort.cpp \
          ../../src/BaseHttpPort.cpp \
          ../../src/MockHttpPort.cpp

include(unittest.pri)

