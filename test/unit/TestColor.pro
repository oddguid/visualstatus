#
#
#

TEMPLATE = app
TARGET = testcolor 

# use Qt test
CONFIG += qtestlib
CONFIG += console
CONFIG -= app_bundle
QT -= gui
QT += script

CONFIG += debug_and_release

INCLUDEPATH += .

DEPENDPATH += .

# embed the manifest on win32 + vs2005
win32:win32-msvc2005 {
  CONFIG += embed_manifest_exe
  QMAKE_CLEAN += debug/*.intermediate.manifest
  QMAKE_CLEAN += release/*.intermediate.manifest
}

CONFIG(debug, debug|release) {
  DESTDIR = ../../build/debug

  mac: TARGET = $$join(TARGET,,,_debug)
  win32: TARGET = $$join(TARGET,,,d)
} else {
  DESTDIR = ../../build/release
}

HEADERS = TestColor.h \
          ../../src/Color.h

SOURCES = TestColor.cpp \
          ../../src/Color.cpp
