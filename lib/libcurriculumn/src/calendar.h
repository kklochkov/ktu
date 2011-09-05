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

#ifndef CALENDAR_H
#define CALENDAR_H

#include "curriculumnentity.h"
#include "nameinterface.h"

namespace KTU
{
    class CalendarPrivate;
    class CalendarCourse;
    class CalendarWeekSign;
    class CalendarWeek;
    class CalendarSemester;
    class Curriculumn;

    class CURRICULUMN_EXPORT Calendar : public CurriculumnEntity, public NameInterface
    {
        friend class Curriculumn;

        Q_DECLARE_PRIVATE(Calendar)

    public:
        QString name() const;

        Curriculumn *curriculumn() const;

        void clear();

        quint32 coursesCount() const;
        quint32 semestersCount() const;
        static quint32 weeksCount();

        CalendarCourse *course(quint32 course) const;
        QList<CalendarCourse *> courses() const;

        CalendarSemester *semester(quint32 semester) const;
        CalendarSemester *semester(quint32 course, quint32 week) const;
        QList<CalendarSemester *> semesters(quint32 course) const;
        QList<CalendarSemester *> semesters() const;

        CalendarWeek *week(quint32 course, quint32 week) const;
        QList<CalendarWeek *> weeks(quint32 course) const;

        void setSemestersInYear(quint32 count);
        quint32 semestersInYear() const;

        void setWorkCalendarWeekSigns(const QList<CalendarWeekSign *> &signs);
        QList<CalendarWeekSign *> workCalendarWeekSigns() const;

        void setDefaultWeekSign(CalendarWeekSign *sign);
        CalendarWeekSign *defaultWeekSign() const;

        quint32 sum(quint32 course, CalendarWeekSign *sign) const;

        QDataStream &operator>>(QDataStream &s);

        friend QDataStream &operator>>(QDataStream &s, Calendar &c);
        friend QDataStream &operator<<(QDataStream &s, const Calendar &c);

    private:
        explicit Calendar(Curriculumn *curriculumn);
        Calendar(CalendarPrivate &dd, Curriculumn *curriculumn);
        ~Calendar();

        void init();

        void setName(const QString &) { }
    };

    CURRICULUMN_EXPORT QDataStream &operator>>(QDataStream &s, Calendar &c);
    CURRICULUMN_EXPORT QDataStream &operator<<(QDataStream &s, const Calendar &c);
}

#endif // CALENDAR_H
