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


#ifndef CURRICULUMNCOURSE_P_H
#define CURRICULUMNCOURSE_P_H

#include "curriculumn_p.h"
#include "curriculumncourse.h"

namespace KTU
{
    class CURRICULUMN_EXPORT CurriculumnCoursePrivate : public AbstractCurriculumnDataPrivate<CurriculumnSemester>
    {
        Q_DECLARE_PUBLIC(CurriculumnCourse)

    public:
        CurriculumnSemester *createEntity() const;
        void deleteEntity(CurriculumnSemester *entity) const;

        CalendarCourse *course;
        CurriculumnRecord *record;
    };
}

#endif // CURRICULUMNCOURSE_P_H
