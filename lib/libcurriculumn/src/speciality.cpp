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

#include "speciality.h"
#include "speciality_p.h"
#include "department.h"
#include "constantsfactory.h"
#include "group.h"

namespace KTU
{
    Speciality::Speciality(Department *parent)
        : Constant(*new SpecialityPrivate, parent)
    {
        Q_D(Speciality);
        d->level = constantsFactory.defaultEducationLevel();
        d->department = parent;
    }

    Speciality::Speciality(quint64 id, Department *parent)
        : Constant(*new SpecialityPrivate, parent)
    {
        Q_D(Speciality);
        d->level = constantsFactory.defaultEducationLevel();
        d->department = parent;
        setId(id);
    }

    Speciality::Speciality(SpecialityPrivate &dd, Department *parent)
        : Constant(dd, parent)
    {
        Q_D(Speciality);
        d->department = parent;
    }

    Speciality::~Speciality()
    {

    }

    Department *Speciality::department() const
    {
        Q_D(const Speciality);
        return d->department;
    }

    void Speciality::setCode(const QString &code)
    {
        Q_D(Speciality);
        d->code = code;
    }

    QString Speciality::code() const
    {
        Q_D(const Speciality);
        return d->code;
    }

    void Speciality::setLevel(EducationLevel *level)
    {
        Q_D(Speciality);
        d->level = level;
    }

    EducationLevel *Speciality::level() const
    {
        Q_D(const Speciality);
        return d->level;
    }

    Group *Speciality::createGroup(const QString &name)
    {
        Q_D(Speciality);
        Group *res = constantsFactory.createGroup(id(), name);
        if (!res)
            return 0;
        d->groups.insert(res->id(), res);
        return res;
    }

    Group *Speciality::group(quint64 id) const
    {
        return constantsFactory.group(id);
    }

    QList<Group *> Speciality::groups() const
    {
        Q_D(const Speciality);
        return d->groups.values();
    }

    void Speciality::removeGroup(quint64 id)
    {
        Q_D(Speciality);
        d->groups.remove(id);
        constantsFactory.removeGroup(id);
    }
}
