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


#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "constant.h"

namespace KTU
{
    class CURRICULUMN_EXPORT Discipline : public Constant
    {
        friend class AbstractFactoryInterface;

        explicit Discipline(Entity *parent = 0);
        Discipline(quint64 id, Entity *parent = 0);
        ~Discipline();
    };

    class CURRICULUMN_EXPORT CurriculumnSection : public Constant
    {
        friend class AbstractFactoryInterface;

        explicit CurriculumnSection(Entity *parent = 0);
        CurriculumnSection(quint64 id, Entity *parent = 0);
        ~CurriculumnSection();
    };

    class CURRICULUMN_EXPORT CurriculumnGroup : public Constant
    {
        friend class AbstractFactoryInterface;

        explicit CurriculumnGroup(Entity *parent = 0);
        CurriculumnGroup(quint64 id, Entity *parent = 0);
        ~CurriculumnGroup();
    };

    class CURRICULUMN_EXPORT EducationLevel : public Constant
    {
        friend class AbstractFactoryInterface;

        explicit EducationLevel(Entity *parent = 0);
        EducationLevel(quint64 id, Entity *parent = 0);
        ~EducationLevel();
    };

    class CURRICULUMN_EXPORT EducationForm : public Constant
    {
        friend class AbstractFactoryInterface;

        explicit EducationForm(Entity *parent = 0);
        EducationForm(quint64 id, Entity *parent = 0);
        ~EducationForm();
    };
}

#endif // CONSTANTS_H
