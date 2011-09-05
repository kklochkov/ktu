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


#ifndef NUMBERINTERFACE_H
#define NUMBERINTERFACE_H

#include <QtGlobal>

namespace KTU
{
    class NumberInterface
    {
    public:
        virtual ~NumberInterface() {}

        virtual void setNumber(quint32 number) = 0;
        virtual quint32 number() const = 0;
    };
}

#endif // NUMBERINTERFACE_H
