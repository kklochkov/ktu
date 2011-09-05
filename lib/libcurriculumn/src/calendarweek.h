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

#ifndef CALENDARWEEK_H
#define CALENDARWEEK_H

#include <QDate>

#include "curriculumnentity.h"

namespace KTU
{
    class CalendarWeekPrivate;
    class CalendarWeekSign;
    class CalendarSemester;
    class CalendarCourse;
    class Calendar;

    class CURRICULUMN_EXPORT CalendarWeek : public CurriculumnEntity
    {
        friend class Calendar;
        friend class CalendarCourse;
        Q_DECLARE_PRIVATE(CalendarWeek)

    public:
        void setStartDate(const QDate &date);
        QDate startDate() const;

        void setEndDate(const QDate &date);
        QDate endDate() const;

        void setSign(CalendarWeekSign *sign);
        CalendarWeekSign *sign() const;

        CalendarCourse *course() const;
        CalendarSemester *semester() const;

        friend QDataStream &operator>>(QDataStream &s, CalendarWeek &cw);
        friend QDataStream &operator<<(QDataStream &s, const CalendarWeek &cw);

    private:
        explicit CalendarWeek(CalendarCourse *course);
        CalendarWeek(quint32 number, CalendarCourse *course);
        CalendarWeek(CalendarWeekPrivate &dd, CalendarCourse *course);
        ~CalendarWeek();
    };

    CURRICULUMN_EXPORT QDataStream &operator>>(QDataStream &s, CalendarWeek &cw);
    CURRICULUMN_EXPORT QDataStream &operator<<(QDataStream &s, const CalendarWeek &cw);
}

#endif // CALENDARWEEK_H
