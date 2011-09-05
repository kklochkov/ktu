include($$PWD/../ktu.pri)

TEMPLATE = lib
CONFIG += dll

unix:CLEAN_FILES +=  $(DESTDIR)lib$(QMAKE_TARGET).*
win32:CLEAN_FILES +=  $(DESTDIR)$(QMAKE_TARGET).*

