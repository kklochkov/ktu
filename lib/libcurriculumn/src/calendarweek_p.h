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


#ifndef CALENDARWEEK_P_H
#define CALENDARWEEK_P_H

#include "entity_p.h"
#include "calendarweek.h"

namespace KTU
{
    class CalendarWeekPrivate : public EntityPrivate
    {
        Q_DECLARE_PUBLIC(CalendarWeek)

    public:
        QDate start;
        QDate end;
        CalendarWeekSign *sign;
        CalendarCourse *course;
    };
}

#endif // CALENDARWEEK_P_H
