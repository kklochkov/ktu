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

#ifndef CURRICULUMN_H
#define CURRICULUMN_H

#include "curriculumnentity.h"
#include "nameinterface.h"
#include "curriculumncalculableinterface.h"

namespace KTU
{
    class CurriculumnPrivate;
    class Calendar;
    class CurriculumnDisciplineGroup;
    class CurriculumnSection;
    class Speciality;
    class Department;
    class Chair;
    class EducationForm;

    class CURRICULUMN_EXPORT Curriculumn : public CurriculumnEntity, public NameInterface, public CurriculumnCalculableInterface
    {
        friend class AbstractFactoryInterface;
        Q_DECLARE_PRIVATE(Curriculumn)

    public:
        void setName(const QString &name);
        QString name() const;

        void setDepartment(Department *department);
        Department *department() const;

        void setChair(Chair *chair);
        Chair *chair() const;

        Calendar *calendar() const;

        void setSpeciality(Speciality *speciality);
        Speciality *speciality() const;

        void setEducationForm(EducationForm *educationForm);
        EducationForm *educationForm() const;

        void setEducationTerm(quint32 educationTerm);
        quint32 educationTerm() const;

        void setQualification(const QString &qualification);
        QString qualification() const;

        void setSpecialization(const QString &specialization);
        QString specialization() const;

        friend QDataStream &operator>>(QDataStream &s, Curriculumn &c);
        friend QDataStream &operator<<(QDataStream &s, const Curriculumn &c);

        CurriculumnDisciplineGroup *addGroup(CurriculumnSection *section);
        void removeGroup(CurriculumnDisciplineGroup *group);
        CurriculumnDisciplineGroup *group(int index) const;
        CurriculumnDisciplineGroup *group(CurriculumnSection *section) const;
        QList<CurriculumnDisciplineGroup *> groups() const;
        int indexOf(CurriculumnDisciplineGroup *group) const;
        bool hasGroup(CurriculumnSection *section) const;

        qreal lectionsHoursTotal() const;
        qreal labsHoursTotal() const;
        qreal practicesHoursTotal() const;
        qreal kksHoursTotal() const;

        quint32 exams() const;
        quint32 tests() const;
        quint32 rs() const;
        quint32 courseWorks() const;
        quint32 courseProjects() const;
        quint32 diffTests() const;
        quint32 qualifications() const;
        quint32 diploms() const;
        quint32 magisters() const;
        quint32 practices() const;
        quint32 dimplomPractices() const;
        quint32 magisterPractices() const;
        quint32 qualificationPractices() const;
        quint32 stateExams() const;
        quint32 enterprisePractices() const;

    private:
        explicit Curriculumn(Entity *parent = 0);
        Curriculumn(quint32 number, Entity *parent);
        Curriculumn(CurriculumnPrivate &dd, Entity *parent);
        ~Curriculumn();
    };

    CURRICULUMN_EXPORT QDataStream &operator>>(QDataStream &s, Curriculumn &c);
    CURRICULUMN_EXPORT QDataStream &operator<<(QDataStream &s, const Curriculumn &c);
}

#endif // CURRICULUMN_H
