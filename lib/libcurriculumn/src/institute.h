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


#ifndef INSTITUTE_H
#define INSTITUTE_H

#include "entityfactory.h"
#include "constant.h"

namespace KTU
{
    class InstitutePrivate;
    class Department;
    class University;

    class CURRICULUMN_EXPORT Institute : public Constant
    {
        friend class AbstractFactoryInterface;

        Q_DECLARE_PRIVATE(Institute)

        explicit Institute(University *parent = 0);
        Institute(quint64 id, University *parent = 0);
        Institute(InstitutePrivate &dd, University *parent = 0);
        ~Institute();

    public:
        Department *createDepartment(const QString &name = QString());
        Department *department(quint64 id) const;
        QList<Department *> departments() const;
        void removeDepartment(quint64 id);

        University *university() const;
    };
}

#endif // INSTITUTE_H
