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


#include "institute.h"
#include "institute_p.h"
#include "department.h"
#include "constantsfactory.h"
#include "university.h"

namespace KTU
{
    Institute::Institute(University *parent)
        : Constant(*new InstitutePrivate, parent)
    {
        Q_D(Institute);
        d->university = parent;
    }

    Institute::Institute(quint64 id, University *parent)
        : Constant(*new InstitutePrivate, parent)
    {
        Q_D(Institute);
        d->university = parent;
        setId(id);
    }

    Institute::Institute(InstitutePrivate &dd, University *parent)
        : Constant(dd, parent)
    {
        Q_D(Institute);
        d->university = parent;
    }

    Institute::~Institute()
    {

    }

    Department *Institute::createDepartment(const QString &name)
    {
        Q_D(Institute);
        Department *department = constantsFactory.createDepartment(id(), name);
        if (!department)
            return 0;
        d->departments.insert(department->id(), department);
        return department;
    }

    Department *Institute::department(quint64 id) const
    {
        return constantsFactory.department(id);
    }

    QList<Department *> Institute::departments() const
    {
        Q_D(const Institute);
        return d->departments.values();
    }

    void Institute::removeDepartment(quint64 id)
    {
        Q_D(Institute);
        d->departments.remove(id);
        constantsFactory.removeDepartment(id);
    }

    University *Institute::university() const
    {
        Q_D(const Institute);
        return d->university;
    }
}
