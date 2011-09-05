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

#include "entityfactory.h"
#include "entityfactory_p.h"

namespace KTU
{
    AbstractFactoryInterface::~AbstractFactoryInterface()
    {

    }

    EntityFactory::EntityFactory(Entity *parent)
        : Entity(*new EntityFactoryPrivate, parent)
    {

    }

    EntityFactory::EntityFactory(EntityFactoryPrivate &dd, Entity *parent)
        : Entity(dd, parent)
    {

    }
}
