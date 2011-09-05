TARGET = test1

include($$PWD/../../ktu.pri)
include($$PWD/../../lib/libcurriculumn/libcurriculumn.pri)

TEMPLATE = app
DEPENDPATH += . src
INCLUDEPATH += .

#QT += webkit

# Input
HEADERS += src/test.h \
    src/curriculumndialog.h \
    src/calendarwidget.h

FORMS += src/curriculumndialog.ui

SOURCES += src/main.cpp \
    src/test.cpp \
    src/curriculumndialog.cpp \
    src/calendarwidget.cpp

LIBS += $$CURRICULUMN_LIB
