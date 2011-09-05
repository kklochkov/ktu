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
#include <QObject>

#include "constantsfactory.h"
#include "constantsfactory_p.h"
#include "calendarweeksign.h"
#include "constants.h"
#include "department.h"
#include "university.h"
#include "institute.h"
#include "speciality.h"
#include "chair.h"
#include "group.h"
#include "curriculumn.h"

namespace KTU
{
    ConstantsFactory::ConstantsFactory()
        : EntityFactory(*new ConstantsFactoryPrivate)
    {
        Q_D(ConstantsFactory);
        d->defaultCalendarWeekSign = 0;
        d->defaultEducationLevel = createEducationLevel(QObject::tr("Empty"));              //TODO: will be created each time, must be created only once!
        d->emptyCalendarWeekSign = createCalendarWeekSign(QString(), QObject::tr("Empty")); //TODO: will be created each time, must be created only once!
        d->storage = 0;
    }

    ConstantsFactory::ConstantsFactory(ConstantsFactoryPrivate &dd)
        : EntityFactory(dd)
    {

    }

    ConstantsFactory::~ConstantsFactory()
    {

    }

    void ConstantsFactory::setStorage(AbstractStorage *storage)
    {
        Q_D(ConstantsFactory);
        if (!storage || d->storage == storage)
            return;
        d->storage = storage;
    }

    AbstractStorage *ConstantsFactory::storage() const
    {
        Q_D(const ConstantsFactory);
        return d->storage;
    }

    CalendarWeekSign *ConstantsFactory::createCalendarWeekSign(const QString &sign, const QString &description)
    {
        Q_D(ConstantsFactory);
        CalendarWeekSign *ws = d->createEntity<CalendarWeekSign, ConstantsFactory>(d->calendarWeekSigns, this);
        if (ws) {
            ws->setSign(sign);
            ws->setDescription(description);
            if (!d->defaultCalendarWeekSign)
                d->defaultCalendarWeekSign = ws;
        }
        return ws;
    }

    CalendarWeekSign *ConstantsFactory::calendarWeekSign(quint64 id) const
    {
        Q_D(const ConstantsFactory);
        return d->entity<CalendarWeekSign>(id, d->calendarWeekSigns);
    }

    CalendarWeekSign *ConstantsFactory::calendarWeekSign(const QString &sign) const
    {
        Q_D(const ConstantsFactory);
        return d->entity<CalendarWeekSign>(sign, &CalendarWeekSign::sign, d->calendarWeekSigns);
    }

    void ConstantsFactory::setDefaultCalendarWeekSign(CalendarWeekSign *sign)
    {
        Q_D(ConstantsFactory);
        if (d->defaultCalendarWeekSign == sign)
            return;
        d->defaultCalendarWeekSign = sign;
    }

    CalendarWeekSign *ConstantsFactory::defaultCalendarWeekSign() const
    {
        Q_D(const ConstantsFactory);
        return d->defaultCalendarWeekSign;
    }

    CalendarWeekSign *ConstantsFactory::emptyCalendarWeekSign() const
    {
        Q_D(const ConstantsFactory);
        return d->emptyCalendarWeekSign;
    }

    QList<CalendarWeekSign *> ConstantsFactory::calendarWeekSigns() const
    {
        Q_D(const ConstantsFactory);
        return d->calendarWeekSigns.values();
    }

    void ConstantsFactory::removeCalendarWeekSign(quint64 id)
    {
        Q_D(ConstantsFactory);
        d->removeEntity<CalendarWeekSign>(id, d->calendarWeekSigns);
    }

    void ConstantsFactory::setWorkCalendarWeekSigns(const QList<CalendarWeekSign *> &signs)
    {
        Q_D(ConstantsFactory);
        d->workCalendarWeekSigns = signs;
    }

    QList<CalendarWeekSign *> ConstantsFactory::workCalendarWeekSigns() const
    {
        Q_D(const ConstantsFactory);
        return d->workCalendarWeekSigns;
    }

    CurriculumnSection *ConstantsFactory::createCurriculumnSection(const QString &name)
    {
        Q_D(ConstantsFactory);
        CurriculumnSection *res = d->createEntity<CurriculumnSection, ConstantsFactory>(d->curriculumnSections, this);
        if (res)
            res->setName(name);
        return res;
    }

    CurriculumnSection *ConstantsFactory::curriculumnSection(quint64 id) const
    {
        Q_D(const ConstantsFactory);
        return d->entity<CurriculumnSection>(id, d->curriculumnSections);
    }

    CurriculumnSection *ConstantsFactory::curriculumnSection(const QString &name) const
    {
        Q_D(const ConstantsFactory);
        return d->entity<CurriculumnSection>(name, &CurriculumnSection::name, d->curriculumnSections);
    }

    QList<CurriculumnSection *> ConstantsFactory::curriculumnSections() const
    {
        Q_D(const ConstantsFactory);
        return d->curriculumnSections.values();
    }

    void ConstantsFactory::removeCurriculumnSection(quint64 id)
    {
        Q_D(ConstantsFactory);
        d->removeEntity<CurriculumnSection>(id, d->curriculumnSections);
    }

    CurriculumnGroup *ConstantsFactory::createCurriculumnGroup(const QString &name)
    {
        Q_D(ConstantsFactory);
        CurriculumnGroup *res = d->createEntity<CurriculumnGroup, ConstantsFactory>(d->curriculumnGroups, this);
        if (res)
            res->setName(name);
        return res;
    }

    CurriculumnGroup *ConstantsFactory::curriculumnGroup(quint64 id) const
    {
        Q_D(const ConstantsFactory);
        return d->entity<CurriculumnGroup>(id, d->curriculumnGroups);
    }

    CurriculumnGroup *ConstantsFactory::curriculumnGroup(const QString &name) const
    {
        Q_D(const ConstantsFactory);
        return d->entity<CurriculumnGroup>(name, &CurriculumnGroup::name, d->curriculumnGroups);
    }

    QList<CurriculumnGroup *> ConstantsFactory::curriculumnGroups() const
    {
        Q_D(const ConstantsFactory);
        return d->curriculumnGroups.values();
    }

    void ConstantsFactory::removeCurriculumnGroup(quint64 id)
    {
        Q_D(ConstantsFactory);
        d->removeEntity<CurriculumnGroup>(id, d->curriculumnGroups);
    }

    Discipline *ConstantsFactory::createDiscipline(const QString &name)
    {
        Q_D(ConstantsFactory);
        Discipline *res = d->createEntity<Discipline, ConstantsFactory>(d->disciplines, this);
        if (res)
            res->setName(name);
        return res;
    }

    Discipline *ConstantsFactory::discipline(quint64 id) const
    {
        Q_D(const ConstantsFactory);
        return d->entity<Discipline>(id, d->disciplines);
    }

    Discipline *ConstantsFactory::discipline(const QString &name) const
    {
        Q_D(const ConstantsFactory);
        return d->entity<Discipline>(name, &Discipline::name, d->disciplines);
    }

    QList<Discipline *> ConstantsFactory::disciplines() const
    {
        Q_D(const ConstantsFactory);
        return d->disciplines.values();
    }

    void ConstantsFactory::removeDiscipline(quint64 id)
    {
        Q_D(ConstantsFactory);
        d->removeEntity<Discipline>(id, d->disciplines);
    }

    Chair *ConstantsFactory::createChair(quint64 departmentId, const QString &name)
    {
        Q_D(ConstantsFactory);
        Department *department = this->department(departmentId);
        if (!department)
            return 0;
        Chair *res = d->createEntity<Chair, Department>(d->chairs, department);
        if (res)
            res->setName(name);
        return res;
    }

    Chair *ConstantsFactory::chair(quint64 id) const
    {
        Q_D(const ConstantsFactory);
        return d->entity<Chair>(id, d->chairs);
    }

    QList<Chair *> ConstantsFactory::chairs() const
    {
        Q_D(const ConstantsFactory);
        return d->chairs.values();
    }

    void ConstantsFactory::removeChair(quint64 id)
    {
        Q_D(ConstantsFactory);
        d->removeEntity<Chair>(id, d->chairs);
    }

    Speciality *ConstantsFactory::createSpeciality(quint64 departmentId, const QString &name)
    {
        Q_D(ConstantsFactory);
        Department *department = this->department(departmentId);
        if (!department)
            return 0;
        Speciality *res = d->createEntity<Speciality, Department>(d->specialities, department);
        if (res)
            res->setName(name);
        return res;
    }

    QList<Speciality *> ConstantsFactory::specialities() const
    {
        Q_D(const ConstantsFactory);
        return d->specialities.values();
    }

    Speciality *ConstantsFactory::speciality(quint64 id) const
    {
        Q_D(const ConstantsFactory);
        return d->entity<Speciality>(id, d->specialities);
    }

    void ConstantsFactory::removeSpeciality(quint64 id)
    {
        Q_D(ConstantsFactory);
        d->removeEntity<Speciality>(id, d->specialities);
    }

    Group *ConstantsFactory::createGroup(quint64 specialityId, const QString &name)
    {
        Q_D(ConstantsFactory);
        Speciality *speciality = this->speciality(specialityId);
        if (!speciality)
            return 0;
        Group *res = d->createEntity<Group, Speciality>(d->groups, speciality);
        if (res)
            res->setName(name);
        return res;
    }

    QList<Group *> ConstantsFactory::groups() const
    {
        Q_D(const ConstantsFactory);
        return d->groups.values();
    }

    Group *ConstantsFactory::group(quint64 id) const
    {
        Q_D(const ConstantsFactory);
        return d->entity<Group>(id, d->groups);
    }

    void ConstantsFactory::removeGroup(quint64 id)
    {
        Q_D(ConstantsFactory);
        d->removeEntity<Group>(id, d->groups);
    }

    University *ConstantsFactory::createUniversity(const QString &name)
    {
        Q_D(ConstantsFactory);
        University *res = d->createEntity<University, ConstantsFactory>(d->universities, this);
        if (res)
            res->setName(name);
        return res;
    }

    University *ConstantsFactory::university(quint64 id) const
    {
        Q_D(const ConstantsFactory);
        return d->entity<University>(id, d->universities);
    }

    QList<University *> ConstantsFactory::universities() const
    {
        Q_D(const ConstantsFactory);
        return d->universities.values();
    }

    void ConstantsFactory::removeUniversity(quint64 id)
    {
        Q_D(ConstantsFactory);
        d->removeEntity<University>(id, d->universities);
    }

    Institute *ConstantsFactory::createInstitute(quint64 universityId, const QString &name)
    {
        Q_D(ConstantsFactory);
        University *university = this->university(universityId);
        if (!university)
            return 0;
        Institute *res = d->createEntity<Institute, University>(d->institutes, university);
        if (res)
            res->setName(name);
        return res;
    }

    Institute *ConstantsFactory::institute(quint64 id) const
    {
        Q_D(const ConstantsFactory);
        return d->entity<Institute>(id, d->institutes);
    }

    QList<Institute *> ConstantsFactory::institutes() const
    {
        Q_D(const ConstantsFactory);
        return d->institutes.values();
    }

    void ConstantsFactory::removeInstitute(quint64 id)
    {
        Q_D(ConstantsFactory);
        d->removeEntity<Institute>(id, d->institutes);
    }

    Department *ConstantsFactory::createDepartment(quint64 instituteId, const QString &name)
    {
        Q_D(ConstantsFactory);
        Institute *institute = this->institute(instituteId);
        if (!institute)
            return 0;
        Department *res = d->createEntity<Department, Institute>(d->departments, institute);
        if (res)
            res->setName(name);
        return res;
    }

    Department *ConstantsFactory::department(quint64 id) const
    {
        Q_D(const ConstantsFactory);
        return d->entity<Department>(id, d->departments);
    }

    QList<Department *> ConstantsFactory::departments() const
    {
        Q_D(const ConstantsFactory);
        return d->departments.values();
    }

    void ConstantsFactory::removeDepartment(quint64 id)
    {
        Q_D(ConstantsFactory);
        d->removeEntity<Department>(id, d->departments);
    }

    EducationLevel *ConstantsFactory::createEducationLevel(const QString &name)
    {
        Q_D(ConstantsFactory);
        EducationLevel *res = d->createEntity<EducationLevel, ConstantsFactory>(d->educationLevels, this);
        if (res)
            res->setName(name);
        return res;
    }

    EducationLevel *ConstantsFactory::educationLevel(quint64 id) const
    {
        Q_D(const ConstantsFactory);
        return d->entity<EducationLevel>(id, d->educationLevels);
    }

    EducationLevel *ConstantsFactory::educationLevel(const QString &name) const
    {
        Q_D(const ConstantsFactory);
        return d->entity<EducationLevel>(name, &EducationLevel::name, d->educationLevels);
    }

    QList<EducationLevel *> ConstantsFactory::educationLevels() const
    {
        Q_D(const ConstantsFactory);
        return d->educationLevels.values();
    }

    void ConstantsFactory::removeEducationLevel(quint64 id)
    {
        Q_D(ConstantsFactory);
        d->removeEntity<EducationLevel>(id, d->educationLevels);
    }

    EducationLevel *ConstantsFactory::defaultEducationLevel() const
    {
        Q_D(const ConstantsFactory);
        return d->defaultEducationLevel;
    }

    EducationForm *ConstantsFactory::createEducationForm(const QString &name)
    {
        Q_D(ConstantsFactory);
        EducationForm *res = d->createEntity<EducationForm, ConstantsFactory>(d->educationForms, this);
        if (res)
            res->setName(name);
        return res;
    }

    EducationForm *ConstantsFactory::educationForm(quint64 id) const
    {
        Q_D(const ConstantsFactory);
        return d->entity<EducationForm>(id, d->educationForms);
    }

    EducationForm *ConstantsFactory::educationForm(const QString &name) const
    {
        Q_D(const ConstantsFactory);
        return d->entity<EducationForm>(name, &EducationForm::name, d->educationForms);
    }

    QList<EducationForm *> ConstantsFactory::educationForms() const
    {
        Q_D(const ConstantsFactory);
        return d->educationForms.values();
    }

    void ConstantsFactory::removeEducationForm(quint64 id)
    {
        Q_D(ConstantsFactory);
        d->removeEntity<EducationForm>(id, d->educationForms);
    }

    Curriculumn *ConstantsFactory::createCurriculumn(const QString &name)
    {
        Q_D(ConstantsFactory);
        Curriculumn *res = d->createEntity<Curriculumn, ConstantsFactory>(d->curriculumns, this);
        if (res)
            res->setName(name);
        return res;
    }

    Curriculumn *ConstantsFactory::curriculumn(quint64 id) const
    {
        Q_D(const ConstantsFactory);
        return d->entity<Curriculumn>(id, d->curriculumns);
    }

    QList<Curriculumn *> ConstantsFactory::curriculumns() const
    {
        Q_D(const ConstantsFactory);
        return d->curriculumns.values();
    }

    void ConstantsFactory::removeCurriculumn(quint64 id)
    {
        Q_D(ConstantsFactory);
        d->removeEntity<Curriculumn>(id, d->curriculumns);
    }

    QDataStream &operator <<(QDataStream &s, const ConstantsFactory &cf)
    {
//        s << cf.d_func()->defaultCalendarWeekSign;
//        s << cf.d_func()->defaultEducationLevel;
//        s << cf.d_func()->emptyCalendarWeekSign;
        return s;
    }

    QDataStream &operator >>(QDataStream &s, ConstantsFactory &cf)
    {

        return s;
    }
}
