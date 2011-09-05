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

#include "curriculumnsemester.h"
#include "curriculumnsemester_p.h"
#include "curriculumncourse.h"
#include "calendarsemester.h"

namespace KTU
{
    QDataStream &operator << (QDataStream &s, CurriculumnSemesterPrivate::KindOfWork kod)
    {
        s << qint32(kod);
        return s;
    }

    QDataStream &operator >> (QDataStream &s, CurriculumnSemesterPrivate::KindOfWork &kod)
    {
        qint32 v;
        s >> v;
        kod = CurriculumnSemesterPrivate::KindOfWork(v);
        return s;
    }

    CurriculumnSemester::CurriculumnSemester(CurriculumnCourse *parent)
        : Entity(*new CurriculumnSemesterPrivate, parent)
    {
        Q_D(CurriculumnSemester);
        d->semester = 0;
        d->lections = 0.0;
        d->labs = 0.0;
        d->practices = 0.0;
        d->kks = 0.0;
        d->course = parent;
    }

    CurriculumnSemester::CurriculumnSemester(CurriculumnSemesterPrivate &dd, CurriculumnCourse *parent)
        : Entity(dd, parent)
    {

    }

    CurriculumnSemester::~CurriculumnSemester()
    {

    }

    void CurriculumnSemester::setSemester(CalendarSemester *semester)
    {
        Q_D(CurriculumnSemester);
        d->semester = semester;
    }

    quint32 CurriculumnSemester::number() const
    {
        Q_D(const CurriculumnSemester);
        if (!d->semester)
            return 0;
        return d->semester->number();
    }

    quint32 CurriculumnSemester::weeksCount() const
    {
        Q_D(const CurriculumnSemester);
        if (!d->semester)
            return 0;
        return d->semester->workWeeksCount();
    }

    void CurriculumnSemester::setLectionsHours(qreal hours)
    {
        Q_D(CurriculumnSemester);
        d->lections = hours;
    }

    qreal CurriculumnSemester::lectionsHours() const
    {
        Q_D(const CurriculumnSemester);
        return d->lections;
    }

    qreal CurriculumnSemester::lectionsHoursTotal() const
    {
        Q_D(const CurriculumnSemester);
        return d->lections * weeksCount();
    }

    void CurriculumnSemester::setLabsHours(qreal hours)
    {
        Q_D(CurriculumnSemester);
        d->labs = hours;
    }

    qreal CurriculumnSemester::labsHours() const
    {
        Q_D(const CurriculumnSemester);
        return d->labs;
    }

    qreal CurriculumnSemester::labsHoursTotal() const
    {
        Q_D(const CurriculumnSemester);
        return d->labs * weeksCount();
    }

    void CurriculumnSemester::setPracticesHours(qreal hours)
    {
        Q_D(CurriculumnSemester);
        d->practices = hours;
    }

    qreal CurriculumnSemester::practicesHours() const
    {
        Q_D(const CurriculumnSemester);
        return d->practices;
    }

    qreal CurriculumnSemester::practicesHoursTotal() const
    {
        Q_D(const CurriculumnSemester);
        return d->practices * weeksCount();
    }

    void CurriculumnSemester::setKKSHours(qreal hours)
    {
        Q_D(CurriculumnSemester);
        d->kks = hours;
    }

    qreal CurriculumnSemester::kksHours() const
    {
        Q_D(const CurriculumnSemester);
        return d->kks;
    }

    qreal CurriculumnSemester::kksHoursTotal() const
    {
        Q_D(const CurriculumnSemester);
        return d->kks * weeksCount();
    }

    CurriculumnCourse *CurriculumnSemester::course() const
    {
        Q_D(const CurriculumnSemester);
        return d->course;
    }

    void CurriculumnSemester::setExam(bool has)
    {
        Q_D(CurriculumnSemester);
        d->works.insert(CurriculumnSemesterPrivate::Exam, has);
    }

    quint32 CurriculumnSemester::exams() const
    {
        Q_D(const CurriculumnSemester);
        return d->works[CurriculumnSemesterPrivate::Exam] ? 1 : 0;
    }

    void CurriculumnSemester::setTest(bool has)
    {
        Q_D(CurriculumnSemester);
        d->works.insert(CurriculumnSemesterPrivate::Test, has);
    }

    quint32 CurriculumnSemester::tests() const
    {
        Q_D(const CurriculumnSemester);
        return d->works[CurriculumnSemesterPrivate::Test] ? 1 : 0;
    }

    void CurriculumnSemester::setR(bool has)
    {
        Q_D(CurriculumnSemester);
        d->works.insert(CurriculumnSemesterPrivate::R, has);
    }

    quint32 CurriculumnSemester::rs() const
    {
        Q_D(const CurriculumnSemester);
        return d->works[CurriculumnSemesterPrivate::R] ? 1 : 0;
    }

    void CurriculumnSemester::setCourseWork(bool has)
    {
        Q_D(CurriculumnSemester);
        d->works.insert(CurriculumnSemesterPrivate::CourseWork, has);
    }

    quint32 CurriculumnSemester::courseWorks() const
    {
        Q_D(const CurriculumnSemester);
        return d->works[CurriculumnSemesterPrivate::CourseWork] ? 1 : 0;
    }

    void CurriculumnSemester::setCourseProject(bool has)
    {
        Q_D(CurriculumnSemester);
        d->works.insert(CurriculumnSemesterPrivate::CourseProject, has);
    }

    quint32 CurriculumnSemester::courseProjects() const
    {
        Q_D(const CurriculumnSemester);
        return d->works[CurriculumnSemesterPrivate::CourseProject] ? 1 : 0;
    }

    void CurriculumnSemester::setDiffTest(bool has)
    {
        Q_D(CurriculumnSemester);
        d->works.insert(CurriculumnSemesterPrivate::DiffTest, has);
    }

    quint32 CurriculumnSemester::diffTests() const
    {
        Q_D(const CurriculumnSemester);
        return d->works[CurriculumnSemesterPrivate::DiffTest] ? 1 : 0;
    }

    void CurriculumnSemester::setQualification(bool has)
    {
        Q_D(CurriculumnSemester);
        d->works.insert(CurriculumnSemesterPrivate::QualTest, has);
    }

    quint32 CurriculumnSemester::qualifications() const
    {
        Q_D(const CurriculumnSemester);
        return d->works[CurriculumnSemesterPrivate::QualTest] ? 1 : 0;
    }

    void CurriculumnSemester::setDiplom(bool has)
    {
        Q_D(CurriculumnSemester);
        d->works.insert(CurriculumnSemesterPrivate::Diplom, has);
    }

    quint32 CurriculumnSemester::diploms() const
    {
        Q_D(const CurriculumnSemester);
        return d->works[CurriculumnSemesterPrivate::Diplom] ? 1 : 0;
    }

    void CurriculumnSemester::setMagister(bool has)
    {
        Q_D(CurriculumnSemester);
        d->works.insert(CurriculumnSemesterPrivate::Magister, has);
    }

    quint32 CurriculumnSemester::magisters() const
    {
        Q_D(const CurriculumnSemester);
        return d->works[CurriculumnSemesterPrivate::Magister] ? 1 : 0;
    }

    void CurriculumnSemester::setPractice(bool has)
    {
        Q_D(CurriculumnSemester);
        d->works.insert(CurriculumnSemesterPrivate::Practice, has);
    }

    quint32 CurriculumnSemester::practices() const
    {
        Q_D(const CurriculumnSemester);
        return d->works[CurriculumnSemesterPrivate::Practice] ? 1 : 0;
    }

    void CurriculumnSemester::setDimplomPractice(bool has)
    {
        Q_D(CurriculumnSemester);
        d->works.insert(CurriculumnSemesterPrivate::DipPractice, has);
    }

    quint32 CurriculumnSemester::dimplomPractices() const
    {
        Q_D(const CurriculumnSemester);
        return d->works[CurriculumnSemesterPrivate::DipPractice] ? 1 : 0;
    }

    void CurriculumnSemester::setMagisterPractice(bool has)
    {
        Q_D(CurriculumnSemester);
        d->works.insert(CurriculumnSemesterPrivate::MagPractice, has);
    }

    quint32 CurriculumnSemester::magisterPractices() const
    {
        Q_D(const CurriculumnSemester);
        return d->works[CurriculumnSemesterPrivate::MagPractice] ? 1 : 0;
    }

    void CurriculumnSemester::setQualificationPractice(bool has)
    {
        Q_D(CurriculumnSemester);
        d->works.insert(CurriculumnSemesterPrivate::QuaPractice, has);
    }

    quint32 CurriculumnSemester::qualificationPractices() const
    {
        Q_D(const CurriculumnSemester);
        return d->works[CurriculumnSemesterPrivate::QuaPractice] ? 1 : 0;
    }

    void CurriculumnSemester::setStateExam(bool has)
    {
        Q_D(CurriculumnSemester);
        d->works.insert(CurriculumnSemesterPrivate::StateExam, has);
    }

    quint32 CurriculumnSemester::stateExams() const
    {
        Q_D(const CurriculumnSemester);
        return d->works[CurriculumnSemesterPrivate::StateExam] ? 1 : 0;
    }

    void CurriculumnSemester::setEnterprisePractice(bool has)
    {
        Q_D(CurriculumnSemester);
        d->works.insert(CurriculumnSemesterPrivate::EntPractice, has);
    }

    quint32 CurriculumnSemester::enterprisePractices() const
    {
        Q_D(const CurriculumnSemester);
        return d->works[CurriculumnSemesterPrivate::EntPractice] ? 1 : 0;
    }

    QDataStream &operator<<(QDataStream &s, const CurriculumnSemester &semester)
    {
        s << semester.d_func()->lections;
        s << semester.d_func()->labs;
        s << semester.d_func()->practices;
        s << semester.d_func()->kks;
        s << semester.d_func()->works;
        return s;
    }

    QDataStream &operator>>(QDataStream &s, CurriculumnSemester &semester)
    {
        s >> semester.d_func()->lections;
        s >> semester.d_func()->labs;
        s >> semester.d_func()->practices;
        s >> semester.d_func()->kks;
        s >> semester.d_func()->works;
        return s;
    }
}

