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

#include "chair.h"
#include "chair_p.h"
#include "department.h"

namespace KTU
{
    Chair::Chair(Department *parent)
        : Constant(*new ChairPrivate, parent)
    {
        Q_D(Chair);
        d->department = parent;
    }

    Chair::Chair(quint64 id, Department *parent)
        : Constant(*new ChairPrivate, parent)
    {
        Q_D(Chair);
        d->department = parent;
        setId(id);
    }

    Chair::Chair(ChairPrivate &dd, Department *parent)
        : Constant(dd, parent)
    {
        Q_D(Chair);
        d->department = parent;
    }

    Chair::~Chair()
    {

    }

    Department *Chair::department() const
    {
        Q_D(const Chair);
        return d->department;
    }
}
