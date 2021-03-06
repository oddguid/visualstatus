message("Mac X settings...")

INCLUDEPATH += /usr/local/include
QMAKE_LIBDIR += /usr/local/lib

# no app bundle
CONFIG -= app_bundle

# boost
CONFIG(debug, debug|release) {
  LIBS += -lboost_system-mt \
          -lboost_thread-mt \
          -lboost_date_time-mt
} else {
  LIBS += -lboost_system-mt \
          -lboost_thread-mt \
          -lboost_date_time-mt
}

# curl
CONFIG(debug, debug|release) {
  LIBS += -lcurl
} else {
  LIBS += -lcurl
}
