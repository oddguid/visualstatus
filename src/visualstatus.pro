#-------------------------------------------------------------------------------
# project created 2013-03-23
#-------------------------------------------------------------------------------

# set paths and libs
win32 {
  include(win32.pri)
}

macx {
  include(macx.pri)
}

TARGET = visualstatus
TEMPLATE = app

# use Qt gui, network, console and script
CONFIG += qt
CONFIG += console
QT += network
QT += script

INCLUDEPATH += .

# embed the manifest on windows + visual studio 2005
win32:win32-msvc2005 {
    CONFIG += embed_manifest_exe
    QMAKE_CLEAN += debug/*.intermediate.manifest
    QMAKE_CLEAN += release/*.intermediate.manifest
}

HEADERS = serial/TimeoutSerial.h \
          Color.h \
          JenkinsJob.h \
          BaseJenkinsManager.h \
          JenkinsManager.h

SOURCES = main.cpp \
          serial/TimeoutSerial.cpp \
          Color.cpp \
          JenkinsJob.cpp \
          BaseJenkinsManager.cpp \
          JenkinsManager.cpp
 
