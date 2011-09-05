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


#ifndef SHORTNAMEINTERFACE_H
#define SHORTNAMEINTERFACE_H

#include <QString>

namespace KTU
{
    class ShortNameInterface
    {
    public:
        virtual ~ShortNameInterface() {}

        virtual void setShortName(const QString &shortName) = 0;
        virtual QString shortName() const = 0;
    };
}

#endif // SHORTNAMEINTERFACE_H
