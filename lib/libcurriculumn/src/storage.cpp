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

#include <QtSql>

#include "entity.h"
#include "storage.h"

#include "university.h"
#include "institute.h"
#include "department.h"
#include "speciality.h"
#include "chair.h"
#include "group.h"
#include "curriculumn.h"
#include "constants.h"
#include "calendarweeksign.h"

namespace KTU
{
    QString SqlStorage::m_connectionName = "ktu_sql_storage_connection";

    AbstractStorage::AbstractStorage()
    {
        m_fieldNames[Id] = "id";
        m_fieldNames[ShortName] = "shortName";
        m_fieldNames[Name] = "name";
        m_fieldNames[Data] = "data";

        m_entityNames[Universitets] = "universitets";
        m_entityNames[Institutes] = "institutes";
        m_entityNames[Departments] = "departments";
        m_entityNames[Specialities] = "specialities";
        m_entityNames[Chairs] = "chairs";
        m_entityNames[Groups] = "groups";
        m_entityNames[Curriculumns] = "curriculumns";
        m_entityNames[Constants] = "constants";
        m_entityNames[Disciplines] = "disciplines";

        m_seriarizableObjects.insertMulti(typeid(University).name(), Universitets);
        m_seriarizableObjects.insertMulti(typeid(Institute).name(), Institutes);
        m_seriarizableObjects.insertMulti(typeid(Department).name(), Departments);
        m_seriarizableObjects.insertMulti(typeid(Speciality).name(), Specialities);
        m_seriarizableObjects.insertMulti(typeid(Chair).name(), Chairs);
        m_seriarizableObjects.insertMulti(typeid(Group).name(), Groups);
        m_seriarizableObjects.insertMulti(typeid(Curriculumn).name(), Curriculumns);
        m_seriarizableObjects.insertMulti(typeid(Discipline).name(), Disciplines);
        m_seriarizableObjects.insertMulti(typeid(CurriculumnSection).name(), Constants);
        m_seriarizableObjects.insertMulti(typeid(CurriculumnGroup).name(), Constants);
        m_seriarizableObjects.insertMulti(typeid(EducationLevel).name(), Constants);
        m_seriarizableObjects.insertMulti(typeid(EducationForm).name(), Constants);
        m_seriarizableObjects.insertMulti(typeid(CalendarWeekSign).name(), Constants);
    }

    SqlStorage::~SqlStorage()
    {

    }

    void SqlStorage::setDatabaseName(const QString &name)
    {
        m_database.setDatabaseName(name);
    }

    QString SqlStorage::databaseName() const
    {
        return m_database.databaseName();
    }

    void SqlStorage::setUserName(const QString &name)
    {
        m_database.setUserName(name);
    }

    QString SqlStorage::userName() const
    {
        return m_database.userName();
    }

    void SqlStorage::setPassword(const QString &password)
    {
        m_database.setPassword(password);
    }

    QString SqlStorage::password() const
    {
        return m_database.password();
    }

    void SqlStorage::setPort(int port)
    {
        m_database.setPort(port);
    }

    int SqlStorage::port() const
    {
        return m_database.port();
    }

    void SqlStorage::setHost(const QString &host)
    {
        m_database.setHostName(host);
    }

    QString SqlStorage::host() const
    {
        return m_database.hostName();
    }

    bool SqlStorage::openStorage()
    {
        if (QSqlDatabase::contains(m_connectionName)) {
            m_database = QSqlDatabase::database(m_connectionName);
        } else {
            m_database = QSqlDatabase::addDatabase(m_driverName, m_connectionName);
        }
        if (m_database.isOpen())
            return true;
        const bool isOk = m_database.open();
        if (!isOk)
            m_error = m_database.lastError().text();
        return isOk;
    }

    void SqlStorage::closeStorage()
    {
        m_database.close();
        m_database = QSqlDatabase();
        QSqlDatabase::removeDatabase(m_connectionName);
    }

    bool SqlStorage::insert(const Entity &entity)
    {
        if (!m_database.isOpen()) {
            m_error = QString("Database '%1' is not opened.").arg(m_database.databaseName());
            return false;
        }

        const QString entityName = this->entityName(typeid(entity).name());
        if (entityName.isEmpty())   //check if entity should serialize its data into a table
            return false;

        QSqlQuery query(m_database);
        query.prepare(QString("INSERT INTO %1 (%2, %3) VALUES (?, ?)").arg(entityName).arg(fieldName(Id)).arg(fieldName(Data)));

        QByteArray ba;
        QBuffer buff(&ba);
        QDataStream out(&buff);
        out << entity;

        query.addBindValue(entity.id());
        query.addBindValue(ba);

        if (!query.exec()) {
            m_error = query.lastError().text();
            return false;
        }

        return true;
    }

    bool SqlStorage::save(const Entity &entity)
    {
        if (!m_database.isOpen()) {
            m_error = QString("Database '%1' is not opened.").arg(m_database.databaseName());
            return false;
        }

        const QString entityName = this->entityName(typeid(entity).name());
        if (entityName.isEmpty())   //check if entity should serialize its data into a table
            return 0;

        QSqlQuery query(m_database);
        query.prepare(QString("UPDATE %1 SET %2 = ? WHERE %3 = ?").arg(entityName).arg(fieldName(Data)).arg(fieldName(Id)));

        QByteArray ba;
        QBuffer buff(&ba);
        QDataStream out(&buff);
        out << entity;

        query.addBindValue(ba);
        query.addBindValue(entity.id());

        if (!query.exec()) {
            m_error = query.lastError().text();
            return false;
        }

        return false;
    }

    bool SqlStorage::remove(const Entity &entity)
    {
        if (!m_database.isOpen()) {
            m_error = QString("Database '%1' is not opened.").arg(m_database.databaseName());
            return false;
        }

        const QString entityName = this->entityName(typeid(entity).name());
        if (entityName.isEmpty())   //check if entity should serialize its data into a table
            return 0;

        QSqlQuery query(m_database);
        query.prepare(QString("DELETE FROM %1 WHERE %2 = ?").arg(entityName).arg(fieldName(Id)));
        query.addBindValue(entity.id());

        if (!query.exec()) {
            m_error = query.lastError().text();
            return false;
        }

        return false;
    }

    bool SqlStorage::load(Entity &entity)
    {
        if (!m_database.isOpen()) {
            m_error = QString("Database '%1' is not opened.").arg(m_database.databaseName());
            return false;
        }

        const QString entityName = this->entityName(typeid(entity).name());
        if (entityName.isEmpty())   //check if entity should serialize its data into a table
            return 0;

        QSqlQuery query(m_database);
        query.prepare(QString("SELECT %1 FROM %2 WHERE %3 = ?").arg(fieldName(Data)).arg(entityName).arg(fieldName(Id)));
        query.addBindValue(entity.id());

        if (!query.exec() || !query.next()) {
            m_error = query.lastError().text();
            return false;
        }

        QByteArray ba = query.record().value(fieldName(Data)).toByteArray();
        QBuffer buff(&ba);
        QDataStream in(&buff);
        in >> entity;

        return false;
    }
}
