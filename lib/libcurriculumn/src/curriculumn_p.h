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


#ifndef CURRICULUMN_P_H
#define CURRICULUMN_P_H

#include "entity_p.h"
#include "curriculumn.h"

namespace KTU
{
    template <typename T>
    class CURRICULUMN_EXPORT AbstractCurriculumnDataPrivate : public EntityPrivate
    {
    public:
        qreal lectionsHoursTotal() const
        {
            return calculateTotal<qreal>(&T::lectionsHoursTotal);
        }

        qreal labsHoursTotal() const
        {
            return calculateTotal<qreal>(&T::labsHoursTotal);
        }

        qreal practicesHoursTotal() const
        {
            return calculateTotal<qreal>(&T::practicesHoursTotal);
        }

        qreal kksHoursTotal() const
        {
            return calculateTotal<qreal>(&T::kksHoursTotal);
        }

        qreal autidoriumTotal() const
        {
            return lectionsHoursTotal() +
                    labsHoursTotal() +
                    practicesHoursTotal();
        }

        quint32 exams() const
        {
            return calculateTotal<quint32>(&T::exams);
        }

        quint32 tests() const
        {
            return calculateTotal<quint32>(&T::tests);
        }

        quint32 rs() const
        {
            return calculateTotal<quint32>(&T::rs);
        }

        quint32 courseWorks() const
        {
            return calculateTotal<quint32>(&T::courseWorks);
        }

        quint32 courseProjects() const
        {
            return calculateTotal<quint32>(&T::courseProjects);
        }

        quint32 diffTests() const
        {
            return calculateTotal<quint32>(&T::diffTests);
        }

        quint32 qualifications() const
        {
            return calculateTotal<quint32>(&T::qualifications);
        }

        quint32 diploms() const
        {
            return calculateTotal<quint32>(&T::diploms);
        }

        quint32 magisters() const
        {
            return calculateTotal<quint32>(&T::magisters);
        }

        quint32 practices() const
        {
            return calculateTotal<quint32>(&T::practices);
        }

        quint32 dimplomPractices() const
        {
            return calculateTotal<quint32>(&T::dimplomPractices);
        }

        quint32 magisterPractices() const
        {
            return calculateTotal<quint32>(&T::magisterPractices);
        }

        quint32 qualificationPractices() const
        {
            return calculateTotal<quint32>(&T::qualificationPractices);
        }

        quint32 stateExams() const
        {
            return calculateTotal<quint32>(&T::stateExams);
        }

        quint32 enterprisePractices() const
        {
            return calculateTotal<quint32>(&T::enterprisePractices);
        }

        virtual T *createEntity() const = 0;
        virtual void deleteEntity(T *entity) const = 0;

        T *addEntity()
        {
            T *entity = createEntity();
            entities << entity;
            return entity;
        }

        void removeEntity(T *t)
        {
            entities.removeAll(t);
            deleteEntity(t);
        }

        void clear()
        {
            foreach (T *t, entities)
                removeEntity(t);
        }

        T *entity(int index) const
        {
            if (index >= entities.count() || index < 0)
                return 0;
            return entities[index];
        }

        int indexOf(T *entity) const
        {
            if (entities.isEmpty())
                return -1;
            return entities.indexOf(entity);
        }

        template <typename C>
        bool hasEntity(C *c, C *(T::*func)() const) const
        {
            return entityByConstant<C>(c, func);
        }

        template <typename C>
        T *entityByConstant(C *c, C *(T::*func)() const) const
        {
            foreach (T *t, entities) {
                if ((t->*func)() == c)
                    return t;
            }
            return 0;
        }

    private:
        template <typename ReturnType>
        ReturnType calculateTotal(ReturnType (T::*func)() const) const
        {
            ReturnType res = 0;
            QList<T *> list = entities;
            foreach (T *t, list)
                res += (t->*func)();
            return res;
        }

    public:
        QList<T *> entities;
    };

    class Calendar;

    class CURRICULUMN_EXPORT CurriculumnPrivate : public AbstractCurriculumnDataPrivate<CurriculumnDisciplineGroup>
    {
        Q_DECLARE_PUBLIC(Curriculumn)

    public:
        CurriculumnDisciplineGroup *createEntity() const;
        void deleteEntity(CurriculumnDisciplineGroup *entity) const;

        Speciality *speciality;
        Department *department;
        Chair *chair;
        QString specialization;
        QString qualification;
        EducationForm *educationForm;
        quint32 educationTerm;
        Calendar *calendar;
    };
}

#endif // CURRICULUMN_P_H
