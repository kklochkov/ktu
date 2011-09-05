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


#ifndef CONSTANT_H
#define CONSTANT_H

#include "entity.h"
#include "nameinterface.h"
#include "shortnameinterface.h"

namespace KTU
{
    class CURRICULUMN_EXPORT Constant : public Entity, public NameInterface, public ShortNameInterface
    {
        friend class EntityFactory;

    public:
        void setName(const QString &name);
        QString name() const;

        void setShortName(const QString &name);
        QString shortName() const;

    protected:
        explicit Constant(Entity *parent = 0);
        Constant(quint64 id, Entity *parent = 0);
        Constant(EntityPrivate &dd, Entity *parent = 0);
        ~Constant();
    };

    CURRICULUMN_EXPORT QDataStream &operator>>(QDataStream &s, Constant &e);
    CURRICULUMN_EXPORT QDataStream &operator<<(QDataStream &s, const Constant &e);
}

#endif // CONSTANT_H
