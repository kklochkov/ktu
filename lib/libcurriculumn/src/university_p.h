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


#ifndef UNIVERSITY_P_H
#define UNIVERSITY_P_H

#include "entity_p.h"
#include "university.h"

namespace KTU
{
    class CURRICULUMN_EXPORT UniversityPrivate : public EntityPrivate
    {
        Q_DECLARE_PUBLIC(University)

    public:
        QMap<quint64, Institute *> institutes;
    };
}

#endif // UNIVERSITY_P_H
