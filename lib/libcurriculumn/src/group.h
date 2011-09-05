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


#ifndef GROUP_H
#define GROUP_H

#include "constant.h"

namespace KTU
{
    class GroupPrivate;
    class Speciality;
    class EducationForm;
    class Curriculumn;

    class CURRICULUMN_EXPORT Group : public Constant
    {
        friend class AbstractFactoryInterface;

        Q_DECLARE_PRIVATE(Group)

        explicit Group(Speciality *parent = 0);
        Group(quint64 id, Speciality *parent = 0);
        Group(GroupPrivate &dd, Speciality *parent = 0);
        ~Group();

    public:
        Speciality *speciality() const;

        void setEducationForm(EducationForm *form);
        EducationForm *educationForm() const;

        void setStartYear(quint32 year);
        quint32 startYear() const;

        void setEndYear(quint32 year);
        quint32 endYear() const;

        void setStudentsCount(quint32 count);
        quint32 studentsCount() const;

        void setSubGroupsCount(quint32 count);
        quint32 subGroupsCount() const;

        quint32 course() const;

        void setCurriculumn(Curriculumn *curriculumn);
        Curriculumn *curriculumn() const;
    };
}

#endif // GROUP_H
