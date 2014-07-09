#
# Application test for HttpPort
#

TARGET = httpget 

HEADERS = ../../src/BaseHttpPort.h \
          ../../src/HttpPort.h

SOURCES = HttpGet.cpp \
          ../../src/BaseHttpPort.cpp \
          ../../src/HttpPort.cpp

include(apptest.pri)
