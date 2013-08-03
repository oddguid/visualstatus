#
# Unit test for Logger class
#

TARGET = testlogger 

HEADERS = TestLogger.h \
          ../../src/LogLevel.h \
          ../../src/Logger.h

SOURCES = TestLogger.cpp \
          ../../src/LogLevel.cpp \
          ../../src/Logger.cpp

include(unittest.pri)
