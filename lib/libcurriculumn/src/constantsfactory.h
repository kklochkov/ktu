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


#ifndef CONSTANTSFACTORY_H
#define CONSTANTSFACTORY_H

#include "entityfactory.h"

namespace KTU
{
    class ConstantsFactoryPrivate;
    class CalendarWeekSign;
    class Constant;
    class CurriculumnSection;
    class CurriculumnGroup;
    class Discipline;
    class Chair;
    class University;
    class Institute;
    class Department;
    class Speciality;
    class EducationLevel;
    class EducationForm;
    class Group;
    class Curriculumn;
    class AbstractStorage;

    class CURRICULUMN_EXPORT ConstantsFactory : private EntityFactory
    {
        friend class AbstractFactoryInterface;
        Q_DECLARE_PRIVATE(ConstantsFactory)

    public:
        void setStorage(AbstractStorage *storage);
        AbstractStorage *storage() const;

        static ConstantsFactory &instance()
        {
            static ConstantsFactory factory;
            return factory;
        }

        CalendarWeekSign *createCalendarWeekSign(const QString &sign = QString(), const QString &description = QString());
        CalendarWeekSign *calendarWeekSign(quint64 id) const;
        CalendarWeekSign *calendarWeekSign(const QString &sign) const;
        void setDefaultCalendarWeekSign(CalendarWeekSign *sign);
        CalendarWeekSign *defaultCalendarWeekSign() const;
        CalendarWeekSign *emptyCalendarWeekSign() const;
        QList<CalendarWeekSign *> calendarWeekSigns() const;
        void removeCalendarWeekSign(quint64 id);
        void setWorkCalendarWeekSigns(const QList<CalendarWeekSign *> &signs);
        QList<CalendarWeekSign *> workCalendarWeekSigns() const;

        CurriculumnSection *createCurriculumnSection(const QString &name = QString());
        CurriculumnSection *curriculumnSection(quint64 id) const;
        CurriculumnSection *curriculumnSection(const QString &name) const;
        QList<CurriculumnSection *> curriculumnSections() const;
        void removeCurriculumnSection(quint64 id);

        CurriculumnGroup *createCurriculumnGroup(const QString &name = QString());
        CurriculumnGroup *curriculumnGroup(quint64 id) const;
        CurriculumnGroup *curriculumnGroup(const QString &name) const;
        QList<CurriculumnGroup *> curriculumnGroups() const;
        void removeCurriculumnGroup(quint64 id);

        Discipline *createDiscipline(const QString &name = QString());
        Discipline *discipline(quint64 id) const;
        Discipline *discipline(const QString &name) const;
        QList<Discipline *> disciplines() const;
        void removeDiscipline(quint64 id);

        University *createUniversity(const QString &name = QString());
        University *university(quint64 id) const;
        QList<University *> universities() const;
        void removeUniversity(quint64 id);

        Institute *createInstitute(quint64 universityId, const QString &name = QString());
        Institute *institute(quint64 id) const;
        QList<Institute *> institutes() const;
        void removeInstitute(quint64 id);

        Department *createDepartment(quint64 instituteId, const QString &name = QString());
        Department *department(quint64 id) const;
        QList<Department *> departments() const;
        void removeDepartment(quint64 id);

        Chair *createChair(quint64 departmentId, const QString &name = QString());
        Chair *chair(quint64 id) const;
        QList<Chair *> chairs() const;
        void removeChair(quint64 id);

        Speciality *createSpeciality(quint64 departmentId, const QString &name = QString());
        Speciality *speciality(quint64 id) const;
        QList<Speciality *> specialities() const;
        void removeSpeciality(quint64 id);

        Group *createGroup(quint64 specialityId, const QString &name = QString());
        Group *group(quint64 id) const;
        QList<Group *> groups() const;
        void removeGroup(quint64 id);

        EducationLevel *createEducationLevel(const QString &name = QString());
        EducationLevel *educationLevel(quint64 id) const;
        EducationLevel *educationLevel(const QString &name) const;
        QList<EducationLevel *> educationLevels() const;
        void removeEducationLevel(quint64 id);
        EducationLevel *defaultEducationLevel() const;

        EducationForm *createEducationForm(const QString &name = QString());
        EducationForm *educationForm(quint64 id) const;
        EducationForm *educationForm(const QString &name) const;
        QList<EducationForm *> educationForms() const;
        void removeEducationForm(quint64 id);

        Curriculumn *createCurriculumn(const QString &name = QString());
        Curriculumn *curriculumn(quint64 id) const;
        QList<Curriculumn *> curriculumns() const;
        void removeCurriculumn(quint64 id);

        friend QDataStream &operator <<(QDataStream &s, const ConstantsFactory &cf);
        friend QDataStream &operator >>(QDataStream &s, ConstantsFactory &cf);

    private:
        ConstantsFactory();
        ConstantsFactory(ConstantsFactoryPrivate &dd);
        ~ConstantsFactory();
    };
}

#define constantsFactory KTU::ConstantsFactory::instance()

#endif // CONSTANTSFACTORY_H
