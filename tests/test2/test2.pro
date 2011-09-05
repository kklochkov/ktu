TARGET = test2

include($$PWD/../../ktu.pri)
include($$PWD/../../lib/libcurriculumn/libcurriculumn.pri)

CONFIG += console

QT -= gui
QT += sql

TEMPLATE = app
DEPENDPATH += . src
INCLUDEPATH += .

# Input
SOURCES += src/main.cpp \
    src/importer.cpp

LIBS += $$CURRICULUMN_LIB

HEADERS += \
    src/importer.h
