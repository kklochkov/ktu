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


#ifndef CURRICULUMNSEMESTER_H
#define CURRICULUMNSEMESTER_H

#include "entity.h"
#include "curriculumncalculableinterface.h"

namespace KTU
{
    class CurriculumnSemesterPrivate;
    class CurriculumnCourse;
    class CalendarSemester;

    class CURRICULUMN_EXPORT CurriculumnSemester : public Entity, public CurriculumnCalculableInterface
    {
        friend class CurriculumnCourse;
        friend class CurriculumnCoursePrivate;
        Q_DECLARE_PRIVATE(CurriculumnSemester)

    public:
        quint32 number() const;

        void setLectionsHours(qreal hours);
        qreal lectionsHours() const;
        qreal lectionsHoursTotal() const;

        void setLabsHours(qreal hours);
        qreal labsHours() const;
        qreal labsHoursTotal() const;

        void setPracticesHours(qreal hours);
        qreal practicesHours() const;
        qreal practicesHoursTotal() const;

        void setKKSHours(qreal hours);
        qreal kksHours() const;
        qreal kksHoursTotal() const;

        void setExam(bool has);
        quint32 exams() const;

        void setTest(bool has);
        quint32 tests() const;

        void setR(bool has);
        quint32 rs() const;

        void setCourseWork(bool has);
        quint32 courseWorks() const;

        void setCourseProject(bool has);
        quint32 courseProjects() const;

        void setDiffTest(bool has);
        quint32 diffTests() const;

        void setQualification(bool has);
        quint32 qualifications() const;

        void setDiplom(bool has);
        quint32 diploms() const;

        void setMagister(bool has);
        quint32 magisters() const;

        void setPractice(bool has);
        quint32 practices() const;

        void setDimplomPractice(bool has);
        quint32 dimplomPractices() const;

        void setMagisterPractice(bool has);
        quint32 magisterPractices() const;

        void setQualificationPractice(bool has);
        quint32 qualificationPractices() const;

        void setStateExam(bool has);
        quint32 stateExams() const;

        void setEnterprisePractice(bool has);
        quint32 enterprisePractices() const;

        quint32 weeksCount() const;

        friend QDataStream &operator>>(QDataStream &s, KTU::CurriculumnSemester &g);
        friend QDataStream &operator<<(QDataStream &s, const KTU::CurriculumnSemester &g);

        CurriculumnCourse *course() const;

    private:
        explicit CurriculumnSemester(CurriculumnCourse *parent);
        CurriculumnSemester(CurriculumnSemesterPrivate &dd, CurriculumnCourse *parent);
        ~CurriculumnSemester();

        void setSemester(CalendarSemester *semester);
    };
}

#endif // CURRICULUMNSEMESTER_H
