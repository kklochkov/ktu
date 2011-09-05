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


#ifndef CURRICULUMNENTITY_H
#define CURRICULUMNENTITY_H

#include "entity.h"
#include "numberinterface.h"

namespace KTU
{
    class CURRICULUMN_EXPORT CurriculumnEntity : public Entity, public NumberInterface
    {
    public:
        void setNumber(quint32 number) { setId(number); }
        quint32 number() const { return id(); }

    protected:
        explicit CurriculumnEntity(Entity *parent);
        CurriculumnEntity(quint32 number, Entity *parent);
        CurriculumnEntity(EntityPrivate &dd, Entity *parent);
        ~CurriculumnEntity();
    };
}

#endif // CURRICULUMNENTITY_H
