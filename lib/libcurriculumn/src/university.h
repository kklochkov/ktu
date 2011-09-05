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


#ifndef UNIVERSITY_H
#define UNIVERSITY_H

#include "entityfactory.h"
#include "constant.h"

namespace KTU
{
    class UniversityPrivate;
    class Institute;

    class CURRICULUMN_EXPORT University : public Constant
    {
        friend class AbstractFactoryInterface;

        Q_DECLARE_PRIVATE(University)

        explicit University(Entity *parent = 0);
        University(quint64 id, Entity *parent = 0);
        University(UniversityPrivate &dd, Entity *parent = 0);
        ~University();

    public:
        void setName(const QString &name);
        QString name() const;

        void setShortName(const QString &name);
        QString shortName() const;

        Institute *createInstitute(const QString &name = QString());
        Institute *institute(quint64 id) const;
        QList<Institute *> institutes() const;
        void removeInstitute(quint64 id);
    };
}

#endif // UNIVERSITY_H
