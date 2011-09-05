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

#include <QtGui>
//#include <QtWebKit>

#include <KtuCurriculumn>

#include "test.h"
#include "curriculumndialog.h"
#include "calendarwidget.h"

Test::Test(QWidget *parent)
    : QWidget(parent)
{
    init();

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    m_treeWidget = new QTreeWidget(this);
    m_treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(m_treeWidget, SIGNAL(customContextMenuRequested(const QPoint &)), SLOT(showTreeViewContextMenu(const QPoint &)));

    m_treeWidget->hide();

//    m_curriculumn = new KTU::Curriculumn(1, tr("Curriculumn #1"));//--
//    m_curriculumn = new KTU::Curriculumn();//++
    KTU::Curriculumn *curriculumn = curriculumnFactory->createCurriculumn();

    QFile file("test.dat");//++
    file.open(QIODevice::ReadOnly);//++
    QDataStream in(&file);//++
    in >> *(curriculumn);//++

    m_calendarWidget = new CalendarWidget(curriculumn->calendar(), this);
//    m_calendarWidget->setEducationTerm(4);//--
    m_calendarWidget->setSigns(m_signs);

    m_curriculumnWidget = new CurriculumnWidget(curriculumn, this);

//    m_webView = new QWebView(this);

    mainLayout->addWidget(m_treeWidget);
    mainLayout->addWidget(m_calendarWidget);
    mainLayout->addWidget(m_curriculumnWidget);
//    mainLayout->addWidget(m_webView);

//    connect(m_calendarWidget, SIGNAL(curriculumnGenerated()), SLOT(updateWebView()));
}

Test::~Test()
{

}

void Test::init()
{
    m_signs << constantsFactory->createCalendarWeekSign(tr("."), tr("Teoretichne navchannya"))
            << constantsFactory->createCalendarWeekSign(tr("KZ"), tr("Kontrol'ni zahody"))
            << constantsFactory->createCalendarWeekSign(tr("="), tr("Kanikuly"))
            << constantsFactory->createCalendarWeekSign(tr("::"), tr("Ekzaminacijna sesiya"))
            << constantsFactory->createCalendarWeekSign(tr("O"), tr("Navchal'na praktyka"))
            << constantsFactory->createCalendarWeekSign(tr("X"), tr("Vyrobnycha praktyka"))
            << constantsFactory->createCalendarWeekSign(tr("D"), tr("Derganva attestaciya"))
            << constantsFactory->createCalendarWeekSign(tr("||"), tr("Dyplomne proektuvannya"))
            << constantsFactory->createCalendarWeekSign(tr("X||"), tr("Dyplomne proektuvannya-Vyrobnycha praktyka"))
            << constantsFactory->createCalendarWeekSign(QString(" "), tr("End of education"));

    QList<KTU::CalendarWeekSign *> signs;
    signs << m_signs.at(0) << m_signs.at(1);
    constantsFactory->setWorkCalendarWeekSigns(signs);
    constantsFactory->setDefaultCalendarWeekSign(m_signs.first());

    constantsFactory->createCurriculumnSection(tr("NORMATYVNI NAVCHAL'NI DYSCYPLINY"));
    constantsFactory->createCurriculumnSection(tr("VYBIRKOVI NAVCHAL'NI DYSCYPLINY"));
    constantsFactory->createCurriculumnGroup(tr("Cykl gumanitarnyh ta socyal'no-ekonomichnyh dyscyplin"));
    constantsFactory->createCurriculumnGroup(tr("Cykl dyscyplin pryrodnychno-naukovoj pidgotovky"));
    constantsFactory->createCurriculumnGroup(tr("Cykl dyscyplin profesijnoj i praktychnoj pidgotovky"));
    constantsFactory->createCurriculumnGroup(tr("Cykl dyscyplin samostijnogo vyboru navchal'nogo zakladu"));
    constantsFactory->createCurriculumnGroup(tr("Cykl dyscyplin profesiynoj i praktychnoj pidgotovky 1"));
    constantsFactory->createCurriculumnGroup(tr("Cykl dyscyplin profesiynoj i praktychnoj pidgotovky 2"));
    constantsFactory->createCurriculumnGroup(tr("Cykl dyscyplin profesiynoj i praktychnoj pidgotovky 3"));
    constantsFactory->createCurriculumnGroup(tr("Cykl dyscyplin profesiynoj i praktychnoj pidgotovky 4"));
    constantsFactory->createCurriculumnGroup(tr("Praktychna pidgotovka"));

//    constantsFactory->createChair(tr("PRRKK"));
//    constantsFactory->createChair(tr("VRG"));
//    constantsFactory->createChair(tr("IM"));
//    constantsFactory->createChair(tr("IPMP"));
//    constantsFactory->createChair(tr("BK"));
//    constantsFactory->createChair(tr("IASU"));
//    constantsFactory->createChair(tr("IU"));
//    constantsFactory->createChair(tr("FL"));
//    constantsFactory->createChair(tr("ETIP"));
//    constantsFactory->createChair(tr("VM"));
//    constantsFactory->createChair(tr("F"));
//    constantsFactory->createChair(tr("H"));
//    constantsFactory->createChair(tr("NGG"));
//    constantsFactory->createChair(tr("TPM"));
//    constantsFactory->createChair(tr("EK"));
//    constantsFactory->createChair(tr("MPZ"));
//    constantsFactory->createChair(tr("EM"));
//    constantsFactory->createChair(tr("Fv"));
//    constantsFactory->createChair(tr("MRV"));
//    constantsFactory->createChair(tr("BG"));
//    constantsFactory->createChair(tr("AAG"));
//    constantsFactory->createChair(tr("OEUP"));
//    constantsFactory->createChair(tr("TBVK"));
//    constantsFactory->createChair(tr("GTO"));
//    constantsFactory->createChair(tr("MChMLV"));
//    constantsFactory->createChair(tr("AEP"));
//    constantsFactory->createChair(tr("TPMi"));
//    constantsFactory->createChair(tr("GRKK"));
//    constantsFactory->createChair(tr("OMTMO"));
//    constantsFactory->createChair(tr("TM"));
//    constantsFactory->createChair(tr("EE"));
//    constantsFactory->createChair(tr("ARH"));
//    constantsFactory->createChair(tr("TOMB"));
//    constantsFactory->createChair(tr("RAOP"));
//    constantsFactory->createChair(tr("Msh"));
//    constantsFactory->createChair(tr("PE"));
//    constantsFactory->createChair(tr("OMBM"));
//    constantsFactory->createChair(tr("TGPV"));
//    constantsFactory->createChair(tr("ZKK"));
//    constantsFactory->createChair(tr("TEP"));
//    constantsFactory->createChair(tr("EAF"));
//    constantsFactory->createChair(tr("OAfA"));
//    constantsFactory->createChair(tr("Gz"));

    constantsFactory->createDiscipline(tr("Istoriya Ukrainy"));
    constantsFactory->createDiscipline(tr("Ukains'ka mova"));
    constantsFactory->createDiscipline(tr("Inozemna mova"));
    constantsFactory->createDiscipline(tr("Istoriya ukains'koi kultury"));
    constantsFactory->createDiscipline(tr("Filisofiya"));
}

void Test::showTreeViewContextMenu(const QPoint &point)
{
    QMenu menu;

    menu.addAction(tr("Add curriculumn"), this, SLOT(addCurriculumn()));
    menu.addAction(tr("Delete curriculumn"), this, SLOT(deleteCurriculumn()));
    menu.addAction(tr("Clone curriculumn"), this, SLOT(cloneCurriculumn()));

    menu.exec(m_treeWidget->mapToGlobal(point));
}

void Test::addCurriculumn()
{
    CurriculumnDialog cd(this);
    if (!cd.exec())
        return;
}

void Test::deleteCurriculumn()
{

}

void Test::cloneCurriculumn()
{

}

//void Test::updateWebView()
//{
//    m_webView->load(QUrl("curriculumn.html"));
////    m_webView->reload();
//}
