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


#ifndef CHAIR_P_H
#define CHAIR_P_H

#include "entity_p.h"
#include "chair.h"

namespace KTU
{
    class Department;

    class ChairPrivate : public EntityPrivate
    {
        Q_DECLARE_PUBLIC(Chair)

    public:
        Department *department;
    };
}

#endif // CHAIR_P_H
