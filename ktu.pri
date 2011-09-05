CONFIG += qt warn_on release

DESTDIR = $$PWD/bin
QMAKE_LIBDIR += $$PWD/bin

CONFIG(debug, debug|release) {
    MOC_DIR = tmp/debug/moc
    OBJECTS_DIR = tmp/debug/obj
    UI_DIR = tmp/debug/ui
    RCC_DIR = tmp/debug/rcc
} else {
    MOC_DIR = tmp/release/moc
    OBJECTS_DIR = tmp/release/obj
    UI_DIR = tmp/release/ui
    RCC_DIR = tmp/release/rcc
}

TARGET = $$qtLibraryTarget($$TARGET)
