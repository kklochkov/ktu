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


#ifndef ENTITYFACTORY_P_H
#define ENTITYFACTORY_P_H

#include "entity_p.h"
#include "entityfactory.h"
#include "storage.h"

namespace KTU
{
    class CURRICULUMN_EXPORT EntityFactoryPrivate : public EntityPrivate
    {
        Q_DECLARE_PUBLIC(EntityFactory)

    public:
        template<typename T, typename P>
        T *createEntity(QMap<quint64, T *> &container, P *parent)
        {
            Q_Q(EntityFactory);
            const quint64 id = container.isEmpty() ? 1 : (*(--container.constEnd()))->id() + 1;
            T *t = q->createEntity<T, P>(id, parent);
            if (!storage->insert(*t)) {
                q->removeEntity(t);
                return 0;
            }
            container.insert(t->id(), t);
            return t;
        }

        template<typename T>
        T *entity(quint64 id, const QMap<quint64, T *> &container) const
        {
            typename QMap<quint64, T *>::const_iterator it = container.constFind(id);
            if (it == container.constEnd())
                return 0;
            return (*it);
        }

        template<typename T>
        T *entity(const QString &name, QString (T::*compareFunc)() const, const QMap<quint64, T *> &container) const
        {
            typename QMap<quint64, T *>::const_iterator it = container.constBegin();
            typename QMap<quint64, T *>::const_iterator end = container.constEnd();
            for (; it != end; ++it) {
                if (((*it)->*compareFunc)() == name)
                    return (*it);
            }
            return 0;
        }

        template<typename T>
        void removeEntity(quint64 id, QMap<quint64, T *> &container)
        {
            Q_Q(EntityFactory);
            T *t = entity<T>(id, container);
            if (!t)
                return;
            container.remove(t->id());
            if (!storage->remove(*t))
                qWarning() << Q_FUNC_INFO << storage->error();
            q->removeEntity(t);
        }

    public:
        AbstractStorage *storage;
    };
}

#endif // ENTITYFACTORY_P_H
