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

#include "constants.h"
#include "constantsfactory.h"

namespace KTU
{
    Discipline::Discipline(Entity *parent)
        : Constant(parent)
    {

    }

    Discipline::Discipline(quint64 id, Entity *parent)
        : Constant(id, parent)
    {

    }

    Discipline::~Discipline()
    {

    }

    CurriculumnSection::CurriculumnSection(Entity *parent)
        : Constant(parent)
    {

    }

    CurriculumnSection::CurriculumnSection(quint64 id, Entity *parent)
        : Constant(id, parent)
    {

    }

    CurriculumnSection::~CurriculumnSection()
    {

    }

    CurriculumnGroup::CurriculumnGroup(Entity *parent)
        : Constant(parent)
    {

    }

    CurriculumnGroup::CurriculumnGroup(quint64 id, Entity *parent)
        : Constant(id, parent)
    {

    }

    CurriculumnGroup::~CurriculumnGroup()
    {

    }

    EducationLevel::EducationLevel(Entity *parent)
        : Constant(parent)
    {

    }

    EducationLevel::EducationLevel(quint64 id, Entity *parent)
        : Constant(id, parent)
    {

    }

    EducationLevel::~EducationLevel()
    {

    }

    EducationForm::EducationForm(Entity *parent)
        : Constant(parent)
    {

    }

    EducationForm::EducationForm(quint64 id, Entity *parent)
        : Constant(id, parent)
    {

    }

    EducationForm::~EducationForm()
    {

    }
}
