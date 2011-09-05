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


#ifndef NAMEINTERFACE_H
#define NAMEINTERFACE_H

#include <QString>

namespace KTU
{
    class NameInterface
    {
    public:
        virtual ~NameInterface() {}

        virtual void setName(const QString &name) = 0;
        virtual QString name() const = 0;
    };
}

#endif // NAMEINTERFACE_H
