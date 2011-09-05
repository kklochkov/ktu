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


#ifndef CURRICULUMNDISCIPLINEGROUP_H
#define CURRICULUMNDISCIPLINEGROUP_H

#include "entity.h"
#include "curriculumncalculableinterface.h"

namespace KTU
{
    class CurriculumnDisciplineGroupPrivate;
    class CurriculumnDisciplineSubGroup;
    class CurriculumnGroup;
    class CurriculumnSection;
    class Curriculumn;

    class CURRICULUMN_EXPORT CurriculumnDisciplineGroup : public Entity, public CurriculumnCalculableInterface
    {
        friend class Curriculumn;
        friend class CurriculumnPrivate;
        Q_DECLARE_PRIVATE(CurriculumnDisciplineGroup)

    public:
        CurriculumnSection *curriculumnSection() const;

        Curriculumn *curriculumn() const;

        CurriculumnDisciplineSubGroup *addSubGroup(CurriculumnGroup *group);
        void removeSubGroup(CurriculumnDisciplineSubGroup *subGroup);
        CurriculumnDisciplineSubGroup *subGroup(int index) const;
        CurriculumnDisciplineSubGroup *subGroup(CurriculumnGroup *subGroup) const;
        QList<CurriculumnDisciplineSubGroup *> subGroups() const;
        int indexOf(CurriculumnDisciplineSubGroup *subGroup) const;
        bool hasSubGroup(CurriculumnGroup *subGroup) const;

        friend QDataStream &operator>>(QDataStream &s, KTU::CurriculumnDisciplineGroup &g);
        friend QDataStream &operator<<(QDataStream &s, const KTU::CurriculumnDisciplineGroup &g);

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
        explicit CurriculumnDisciplineGroup(Curriculumn *curriculumn);
        CurriculumnDisciplineGroup(CurriculumnDisciplineGroupPrivate &dd, Curriculumn *curriculumn);
        ~CurriculumnDisciplineGroup();

        void setCurriculumnSection(CurriculumnSection *section);
    };
}
Q_DECLARE_METATYPE(KTU::CurriculumnDisciplineGroup *)

#endif // CURRICULUMNDISCIPLINEGROUP_H
