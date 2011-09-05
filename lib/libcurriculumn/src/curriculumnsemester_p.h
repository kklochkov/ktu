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


#ifndef CURRICULUMNSEMESTER_P_H
#define CURRICULUMNSEMESTER_P_H

#include "entity_p.h"
#include "curriculumnsemester.h"

namespace KTU
{
    class CalendarSemester;
    class CurriculumnCourse;

    class CURRICULUMN_EXPORT CurriculumnSemesterPrivate : public EntityPrivate
    {
        Q_DECLARE_PUBLIC(CurriculumnSemester)

    public:
        CalendarSemester *semester;
        qreal lections;
        qreal labs;
        qreal practices;
        qreal kks;
        CurriculumnCourse *course;

        enum KindOfWork {
            Exam,
            Test,
            R,
            CourseWork,
            CourseProject,
            DiffTest,
            QualTest,
            Diplom,
            Magister,
            Practice,
            DipPractice,
            MagPractice,
            QuaPractice,
            EntPractice,
            StateExam
        };
        QMap<KindOfWork, bool> works;
    };
}

#endif // CURRICULUMNSEMESTER_P_H
