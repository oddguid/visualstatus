#
# Unit test for SerialLed class
#

TARGET = testserialled

HEADERS = TestSerialLed.h \
          ../../src/SerialLed.h \
          ../../src/BaseSerialObject.h \
          ../../src/BaseSerialPort.h \
          ../../src/Color.h

SOURCES = TestSerialLed.cpp \
          ../../src/SerialLed.cpp \
          ../../src/BaseSerialObject.cpp \
          ../../src/BaseSerialPort.cpp \
          ../../src/Color.cpp

include(unittest.pri)

