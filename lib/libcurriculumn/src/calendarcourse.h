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

#ifndef CALENDARCOURSE_H
#define CALENDARCOURSE_H

#include "curriculumnentity.h"

namespace KTU
{
    class CalendarCoursePrivate;
    class CalendarWeekSign;
    class CalendarWeek;
    class CalendarSemester;
    class Calendar;

    class CURRICULUMN_EXPORT CalendarCourse : public CurriculumnEntity
    {
        friend class Calendar;
        Q_DECLARE_PRIVATE(CalendarCourse)

    public:
        Calendar *calendar() const;

        /// Sets course start date, usually it's 1th of September. By default 1.09.2008 is used.
        void setDate(const QDate &date);

        CalendarWeek *week(quint32 weekNumber) const;
        QList<CalendarWeek *> weeks() const;

        CalendarSemester *semester(quint32 semester) const;
        QList<CalendarSemester *> semesters() const;

        quint32 semestersCount() const;
        quint32 weeksCount() const;

        void setDefaultWeekSign(CalendarWeekSign *sign);
        quint32 sum(CalendarWeekSign *sign) const;

        quint32 workWeeksCount() const;

        static QDate adjustFirstWeek(QDate &start);

    private:
        explicit CalendarCourse(Calendar *calendar);
        CalendarCourse(quint32 number, Calendar *calendar);
        CalendarCourse(CalendarCoursePrivate &dd, Calendar *calendar);
        ~CalendarCourse();
    };
}

//Q_DECLARE_METATYPE(KTU::CalendarCourse);

#endif // CALENDARCOURSE_H
