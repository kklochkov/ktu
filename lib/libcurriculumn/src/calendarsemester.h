/****************************************************************************
**
** Copyright (C) 2010 Kirill (spirit) Klochkov.
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

#ifndef CALENDARSEMESTER_H
#define CALENDARSEMESTER_H

#include <QDate>

#include "curriculumnentity.h"

namespace KTU
{
    class CalendarSemesterPrivate;
    class CalendarWeek;
    class CalendarCourse;
    class CalendarWeekSign;
    class Calendar;

    class CURRICULUMN_EXPORT CalendarSemester : public CurriculumnEntity
    {
        friend class Calendar;
        Q_DECLARE_PRIVATE(CalendarSemester)

    public:
        CalendarCourse *course() const;

        void setStartWeek(quint32 weekNumber);
        quint32 startWeek() const;

        void setWeeksInSemester(quint32 count);
        quint32 weeksInSemester() const;

        void setStartDate(const QDate &date);
        QDate startDate() const;
        QDate endDate() const;

        quint32 endWeek() const;

        CalendarWeek *week(quint32 weekNumber) const;
        QList<CalendarWeek *> weeks() const;

        void setDefaultWeekSign(CalendarWeekSign *sign);
        quint32 sum(CalendarWeekSign *sign) const;

        quint32 workWeeksCount() const;

        friend QDataStream &operator>>(QDataStream &s, CalendarSemester &cs);

    private:
        explicit CalendarSemester(CalendarCourse *course);
        CalendarSemester(quint32 number, CalendarCourse *course);
        CalendarSemester(CalendarSemesterPrivate &dd, CalendarCourse *course);
        ~CalendarSemester();

        void init();
    };

    CURRICULUMN_EXPORT QDataStream &operator>>(QDataStream &s, CalendarSemester &cs);
    CURRICULUMN_EXPORT QDataStream &operator<<(QDataStream &s, const CalendarSemester &cs);
}

#endif // CALENDARSEMESTER_H
