#
# Unit test for LogLevel functions
#

TARGET = testloglevel

HEADERS = TestLogLevel.h \
          ../../src/LogLevel.h

SOURCES = TestLogLevel.cpp \
          ../../src/LogLevel.cpp

include(unittest.pri)
