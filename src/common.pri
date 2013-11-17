message("Common settings...")

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

