#
# Unit test for BaseSerialPort class
#

TARGET = testbaseserialport 

HEADERS = TestBaseSerialPort.h \
          ../../src/BaseSerialPort.h

SOURCES = TestBaseSerialPort.cpp \
          ../../src/BaseSerialPort.cpp

include(unittest.pri)

