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

#include "curriculumnrecord.h"
#include "curriculumnrecord_p.h"
#include "calendar.h"
#include "curriculumn.h"
#include "curriculumndisciplinegroup.h"
#include "curriculumndisciplinesubgroup.h"
#include "calendarcourse.h"
#include "constants.h"
#include "constantsfactory.h"
#include "chair.h"
#include "curriculumnsemester.h"
#include "curriculumncourse.h"

namespace KTU
    {
    CurriculumnCourse *CurriculumnRecordPrivate::createEntity() const
    {
        Q_Q(const CurriculumnRecord);
        return new CurriculumnCourse(const_cast<CurriculumnRecord *>(q));
    }

    void CurriculumnRecordPrivate::deleteEntity(CurriculumnCourse *entity) const
    {
        delete entity;
    }
//--------------------------------------------------------------------------------------
    CurriculumnRecord::CurriculumnRecord(CurriculumnDisciplineSubGroup *subGroup)
        : Entity(*new CurriculumnRecordPrivate, subGroup)
    {
        Q_D(CurriculumnRecord);
        d->chair = 0;
        d->discipline = 0;
        d->totalByPlan = 0.0;
        d->subGroup = subGroup;
        init();
    }

    CurriculumnRecord::CurriculumnRecord(quint64 number, CurriculumnDisciplineSubGroup *subGroup)
        : Entity(*new CurriculumnRecordPrivate, subGroup)
    {
        Q_D(CurriculumnRecord);
        d->chair = 0;
        d->discipline = 0;
        d->totalByPlan = 0.0;
        d->subGroup = subGroup;
        setId(number);
        init();
    }

    CurriculumnRecord::CurriculumnRecord(CurriculumnRecordPrivate &dd, CurriculumnDisciplineSubGroup *subGroup)
        : Entity(dd, subGroup)
    {
        Q_D(CurriculumnRecord);
        d->subGroup = subGroup;
    }

    CurriculumnRecord::~CurriculumnRecord()
    {

    }

    CurriculumnDisciplineSubGroup *CurriculumnRecord::subGroup() const
    {
        Q_D(const CurriculumnRecord);
        return d->subGroup;
    }

    void CurriculumnRecord::setChair(Chair *chair)
    {
        Q_D(CurriculumnRecord);
        if (d->chair == chair)
            return;
        d->chair = chair;
    }

    Chair *CurriculumnRecord::chair() const
    {
        Q_D(const CurriculumnRecord);
        return d->chair;
    }

    void CurriculumnRecord::setDiscipline(Discipline *discipline)
    {
        Q_D(CurriculumnRecord);
        d->discipline = discipline;
    }

    Discipline *CurriculumnRecord::discipline() const
    {
        Q_D(const CurriculumnRecord);
        return d->discipline;
    }

    void CurriculumnRecord::init()
    {
        Q_D(CurriculumnRecord);
        d->clear();

        if (!subGroup())
            return;

        Calendar *calendar = subGroup()->group()->curriculumn()->calendar();
        for (quint32 c = 1; c <= calendar->coursesCount(); ++c) {
            CalendarCourse *course = calendar->course(c);
            CurriculumnCourse *cc = d->addEntity();
            cc->init(course);
        }
    }

    CurriculumnCourse *CurriculumnRecord::course(quint32 number) const
    {
        Q_D(const CurriculumnRecord);
        return d->entity(number - 1);
    }

    QList<CurriculumnCourse *> CurriculumnRecord::courses() const
    {
        Q_D(const CurriculumnRecord);
        return d->entities;
    }

    CurriculumnSemester *CurriculumnRecord::semester(quint32 number) const
    {
        Q_D(const CurriculumnRecord);
        foreach (CurriculumnCourse *c, d->entities) {
            CurriculumnSemester *s = c->semester(number);
            if (s)
                return s;
        }
        return 0;
    }

    QList<CurriculumnSemester *> CurriculumnRecord::semesters() const
    {
        Q_D(const CurriculumnRecord);
        QList<CurriculumnSemester *> res;
        foreach (CurriculumnCourse *c, d->entities)
            res << c->semesters();
        return res;
    }

    qreal CurriculumnRecord::lectionsHours(quint32 number) const
    {
        return calculateSubTotal(number, &CurriculumnSemester::lectionsHours);
    }

    qreal CurriculumnRecord::labsHours(quint32 number) const
    {
        return calculateSubTotal(number, &CurriculumnSemester::labsHours);
    }

    qreal CurriculumnRecord::practicesHours(quint32 number) const
    {
        return calculateSubTotal(number, &CurriculumnSemester::practicesHours);
    }

    qreal CurriculumnRecord::kksHours(quint32 number) const
    {
        return calculateSubTotal(number, &CurriculumnSemester::kksHours);
    }

    qreal CurriculumnRecord::calculateSubTotal(quint32 number, qreal (CurriculumnSemester::*func)() const) const
    {
        CurriculumnSemester *s = semester(number);
        if (!s)
            return 0.0;
        return (s->*func)();
    }

    qreal CurriculumnRecord::lectionsHoursTotal() const
    {
        Q_D(const CurriculumnRecord);
        return d->lectionsHoursTotal();
    }

    qreal CurriculumnRecord::labsHoursTotal() const
    {
        Q_D(const CurriculumnRecord);
        return d->labsHoursTotal();
    }

    qreal CurriculumnRecord::practicesHoursTotal() const
    {
        Q_D(const CurriculumnRecord);
        return d->practicesHoursTotal();
    }

    qreal CurriculumnRecord::kksHoursTotal() const
    {
        Q_D(const CurriculumnRecord);
        return d->kksHoursTotal();
    }

    quint32 CurriculumnRecord::exams() const
    {
        Q_D(const CurriculumnRecord);
        return d->exams();
    }

    quint32 CurriculumnRecord::tests() const
    {
        Q_D(const CurriculumnRecord);
        return d->tests();
    }

    quint32 CurriculumnRecord::rs() const
    {
        Q_D(const CurriculumnRecord);
        return d->rs();
    }

    quint32 CurriculumnRecord::courseWorks() const
    {
        Q_D(const CurriculumnRecord);
        return d->courseWorks();
    }

    quint32 CurriculumnRecord::courseProjects() const
    {
        Q_D(const CurriculumnRecord);
        return d->courseProjects();
    }

    quint32 CurriculumnRecord::diffTests() const
    {
        Q_D(const CurriculumnRecord);
        return d->diffTests();
    }

    quint32 CurriculumnRecord::qualifications() const
    {
        Q_D(const CurriculumnRecord);
        return d->qualifications();
    }

    quint32 CurriculumnRecord::diploms() const
    {
        Q_D(const CurriculumnRecord);
        return d->diploms();
    }

    quint32 CurriculumnRecord::magisters() const
    {
        Q_D(const CurriculumnRecord);
        return d->magisters();
    }

    quint32 CurriculumnRecord::practices() const
    {
        Q_D(const CurriculumnRecord);
        return d->practices();
    }

    quint32 CurriculumnRecord::dimplomPractices() const
    {
        Q_D(const CurriculumnRecord);
        return d->dimplomPractices();
    }

    quint32 CurriculumnRecord::magisterPractices() const
    {
        Q_D(const CurriculumnRecord);
        return d->magisterPractices();
    }

    quint32 CurriculumnRecord::qualificationPractices() const
    {
        Q_D(const CurriculumnRecord);
        return d->qualificationPractices();
    }

    quint32 CurriculumnRecord::stateExams() const
    {
        Q_D(const CurriculumnRecord);
        return d->stateExams();
    }

    quint32 CurriculumnRecord::enterprisePractices() const
    {
        Q_D(const CurriculumnRecord);
        return d->enterprisePractices();
    }

    void CurriculumnRecord::setTotalByPlan(qreal hours)
    {
        Q_D(CurriculumnRecord);
        d->totalByPlan = hours;
    }

    qreal CurriculumnRecord::totalByPlan() const
    {
        Q_D(const CurriculumnRecord);
        return d->totalByPlan;
    }

    QDataStream &operator << (QDataStream &s, const CurriculumnRecord &r)
    {
        const quint64 chairId = r.d_func()->chair ? r.d_func()->chair->id() : 0;
        const quint64 disciplineId = r.d_func()->discipline ? r.d_func()->discipline->id() : 0;

        s << chairId;
        s << disciplineId;
        s << r.d_func()->totalByPlan;

        QList<CurriculumnSemester *> semesters = r.semesters();
        s << semesters.count();
        foreach (CurriculumnSemester *semester, semesters) {
            s << semester->number();
            s << (*semester);
        }

        return s;
    }

    QDataStream &operator >> (QDataStream &s, CurriculumnRecord &r)
    {
        quint64 chairId = 0;
        quint64 disciplineId = 0;

        s >> chairId;
        s >> disciplineId;

        r.d_func()->chair = constantsFactory.chair(chairId);
        r.d_func()->discipline = constantsFactory.discipline(disciplineId);

        s >> r.d_func()->totalByPlan;

        r.init();

        int semestersCount = 0;
        s >> semestersCount;
        for (int i = 0; i < semestersCount; ++i) {
            quint32 semesterNumber = 0;
            s >> semesterNumber;
            CurriculumnSemester *semester = r.semester(semesterNumber);
            Q_ASSERT(semester);
            if (!semester)
                continue;
            s >> (*semester);
        }

        return s;
    }
}
