message("Win32 settings...")

# define supported windows version (windows 7 and up)
DEFINES += "_WIN32_WINNT=0x0601"

# embed the manifest on windows (visual studio 2005 and up)
CONFIG += embed_manifest_exe

# qjson
CONFIG(debug, debug|release) {
  LIBS += qjson.lib
} else {
  LIBS += qjson.lib
}

# boost
CONFIG(debug, debug|release) {
  win32-msvc2013 {
    LIBS += libboost_system-vc120-mt-gd-1_55.lib \
            libboost_thread-vc120-mt-gd-1_55.lib \
            libboost_date_time-vc120-mt-gd-1_55.lib
  }
} else {
  win32-msvc2013 {
    LIBS += libboost_system-vc120-mt-1_55.lib \
            libboost_thread-vc120-mt-1_55.lib \
            libboost_date_time-vc120-mt-1_55.lib
  }
}

# curl
CONFIG(debug, debug|release) {
  LIBS += curllib.lib
} else {
  LIBS += curllib.lib
}
