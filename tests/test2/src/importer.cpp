#include <QtSql>
#include <QElapsedTimer>
#include <KtuCurriculumn>

#include "importer.h"

Importer::Importer(QObject *parent)
    : QObject(parent)
{
    m_db = QSqlDatabase::addDatabase("QODBC", "ktu_sql_importer");
}

bool Importer::openMDB(const QString &mdbName)
{
    m_db.setDatabaseName(mdbName);
    return m_db.open();
}

QString Importer::lastError() const
{
    return m_db.lastError().text();
}

static qulonglong recordsCount(QSqlDatabase &db, const QString &tableName)
{
    QSqlQuery query(db);
    if (query.exec(QString("SELECT COUNT(*) AS recordsCount FROM %1").arg(tableName)) && query.next())
        return query.record().value("recordsCount").toULongLong();
    return 0;
}

static qreal currentProgress(qulonglong maxValue, qulonglong currentValue)
{
    return 100.0 * currentValue / maxValue;
}

bool Importer::importDepartments()
{
    QSqlQuery query(m_db);
    if (!query.exec("SELECT * FROM Fakultet"))
        return false;

    const qulonglong maxValue = ::recordsCount(m_db, "Fakultet");
    qulonglong currentValue = 0;
    qDebug() << Q_FUNC_INFO << ::currentProgress(maxValue, currentValue) << "%";

    m_departmentsMap.clear();
    while (query.next()) {
        const QSqlRecord record = query.record();
#warning add University & Institute first!
        KTU::Department *department = constantsFactory.createDepartment(1, record.value("Naim").toString());
        department->setShortName(record.value("Pole").toString());
        m_departmentsMap.insert(record.value("Nzz").toULongLong(), department->id());

        qDebug() << Q_FUNC_INFO << ::currentProgress(maxValue, ++currentValue) << "%";
    }

    const QList<KTU::Department *> departments = constantsFactory.departments();
    addToLog(QString("%1 %2 %3").arg(Q_FUNC_INFO).arg("--------------------------------------").arg(departments.count()));
    return true;
}

bool Importer::importChairs()
{
    QSqlQuery query(m_db);
    if (!query.exec("SELECT * FROM Kafedra"))
        return false;

    const qulonglong maxValue = ::recordsCount(m_db, "Kafedra");
    qulonglong currentValue = 0;
    qDebug() << Q_FUNC_INFO << ::currentProgress(maxValue, currentValue) << "%";

    m_chairsMap.clear();
    while (query.next()) {
        const QSqlRecord record = query.record();
        const quint64 depId = record.value("Fak").toULongLong();
        KTU::Department *department = constantsFactory.department(m_departmentsMap.value(depId));
        if (!department) {
            addToLog(QString("%1 %2 %3 %4").arg(Q_FUNC_INFO)
                     .arg("can't find department with").arg(depId)
                     .arg("id. Skipped."));
            continue;
        }
        KTU::Chair *chair = department->createChair(record.value("Naim").toString());
        chair->setShortName(record.value("Pole").toString());
        m_chairsMap.insert(record.value("Nzz").toULongLong(), chair->id());

        qDebug() << Q_FUNC_INFO << ::currentProgress(maxValue, ++currentValue) << "%";
    }

    const QList<KTU::Chair *> chairs = constantsFactory.chairs();
    addToLog(QString("%1 %2 %3").arg(Q_FUNC_INFO).arg("--------------------------------------").arg(chairs.count()));
    return true;
}

bool Importer::importConstants()
{
    Q_UNUSED(constantsFactory.createEducationLevel(QString::fromLocal8Bit("")));
    Q_UNUSED(constantsFactory.createEducationLevel(QString::fromLocal8Bit("")));
    Q_UNUSED(constantsFactory.createEducationLevel(QString::fromLocal8Bit("")));

    Q_UNUSED(constantsFactory.createEducationForm(QString::fromLocal8Bit("")));
    Q_UNUSED(constantsFactory.createEducationForm(QString::fromLocal8Bit("")));
    Q_UNUSED(constantsFactory.createEducationForm(QString::fromLocal8Bit(".")));

    KTU::CalendarWeekSign *sign = constantsFactory.createCalendarWeekSign(QString::fromLocal8Bit(""),
                                                                           QString::fromLocal8Bit(" "));
    Q_UNUSED(constantsFactory.createCalendarWeekSign(QString::fromLocal8Bit(""),
                                                      QString::fromLocal8Bit("ϳ  ")));
    Q_UNUSED(constantsFactory.createCalendarWeekSign(QString::fromLocal8Bit(""),
                                                      QString::fromLocal8Bit("  ")));
    Q_UNUSED(constantsFactory.createCalendarWeekSign(QString::fromLocal8Bit(""),
                                                      QString::fromLocal8Bit("")));
    Q_UNUSED(constantsFactory.createCalendarWeekSign(QString::fromLocal8Bit(""),
                                                      QString::fromLocal8Bit("")));
    Q_UNUSED(constantsFactory.createCalendarWeekSign(QString::fromLocal8Bit(""),
                                                      QString::fromLocal8Bit("")));
    Q_UNUSED(constantsFactory.createCalendarWeekSign(QString::fromLocal8Bit(""),
                                                      QString::fromLocal8Bit("")));

    QList<KTU::CalendarWeekSign *> workSigns;
    workSigns << sign;
    constantsFactory.setWorkCalendarWeekSigns(workSigns);

    addToLog(QString("%1 %2 %3 %4 %5").arg(Q_FUNC_INFO).arg("--------------------------------------")
             .arg(constantsFactory.educationLevels().count())
             .arg(constantsFactory.educationForms().count())
             .arg(constantsFactory.calendarWeekSigns().count()));

    if (!importCurriculumnSections())
        return false;

    if (!importCurriculumnGroups())
        return false;

    return true;
}

bool Importer::importCurriculumnSections()
{
    QSqlQuery query(m_db);
    if (!query.exec("SELECT Plan_N_Dis.Vid_Grup FROM Plan_N_Dis GROUP BY Plan_N_Dis.Vid_Grup ORDER BY Plan_N_Dis.Vid_Grup"))
        return false;

    const qulonglong maxValue = ::recordsCount(m_db, "Plan_N_Dis");
    qulonglong currentValue = 0;
    qDebug() << Q_FUNC_INFO << ::currentProgress(maxValue, currentValue) << "%";

    while (query.next()) {
        const QSqlRecord record = query.record();
        Q_UNUSED(constantsFactory.createCurriculumnSection(record.value("Vid_Grup").toString()));

        qDebug() << Q_FUNC_INFO << ::currentProgress(maxValue, ++currentValue) << "%";
    }

    addToLog(QString("%1 %2 %3").arg(Q_FUNC_INFO).arg("--------------------------------------")
             .arg(constantsFactory.curriculumnSections().count()));
    return true;
}

bool Importer::importCurriculumnGroups()
{
    QSqlQuery query(m_db);
    if (!query.exec("SELECT Plan_N_Dis.Grup FROM Plan_N_Dis GROUP BY Plan_N_Dis.Grup ORDER BY Plan_N_Dis.Grup"))
        return false;

    const qulonglong maxValue = ::recordsCount(m_db, "Plan_N_Dis");
    qulonglong currentValue = 0;
    qDebug() << Q_FUNC_INFO << ::currentProgress(maxValue, currentValue) << "%";

    while (query.next()) {
        const QSqlRecord record = query.record();
        Q_UNUSED(constantsFactory.createCurriculumnGroup(record.value("Grup").toString()));

        qDebug() << Q_FUNC_INFO << ::currentProgress(maxValue, ++currentValue) << "%";
    }

    addToLog(QString("%1 %2 %3").arg(Q_FUNC_INFO).arg("--------------------------------------")
             .arg(constantsFactory.curriculumnGroups().count()));
    return true;
}

bool Importer::importSpecialities()
{
    QSqlQuery query(m_db);
    if (!query.exec("SELECT * FROM Spez_Min"))
        return false;

    const qulonglong maxValue = ::recordsCount(m_db, "Spez_Min");
    qulonglong currentValue = 0;
    qDebug() << Q_FUNC_INFO << ::currentProgress(maxValue, currentValue) << "%";

    m_specialitiesMap.clear();
    while (query.next()) {
        qDebug() << Q_FUNC_INFO << ::currentProgress(maxValue, currentValue++) << "%";

        const QSqlRecord record = query.record();
        const quint64 depId = record.value("Fak").toULongLong();
        const quint64 specId = record.value("Nzz").toULongLong();
        KTU::Department *department = constantsFactory.department(m_departmentsMap.value(depId));
        if (!department) {
            addToLog(QString("%1 %2 %3 %4 %5 %6").arg(Q_FUNC_INFO)
                     .arg("can't find department with").arg(depId)
                     .arg("id for speciality with").arg(specId)
                     .arg("id. Skipped."));
            continue;
        }
        KTU::Speciality *speciality = department->createSpeciality(record.value("Spez").toString());
        speciality->setShortName(record.value("Pole").toString());
        speciality->setCode(record.value("Sifr").toString());
        const QString levelString = record.value("Ur").toString();
        KTU::EducationLevel *level = constantsFactory.educationLevel(levelString);
        if (!level)
            level = constantsFactory.defaultEducationLevel();
        speciality->setLevel(level);
        m_specialitiesMap.insert(specId, speciality->id());
    }

    addToLog(QString("%1 %2 %3").arg(Q_FUNC_INFO).arg("--------------------------------------")
             .arg(constantsFactory.specialities().count()));
    return true;
}

bool Importer::importGroups()
{
    QSqlQuery query(m_db);
    if (!query.exec("SELECT * FROM Dgrup"))
        return false;

    const qulonglong maxValue = ::recordsCount(m_db, "Dgrup");
    qulonglong currentValue = 0;
    qDebug() << Q_FUNC_INFO << ::currentProgress(maxValue, currentValue) << "%";

    m_groupsMap.clear();
    while (query.next()) {
        qDebug() << Q_FUNC_INFO << ::currentProgress(maxValue, currentValue++) << "%";

        const QSqlRecord record = query.record();
        const quint64 specId = record.value("spez").toULongLong();
        const quint64 groupId = record.value("Nzz").toULongLong();
        KTU::Speciality *speciality = constantsFactory.speciality(m_specialitiesMap.value(specId));
        if (!speciality) {
            addToLog(QString("%1 %2 %3 %4 %5 %6").arg(Q_FUNC_INFO)
                     .arg("can't find speciality with").arg(specId)
                     .arg("id for group with").arg(groupId)
                     .arg("id. Skipped."));
            continue;
        }
        KTU::Group *group = speciality->createGroup(record.value("gr").toString());
        group->setShortName(record.value("Sifr").toString());
        group->setStartYear(record.value("Rik").toULongLong());
        group->setEndYear(record.value("Rikz").toULongLong());
        group->setStudentsCount(record.value("Kstud").toULongLong());
        group->setSubGroupsCount(record.value("Pod").toULongLong());
        const QString eduForm = record.value("forma").toString();
        KTU::EducationForm *form = constantsFactory.educationForm(eduForm);
        if (!form) {
            addToLog(QString("%1 can't find education form '%2'").arg(Q_FUNC_INFO).arg(eduForm));
            continue;
        }
        group->setEducationForm(form);
        m_groupsMap.insert(groupId, group->id());
    }

    addToLog(QString("%1 %2 %3").arg(Q_FUNC_INFO)
             .arg("--------------------------------------").arg(constantsFactory.groups().count()));
    return true;
}

bool Importer::importDisciplines()
{
    QSqlQuery query(m_db);
    if (!query.exec("SELECT Plan_N_Dis.Dis FROM Plan_N_Dis GROUP BY Plan_N_Dis.Dis HAVING ((Not (Plan_N_Dis.Dis) Is Null)) ORDER BY Plan_N_Dis.Dis"))
        return false;

    const qulonglong maxValue = ::recordsCount(m_db, "Plan_N_Dis");
    qulonglong currentValue = 0;
    qDebug() << Q_FUNC_INFO << ::currentProgress(maxValue, currentValue) << "%";

    while(query.next()) {
        qDebug() << Q_FUNC_INFO << ::currentProgress(maxValue, currentValue++) << "%";

        const QSqlRecord record = query.record();
        Q_UNUSED(constantsFactory.createDiscipline(record.value("Dis").toString().simplified()));
    }

    addToLog(QString("%1 %2 %3").arg(Q_FUNC_INFO)
             .arg("--------------------------------------").arg(constantsFactory.disciplines().count()));
    return true;
}

bool Importer::importCurriculumn()
{
    QSqlQuery query(m_db);
    if (!query.exec("SELECT * FROM Plan_N ORDER BY Nzz"))
        return false;

    const qulonglong maxValue = ::recordsCount(m_db, "Plan_N");
    qulonglong currentValue = 0;
    qDebug() << Q_FUNC_INFO << ::currentProgress(maxValue, currentValue) << "%";

    while (query.next()) {
        qDebug() << Q_FUNC_INFO << ::currentProgress(maxValue, currentValue++) << "%";

        const QSqlRecord record = query.record();

        const quint64 curriculumnId = record.value("Nzz").toULongLong();
        const quint64 departmentId = record.value("Fak").toULongLong();
        const quint64 chairId = record.value("Kaf").toULongLong();
        const quint64 specialityId = record.value("Spez").toULongLong();

        KTU::Department *department = constantsFactory.department(m_departmentsMap[departmentId]);
        KTU::Chair *chair = constantsFactory.chair(m_chairsMap[chairId]);
        KTU::Speciality *speciality = constantsFactory.speciality(m_specialitiesMap[specialityId]);

        if (!department) {
            addToLog(QString("%1 %2 %3 %4 %5 %6").arg(Q_FUNC_INFO)
                     .arg("can't find department with").arg(departmentId)
                     .arg("id for curriculumn with").arg(curriculumnId)
                     .arg("id. Skipped."));
            continue;
        }

        if (!chair) {
            addToLog(QString("%1 %2 %3 %4 %5 %6").arg(Q_FUNC_INFO)
                     .arg("can't find chair with").arg(chairId)
                     .arg("id for curriculumn with").arg(curriculumnId)
                     .arg("id. Skipped."));
            continue;
        }

        if (!speciality) {
            addToLog(QString("%1 %2 %3 %4 %5 %6").arg(Q_FUNC_INFO)
                     .arg("can't find speciality with").arg(specialityId)
                     .arg("id for curriculumn with").arg(curriculumnId)
                     .arg("id. Skipped."));
            continue;
        }

        KTU::Curriculumn *curriculumn = constantsFactory.createCurriculumn();
        curriculumn->setName(QString("%1").arg(curriculumnId));
        curriculumn->setDepartment(department);
        curriculumn->setChair(chair);
        curriculumn->setSpeciality(speciality);
        curriculumn->setSpecialization(record.value("Spezi").toString());
        curriculumn->setQualification(record.value("Kvali").toString());

        const QString eduForm = record.value("Forma").toString();
        KTU::EducationForm *form = constantsFactory.educationForm(eduForm);
        if (!form) {
            addToLog(QString("%1 can't find education form '%2'").arg(Q_FUNC_INFO).arg(eduForm));
            continue;
        }

        curriculumn->setEducationForm(form);
        curriculumn->setEducationTerm(record.value("Termin").toULongLong());

        importCurriculumnCalendar(curriculumnId, curriculumn);
        importCurriculumnAcademicalGroups(curriculumnId, curriculumn);
    }

    const QList<KTU::Curriculumn *> curriculumns = constantsFactory.curriculumns();
    addToLog(QString("%1 %2 %3").arg(Q_FUNC_INFO)
             .arg("--------------------------------------").arg(curriculumns.count()));
    return true;
}

bool Importer::importCurriculumnCalendar(quint64 oldId, KTU::Curriculumn *curriculumn)
{
    Q_ASSERT(curriculumn);

    QSqlQuery query(m_db);
    if (!query.exec(QString("SELECT * FROM Plan_N_Gra WHERE Nzp = %1 ORDER BY Kurs, Sem").arg(oldId)))
        return false;

    while (query.next()) {
        const QSqlRecord record = query.record();
        const quint64 id = record.value("Nzp").toULongLong();

        const quint64 sem = record.value("Sem").toULongLong();
//        quint64 course = record.value("Kurs").toULongLong();
        const quint64 workWeeks = record.value("Ned_1").toULongLong();
        const quint64 totalWeeks = record.value("Ned_2").toULongLong();
        const QString strCalendar = record.value("Grafik").toString();

        if (curriculumn->educationTerm() * 2 < sem) {
            addToLog(QString("%1 education term by plan (%2) doesn't match to a griphic's, for a curriculumn with %3 id")
                     .arg(Q_FUNC_INFO).arg(curriculumn->educationTerm()).arg(oldId));
            continue;
        }

        KTU::Calendar *calendar = curriculumn->calendar();
        KTU::CalendarSemester *semester = calendar->semester(sem);
        semester->setWeeksInSemester(totalWeeks);

        for (int i = 0; i < strCalendar.length(); ++i) {
            KTU::CalendarWeek *week = semester->week(semester->startWeek() + i);
            if (!week) {
                addToLog(QString("%1 week's' number (%2) is greater then weeks count (%3) for course (%4) and semester (%5). Plan (%6).")
                                .arg(Q_FUNC_INFO)
                                .arg(semester->startWeek() + i)
                                .arg(semester->course()->weeksCount())
                                .arg(semester->course()->number())
                                .arg(semester->number())
                                .arg(id));
                continue;
            }

            KTU::CalendarWeekSign *sign = constantsFactory.calendarWeekSign(QString(strCalendar[i]));
            if (!sign) {
                addToLog(QString("%1 can't find sign '%2'").arg(Q_FUNC_INFO).arg(strCalendar[i]));
                continue;
            }
            week->setSign(sign);
        }

        if (workWeeks != semester->workWeeksCount()) {
            addToLog(QString("%1 workWeekCount(%2) != workWeekCount(%3) for semester(%4) in curriculumn(%5)").arg(Q_FUNC_INFO)
                     .arg(workWeeks)
                     .arg(semester->workWeeksCount())
                     .arg(semester->number())
                     .arg(id));
        }
    }

    return importCurriculumnDisciplines(oldId, curriculumn);
}

bool Importer::importCurriculumnDisciplines(quint64 oldId, KTU::Curriculumn *curriculumn)
{
    Q_ASSERT(curriculumn);

    QSqlQuery query(m_db);
    if (!query.exec(QString("SELECT * FROM Plan_N_Dis WHERE Nzp  = %1 ORDER BY Vid_Grup, Grup").arg(oldId)))
        return false;

    while (query.next()) {
        const QSqlRecord record = query.record();

        const quint64 disId = record.value("Nzz").toULongLong();
        const quint64 chairId = record.value("Kaf").toULongLong();
        const QString sectionName = record.value("Vid_Grup").toString();
        const QString groupName = record.value("Grup").toString();
        const QString dis = record.value("Dis").toString().simplified();
//        const quint64 hoursByPlan = record.value("Sum").toULongLong();

        KTU::Chair *chair = constantsFactory.chair(m_chairsMap[chairId]);
        KTU::Discipline *discipline = constantsFactory.discipline(dis);
        KTU::CurriculumnSection *section = constantsFactory.curriculumnSection(sectionName);
        KTU::CurriculumnGroup *group = constantsFactory.curriculumnGroup(groupName);

        if (!chair) {
            addToLog(QString("%1 %2 %3 %4 %5 %6").arg(Q_FUNC_INFO)
                     .arg("can't find chair with").arg(chairId)
                     .arg("id for curriculumn with").arg(oldId)
                     .arg("id. Skipped."));
            continue;
        }

        if (!discipline) {
            addToLog(QString("%1 %2 %3 %4 %5 %6").arg(Q_FUNC_INFO)
                     .arg("can't find discipline '").arg(disId)
                     .arg("' for curriculumn with").arg(oldId)
                     .arg("id. Skipped."));
            continue;
        }

        if (!section) {
            addToLog(QString("%1 can't find '%2'").arg(Q_FUNC_INFO).arg(sectionName));
            continue;
        }

        if (!group) {
            addToLog(QString("%1 can't find '%2'").arg(Q_FUNC_INFO).arg(groupName));
            continue;
        }

//        if (!hoursByPlan) {
//            addToLog(QString("%1 %2 %3 %4 %5 %6").arg(Q_FUNC_INFO)
//                     .arg("hours by plan for discipline '").arg(disId)
//                     .arg("' for curriculumn with id").arg(oldId).arg("is 0"));
//        }

        importCurriculumnHours(oldId, disId, curriculumn, chair, discipline, section, group);
    }

    return true;
}

bool Importer::importCurriculumnHours(quint64 oldId, quint64 disId, KTU::Curriculumn *curriculumn,
                                      KTU::Chair *chair, KTU::Discipline *discipline,
                                      KTU::CurriculumnSection *section, KTU::CurriculumnGroup *group)
{
    QSqlQuery hoursQuery(m_db);
    if (!hoursQuery.exec(QString("SELECT * FROM Plan_N_Dis_E WHERE Nzp = %1 ORDER BY Sem").arg(disId))) {
        addToLog(QString("%1 %2").arg(Q_FUNC_INFO).arg(hoursQuery.lastError().text()));
        return false;
    }

    KTU::CurriculumnDisciplineGroup *cdg = curriculumn->group(section);
    if (!cdg)
        cdg = curriculumn->addGroup(section);

    KTU::CurriculumnDisciplineSubGroup *cdsg = cdg->subGroup(group);
    if (!cdsg)
        cdsg = cdg->addSubGroup(group);

    while (hoursQuery.next()) {
        const QSqlRecord r = hoursQuery.record();
        const quint64 sem = r.value("Sem").toULongLong();
        const qreal lec = r.value("Lek").toReal();
        const qreal lab = r.value("Lr").toReal();
        const qreal pra = r.value("Prakt").toReal();
        const bool I = r.value("I").toBool();
        const bool Z = r.value("Z").toBool();
        const bool R = r.value("R").toBool();
        const bool KR = r.value("KR").toBool();
        const bool KP = r.value("KP").toBool();
        const bool dzal = r.value("dzal").toBool();
        const bool kvali = r.value("kvali").toBool();
        const bool diplom = r.value("diplom").toBool();
        const bool mag = r.value("mag").toBool();
        const bool praktika = r.value("praktika").toBool();
        const bool dipprakt = r.value("dipprakt").toBool();
        const bool magprakt = r.value("magprakt").toBool();
        const bool kvaliprakt = r.value("kvaliprakt").toBool();
        const bool derisp = r.value("derisp").toBool();
        const bool praktikav = r.value("praktikav").toBool();

        KTU::CurriculumnRecord *record = cdsg->addRecord();
        record->setChair(chair);
        record->setDiscipline(discipline);
        KTU::CurriculumnSemester *semester = record->semester(sem);
        if (!semester) {
            addToLog(QString("%1 can't find semester(%2) in plan(%3)")
                     .arg(Q_FUNC_INFO)
                     .arg(sem).arg(oldId));
            continue;
        }

        semester->setLectionsHours(lec / semester->weeksCount());
        semester->setLabsHours(lab / semester->weeksCount());
        semester->setPracticesHours(pra / semester->weeksCount());
        semester->setExam(I);
        semester->setTest(Z);
        semester->setR(R);
        semester->setCourseWork(KR);
        semester->setCourseProject(KP);
        semester->setDiffTest(dzal);
        semester->setQualification(kvali);
        semester->setDiplom(diplom);
        semester->setMagister(mag);
        semester->setPractice(praktika);
        semester->setDimplomPractice(dipprakt);
        semester->setMagisterPractice(magprakt);
        semester->setQualificationPractice(kvaliprakt);
        semester->setStateExam(derisp);
        semester->setEnterprisePractice(praktikav);

        if (lec != semester->lectionsHoursTotal()) {
            addToLog(QString("%1 lecHours(%2) != lecHours(%3) for semester(%4) in plan(%5) for discipline (%6)")
                     .arg(Q_FUNC_INFO)
                     .arg(lec)
                     .arg(semester->lectionsHoursTotal())
                     .arg(semester->number())
                     .arg(oldId)
                     .arg(disId));
        }

        if (lab != semester->labsHoursTotal()) {
            addToLog(QString("%1 labHours(%2) != labHours(%3) for semester(%4) in plan(%5) for discipline (%6)")
                     .arg(Q_FUNC_INFO)
                     .arg(lab)
                     .arg(semester->labsHoursTotal())
                     .arg(semester->number())
                     .arg(oldId)
                     .arg(disId));
        }

        if (pra != semester->practicesHoursTotal()) {
            addToLog(QString("%1 praHours(%2) != praHours(%3) for semester(%4) in plan(%5) for discipline (%6)")
                     .arg(Q_FUNC_INFO)
                     .arg(pra)
                     .arg(semester->practicesHoursTotal())
                     .arg(semester->number())
                     .arg(oldId)
                     .arg(disId));
        }
    }
    return true;
}

bool Importer::importCurriculumnAcademicalGroups(quint64 oldId, KTU::Curriculumn *curriculumn)
{
    Q_ASSERT(curriculumn);

    QSqlQuery query(m_db);
    if (!query.exec(QString("SELECT * FROM Plan_N_Gru WHERE Nzp  = %1").arg(oldId)))
        return false;

    while (query.next()) {
        const QSqlRecord record = query.record();
        const quint64 groupId = m_groupsMap[record.value("Grup").toULongLong()];
        KTU::Group *group = constantsFactory.group(groupId);
        if (!group) {
            addToLog(QString("%1 can't find a group(%2) for a curricculumn(%3).")
                     .arg(Q_FUNC_INFO).arg(groupId).arg(oldId));
            continue;
        }
        group->setCurriculumn(curriculumn);
    }

    return true;
}

void Importer::import()
{
    QElapsedTimer timer;
    timer.start();

    bool ok = importDepartments();

    if (ok) {
        qDebug() << Q_FUNC_INFO << "departments imported.";
        ok = importChairs();
    }

    if (ok) {
        qDebug() << Q_FUNC_INFO << "chairs imported.";
        ok = importConstants();
    }

    if (ok) {
        qDebug() << Q_FUNC_INFO << "constants imported.";
        ok = importSpecialities();
    }

    if (ok) {
        qDebug() << Q_FUNC_INFO << "specialities imported.";
        ok = importGroups();
    }

    if (ok) {
        qDebug() << Q_FUNC_INFO << "groups imported.";
        ok = importDisciplines();
    }

    if (ok) {
        qDebug() << Q_FUNC_INFO << "disciplines imported.";
        ok = importCurriculumn();
    }

    if (ok)
        qDebug() << Q_FUNC_INFO << "curriculumns imported.";

    const QList<KTU::Curriculumn *> curriculumns = constantsFactory.curriculumns();
    const QList<KTU::Group *> groups = constantsFactory.groups();

    addToLog(QString("%1 %2 groups are registered.").arg(Q_FUNC_INFO).arg(groups.count()));
    addToLog(QString("%1 %2 curriculumns are registered.").arg(Q_FUNC_INFO).arg(curriculumns.count()));

    QList<KTU::Group *> groupsWithoutCurriculumns;
    QList<KTU::Curriculumn *> curriculumnsWithoutGroups = curriculumns;

    foreach (KTU::Group *group, groups) {
        if (!group->curriculumn()) {
            groupsWithoutCurriculumns << group;
            continue;
        }
        curriculumnsWithoutGroups.removeAll(group->curriculumn());
    }

    addToLog(QString("%1 %2").arg(Q_FUNC_INFO).arg("--------------------------------------"));
    addToLog(QString("%1 %2 groups have no curriculumns.").arg(Q_FUNC_INFO).arg(groupsWithoutCurriculumns.count()));
    addToLog(QString("%1 %2 curriculumns have no groups.").arg(Q_FUNC_INFO).arg(curriculumnsWithoutGroups.count()));
    addToLog(QString("%1 %2").arg(Q_FUNC_INFO).arg("--------------------------------------"));

    foreach (KTU::Group *group, groupsWithoutCurriculumns)
        addToLog(QString("%1 %2 has no curriculumn.").arg(Q_FUNC_INFO).arg(group->name()));

    foreach (KTU::Curriculumn *curriculumn, curriculumnsWithoutGroups)
        addToLog(QString("%1 %2 doesn't belong to any group.").arg(Q_FUNC_INFO).arg(curriculumn->name()));

    foreach (const QString &message, m_log)
        qDebug() << message;

    qDebug() << Q_FUNC_INFO << "Import took" << timer.elapsed() / 60000.0 << "minutes.";

    emit finished();
}

void Importer::addToLog(const QString &message)
{
    if (m_log.contains(message))
        return;
    m_log << message;
}
