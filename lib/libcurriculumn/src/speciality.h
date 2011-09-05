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


#ifndef SPECIALITY_H
#define SPECIALITY_H

#include "constant.h"

namespace KTU
{
    class SpecialityPrivate;
    class EducationLevel;
    class Department;
    class Group;

    class CURRICULUMN_EXPORT Speciality : public Constant
    {
        friend class AbstractFactoryInterface;

        Q_DECLARE_PRIVATE(Speciality)

        explicit Speciality(Department *parent = 0);
        Speciality(quint64 id, Department *parent = 0);
        Speciality(SpecialityPrivate &dd, Department *parent = 0);
        ~Speciality();

    public:
        Department *department() const;

        void setCode(const QString &code);
        QString code() const;

        void setLevel(EducationLevel *level);
        EducationLevel *level() const;

        Group *createGroup(const QString &name = QString());
        Group *group(quint64 id) const;
        QList<Group *> groups() const;
        void removeGroup(quint64 id);
    };
}

#endif // SPECIALITY_H
