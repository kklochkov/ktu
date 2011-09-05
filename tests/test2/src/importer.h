#ifndef IMPORTER_H
#define IMPORTER_H

#include <QObject>
#include <QSqlDatabase>
#include <QMap>
#include <QStringList>

namespace KTU
{
    class Curriculumn;
    class Chair;
    class Discipline;
    class CurriculumnSection;
    class CurriculumnGroup;
}

class Importer : public QObject
{
    Q_OBJECT
public:
    Importer(QObject *parent = 0);

    bool openMDB(const QString &mdbName);

    QString lastError() const;

    QStringList log() const { return m_log; }

public slots:
    void import();

signals:
    void finished();

private:
    bool importDepartments();
    bool importChairs();
    bool importConstants();
    bool importCurriculumnGroups();
    bool importCurriculumnSections();
    bool importSpecialities();
    bool importGroups();
    bool importDisciplines();
    bool importCurriculumn();
    bool importCurriculumnCalendar(quint64 oldId, KTU::Curriculumn *curriculumn);
    bool importCurriculumnDisciplines(quint64 oldId, KTU::Curriculumn *curriculumn);
    bool importCurriculumnHours(quint64 oldId,
                                quint64 disId,
                                KTU::Curriculumn *curriculumn,
                                KTU::Chair *chair,
                                KTU::Discipline *discipline,
                                KTU::CurriculumnSection *section,
                                KTU::CurriculumnGroup *group);
    bool importCurriculumnAcademicalGroups(quint64 oldId, KTU::Curriculumn *curriculumn);

    void addToLog(const QString &message);

private:
    QSqlDatabase m_db;
    QMap<quint64, quint64> m_departmentsMap;//[oldId, newId]
    QMap<quint64, quint64> m_chairsMap;//[oldId, newId]
    QMap<quint64, quint64> m_specialitiesMap;//[oldId, newId]
    QMap<quint64, quint64> m_groupsMap;//[oldId, newId]

    QStringList m_log;
};

#endif // IMPORTER_H
