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

#ifndef STORAGE_H
#define STORAGE_H

#include <QString>
#include <QMap>
#include <QMultiMap>
#include <QSqlDatabase>

namespace KTU
{
    class Entity;

    class AbstractStorage
    {
    public:
        AbstractStorage();
        virtual ~AbstractStorage() { }

        virtual bool insert(const Entity &entity) = 0;
        virtual bool save(const Entity &entity) = 0;
        virtual bool remove(const Entity &entity) = 0;
        virtual bool load(Entity &entity) = 0;

        QString error() const { return m_error; }

    protected:
        enum FieldNames { Id, ShortName, Name, Data };
        enum EntityNames { Universitets,
                           Institutes,
                           Departments,
                           Chairs,
                           Specialities,
                           Groups,
                           Curriculumns,
                           Constants,
                           Disciplines };

        QString fieldName(FieldNames field) { return m_fieldNames.value(field); }
        QString entityName(const QString &className) { return m_entityNames.value(m_seriarizableObjects.value(className)); }

    protected:
        QString m_error;

    private:
        QMap<FieldNames, QString> m_fieldNames;
        QMap<EntityNames, QString> m_entityNames;
        QMultiMap<QString, EntityNames> m_seriarizableObjects;
    };

    class SqlStorage : public AbstractStorage
    {
    public:
        ~SqlStorage();

        void setUserName(const QString &name);
        QString userName() const;

        void setPassword(const QString &password);
        QString password() const;

        void setDriver(const QString &driver) { m_driverName = driver; }
        QString driver() const { return m_driverName; }

        void setHost(const QString &host);
        QString host() const;

        void setPort(int port);
        int port() const;

        void setDatabaseName(const QString &name);
        QString databaseName() const;

        bool openStorage();
        void closeStorage();

        bool insert(const Entity &entity);
        bool save(const Entity &entity);
        bool remove(const Entity &entity);
        bool load(Entity &entity);

    private:
        QSqlDatabase m_database;
        QString m_driverName;
        static QString m_connectionName;
    };
}

#endif // STORAGE_H
