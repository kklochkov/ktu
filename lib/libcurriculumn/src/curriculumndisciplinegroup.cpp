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

#include "curriculumndisciplinegroup.h"
#include "curriculumndisciplinegroup_p.h"
#include "curriculumn.h"
#include "curriculumndisciplinesubgroup.h"
#include "constants.h"
#include "constantsfactory.h"

namespace KTU
{
    CurriculumnDisciplineSubGroup *CurriculumnDisciplineGroupPrivate::createEntity() const
    {
        Q_Q(const CurriculumnDisciplineGroup);
        return new CurriculumnDisciplineSubGroup(const_cast<CurriculumnDisciplineGroup *>(q));
    }


    void CurriculumnDisciplineGroupPrivate::deleteEntity(CurriculumnDisciplineSubGroup *entity) const
    {
        delete entity;
    }
//--------------------------------------------------------------------------------------
    CurriculumnDisciplineGroup::CurriculumnDisciplineGroup(Curriculumn *curriculumn)
        : Entity(*new CurriculumnDisciplineGroupPrivate, curriculumn)
    {
        Q_D(CurriculumnDisciplineGroup);
        d->curriculumnSection = 0;
        d->curriculumn = curriculumn;
    }

    CurriculumnDisciplineGroup::CurriculumnDisciplineGroup(CurriculumnDisciplineGroupPrivate &dd, Curriculumn *curriculumn)
        : Entity(dd, curriculumn)
    {
        Q_D(CurriculumnDisciplineGroup);
        d->curriculumnSection = 0;
        d->curriculumn = curriculumn;
    }

    CurriculumnDisciplineGroup::~CurriculumnDisciplineGroup()
    {

    }

    void CurriculumnDisciplineGroup::setCurriculumnSection(CurriculumnSection *section)
    {
        Q_D(CurriculumnDisciplineGroup);
        d->curriculumnSection = section;
    }

    CurriculumnSection *CurriculumnDisciplineGroup::curriculumnSection() const
    {
        Q_D(const CurriculumnDisciplineGroup);
        return d->curriculumnSection;
    }

    Curriculumn *CurriculumnDisciplineGroup::curriculumn() const
    {
        Q_D(const CurriculumnDisciplineGroup);
        return d->curriculumn;
    }

    CurriculumnDisciplineSubGroup *CurriculumnDisciplineGroup::addSubGroup(CurriculumnGroup *group)
    {
        Q_D(CurriculumnDisciplineGroup);
        CurriculumnDisciplineSubGroup *sg = d->addEntity();
        sg->setCurriculumnGroup(group);
        return sg;
    }

    void CurriculumnDisciplineGroup::removeSubGroup(CurriculumnDisciplineSubGroup *subGroup)
    {
        Q_D(CurriculumnDisciplineGroup);
        d->removeEntity(subGroup);
    }

    CurriculumnDisciplineSubGroup *CurriculumnDisciplineGroup::subGroup(int index) const
    {
        Q_D(const CurriculumnDisciplineGroup);
        return d->entity(index);
    }

    CurriculumnDisciplineSubGroup *CurriculumnDisciplineGroup::subGroup(CurriculumnGroup *subGroup) const
    {
        Q_D(const CurriculumnDisciplineGroup);
        return d->entityByConstant(subGroup, &CurriculumnDisciplineSubGroup::curriculumnGroup);
    }

    QList<CurriculumnDisciplineSubGroup *> CurriculumnDisciplineGroup::subGroups() const
    {
        Q_D(const CurriculumnDisciplineGroup);
        return d->entities;
    }

    int CurriculumnDisciplineGroup::indexOf(CurriculumnDisciplineSubGroup *subGroup) const
    {
        Q_D(const CurriculumnDisciplineGroup);
        return d->indexOf(subGroup);
    }

    bool CurriculumnDisciplineGroup::hasSubGroup(CurriculumnGroup *subGroup) const
    {
        Q_D(const CurriculumnDisciplineGroup);
        return d->hasEntity(subGroup, &CurriculumnDisciplineSubGroup::curriculumnGroup);
    }

    qreal CurriculumnDisciplineGroup::lectionsHoursTotal() const
    {
        Q_D(const CurriculumnDisciplineGroup);
        return d->lectionsHoursTotal();
    }

    qreal CurriculumnDisciplineGroup::labsHoursTotal() const
    {
        Q_D(const CurriculumnDisciplineGroup);
        return d->labsHoursTotal();
    }

    qreal CurriculumnDisciplineGroup::practicesHoursTotal() const
    {
        Q_D(const CurriculumnDisciplineGroup);
        return d->practicesHoursTotal();
    }

    qreal CurriculumnDisciplineGroup::kksHoursTotal() const
    {
        Q_D(const CurriculumnDisciplineGroup);
        return d->kksHoursTotal();
    }

    quint32 CurriculumnDisciplineGroup::exams() const
    {
        Q_D(const CurriculumnDisciplineGroup);
        return d->exams();
    }

    quint32 CurriculumnDisciplineGroup::tests() const
    {
        Q_D(const CurriculumnDisciplineGroup);
        return d->tests();
    }

    quint32 CurriculumnDisciplineGroup::rs() const
    {
        Q_D(const CurriculumnDisciplineGroup);
        return d->rs();
    }

    quint32 CurriculumnDisciplineGroup::courseWorks() const
    {
        Q_D(const CurriculumnDisciplineGroup);
        return d->courseWorks();
    }

    quint32 CurriculumnDisciplineGroup::courseProjects() const
    {
        Q_D(const CurriculumnDisciplineGroup);
        return d->courseProjects();
    }

    quint32 CurriculumnDisciplineGroup::diffTests() const
    {
        Q_D(const CurriculumnDisciplineGroup);
        return d->diffTests();
    }

    quint32 CurriculumnDisciplineGroup::qualifications() const
    {
        Q_D(const CurriculumnDisciplineGroup);
        return d->qualifications();
    }

    quint32 CurriculumnDisciplineGroup::diploms() const
    {
        Q_D(const CurriculumnDisciplineGroup);
        return d->diploms();
    }

    quint32 CurriculumnDisciplineGroup::magisters() const
    {
        Q_D(const CurriculumnDisciplineGroup);
        return d->magisters();
    }

    quint32 CurriculumnDisciplineGroup::practices() const
    {
        Q_D(const CurriculumnDisciplineGroup);
        return d->practices();
    }

    quint32 CurriculumnDisciplineGroup::dimplomPractices() const
    {
        Q_D(const CurriculumnDisciplineGroup);
        return d->dimplomPractices();
    }

    quint32 CurriculumnDisciplineGroup::magisterPractices() const
    {
        Q_D(const CurriculumnDisciplineGroup);
        return d->magisterPractices();
    }

    quint32 CurriculumnDisciplineGroup::qualificationPractices() const
    {
        Q_D(const CurriculumnDisciplineGroup);
        return d->qualificationPractices();
    }

    quint32 CurriculumnDisciplineGroup::stateExams() const
    {
        Q_D(const CurriculumnDisciplineGroup);
        return d->stateExams();
    }

    quint32 CurriculumnDisciplineGroup::enterprisePractices() const
    {
        Q_D(const CurriculumnDisciplineGroup);
        return d->enterprisePractices();
    }
    //-----------------------------------------------------
    QDataStream &operator<<(QDataStream &s, const CurriculumnDisciplineGroup &g)
    {
        QList<CurriculumnDisciplineSubGroup *> subGroups = g.subGroups();
        s << subGroups.count();
        foreach (CurriculumnDisciplineSubGroup *subGroup, subGroups) {
            s << subGroup->curriculumnGroup()->id();
            s << (*subGroup);
        }
        return s;
    }

    QDataStream &operator>>(QDataStream &s, CurriculumnDisciplineGroup &g)
    {
        qint32 count = 0;
        s >> count;
        for (qint32 i = 0; i < count; ++i) {
            quint64 id = 0;
            s >> id;
            CurriculumnGroup *group = constantsFactory.curriculumnGroup(id);
            if (!group)
                continue;
            CurriculumnDisciplineSubGroup *subGroup = g.addSubGroup(group);
            s >> (*subGroup);
        }
        return s;
    }
}
