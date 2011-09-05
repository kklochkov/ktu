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

#include "calendarsemester.h"
#include "calendarsemester_p.h"
#include "calendarweek.h"
#include "calendarcourse.h"
#include "calendarweeksign.h"
#include "calendar.h"

namespace KTU
{
    CalendarSemester::CalendarSemester(CalendarCourse *course)
        : CurriculumnEntity(*new CalendarSemesterPrivate, course)
    {
        Q_D(CalendarSemester);
        d->startWeek = 0;
        d->weeksInSemester = 0;
        d->course = course;
    }

    CalendarSemester::CalendarSemester(quint32 number, CalendarCourse *course)
        : CurriculumnEntity(*new CalendarSemesterPrivate, course)
    {
        Q_D(CalendarSemester);
        d->startWeek = 0;
        d->weeksInSemester = 0;
        d->course = course;
        setNumber(number);
    }

    CalendarSemester::CalendarSemester(CalendarSemesterPrivate &dd, CalendarCourse *course)
        : CurriculumnEntity(dd, course)
    {
        Q_D(CalendarSemester);
        d->startWeek = 0;
        d->weeksInSemester = 0;
        d->course = course;
    }

    CalendarSemester::~CalendarSemester()
    {

    }

    void CalendarSemester::init()
    {
        CalendarSemester *nextSemester = course()->semester(number() + 1);
        if (!nextSemester)
            return;
        nextSemester->setStartWeek(endWeek() + 1);
    }

    CalendarWeek *CalendarSemester::week(quint32 weekNumber) const
    {
        Q_D(const CalendarSemester);
        if (startWeek() >= weekNumber && endWeek() <= weekNumber)
            return d->course->week(weekNumber);
        return 0;
    }

    QList<CalendarWeek *> CalendarSemester::weeks() const
    {
        Q_D(const CalendarSemester);
        return d->course->weeks().mid(d->startWeek - 1, weeksInSemester());
    }

    CalendarCourse *CalendarSemester::course() const
    {
        Q_D(const CalendarSemester);
        return d->course;
    }

    void CalendarSemester::setStartWeek(quint32 weekNumber)
    {
        Q_D(CalendarSemester);
        d->startWeek = weekNumber;
        init();
    }

    quint32 CalendarSemester::startWeek() const
    {
        Q_D(const CalendarSemester);
        return d->startWeek;
    }

    void CalendarSemester::setWeeksInSemester(quint32 count)
    {
        Q_D(CalendarSemester);
        d->weeksInSemester = count;
        init();
    }

    quint32 CalendarSemester::weeksInSemester() const
    {
        Q_D(const CalendarSemester);
        return d->weeksInSemester;
    }

    quint32 CalendarSemester::endWeek() const
    {
        Q_D(const CalendarSemester);
        return (d->startWeek + d->weeksInSemester) - 1;
    }

    void CalendarSemester::setStartDate(const QDate &date)
    {
        Q_D(CalendarSemester);
        d->startDate = date;

        QDate startOfWeek(date);
        QDate endOfWeek(course()->adjustFirstWeek(startOfWeek));
        QList<CalendarWeek *> weeks = this->weeks();
        for (int i = 0; i < weeks.count(); ++i) {
            CalendarWeek *week = weeks[i];
            week->setStartDate(startOfWeek);
            week->setEndDate(endOfWeek);

            startOfWeek = endOfWeek.addDays(1);
            endOfWeek = startOfWeek.addDays(6);
        }
    }

    QDate CalendarSemester::startDate() const
    {
        Q_D(const CalendarSemester);
        return d->startDate;
    }

    QDate CalendarSemester::endDate() const
    {
        return startDate().addDays(weeksInSemester() * 7);
    }

    void CalendarSemester::setDefaultWeekSign(CalendarWeekSign *sign)
    {
        if (!sign)
            return;

        QList<CalendarWeek *> weeks = this->weeks();
        for (int i = 0; i < weeks.count(); ++i)
            weeks[i]->setSign(sign);
    }

    quint32 CalendarSemester::sum(CalendarWeekSign *sign) const
    {
        if (!sign)
            return 0;

        quint32 res = 0;
        QList<CalendarWeek *> weeks = this->weeks();
        for (int i = 0; i < weeks.count(); ++i) {
            CalendarWeekSign *s = weeks[i]->sign();
            if (*s == *sign)
                ++res;
        }

        return res;
    }

    quint32 CalendarSemester::workWeeksCount() const
    {
        if (!course() || !course()->calendar())
            return 0;
        quint32 res = 0;
        foreach (CalendarWeekSign *sign, course()->calendar()->workCalendarWeekSigns())
            res += sum(sign);
        return res;
    }

    QDataStream &operator>>(QDataStream &s, CalendarSemester &cs)
    {
        s >> static_cast<KTU::Entity &>(cs);
        s >> cs.d_func()->startWeek;
        s >> cs.d_func()->weeksInSemester;
        s >> cs.d_func()->startDate;
        cs.init();
        return s;
    }

    QDataStream &operator<<(QDataStream &s, const CalendarSemester &cs)
    {
        s << static_cast<const KTU::Entity &>(cs);
        s << cs.startWeek();
        s << cs.weeksInSemester();
        s << cs.startDate();
        return s;
    }
}
