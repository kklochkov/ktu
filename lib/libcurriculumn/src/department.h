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


#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include "entityfactory.h"
#include "constant.h"

namespace KTU
{
    class DepartmentPrivate;
    class Chair;
    class Speciality;
    class Institute;

    class CURRICULUMN_EXPORT Department : public Constant
    {
        friend class AbstractFactoryInterface;

        Q_DECLARE_PRIVATE(Department)

        explicit Department(Institute *parent = 0);
        Department(quint64 id, Institute *parent = 0);
        Department(DepartmentPrivate &dd, Institute *parent = 0);
        ~Department();

    public:
        Chair *createChair(const QString &name = QString());
        Chair *chair(quint64 id) const;
        QList<Chair *> chairs() const;
        void removeChair(quint64 id);

        Speciality *createSpeciality(const QString &name = QString());
        Speciality *speciality(quint64 id) const;
        QList<Speciality *> specialities() const;
        void removeSpeciality(quint64 id);

        Institute *institute() const;
    };
}

#endif // DEPARTMENT_H
