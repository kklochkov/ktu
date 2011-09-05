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


#include "university.h"
#include "university_p.h"
#include "institute.h"
#include "constantsfactory.h"

namespace KTU
{
    University::University(Entity *parent)
        : Constant(*new UniversityPrivate, parent)
    {

    }

    University::University(quint64 id, Entity *parent)
        : Constant(*new UniversityPrivate, parent)
    {
        setId(id);
    }

    University::University(UniversityPrivate &dd, Entity *parent)
        : Constant(dd, parent)
    {

    }

    University::~University()
    {

    }

    void University::setName(const QString &name)
    {
        setProperty(EntityPrivate::nameProperty, name);
    }

    QString University::name() const
    {
        return property(EntityPrivate::nameProperty).toString();
    }

    void University::setShortName(const QString &name)
    {
        setProperty(EntityPrivate::shortNameProperty, name);
    }

    QString University::shortName() const
    {
        return property(EntityPrivate::shortNameProperty).toString();
    }

    Institute *University::createInstitute(const QString &name)
    {
        Q_D(University);
        Institute *institute = constantsFactory.createInstitute(id(), name);
        if (!institute)
            return 0;
        d->institutes.insert(institute->id(), institute);
        return institute;
    }

    Institute *University::institute(quint64 id) const
    {
        return constantsFactory.institute(id);
    }

    QList<Institute *> University::institutes() const
    {
        Q_D(const University);
        return d->institutes.values();
    }

    void University::removeInstitute(quint64 id)
    {
        Q_D(University);
        d->institutes.remove(id);
        constantsFactory.removeInstitute(id);
    }
}
