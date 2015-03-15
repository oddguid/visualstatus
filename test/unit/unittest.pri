#
# General settings for unit test applications
#

TEMPLATE = app

# use Qt test, console, script.
CONFIG += console
CONFIG -= app_bundle
QT -= gui
QT += script
QT += testlib

CONFIG += debug_and_release

INCLUDEPATH += .

DEPENDPATH += .

include(../../src/common.pri)

# output dirs
CONFIG(debug, debug|release) {
  DESTDIR = ../../build/debug
} else {
  DESTDIR = ../../build/release
}
