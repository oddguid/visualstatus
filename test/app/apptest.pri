#
# General settings for test applications
#

TEMPLATE = app

# use Qt console, script.
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
