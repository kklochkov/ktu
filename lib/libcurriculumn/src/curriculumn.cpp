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

#include "curriculumn.h"
#include "curriculumn_p.h"
#include "calendar.h"
#include "curriculumndisciplinegroup.h"
#include "constants.h"
#include "constantsfactory.h"
#include "speciality.h"
#include "department.h"
#include "chair.h"

namespace KTU
{
    CurriculumnDisciplineGroup *CurriculumnPrivate::createEntity() const
    {
        Q_Q(const Curriculumn);
        return new CurriculumnDisciplineGroup(const_cast<Curriculumn *>(q));
    }

    void CurriculumnPrivate::deleteEntity(CurriculumnDisciplineGroup *entity) const
    {
        delete entity;
    }
//--------------------------------------------------------------------------------------
    Curriculumn::Curriculumn(Entity *parent)
        : CurriculumnEntity(*new CurriculumnPrivate, parent)
    {
        Q_D(Curriculumn);
        d->chair = 0;
        d->department = 0;
        d->educationForm = 0;
        d->calendar = new Calendar(this);
        d->educationTerm = 0;
    }

    Curriculumn::Curriculumn(quint32 number, Entity *parent)
        : CurriculumnEntity(*new CurriculumnPrivate, parent)
    {
        Q_D(Curriculumn);
        d->chair = 0;
        d->department = 0;
        d->educationForm = 0;
        d->calendar = new Calendar(this);
        d->educationTerm = 0;
        setNumber(number);
    }

    Curriculumn::Curriculumn(CurriculumnPrivate &dd, Entity *parent)
        : CurriculumnEntity(dd, parent)
    {
        Q_D(Curriculumn);
        d->calendar = new Calendar(*(dd.calendar->d_func()), this);
    }

    Curriculumn::~Curriculumn()
    {

    }

    void Curriculumn::setName(const QString &name)
    {
        setProperty(EntityPrivate::nameProperty, name);
    }

    QString Curriculumn::name() const
    {
        return property(EntityPrivate::nameProperty).toString();
    }

    Calendar *Curriculumn::calendar() const
    {
        Q_D(const Curriculumn);
        return d->calendar;
    }

    void Curriculumn::setSpeciality(Speciality *speciality)
    {
        Q_D(Curriculumn);
        d->speciality = speciality;
    }

    Speciality *Curriculumn::speciality() const
    {
        Q_D(const Curriculumn);
        return d->speciality;
    }

    void Curriculumn::setEducationForm(EducationForm *educationForm)
    {
        Q_D(Curriculumn);
        d->educationForm = educationForm;
    }

    EducationForm *Curriculumn::educationForm() const
    {
        Q_D(const Curriculumn);
        return d->educationForm;
    }

    void Curriculumn::setEducationTerm(quint32 educationTerm)
    {
        Q_D(Curriculumn);
        d->educationTerm = educationTerm;
        d->calendar->init();
    }

    quint32 Curriculumn::educationTerm() const
    {
        Q_D(const Curriculumn);
        return d->educationTerm;
    }

    void Curriculumn::setQualification(const QString &qualification)
    {
        Q_D(Curriculumn);
        d->qualification = qualification;
    }

    QString Curriculumn::qualification() const
    {
        Q_D(const Curriculumn);
        return d->qualification;
    }

    void Curriculumn::setSpecialization(const QString &specialization)
    {
        Q_D(Curriculumn);
        d->specialization = specialization;
    }

    QString Curriculumn::specialization() const
    {
        Q_D(const Curriculumn);
        return d->specialization;
    }

    CurriculumnDisciplineGroup *Curriculumn::addGroup(CurriculumnSection *section)
    {
        Q_D(Curriculumn);
        CurriculumnDisciplineGroup *g = d->addEntity();
        g->setCurriculumnSection(section);
        return g;
    }

    void Curriculumn::removeGroup(CurriculumnDisciplineGroup *group)
    {
        Q_D(Curriculumn);
        d->removeEntity(group);
    }

    CurriculumnDisciplineGroup *Curriculumn::group(int index) const
    {
        Q_D(const Curriculumn);
        return d->entity(index);
    }

    CurriculumnDisciplineGroup *Curriculumn::group(CurriculumnSection *section) const
    {
        Q_D(const Curriculumn);
        return d->entityByConstant<CurriculumnSection>(section, &CurriculumnDisciplineGroup::curriculumnSection);
    }

    QList<CurriculumnDisciplineGroup *> Curriculumn::groups() const
    {
        Q_D(const Curriculumn);
        return d->entities;
    }

    int Curriculumn::indexOf(CurriculumnDisciplineGroup *group) const
    {
        Q_D(const Curriculumn);
        return d->indexOf(group);
    }

    bool Curriculumn::hasGroup(CurriculumnSection *section) const
    {
        Q_D(const Curriculumn);
        return d->hasEntity(section, &CurriculumnDisciplineGroup::curriculumnSection);
    }

    qreal Curriculumn::lectionsHoursTotal() const
    {
        Q_D(const Curriculumn);
        return d->lectionsHoursTotal();
    }

    qreal Curriculumn::labsHoursTotal() const
    {
        Q_D(const Curriculumn);
        return d->labsHoursTotal();
    }

    qreal Curriculumn::practicesHoursTotal() const
    {
        Q_D(const Curriculumn);
        return d->practicesHoursTotal();
    }

    qreal Curriculumn::kksHoursTotal() const
    {
        Q_D(const Curriculumn);
        return d->kksHoursTotal();
    }

    quint32 Curriculumn::exams() const
    {
        Q_D(const Curriculumn);
        return d->exams();
    }

    quint32 Curriculumn::tests() const
    {
        Q_D(const Curriculumn);
        return d->tests();
    }

    quint32 Curriculumn::rs() const
    {
        Q_D(const Curriculumn);
        return d->rs();
    }

    quint32 Curriculumn::courseWorks() const
    {
        Q_D(const Curriculumn);
        return d->courseWorks();
    }

    quint32 Curriculumn::courseProjects() const
    {
        Q_D(const Curriculumn);
        return d->courseProjects();
    }

    quint32 Curriculumn::diffTests() const
    {
        Q_D(const Curriculumn);
        return d->diffTests();
    }

    quint32 Curriculumn::qualifications() const
    {
        Q_D(const Curriculumn);
        return d->qualifications();
    }

    quint32 Curriculumn::diploms() const
    {
        Q_D(const Curriculumn);
        return d->diploms();
    }

    quint32 Curriculumn::magisters() const
    {
        Q_D(const Curriculumn);
        return d->magisters();
    }

    quint32 Curriculumn::practices() const
    {
        Q_D(const Curriculumn);
        return d->practices();
    }

    quint32 Curriculumn::dimplomPractices() const
    {
        Q_D(const Curriculumn);
        return d->dimplomPractices();
    }

    quint32 Curriculumn::magisterPractices() const
    {
        Q_D(const Curriculumn);
        return d->magisterPractices();
    }

    quint32 Curriculumn::qualificationPractices() const
    {
        Q_D(const Curriculumn);
        return d->qualificationPractices();
    }

    quint32 Curriculumn::stateExams() const
    {
        Q_D(const Curriculumn);
        return d->stateExams();
    }

    quint32 Curriculumn::enterprisePractices() const
    {
        Q_D(const Curriculumn);
        return d->enterprisePractices();
    }

    void Curriculumn::setDepartment(Department *department)
    {
        Q_D(Curriculumn);
        d->department = department;
    }

    Department *Curriculumn::department() const
    {
        Q_D(const Curriculumn);
        return d->department;
    }

    void Curriculumn::setChair(Chair *chair)
    {
        Q_D(Curriculumn);
        d->chair = chair;
    }

    Chair *Curriculumn::chair() const
    {
        Q_D(const Curriculumn);
        return d->chair;
    }
    //-----------------------------------------------------
    QDataStream &operator << (QDataStream &s, const Curriculumn &c)
    {
        s << static_cast<const KTU::Entity &>(c);
        s << c.d_func()->department->id();
        s << c.d_func()->chair->id();
        s << c.d_func()->speciality->id();
        s << c.d_func()->educationForm->id();
        s << c.d_func()->educationTerm;
        s << c.d_func()->qualification;
        s << c.d_func()->specialization;
        s << *(c.d_func()->calendar);

        QList<KTU::CurriculumnDisciplineGroup *> groups = c.groups();
        s << groups.count();
        foreach (KTU::CurriculumnDisciplineGroup *group, groups) {
            s << group->curriculumnSection()->id();
            s << (*group);
        }
        return s;
    }

    QDataStream &operator >> (QDataStream &s, Curriculumn &c)
    {
        s >> static_cast<KTU::Entity &>(c);
        quint64 depId  = 0;
        s >> depId;
        c.d_func()->department = constantsFactory.department(depId);

        quint64 chairId = 0;
        s >> chairId;
        c.d_func()->chair = constantsFactory.chair(chairId);

        quint64 specId = 0;
        s >> specId;
        c.d_func()->speciality = constantsFactory.speciality(specId);

        quint64 eduFormId = 0;
        s >> eduFormId;
        c.d_func()->educationForm = constantsFactory.educationForm(eduFormId);

        s >> c.d_func()->educationTerm;
        s >> c.d_func()->qualification;
        s >> c.d_func()->specialization;
        s >> *(c.d_func()->calendar);

        qint32 count = 0;
        s >> count;
        for (qint32 i = 0; i < count; ++i) {
            quint64 id = 0;
            s >> id;
            KTU::CurriculumnSection *section = constantsFactory.curriculumnSection(id);
            if (!section)
                continue;
            KTU::CurriculumnDisciplineGroup *group = c.addGroup(section);
            s >> (*group);
        }

        return s;
    }
}
