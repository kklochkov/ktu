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


#ifndef ENTITY_P_H
#define ENTITY_P_H

#include "entity.h"

namespace KTU
{
    class CurriculumnDisciplineGroup;

    class CURRICULUMN_EXPORT EntityPrivate
    {
        Q_DECLARE_PUBLIC(Entity)

    public:
        EntityPrivate();
        virtual ~EntityPrivate();

        void setParent(Entity *e);

        Entity *parent;
        quint64 id;
        QList<Entity *> children;

        Entity *q_ptr;

        QMap<QString, QVariant> properties;

        static const char *nameProperty;
        static const char *shortNameProperty;
    private:
        void addChild(Entity *child);
        void removeChild(Entity *child);
    };
}

#endif // ENTITY_P_H
