message("Linux settings...")

# qjson
CONFIG(debug, debug|release) {
  LIBS += -lqjson
} else {
  LIBS += -lqjson
}

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