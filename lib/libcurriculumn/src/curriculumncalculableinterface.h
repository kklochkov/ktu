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


#ifndef CURRICULUMNCALCULABLEINTERFACE_H
#define CURRICULUMNCALCULABLEINTERFACE_H

namespace KTU
{
    class CurriculumnCalculableInterface
    {
    public:
        virtual ~CurriculumnCalculableInterface() {}

        virtual qreal lectionsHoursTotal() const = 0;
        virtual qreal labsHoursTotal() const = 0;
        virtual qreal practicesHoursTotal() const = 0;
        virtual qreal kksHoursTotal() const = 0;

        virtual qreal autidoriumTotal() const
        {
            return lectionsHoursTotal() +
                    labsHoursTotal() +
                    practicesHoursTotal();
        }

        virtual quint32 exams() const = 0;
        virtual quint32 tests() const = 0;
        virtual quint32 rs() const = 0;
        virtual quint32 courseWorks() const = 0;
        virtual quint32 courseProjects() const = 0;
        virtual quint32 diffTests() const = 0;
        virtual quint32 qualifications() const = 0;
        virtual quint32 diploms() const = 0;
        virtual quint32 magisters() const = 0;
        virtual quint32 practices() const = 0;
        virtual quint32 dimplomPractices() const = 0;
        virtual quint32 magisterPractices() const = 0;
        virtual quint32 qualificationPractices() const = 0;
        virtual quint32 stateExams() const = 0;
        virtual quint32 enterprisePractices() const = 0;
    };
}

#endif // CURRICULUMNCALCULABLEINTERFACE_H
