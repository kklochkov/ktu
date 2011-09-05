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


#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include "entity.h"

namespace KTU
{
    class EntityFactoryPrivate;

    class AbstractFactoryInterface
    {
    public:
        virtual ~AbstractFactoryInterface() = 0;

        template<typename T, typename P>
        T *createEntity(quint64 id, P *parent) const { return new T(id, parent); }

        template<typename T>
        void removeEntity(T *t) const { delete t; }
    };

    class EntityFactory : public Entity, protected AbstractFactoryInterface
    {
        Q_DECLARE_PRIVATE(EntityFactory)

    protected:
        EntityFactory(Entity *parent = 0);
        EntityFactory(EntityFactoryPrivate &dd, Entity *parent = 0);
    };
}

#endif // ENTITYFACTORY_H
