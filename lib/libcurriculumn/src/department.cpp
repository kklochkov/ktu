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

#include "department.h"
#include "department_p.h"
#include "speciality.h"
#include "chair.h"
#include "constantsfactory.h"
#include "institute.h"

namespace KTU
{
    Department::Department(Institute *parent)
        : Constant(*new DepartmentPrivate, parent)
    {
        Q_D(Department);
        d->institute = parent;
    }

    Department::Department(quint64 id, Institute *parent)
        : Constant(*new DepartmentPrivate, parent)
    {
        Q_D(Department);
        d->institute = parent;
        setId(id);
    }

    Department::Department(DepartmentPrivate &dd, Institute *parent)
        : Constant(dd, parent)
    {
        Q_D(Department);
        d->institute = parent;
    }

    Department::~Department()
    {

    }

    Chair *Department::createChair(const QString &name)
    {
        Q_D(Department);
        Chair *chair = constantsFactory.createChair(id(), name);
        if (!chair)
            return 0;
        d->chairs.insert(chair->id(), chair);
        return chair;
    }

    Chair *Department::chair(quint64 id) const
    {
        return constantsFactory.chair(id);
    }

    QList<Chair *> Department::chairs() const
    {
        Q_D(const Department);
        return d->chairs.values();
    }

    void Department::removeChair(quint64 id)
    {
        Q_D(Department);
        d->chairs.remove(id);
        constantsFactory.removeChair(id);
    }

    Speciality *Department::createSpeciality(const QString &name)
    {
        Q_D(Department);
        Speciality *speciality = constantsFactory.createSpeciality(id(), name);
        if (!speciality)
            return 0;
        d->specialities.insert(speciality->id(), speciality);
        return speciality;
    }

    Speciality *Department::speciality(quint64 id) const
    {
        return constantsFactory.speciality(id);
    }

    QList<Speciality *> Department::specialities() const
    {
        Q_D(const Department);
        return d->specialities.values();
    }

    void Department::removeSpeciality(quint64 id)
    {
        Q_D(Department);
        d->specialities.remove(id);
        constantsFactory.removeSpeciality(id);
    }

    Institute *Department::institute() const
    {
        Q_D(const Department);
        return d->institute;
    }
}
