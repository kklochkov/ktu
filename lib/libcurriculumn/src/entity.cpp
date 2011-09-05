/****************************************************************************
**
** Copyright (C) 2010 Kirill (spirit) Klochkov.
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

#include <QDebug>

#include "entity.h"
#include "entity_p.h"

namespace KTU
{
    const char *EntityPrivate::nameProperty = "name";
    const char *EntityPrivate::shortNameProperty = "shortName";

    EntityPrivate::EntityPrivate()
        : parent(0),
          id(0),
          q_ptr(0)
    {

    }

    EntityPrivate::~EntityPrivate()
    {

    }

    void EntityPrivate::setParent(Entity *o)
    {
        Q_Q(Entity);
        if (o == parent)
            return;
        if (parent)
            parent->d_func()->removeChild(q);
        if (o)
            o->d_func()->addChild(q);
        parent = o;
    }

    void EntityPrivate::addChild(Entity *child)
    {
        Q_Q(Entity);
        if (!child)
            return;
        if (child->parent() == q)
            return;
        if (children.contains(child))
            return;
        children << child;
    }

    void EntityPrivate::removeChild(Entity *child)
    {
        Q_Q(Entity);
        if (!child)
            return;
        if (child->parent() != q)
            return;
        Q_UNUSED(children.removeAll(child));
    }
//---------------------------------------------------------------------------------------
    Entity::Entity(Entity *parent)
        : d_ptr(new EntityPrivate)
    {
        Q_D(Entity);
        d->q_ptr = this;

        setParent(parent);
    }

    Entity::Entity(quint64 id, Entity *parent)
        : d_ptr(new EntityPrivate)
    {
        Q_D(Entity);
        d->q_ptr = this;
        d->id = id;

        setParent(parent);
    }

    Entity::Entity(EntityPrivate &dd, Entity *parent)
        : d_ptr(&dd)
    {
        Q_D(Entity);
        d->q_ptr = this;

        setParent(parent);
    }

    Entity::~Entity()
    {
        delete d_ptr;
    }

    void Entity::setParent(Entity *parent)
    {
        Q_D(Entity);
        d->setParent(parent);
    }

    Entity *Entity::parent() const
    {
        return d_ptr->parent;
    }

    void Entity::setProperty(const char *name, const QVariant &value)
    {
        Q_D(Entity);
        const QLatin1String tmpName(name);
        const QVariant oldValue = d->properties[tmpName];
        if (oldValue.type() == value.type() || oldValue.type() == QVariant::Invalid) {
            d->properties[tmpName] = value;
        } else {
            qDebug() << Q_FUNC_INFO << QString("Property's '%1' type (%2) doesn't equal to new value type (%3)")
                        .arg(tmpName)
                        .arg(oldValue.typeName())
                        .arg(value.typeName());
        }
    }

    QVariant Entity::property(const char *name) const
    {
        Q_D(const Entity);
        const QLatin1String tmpName(name);
        return d->properties[tmpName];
    }

    void Entity::setId(quint64 id)
    {
        d_ptr->id = id;
    }

    quint64 Entity::id() const
    {
        return d_ptr->id;
    }

    QDataStream &operator<<(QDataStream &s, const Entity &e)
    {
        s << e.d_func()->id;
        return s;
    }

    QDataStream &operator>>(QDataStream &s, Entity &e)
    {
        s >> e.d_func()->id;
        return s;
    }
}
