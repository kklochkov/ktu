/****************************************************************************
**
** Copyright (C) 2011 Kirill (spirit) Klochkov.
** Contact: klochkov.kirill@gmail.com
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
****************************************************************************/


#ifndef CONSTANTSFACTORY_P_H
#define CONSTANTSFACTORY_P_H

#include "entityfactory_p.h"
#include "constantsfactory.h"

namespace KTU
{
    class ConstantsFactoryPrivate : public EntityFactoryPrivate
    {
        Q_DECLARE_PUBLIC(ConstantsFactory)
    public:
        CalendarWeekSign *defaultCalendarWeekSign;
        CalendarWeekSign *emptyCalendarWeekSign;
        QList<CalendarWeekSign *> workCalendarWeekSigns;
        QMap<quint64, CalendarWeekSign *> calendarWeekSigns;
        QMap<quint64, CurriculumnSection *> curriculumnSections;
        QMap<quint64, CurriculumnGroup *> curriculumnGroups;
        QMap<quint64, Discipline *> disciplines;
        QMap<quint64, University *> universities;
        QMap<quint64, Institute *> institutes;
        QMap<quint64, Department *> departments;
        QMap<quint64, EducationLevel *> educationLevels;
        EducationLevel *defaultEducationLevel;
        QMap<quint64, EducationForm *> educationForms;
        QMap<quint64, Chair *> chairs;
        QMap<quint64, Speciality *> specialities;
        QMap<quint64, Group *> groups;
        QMap<quint64, Curriculumn *> curriculumns;
    };
}

#endif // CONSTANTSFACTORY_P_H
