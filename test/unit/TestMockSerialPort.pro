#
# Unit test for MockSerialPort class
#

TARGET = testmockserialport 

HEADERS = TestMockSerialPort.h \
          ../../src/BaseSerialPort.h \
          ../../src/MockSerialPort.h

SOURCES = TestMockSerialPort.cpp \
          ../../src/BaseSerialPort.cpp \
          ../../src/MockSerialPort.cpp

include(unittest.pri)

