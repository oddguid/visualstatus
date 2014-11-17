#-------------------------------------------------------------------------------
# project created 2013-03-23
#-------------------------------------------------------------------------------

# set paths and libs
include(common.pri)

TARGET = visualstatus
TEMPLATE = app

# use Qt gui, network, console and script
CONFIG += qt
CONFIG += console
QT += network
QT += script

CONFIG += debug_and_release

# output dirs
CONFIG(debug, debug|release) {
  DESTDIR = ../build/debug
} else {
  DESTDIR = ../build/release
}

INCLUDEPATH += .

HEADERS = serial/TimeoutSerial.h \
          BaseHttpPort.h \
          BaseJenkinsManager.h \
          BaseSerialObject.h \
          BaseSerialPort.h \
          Color.h \
          HttpPort.h \
          JenkinsJob.h \
          JenkinsManager.h \
          Logger.h \
          LogLevel.h \
          MainConsole.h \
          MockHttpPort.h \
          MockJenkinsManager.h \
          MockSerialPort.h \
          ScriptEngine.h \
          ScriptRunner.h \
          SerialLed.h \
          SerialLedBuffered.h \
          SerialPort.h

SOURCES = serial/TimeoutSerial.cpp \
          BaseHttpPort.cpp \
          BaseJenkinsManager.cpp \
          BaseSerialObject.cpp \
          BaseSerialPort.cpp \
          Color.cpp \
          HttpPort.cpp \
          JenkinsJob.cpp \
          JenkinsManager.cpp \
          Logger.cpp \
          LogLevel.cpp \
          main.cpp \
          MainConsole.cpp \
          MockHttpPort.cpp \
          MockJenkinsManager.cpp \
          MockSerialPort.cpp \
          ScriptEngine.cpp \
          ScriptRunner.cpp \
          SerialLed.cpp \
          SerialLedBuffered.cpp \
          SerialPort.cpp
