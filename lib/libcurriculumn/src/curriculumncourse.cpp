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

#include <QDebug>
#include "calendar.h"

#include "curriculumncourse.h"
#include "curriculumncourse_p.h"
#include "curriculumnrecord.h"
#include "calendarcourse.h"
#include "calendarsemester.h"
#include "curriculumnsemester.h"

namespace KTU
{
    CurriculumnSemester *CurriculumnCoursePrivate::createEntity() const
    {
        Q_Q(const CurriculumnCourse);
        return new CurriculumnSemester(const_cast<CurriculumnCourse *>(q));
    }


    void CurriculumnCoursePrivate::deleteEntity(CurriculumnSemester *entity) const
    {
        delete entity;
    }
//--------------------------------------------------------------------------------------
    CurriculumnCourse::CurriculumnCourse(CurriculumnRecord *parent)
        : Entity(*new CurriculumnCoursePrivate, parent)
    {
        Q_D(CurriculumnCourse);
        d->record = parent;
        d->course = 0;
    }

    CurriculumnCourse::CurriculumnCourse(CurriculumnCoursePrivate &dd, CurriculumnRecord *parent)
        : Entity(dd, parent)
    {

    }

    CurriculumnCourse::~CurriculumnCourse()
    {

    }

    quint32 CurriculumnCourse::number() const
    {
        Q_D(const CurriculumnCourse);
        if (!d->course)
            return 0;
        return d->course->number();
    }

    void CurriculumnCourse::init(CalendarCourse *course)
    {
        Q_D(CurriculumnCourse);
        d->course = course;
        d->clear();

        if (!d->course)
            return;

        foreach (CalendarSemester *semester, d->course->semesters()) {
            CurriculumnSemester *s = d->addEntity();
            s->setSemester(semester);
        }
    }

    CurriculumnSemester *CurriculumnCourse::semester(quint32 number) const
    {
        Q_D(const CurriculumnCourse);
        foreach (CurriculumnSemester *semester, d->entities) {
            if (semester->number() == number)
                return semester;
        }
        return 0;
    }

    QList<CurriculumnSemester *> CurriculumnCourse::semesters() const
    {
        Q_D(const CurriculumnCourse);
        return d->entities;
    }

    qreal CurriculumnCourse::lectionsHoursTotal() const
    {
        Q_D(const CurriculumnCourse);
        return d->lectionsHoursTotal();
    }

    qreal CurriculumnCourse::labsHoursTotal() const
    {
        Q_D(const CurriculumnCourse);
        return d->labsHoursTotal();
    }

    qreal CurriculumnCourse::practicesHoursTotal() const
    {
        Q_D(const CurriculumnCourse);
        return d->practicesHoursTotal();
    }

    qreal CurriculumnCourse::kksHoursTotal() const
    {
        Q_D(const CurriculumnCourse);
        return d->kksHoursTotal();
    }

    CurriculumnRecord *CurriculumnCourse::record() const
    {
        Q_D(const CurriculumnCourse);
        return d->record;
    }

    quint32 CurriculumnCourse::exams() const
    {
        Q_D(const CurriculumnCourse);
        return d->exams();
    }

    quint32 CurriculumnCourse::tests() const
    {
        Q_D(const CurriculumnCourse);
        return d->tests();
    }

    quint32 CurriculumnCourse::rs() const
    {
        Q_D(const CurriculumnCourse);
        return d->rs();
    }

    quint32 CurriculumnCourse::courseWorks() const
    {
        Q_D(const CurriculumnCourse);
        return d->courseWorks();
    }

    quint32 CurriculumnCourse::courseProjects() const
    {
        Q_D(const CurriculumnCourse);
        return d->courseProjects();
    }

    quint32 CurriculumnCourse::diffTests() const
    {
        Q_D(const CurriculumnCourse);
        return d->diffTests();
    }

    quint32 CurriculumnCourse::qualifications() const
    {
        Q_D(const CurriculumnCourse);
        return d->qualifications();
    }

    quint32 CurriculumnCourse::diploms() const
    {
        Q_D(const CurriculumnCourse);
        return d->diploms();
    }

    quint32 CurriculumnCourse::magisters() const
    {
        Q_D(const CurriculumnCourse);
        return d->magisters();
    }

    quint32 CurriculumnCourse::practices() const
    {
        Q_D(const CurriculumnCourse);
        return d->practices();
    }

    quint32 CurriculumnCourse::dimplomPractices() const
    {
        Q_D(const CurriculumnCourse);
        return d->dimplomPractices();
    }

    quint32 CurriculumnCourse::magisterPractices() const
    {
        Q_D(const CurriculumnCourse);
        return d->magisterPractices();
    }

    quint32 CurriculumnCourse::qualificationPractices() const
    {
        Q_D(const CurriculumnCourse);
        return d->qualificationPractices();
    }

    quint32 CurriculumnCourse::stateExams() const
    {
        Q_D(const CurriculumnCourse);
        return d->stateExams();
    }

    quint32 CurriculumnCourse::enterprisePractices() const
    {
        Q_D(const CurriculumnCourse);
        return d->enterprisePractices();
    }
}
