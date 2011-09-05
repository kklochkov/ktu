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


#ifndef CURRICULUMNCOURSE_H
#define CURRICULUMNCOURSE_H

#include "entity.h"
#include "curriculumncalculableinterface.h"

namespace KTU
{
    class CurriculumnCoursePrivate;
    class CalendarCourse;
    class CurriculumnRecord;
    class CurriculumnSemester;

    class CURRICULUMN_EXPORT CurriculumnCourse : public Entity, public CurriculumnCalculableInterface
    {
        friend class CurriculumnRecord;
        friend class CurriculumnRecordPrivate;
        Q_DECLARE_PRIVATE(CurriculumnCourse)

    public:
        quint32 number() const;

        CurriculumnSemester *semester(quint32 number) const;
        QList<CurriculumnSemester *> semesters() const;

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

        CurriculumnRecord *record() const;

    private:
        explicit CurriculumnCourse(CurriculumnRecord *parent);
        CurriculumnCourse(CurriculumnCoursePrivate &dd, CurriculumnRecord *parent);
        ~CurriculumnCourse();

        void init(CalendarCourse *course);
    };
}

#endif // CURRICULUMNCOURSE_H
