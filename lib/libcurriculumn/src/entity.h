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

#ifndef ENTITY_H
#define ENTITY_H

#include <QVariant>
#include <QDataStream>

#include "global.h"

namespace KTU
{
    class EntityPrivate;
    class AbstractFactoryInterface;

    class CURRICULUMN_EXPORT Entity
    {
        Q_DECLARE_PRIVATE(Entity)
        Q_DISABLE_COPY(Entity)

        friend class AbstractFactoryInterface;

    public:
        quint64 id() const;

        friend QDataStream &operator>>(QDataStream &s, Entity &e);
        friend QDataStream &operator<<(QDataStream &s, const Entity &e);

        Entity *parent() const;

    protected:
        explicit Entity(Entity *parent = 0);
        Entity(quint64 id, Entity *parent);
        Entity(EntityPrivate &dd, Entity *parent = 0);
        virtual ~Entity();

        void setId(quint64 id);

        void setParent(Entity *parent);

        void setProperty(const char *name, const QVariant &value);
        QVariant property(const char *name) const;

    protected:
        EntityPrivate *const d_ptr;
    };

    CURRICULUMN_EXPORT QDataStream &operator>>(QDataStream &s, Entity &e);
    CURRICULUMN_EXPORT QDataStream &operator<<(QDataStream &s, const Entity &e);
}

#endif // ENTITY_H
