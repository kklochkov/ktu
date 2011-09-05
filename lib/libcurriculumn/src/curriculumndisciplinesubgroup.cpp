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

#include "curriculumndisciplinesubgroup.h"
#include "curriculumndisciplinesubgroup_p.h"
#include "curriculumndisciplinegroup.h"
#include "curriculumnrecord.h"
#include "constants.h"

namespace KTU
{
    CurriculumnRecord *CurriculumnDisciplineSubGroupPrivate::createEntity() const
    {
        Q_Q(const CurriculumnDisciplineSubGroup);
        return new CurriculumnRecord(const_cast<CurriculumnDisciplineSubGroup *>(q));
    }

    void CurriculumnDisciplineSubGroupPrivate::deleteEntity(CurriculumnRecord *entity) const
    {
        delete entity;
    }
//--------------------------------------------------------------------------------------
    CurriculumnDisciplineSubGroup::CurriculumnDisciplineSubGroup(CurriculumnDisciplineGroup *group)
        : Entity(*new CurriculumnDisciplineSubGroupPrivate, group)
    {
        Q_D(CurriculumnDisciplineSubGroup);
        d->curriculumnGroup = 0;
        d->curriculumnDisciplineGroup = group;
    }

    CurriculumnDisciplineSubGroup::CurriculumnDisciplineSubGroup(CurriculumnDisciplineSubGroupPrivate &dd, CurriculumnDisciplineGroup *group)
        : Entity(dd, group)
    {
        Q_D(CurriculumnDisciplineSubGroup);
        d->curriculumnGroup = 0;
        d->curriculumnDisciplineGroup = group;
    }

    CurriculumnDisciplineSubGroup::~CurriculumnDisciplineSubGroup()
    {

    }

    void CurriculumnDisciplineSubGroup::setCurriculumnGroup(CurriculumnGroup *group)
    {
        Q_D(CurriculumnDisciplineSubGroup);
        d->curriculumnGroup = group;
    }

    CurriculumnGroup *CurriculumnDisciplineSubGroup::curriculumnGroup() const
    {
        Q_D(const CurriculumnDisciplineSubGroup);
        return d->curriculumnGroup;
    }

    CurriculumnDisciplineGroup *CurriculumnDisciplineSubGroup::group() const
    {
        Q_D(const CurriculumnDisciplineSubGroup);
        return d->curriculumnDisciplineGroup;
    }

    CurriculumnRecord *CurriculumnDisciplineSubGroup::addRecord()
    {
        Q_D(CurriculumnDisciplineSubGroup);
        return d->addEntity();
    }

    void CurriculumnDisciplineSubGroup::removeRecord(CurriculumnRecord *record)
    {
        Q_D(CurriculumnDisciplineSubGroup);
        d->removeEntity(record);
    }

    CurriculumnRecord *CurriculumnDisciplineSubGroup::record(int index) const
    {
        Q_D(const CurriculumnDisciplineSubGroup);
        return d->entity(index);
    }

    CurriculumnRecord *CurriculumnDisciplineSubGroup::record(Discipline *discipline) const
    {
        Q_D(const CurriculumnDisciplineSubGroup);
        return d->entityByConstant<Discipline>(discipline, &CurriculumnRecord::discipline);
    }

    QList<CurriculumnRecord *> CurriculumnDisciplineSubGroup::records() const
    {
        Q_D(const CurriculumnDisciplineSubGroup);
        return d->entities;
    }

    int CurriculumnDisciplineSubGroup::indexOf(CurriculumnRecord *record) const
    {
        Q_D(const CurriculumnDisciplineSubGroup);
        return d->indexOf(record);
    }

    qreal CurriculumnDisciplineSubGroup::calculateTotal(qreal (CurriculumnRecord::*func)() const) const
    {
        quint32 res = 0;
        foreach (CurriculumnRecord *record, records())
            res += (record->*func)();
        return res;
    }

    qreal CurriculumnDisciplineSubGroup::calculateTotal(quint32 number, qreal (CurriculumnRecord::*func)(quint32) const) const
    {
        quint32 res = 0;
        foreach (CurriculumnRecord *record, records())
            res += (record->*func)(number);
        return res;
    }

    qreal CurriculumnDisciplineSubGroup::totalByPlan() const
    {
        return calculateTotal(&CurriculumnRecord::totalByPlan);
    }

    qreal CurriculumnDisciplineSubGroup::ects() const
    {
        return calculateTotal(&CurriculumnRecord::ects);
    }

    qreal CurriculumnDisciplineSubGroup::individualWork() const
    {
        return calculateTotal(&CurriculumnRecord::individualWork);
    }

    qreal CurriculumnDisciplineSubGroup::lectionsHours(quint32 number) const
    {
        return calculateTotal(number, &CurriculumnRecord::lectionsHours);
    }

    qreal CurriculumnDisciplineSubGroup::labsHours(quint32 number) const
    {
        return calculateTotal(number, &CurriculumnRecord::labsHours);
    }

    qreal CurriculumnDisciplineSubGroup::practicesHours(quint32 number) const
    {
        return calculateTotal(number, &CurriculumnRecord::practicesHours);
    }

    qreal CurriculumnDisciplineSubGroup::kksHours(quint32 number) const
    {
        return calculateTotal(number, &CurriculumnRecord::kksHours);
    }

    qreal CurriculumnDisciplineSubGroup::lectionsHoursTotal() const
    {
        Q_D(const CurriculumnDisciplineSubGroup);
        return d->lectionsHoursTotal();
    }

    qreal CurriculumnDisciplineSubGroup::labsHoursTotal() const
    {
        Q_D(const CurriculumnDisciplineSubGroup);
        return d->labsHoursTotal();
    }

    qreal CurriculumnDisciplineSubGroup::practicesHoursTotal() const
    {
        Q_D(const CurriculumnDisciplineSubGroup);
        return d->practicesHoursTotal();
    }

    qreal CurriculumnDisciplineSubGroup::kksHoursTotal() const
    {
        Q_D(const CurriculumnDisciplineSubGroup);
        return d->kksHoursTotal();
    }

    quint32 CurriculumnDisciplineSubGroup::exams() const
    {
        Q_D(const CurriculumnDisciplineSubGroup);
        return d->exams();
    }

    quint32 CurriculumnDisciplineSubGroup::tests() const
    {
        Q_D(const CurriculumnDisciplineSubGroup);
        return d->tests();
    }

    quint32 CurriculumnDisciplineSubGroup::rs() const
    {
        Q_D(const CurriculumnDisciplineSubGroup);
        return d->rs();
    }

    quint32 CurriculumnDisciplineSubGroup::courseWorks() const
    {
        Q_D(const CurriculumnDisciplineSubGroup);
        return d->courseWorks();
    }

    quint32 CurriculumnDisciplineSubGroup::courseProjects() const
    {
        Q_D(const CurriculumnDisciplineSubGroup);
        return d->courseProjects();
    }

    quint32 CurriculumnDisciplineSubGroup::diffTests() const
    {
        Q_D(const CurriculumnDisciplineSubGroup);
        return d->diffTests();
    }

    quint32 CurriculumnDisciplineSubGroup::qualifications() const
    {
        Q_D(const CurriculumnDisciplineSubGroup);
        return d->qualifications();
    }

    quint32 CurriculumnDisciplineSubGroup::diploms() const
    {
        Q_D(const CurriculumnDisciplineSubGroup);
        return d->diploms();
    }

    quint32 CurriculumnDisciplineSubGroup::magisters() const
    {
        Q_D(const CurriculumnDisciplineSubGroup);
        return d->magisters();
    }

    quint32 CurriculumnDisciplineSubGroup::practices() const
    {
        Q_D(const CurriculumnDisciplineSubGroup);
        return d->practices();
    }

    quint32 CurriculumnDisciplineSubGroup::dimplomPractices() const
    {
        Q_D(const CurriculumnDisciplineSubGroup);
        return d->dimplomPractices();
    }

    quint32 CurriculumnDisciplineSubGroup::magisterPractices() const
    {
        Q_D(const CurriculumnDisciplineSubGroup);
        return d->magisterPractices();
    }

    quint32 CurriculumnDisciplineSubGroup::qualificationPractices() const
    {
        Q_D(const CurriculumnDisciplineSubGroup);
        return d->qualificationPractices();
    }

    quint32 CurriculumnDisciplineSubGroup::stateExams() const
    {
        Q_D(const CurriculumnDisciplineSubGroup);
        return d->stateExams();
    }

    quint32 CurriculumnDisciplineSubGroup::enterprisePractices() const
    {
        Q_D(const CurriculumnDisciplineSubGroup);
        return d->enterprisePractices();
    }
    //-----------------------------------------------------
    QDataStream &operator<<(QDataStream &s, const CurriculumnDisciplineSubGroup &sg)
    {
        QList<CurriculumnRecord *> records = sg.records();
        s << records.count();
        foreach (CurriculumnRecord *record, records)
            s << (*record);
        return s;
    }

    QDataStream &operator>>(QDataStream &s, CurriculumnDisciplineSubGroup &sg)
    {
        qint32 count = 0;
        s >> count;
        for (qint32 i = 0; i < count; ++i) {
            CurriculumnRecord *record = sg.addRecord();
            s >> (*record);
        }
        return s;
    }
}
