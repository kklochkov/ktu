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

#include "calendarweeksign.h"

namespace KTU
{
    CalendarWeekSign::CalendarWeekSign(Entity *parent)
        : Constant(parent)
    {

    }

    CalendarWeekSign::CalendarWeekSign(quint64 id, Entity *parent)
        : Constant(id, parent)
    {

    }

    CalendarWeekSign::~CalendarWeekSign()
    {

    }

    bool CalendarWeekSign::operator==(const CalendarWeekSign &other) const
    {
        return (id() == other.id()) &&
                (sign() == other.sign()) &&
                (description() == other.description());
    }
}
