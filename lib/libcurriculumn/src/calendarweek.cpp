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

#include "calendarweek.h"
#include "calendarweek_p.h"
#include "calendarweeksign.h"
#include "calendarsemester.h"
#include "calendarcourse.h"
#include "calendar.h"
#include "constantsfactory.h"

namespace KTU
{
    CalendarWeek::CalendarWeek(CalendarCourse *course)
        : CurriculumnEntity(*new CalendarWeekPrivate, course)
    {
        Q_D(CalendarWeek);
        d->sign = constantsFactory.emptyCalendarWeekSign();
        d->course = course;
    }

    CalendarWeek::CalendarWeek(quint32 number, CalendarCourse *course)
        : CurriculumnEntity(*new CalendarWeekPrivate, course)
    {
        Q_D(CalendarWeek);
        d->sign = constantsFactory.emptyCalendarWeekSign();
        d->course = course;
        setNumber(number);
    }

    CalendarWeek::CalendarWeek(CalendarWeekPrivate &dd, CalendarCourse *course)
        : CurriculumnEntity(dd, course)
    {
        Q_D(CalendarWeek);
        d->sign = course->calendar()->defaultWeekSign();
        d->course = course;
    }

    CalendarWeek::~CalendarWeek()
    {

    }

    void CalendarWeek::setStartDate(const QDate &date)
    {
        Q_D(CalendarWeek);
        d->start = date;
    }

    QDate CalendarWeek::startDate() const
    {
        Q_D(const CalendarWeek);
        return d->start;
    }

    void CalendarWeek::setEndDate(const QDate &date)
    {
        Q_D(CalendarWeek);
        d->end = date;
    }

    QDate CalendarWeek::endDate() const
    {
        Q_D(const CalendarWeek);
        return d->end;
    }

    void CalendarWeek::setSign(CalendarWeekSign *sign)
    {
        Q_D(CalendarWeek);
        d->sign = sign;
    }

    CalendarWeekSign *CalendarWeek::sign() const
    {
        Q_D(const CalendarWeek);
        return d->sign;
    }

    CalendarCourse *CalendarWeek::course() const
    {
        Q_D(const CalendarWeek);
        return d->course;
    }

    CalendarSemester *CalendarWeek::semester() const
    {
        Q_D(const CalendarWeek);
        return d->course->calendar()->semester(d->course->number(), number());
    }

    QDataStream &operator<<(QDataStream &s, const CalendarWeek &cw)
    {
        s << static_cast<const KTU::Entity &>(cw);
        s << cw.startDate();
        s << cw.endDate();
        s << cw.sign()->id();
        return s;
    }

    QDataStream &operator>>(QDataStream &s, CalendarWeek &cw)
    {
        s >> static_cast<KTU::Entity &>(cw);
        quint64 signId = 0;
        QDate start;
        QDate end;

        s >> start;
        s >> end;
        s >> signId;

        cw.setStartDate(start);
        cw.setEndDate(end);
        CalendarWeekSign *sign = constantsFactory.calendarWeekSign(signId);
        Q_ASSERT(sign);
        if (sign) {
            cw.setSign(sign);
        } else {
            qWarning() << Q_FUNC_INFO << QString("A sign with '%1' id coulnd't found").arg(signId);
        }
        return s;
    }
}
