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

#ifndef CURRICULUMNRECORD_H
#define CURRICULUMNRECORD_H

#include "entity.h"
#include "curriculumncalculableinterface.h"

namespace KTU
{
    class CurriculumnRecordPrivate;
    class Chair;
    class Discipline;
    class CurriculumnDisciplineSubGroup;
    class CurriculumnSemester;
    class CurriculumnCourse;

    class CURRICULUMN_EXPORT CurriculumnRecord : public Entity, public CurriculumnCalculableInterface
    {
        friend class CurriculumnDisciplineSubGroup;
        friend class CurriculumnDisciplineSubGroupPrivate;
        Q_DECLARE_PRIVATE(CurriculumnRecord)

    public:
        CurriculumnDisciplineSubGroup *subGroup() const;

        void setChair(Chair *chair);
        Chair *chair() const;

        void setDiscipline(Discipline *discipline);
        Discipline *discipline() const;

        CurriculumnCourse *course(quint32 number) const;
        QList<CurriculumnCourse *> courses() const;

        CurriculumnSemester *semester(quint32 number) const;
        QList<CurriculumnSemester *> semesters() const;

        qreal lectionsHours(quint32 number) const;
        qreal labsHours(quint32 number) const;
        qreal practicesHours(quint32 number) const;
        qreal kksHours(quint32 number) const;

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

        void setTotalByPlan(qreal hours);
        qreal totalByPlan() const;

        qreal ects() const { return totalByPlan() / 36; }
        qreal individualWork() const { return totalByPlan() - autidoriumTotal(); }

        friend QDataStream &operator>>(QDataStream &s, KTU::CurriculumnRecord &g);
        friend QDataStream &operator<<(QDataStream &s, const KTU::CurriculumnRecord &g);

    private:
        qreal calculateSubTotal(quint32 number, qreal (CurriculumnSemester::*func)() const) const;

    private:
        explicit CurriculumnRecord(CurriculumnDisciplineSubGroup *subGroup);
        CurriculumnRecord(quint64 id, CurriculumnDisciplineSubGroup *subGroup);
        CurriculumnRecord(CurriculumnRecordPrivate &dd, CurriculumnDisciplineSubGroup *subGroup);
        ~CurriculumnRecord();

        void init();
    };
}
Q_DECLARE_METATYPE(KTU::CurriculumnRecord *)

#endif // CURRICULUMNRECORD_H
