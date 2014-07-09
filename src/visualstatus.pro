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

INCLUDEPATH += .

HEADERS = serial/TimeoutSerial.h \
          Color.h \
          JenkinsJob.h \
          BaseJenkinsManager.h \
          JenkinsManager.h \
          MockJenkinsManager.h \
          LogLevel.h \
          Logger.h \
          BaseSerialPort.h \
          SerialPort.h \
          MockSerialPort.h \
          BaseHttpPort.h \
          MockHttpPort.h \
          HttpPort.h \
          BaseSerialObject.h \
          SerialLed.h \
          ScriptEngine.h \
          ScriptRunner.h \
          MainConsole.h \
          SerialLedBuffered.h

SOURCES = main.cpp \
          serial/TimeoutSerial.cpp \
          Color.cpp \
          JenkinsJob.cpp \
          BaseJenkinsManager.cpp \
          JenkinsManager.cpp \
          MockJenkinsManager.cpp \
          LogLevel.cpp \
          Logger.cpp \
          BaseSerialPort.cpp \
          SerialPort.cpp \
          MockSerialPort.cpp \
          BaseHttpPort.cpp \
          MockHttpPort.cpp \
          HttpPort.cpp \
          BaseSerialObject.cpp \
          SerialLed.cpp \
          ScriptEngine.cpp \
          ScriptRunner.cpp \
          MainConsole.cpp \
          SerialLedBuffered.cpp

