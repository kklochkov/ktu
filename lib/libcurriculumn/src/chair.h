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


#ifndef CHAIR_H
#define CHAIR_H

#include "constant.h"

namespace KTU
{
    class Department;
    class ChairPrivate;

    class CURRICULUMN_EXPORT Chair : public Constant
    {
        friend class AbstractFactoryInterface;
        Q_DECLARE_PRIVATE(Chair)

        explicit Chair(Department *parent = 0);
        Chair(quint64 id, Department *parent = 0);
        Chair(ChairPrivate &dd, Department *parent = 0);
        ~Chair();

    public:
        Department *department() const;
    };
}

#endif // CHAIR_H
