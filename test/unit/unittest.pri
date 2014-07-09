#
# General settings for unit test applications
#

TEMPLATE = app

# use Qt test, console, script.
CONFIG += qtestlib
CONFIG += console
CONFIG -= app_bundle
QT -= gui
QT += script

CONFIG += debug_and_release

INCLUDEPATH += .

DEPENDPATH += .

include(../../src/common.pri)

# output dirs and naming
CONFIG(debug, debug|release) {
  DESTDIR = ../../build/debug
} else {
  DESTDIR = ../../build/release
}
