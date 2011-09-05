TOP = $$PWD/../..

TARGET = $$qtLibraryTarget(curriculumn)

include($$TOP/lib/lib.pri)
include(libcurriculumn.pri)

contains(CONFIG, staticlib) {
    DEFINES += CURRICULUMN_STATICLIB
} else {
    DEFINES += CURRICULUMN_SHAREDLIB
}

win32 {
    DEFINES += CURRICULUMN_MAKEDLL
}

QT -= gui
QT += sql

installPath = /usr/local/lib/$$replace($$TARGET, \\., /)
target.path = $$installPath
INSTALLS += target

HEADERS += src/entity.h \
    src/entity_p.h \
    src/entityfactory.h \
    src/entityfactory_p.h \
    src/constant.h \
    src/calendar.h \
    src/calendar_p.h \
    src/calendarcourse.h \
    src/calendarcourse_p.h \
    src/calendarsemester.h \
    src/calendarsemester_p.h \
    src/calendarweek.h \
    src/calendarweek_p.h \
    src/calendarweeksign.h \
    src/curriculumn.h \
    src/curriculumn_p.h \
    src/curriculumndisciplinegroup.h \
    src/curriculumndisciplinegroup_p.h \
    src/curriculumndisciplinesubgroup.h \
    src/curriculumndisciplinesubgroup_p.h \
    src/curriculumnrecord.h \
    src/curriculumnrecord_p.h \
    src/constantsfactory.h \
    src/constantsfactory_p.h \
    src/constants.h \
    src/curriculumncalculableinterface.h \
    src/department.h \
    src/department_p.h \
    src/chair.h \
    src/speciality.h \
    src/speciality_p.h \
    src/curriculumnsemester.h \
    src/curriculumnsemester_p.h \
    src/curriculumncourse.h \
    src/curriculumncourse_p.h \
    src/nameinterface.h \
    src/shortnameinterface.h \
    src/numberinterface.h \
    src/curriculumnentity.h \
    src/chair_p.h \
    src/group.h \
    src/group_p.h \
    src/storage.h \
    src/institute.h \
    src/institute_p.h \
    src/university.h \
    src/university_p.h

SOURCES += src/calendar.cpp \
    src/calendarcourse.cpp \
    src/calendarsemester.cpp \
    src/calendarweek.cpp \
    src/calendarweeksign.cpp \
    src/curriculumn.cpp \
    src/entity.cpp \
    src/curriculumndisciplinegroup.cpp \
    src/curriculumndisciplinesubgroup.cpp \
    src/curriculumnrecord.cpp \
    src/constantsfactory.cpp \
    src/constants.cpp \
    src/entityfactory.cpp \
    src/constant.cpp \
    src/department.cpp \
    src/chair.cpp \
    src/speciality.cpp \
    src/curriculumnsemester.cpp \
    src/curriculumncourse.cpp \
    src/curriculumnentity.cpp \
    src/group.cpp \
    src/storage.cpp \
    src/institute.cpp \
    src/university.cpp
