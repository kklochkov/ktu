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


#ifndef CURRICULUMNDISCIPLINEGROUP_P_H
#define CURRICULUMNDISCIPLINEGROUP_P_H

#include "curriculumn_p.h"
#include "curriculumndisciplinegroup.h"

namespace KTU
{
    class CURRICULUMN_EXPORT CurriculumnDisciplineGroupPrivate : public AbstractCurriculumnDataPrivate<CurriculumnDisciplineSubGroup>
    {
        Q_DECLARE_PUBLIC(CurriculumnDisciplineGroup)

    public:
        CurriculumnDisciplineSubGroup *createEntity() const;
        void deleteEntity(CurriculumnDisciplineSubGroup *entity) const;

        CurriculumnSection *curriculumnSection;
        Curriculumn *curriculumn;
    };
}

#endif // CURRICULUMNDISCIPLINEGROUP_P_H
