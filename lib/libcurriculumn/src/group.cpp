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

#include <QDate>

#include "group.h"
#include "group_p.h"
#include "speciality.h"

namespace KTU
{
    Group::Group(Speciality *parent)
        : Constant(*new GroupPrivate, parent)
    {
        Q_D(Group);
        d->speciality = parent;
        d->educationForm = 0;
        d->startYear = 0;
        d->endYear = 0;
        d->studentsCount = 0;
        d->subGroupsCount = 0;
        d->curriculumn = 0;
    }

    Group::Group(quint64 id, Speciality *parent)
        : Constant(*new GroupPrivate, parent)
    {
        Q_D(Group);
        d->speciality = parent;
        d->educationForm = 0;
        d->startYear = 0;
        d->endYear = 0;
        d->studentsCount = 0;
        d->subGroupsCount = 0;
        d->curriculumn = 0;
        setId(id);
    }

    Group::Group(GroupPrivate &dd, Speciality *parent)
        : Constant(dd, parent)
    {
        Q_D(Group);
        d->speciality = parent;
    }

    Group::~Group()
    {

    }

    Speciality *Group::speciality() const
    {
        Q_D(const Group);
        return d->speciality;
    }

    void Group::setEducationForm(EducationForm *form)
    {
        Q_D(Group);
        d->educationForm = form;
    }

    EducationForm *Group::educationForm() const
    {
        Q_D(const Group);
        return d->educationForm;
    }

    void Group::setStartYear(quint32 year)
    {
        Q_D(Group);
        d->startYear = year;
    }

    quint32 Group::startYear() const
    {
        Q_D(const Group);
        return d->startYear;
    }

    void Group::setEndYear(quint32 year)
    {
        Q_D(Group);
        d->endYear = year;
    }

    quint32 Group::endYear() const
    {
        Q_D(const Group);
        return d->endYear;
    }

    void Group::setStudentsCount(quint32 count)
    {
        Q_D(Group);
        d->studentsCount = count;
    }

    quint32 Group::studentsCount() const
    {
        Q_D(const Group);
        return d->studentsCount;
    }

    void Group::setSubGroupsCount(quint32 count)
    {
        Q_D(Group);
        d->subGroupsCount = count;
    }

    quint32 Group::subGroupsCount() const
    {
        Q_D(const Group);
        return d->subGroupsCount;
    }

    quint32 Group::course() const
    {
        Q_D(const Group);
        return QDate::currentDate().year() - d->startYear + 1;
    }

    void Group::setCurriculumn(Curriculumn *curriculumn)
    {
        Q_D(Group);
        d->curriculumn = curriculumn;
    }

    Curriculumn *Group::curriculumn() const
    {
        Q_D(const Group);
        return d->curriculumn;
    }
}
