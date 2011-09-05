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

#ifndef CURRICULUMNDISCIPLINESUBGROUP_H
#define CURRICULUMNDISCIPLINESUBGROUP_H

#include "entity.h"
#include "curriculumncalculableinterface.h"

namespace KTU
{
    class CurriculumnDisciplineSubGroupPrivate;
    class CurriculumnRecord;
    class CurriculumnGroup;
    class CurriculumnDisciplineGroup;
    class Discipline;

    class CURRICULUMN_EXPORT CurriculumnDisciplineSubGroup : public Entity, public CurriculumnCalculableInterface
    {
        friend class CurriculumnDisciplineGroup;
        friend class CurriculumnDisciplineGroupPrivate;
        Q_DECLARE_PRIVATE(CurriculumnDisciplineSubGroup)

    public:
        CurriculumnGroup *curriculumnGroup() const;

        CurriculumnDisciplineGroup *group() const;

        CurriculumnRecord *addRecord();
        void removeRecord(CurriculumnRecord *record);
        CurriculumnRecord *record(int index) const;
        CurriculumnRecord *record(Discipline *discipline) const;
        QList<CurriculumnRecord *> records() const;
        int indexOf(CurriculumnRecord *record) const;

        qreal totalByPlan() const;
        qreal ects() const;
        qreal individualWork() const;
        qreal lectionsHours(quint32 number) const;
        qreal labsHours(quint32 number) const;
        qreal practicesHours(quint32 number) const;
        qreal kksHours(quint32 number) const;

        friend QDataStream &operator>>(QDataStream &s, KTU::CurriculumnDisciplineSubGroup &sg);
        friend QDataStream &operator<<(QDataStream &s, const KTU::CurriculumnDisciplineSubGroup &sg);

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
        explicit CurriculumnDisciplineSubGroup(CurriculumnDisciplineGroup *group);
        explicit CurriculumnDisciplineSubGroup(CurriculumnDisciplineSubGroupPrivate &dd, CurriculumnDisciplineGroup *group);
        ~CurriculumnDisciplineSubGroup();

        void setCurriculumnGroup(CurriculumnGroup *group);

        qreal calculateTotal(qreal (CurriculumnRecord::*func)() const) const;
        qreal calculateTotal(quint32 number, qreal (CurriculumnRecord::*func)(quint32) const) const;
    };
}
Q_DECLARE_METATYPE(KTU::CurriculumnDisciplineSubGroup *)

#endif // CURRICULUMNDISCIPLINESUBGROUP_H
