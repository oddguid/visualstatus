message("Common settings...")

# enable c++11
CONFIG += c++11

# win32
win32 {
  include(win32.pri)
}

# macx
macx {
  include(macx.pri)
}

# linux
unix:!macx {
  include(linux.pri)
}

