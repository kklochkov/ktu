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
#include <QList>
#include <QDate>

#include "calendar.h"
#include "calendar_p.h"
#include "calendarcourse.h"
#include "curriculumn.h"
#include "constantsfactory.h"
#include "calendarsemester.h"
#include "calendarweek.h"

namespace KTU
{
    Calendar::Calendar(Curriculumn *curriculumn)
        : CurriculumnEntity(*new CalendarPrivate, curriculumn)
    {
        Q_D(Calendar);
        d->curriculumn = curriculumn;
        d->semestersInYear = 2;
        setNumber(curriculumn->number());
    }

    Calendar::Calendar(CalendarPrivate &dd, Curriculumn *curriculumn)
        : CurriculumnEntity(dd, curriculumn)
    {
        Q_D(Calendar);
        d->curriculumn = curriculumn;
    }

    Calendar::~Calendar()
    {

    }

    QString Calendar::name() const
    {
        return curriculumn()->name();
    }

    Curriculumn *Calendar::curriculumn() const
    {
        Q_D(const Calendar);
        return d->curriculumn;
    }

    void Calendar::setSemestersInYear(quint32 count)
    {
        Q_D(Calendar);
        d->semestersInYear = count;
        init();
    }

    quint32 Calendar::semestersInYear() const
    {
        Q_D(const Calendar);
        return d->semestersInYear;
    }

    void Calendar::setWorkCalendarWeekSigns(const QList<CalendarWeekSign *> &signs)
    {
        constantsFactory.setWorkCalendarWeekSigns(signs);
    }

    QList<CalendarWeekSign *> Calendar::workCalendarWeekSigns() const
    {
        return constantsFactory.workCalendarWeekSigns();
    }

    void Calendar::clear()
    {
        Q_D(Calendar);
        foreach (CalendarCourse *course, d->courses)
            delete course;
        d->courses.clear();

        foreach (CalendarSemester *semester, d->semesters)
            delete semester;
        d->semesters.clear();

        foreach (const QList<CalendarWeek *> &weeks, d->weeks) {
            foreach (CalendarWeek *week, weeks)
                delete week;
        }
        d->weeks.clear();
    }

    quint32 Calendar::weeksCount()
    {
        return 52;
    }

    void Calendar::init()
    {
        Q_D(Calendar);
        if (!curriculumn() || !curriculumn()->educationTerm())
            return;

        clear();

//        for (quint32 course = 1; course <= curriculumn()->educationTerm(); ++course) {
//            CalendarCourse *c = new CalendarCourse(course, this);
//            d->courses.insert(c->number(), c);
//            static const QDate staticDate(2008, 9, 1);//date for abstract calendar
//            QDate startOfSemester(staticDate);
//            quint32 semesterNumber = 1 + (c->number() - 1) * semestersInYear();
//            quint32 startWeek = 1;
//            for (quint32 i = 0; i < semestersInYear(); ++i) {
//                semesterNumber += i;
//                CalendarSemester *semester = new CalendarSemester(semesterNumber, c);
//                semester->setStartWeek(startWeek);
//                semester->setWeeksInSemester(qRound(weeksCount() / semestersInYear()));
//                semester->setStartDate(startOfSemester);
//                startWeek = semester->endWeek() + 1;
//                startOfSemester = semester->endDate().addDays(1);
//                d->semesters.insert(semester->number(), semester);

//                QDate startOfWeek(semester->startDate());
//                QDate endOfWeek(c->adjustFirstWeek(startOfWeek));
//                QList<CalendarWeek *> weeks;
//                for (quint32 weekNumber = 0; weekNumber < semester->weeksInSemester(); ++weekNumber) {
//                    CalendarWeek *week = new CalendarWeek(semester);
//                    week->setNumber(semester->startWeek() + weekNumber);
//                    week->setStartDate(startOfWeek);
//                    week->setEndDate(endOfWeek);

//                    startOfWeek = endOfWeek.addDays(1);
//                    endOfWeek = startOfWeek.addDays(6);
//                    weeks << week;
//                }
//                d->weeks.insert(course, weeks);
//            }
//        }

        static const QDate defaultDate(2008, 9, 1);//date for abstract calendar
        QDate startOfSemester = defaultDate;
        QDate startOfWeek = defaultDate;
        for (quint32 courseNumber = 1; courseNumber <= curriculumn()->educationTerm(); ++courseNumber) {
            CalendarCourse *course = new CalendarCourse(courseNumber, this);
            d->courses << course;

            startOfSemester = course->adjustFirstWeek(startOfSemester);
            startOfWeek = course->adjustFirstWeek(startOfWeek);

            //semesters creation
            quint32 semesterNumber = 1 + (course->number() - 1) * semestersInYear();
            quint32 startWeek = 1;
            for (quint32 i = 0; i < semestersInYear(); ++i) {
                semesterNumber += i;
                CalendarSemester *semester = new CalendarSemester(semesterNumber, course);
                d->semesters << semester;

                semester->setStartWeek(startWeek);
                semester->setWeeksInSemester(qRound(weeksCount() / semestersInYear()));
                semester->setStartDate(startOfSemester);
                startWeek = semester->endWeek() + 1;
                startOfSemester = semester->endDate().addDays(1);
            }

            //weeks creation
            QDate endOfWeek(course->adjustFirstWeek(startOfWeek));
            QList<CalendarWeek *> weeks;
            for (quint32 weekNumber = 1; weekNumber <= weeksCount(); ++weekNumber) {
                CalendarWeek *week = new CalendarWeek(weekNumber, course);
                weeks << week;

                week->setStartDate(startOfWeek);
                week->setEndDate(endOfWeek);

                startOfWeek = endOfWeek.addDays(1);
                endOfWeek = startOfWeek.addDays(6);
            }
            d->weeks << weeks;

            startOfSemester.setDate(startOfSemester.year() + 1, 9, 1);
            startOfWeek.setDate(startOfWeek.year() + 1, 9, 1);
        }
    }

    CalendarCourse *Calendar::course(quint32 course) const
    {
        Q_D(const Calendar);
        const int index = course - 1;
        if (index < 0 || index >= d->courses.count())
            return 0;
        return d->courses[index];
    }

    QList<CalendarCourse *> Calendar::courses() const
    {
        Q_D(const Calendar);
        return d->courses;
    }

    QList<CalendarSemester *> Calendar::semesters(quint32 course) const
    {
        QList<CalendarSemester *> res;
        quint32 semesterNumber = 1 + (course - 1) * semestersInYear();
        for (quint32 i = 0; i < semestersInYear(); ++i) {
            semesterNumber += i;
            CalendarSemester *semester = this->semester(semesterNumber);
            Q_ASSERT(semester);
            if (!semester)
                continue;
            res << semester;
        }
        return res;
    }

    QList<CalendarSemester *> Calendar::semesters() const
    {
        Q_D(const Calendar);
        return d->semesters;
    }

    CalendarSemester *Calendar::semester(quint32 semester) const
    {
        Q_D(const Calendar);
        const int index = semester - 1;
        if (index < 0 || index >= d->semesters.count())
            return 0;
        return d->semesters[index];
    }

    CalendarSemester *Calendar::semester(quint32 course, quint32 week) const
    {
        quint32 semesterNumber = 1 + (course - 1) * semestersInYear();
        for (quint32 i = 0; i < semestersInYear(); ++i) {
            semesterNumber += i;
            CalendarSemester *semester = this->semester(semesterNumber);
            Q_ASSERT(semester);
            if (!semester)
                continue;
            CalendarWeek *w = semester->week(week);
            if (w)
                return semester;
        }
        return 0;
    }

    CalendarWeek *Calendar::week(quint32 course, quint32 week) const
    {
        Q_D(const Calendar);
        int index = course - 1;
        if (index < 0 || index >= d->courses.count())
            return 0;
        const QList<CalendarWeek *> &weeks = d->weeks.at(index);
        index = week - 1;
        if (index < 0 || index >= weeks.count())
            return 0;
        return weeks[index];
    }

    QList<CalendarWeek *> Calendar::weeks(quint32 course) const
    {
        Q_D(const Calendar);
        const int index = course - 1;
        if (index < 0 || index >= d->weeks.count())
            return QList<CalendarWeek *>();
        return d->weeks[index];
    }

    void Calendar::setDefaultWeekSign(CalendarWeekSign *sign)
    {
        Q_D(Calendar);
        if (!sign)
            return;

        constantsFactory.setDefaultCalendarWeekSign(sign);
        foreach (CalendarCourse *course, d->courses)
            course->setDefaultWeekSign(sign);
    }

    CalendarWeekSign *Calendar::defaultWeekSign() const
    {
        return constantsFactory.defaultCalendarWeekSign();
    }

    quint32 Calendar::sum(quint32 course, CalendarWeekSign *sign) const
    {
        CalendarCourse *c = this->course(course);
        if (!c)
            return 0;
        return c->sum(sign);
    }

    quint32 Calendar::coursesCount() const
    {
        Q_D(const Calendar);
        return d->courses.count();
    }

    quint32 Calendar::semestersCount() const
    {
        if (!curriculumn())
            return 0;
        return semestersInYear() * curriculumn()->educationTerm();
    }

    QDataStream &Calendar::operator >> (QDataStream &s)
    {
        Q_D(Calendar);

        clear();
        s >> d->semestersInYear;

        int coursesCount = 0;
        s >> coursesCount;
        for (int i = 0; i < coursesCount; ++i) {
            quint32 courseNumber = 0;
            s >> courseNumber;

            CalendarCourse *course = new CalendarCourse(courseNumber, this);
            d->courses << course;

            int weeksCount = 0;
            s >> weeksCount;
            QList<CalendarWeek *> weeks;
            for (int j = 0; j < weeksCount; ++j) {
                quint32 weekNumber = 0;
                s >> weekNumber;

                CalendarWeek *week = new CalendarWeek(weekNumber, course);
                weeks << week;

                s >> (*week);
            }
            d->weeks << weeks;

            int semestersCount = 0;
            s >> semestersCount;
            for (int j = 0; j < semestersCount; ++j) {
                quint32 semesterNumber = 0;
                s >> semesterNumber;

                CalendarSemester *semester = new CalendarSemester(semesterNumber, course);
                d->semesters << semester;

                s >> (*semester);
            }
        }
        return s;
    }

    //-----------------------------------------------------
    QDataStream &operator << (QDataStream &s, const Calendar &c)
    {
        s << static_cast<const KTU::Entity &>(c);
        s << c.semestersInYear();

        QList<CalendarCourse *> courses = c.courses();
        s << courses.count();
        foreach (CalendarCourse *course, c.courses()) {
            s << course->number();

            QList<CalendarWeek *> weeks = course->weeks();
            s << weeks.count();
            foreach (CalendarWeek *week, weeks) {
                s << week->number();
                s << (*week);
            }

            QList<CalendarSemester *> semesters = course->semesters();
            s << semesters.count();
            foreach (CalendarSemester *semester, semesters) {
                s << semester->number();
                s << (*semester);
            }
        }

        return s;
    }

    QDataStream &operator >> (QDataStream &s, Calendar &c)
    {
        s >> static_cast<KTU::Entity &>(c);
        s >> c;
        return s;
    }
}
