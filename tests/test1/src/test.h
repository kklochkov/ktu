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

#ifndef TEST_H
#define TEST_H

#include <QWidget>

class QTreeWidget;
class CalendarWidget;
//class QWebView;
class CurriculumnWidget;

namespace KTU
{
    class CalendarWeekSign;
}

class Test : public QWidget
{
    Q_OBJECT
public:
    Test(QWidget *parent = 0);
    virtual ~Test();

private slots:
    void showTreeViewContextMenu(const QPoint &point);
    void addCurriculumn();
    void deleteCurriculumn();
    void cloneCurriculumn();
//    void updateWebView();

private:
    void init();

private:
    QTreeWidget *m_treeWidget;
    CalendarWidget *m_calendarWidget;
    QList<KTU::CalendarWeekSign *> m_signs;
//    QWebView *m_webView;
    CurriculumnWidget *m_curriculumnWidget;
};

#endif // TEST_H
