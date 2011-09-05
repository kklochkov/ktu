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

#ifndef CALENDARWEEKSIGN_H
#define CALENDARWEEKSIGN_H

#include "constant.h"

namespace KTU
{
    class CURRICULUMN_EXPORT CalendarWeekSign : public Constant
    {
        friend class AbstractFactoryInterface;

    public:
        void setSign(const QString &sign) { setShortName(sign); }
        QString sign() const { return shortName(); }

        void setDescription(const QString &description) { setName(description); }
        QString description() const { return name(); }

        bool operator==(const CalendarWeekSign &other) const;

    private:
        explicit CalendarWeekSign(Entity *parent = 0);
        CalendarWeekSign(quint64 id, Entity *parent);
        ~CalendarWeekSign();

        void setName(const QString &name) { Constant::setName(name); }
        QString name() const { return Constant::name(); }
        void setShortName(const QString &name) { Constant::setShortName(name); }
        QString shortName() const { return Constant::shortName(); }
    };
}
Q_DECLARE_METATYPE(KTU::CalendarWeekSign *)

#endif // CALENDARWEEKSIGN_H
