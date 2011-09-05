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

#include "constant.h"
#include "entity_p.h"

namespace KTU
{
    Constant::Constant(Entity *parent)
        : Entity(parent)
    {

    }

    Constant::Constant(quint64 id, Entity *parent)
        : Entity(parent)
    {
        setId(id);
    }

    Constant::Constant(EntityPrivate &dd, Entity *parent)
        : Entity(dd, parent)
    {

    }

    Constant::~Constant()
    {

    }

    void Constant::setName(const QString &name)
    {
        setProperty(EntityPrivate::nameProperty, name);
    }

    QString Constant::name() const
    {
        return property(EntityPrivate::nameProperty).toString();
    }

    void Constant::setShortName(const QString &name)
    {
        setProperty(EntityPrivate::shortNameProperty, name);
    }

    QString Constant::shortName() const
    {
        return property(EntityPrivate::shortNameProperty).toString();
    }

    QDataStream &operator << (QDataStream &out, const Constant &constant)
    {
        out << static_cast<const Entity &>(constant);
        out << constant.name();
        out << constant.shortName();
        return out;
    }

    QDataStream &operator >> (QDataStream &in, Constant &constant)
    {
        in >> static_cast<Entity &>(constant);
        QString name;
        QString shortName;
        in >> name;
        in >> shortName;
        constant.setName(name);
        constant.setShortName(shortName);
        return in;
    }
}
