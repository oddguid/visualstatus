#
# Unit test for BaseSerialObject class
#

TARGET = testbaseserialobject

HEADERS = TestBaseSerialObject.h \
          ../../src/BaseSerialObject.h \
          ../../src/BaseSerialPort.h

SOURCES = TestBaseSerialObject.cpp \
          ../../src/BaseSerialObject.cpp \
          ../../src/BaseSerialPort.cpp

include(unittest.pri)

