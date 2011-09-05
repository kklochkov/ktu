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


#ifndef CURRICULUMNFACTORY_P_H
#define CURRICULUMNFACTORY_P_H

#include "entityfactory_p.h"
#include "curriculumnfactory.h"

namespace KTU
{
    class CURRICULUMN_EXPORT CurriculumnFactoryPrivate : public EntityFactoryPrivate
    {
        Q_DECLARE_PUBLIC(CurriculumnFactory)

    public:
        QMap<quint32, Curriculumn *> curriculumns;
    };
}

#endif // CURRICULUMNFACTORY_P_H
