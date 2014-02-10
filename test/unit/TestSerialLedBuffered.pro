#
# Unit test for SerialLedBuffered class
#

TARGET = testserialledbuffered

HEADERS = TestSerialLedBuffered.h \
          ../../src/SerialLedBuffered.h \
          ../../src/BaseSerialObject.h \
          ../../src/BaseSerialPort.h \
          ../../src/Color.h

SOURCES = TestSerialLedBuffered.cpp \
          ../../src/SerialLedBuffered.cpp \
          ../../src/BaseSerialObject.cpp \
          ../../src/BaseSerialPort.cpp \
          ../../src/Color.cpp

include(unittest.pri)

