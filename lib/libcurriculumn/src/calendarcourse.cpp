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

#include <QDebug>
#include <QDate>

#include "calendarcourse.h"
#include "calendarcourse_p.h"
#include "calendarsemester.h"
#include "calendar.h"

namespace KTU
{
    CalendarCourse::CalendarCourse(Calendar *calendar)
        : CurriculumnEntity(*new CalendarCoursePrivate, calendar)
    {
        Q_D(CalendarCourse);
        d->calendar = calendar;
    }

    CalendarCourse::CalendarCourse(quint32 number, Calendar *calendar)
        : CurriculumnEntity(*new CalendarCoursePrivate, calendar)
    {
        Q_D(CalendarCourse);
        d->calendar = calendar;
        setNumber(number);
    }

    CalendarCourse::CalendarCourse(CalendarCoursePrivate &dd, Calendar *calendar)
        : CurriculumnEntity(dd, calendar)
    {
        Q_D(CalendarCourse);
        d->calendar = calendar;
    }

    CalendarCourse::~CalendarCourse()
    {

    }

    QDate CalendarCourse::adjustFirstWeek(QDate &start)
    {
        if (start.dayOfWeek() == Qt::Saturday || start.dayOfWeek() == Qt::Sunday)//skip weekends
            start = start.addDays((Qt::Sunday - start.dayOfWeek()) + 1);
        return start.addDays(Qt::Sunday - start.dayOfWeek());
    }

    Calendar *CalendarCourse::calendar() const
    {
        Q_D(const CalendarCourse);
        return d->calendar;
    }

    void CalendarCourse::setDate(const QDate &date)
    {
        QDate startOfSemester(date);
        const QList<CalendarSemester *> values = semesters();
        for (int i = 0; i < values.count(); ++i) {
            CalendarSemester *semester = values[i];
            semester->setStartDate(startOfSemester);
            startOfSemester = semester->endDate().addDays(1);
        }
    }

    CalendarWeek *CalendarCourse::week(quint32 weekNumber) const
    {
        Q_D(const CalendarCourse);
        return d->calendar->week(number(), weekNumber);
    }

    QList<CalendarWeek *> CalendarCourse::weeks() const
    {
        Q_D(const CalendarCourse);
        return d->calendar->weeks(number());
    }

    CalendarSemester *CalendarCourse::semester(quint32 semester) const
    {
        Q_D(const CalendarCourse);
        return d->calendar->semester(semester);
    }

    QList<CalendarSemester *> CalendarCourse::semesters() const
    {
        Q_D(const CalendarCourse);
        return d->calendar->semesters(number());
    }

    quint32 CalendarCourse::semestersCount() const
    {
        return semesters().count();
    }

    quint32 CalendarCourse::weeksCount() const
    {
        const quint32 res = weeks().count();
        if (res != calendar()->weeksCount())
            qDebug() << Q_FUNC_INFO << "error" << res << "!=" << calendar()->weeksCount();
        return res;
    }

    void CalendarCourse::setDefaultWeekSign(CalendarWeekSign *sign)
    {
        if (!sign)
            return;

        const  QList<CalendarSemester *> semesters = this->semesters();
        for (int i = 0; i < semesters.count(); ++ i)
            semesters[i]->setDefaultWeekSign(sign);
    }

    quint32 CalendarCourse::sum(CalendarWeekSign *sign) const
    {
        if (!sign)
            return 0;

        quint32 res = 0;
        const QList<CalendarSemester *> semesters = this->semesters();
        for (int i = 0; i < semesters.count(); ++ i)
            res += semesters[i]->sum(sign);
        return res;
    }

    quint32 CalendarCourse::workWeeksCount() const
    {
        quint32 res = 0;
        const QList<CalendarSemester *> semesters = this->semesters();
        for (int i = 0; i < semesters.count(); ++ i)
            res += semesters[i]->workWeeksCount();
        return res;
    }
}
