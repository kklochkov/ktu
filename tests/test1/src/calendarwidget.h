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


#ifndef CALENDARWIDGET_H
#define CALENDARWIDGET_H

#include <QWidget>
#include <QDialog>

#include <QDate>
#include <QTableView>
#include <QAbstractTableModel>
#include <QItemDelegate>
#include <QTreeView>

#include "calendarweeksign.h"

class CalendarView;
class QGridLayout;
class QHBoxLayout;
class CurriculumnItemsView;
class QComboBox;
class QFormLayout;
class SelectorDialog;
class QStandardItemModel;

namespace KTU
{
    class CalendarWeek;
    class CalendarSemester;
    class Calendar;
    class Curriculumn;
    class CurriculumnSection;
    class CurriculumnGroup;
    class Discipline;
    class Chair;
    class CurriculumnDisciplineGroup;
    class CurriculumnDisciplineSubGroup;
    class CurriculumnRecord;
}

class CalendarDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    CalendarDelegate(QObject *parent = 0);

    virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    virtual void drawDisplay(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect, const QString &text) const;
    virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
    virtual void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    virtual void setEditorData(QWidget *editor, const QModelIndex &index) const;
    virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

signals:
    void signSelected(KTU::CalendarWeekSign *sign);

private slots:
    void signActivated(int index);

private:
    mutable QModelIndex m_currentPaintedIndex;//workaround: QStyleOptionViewItemV4::index is not set in QItemDelegate::paint
};
//------------------------------------------
class CalendarModel : public QAbstractTableModel
{
    Q_OBJECT
    friend class CalendarDelegate;
    friend class CalendarView;
public:
    CalendarModel(QObject *parnet = 0);

    void setEducationTerm(int years);
    int educationTerm() const;

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;

    virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    virtual Qt::ItemFlags flags(const QModelIndex &index) const;

    virtual QModelIndex index(int row, int column, const QModelIndex &parent) const;

    void setSign(const QModelIndexList &list, KTU::CalendarWeekSign *sign);

    void setCalendar(KTU::Calendar *calendar);
    const KTU::Calendar *calendar() const { return m_calendar; }

    void setSigns(const QList<KTU::CalendarWeekSign *> &signs) { m_signs = signs; }
    QList<KTU::CalendarWeekSign *> signs() const { return m_signs; }

public slots:
    void clear();

signals:
    void modelInitialized();

private:
    KTU::CalendarWeek *week(int course, int weekNumber) const;
    KTU::CalendarSemester *semester(int course, int weekNumber) const;
    int course(int row) const;

private slots:
    void init();

private:
    enum FixedRows { Semesters, Monthes, Dates, Size };

    KTU::Calendar *m_calendar;
    QList<KTU::CalendarWeekSign *> m_signs;
};
//------------------------------------------
class CalendarView : public QTableView
{
    Q_OBJECT
public:
    CalendarView(KTU::Calendar *calendar, QWidget *parent = 0);

    CalendarModel *model() const { return m_model; }

    void setSigns(const QList<KTU::CalendarWeekSign *> &signs);

private:
    virtual void setModel(QAbstractItemModel *model);
    void initSpans(CalendarModel::FixedRows fixedRow);

private slots:
    void initSpans();

private:
    CalendarModel *m_model;
};
//------------------------------------------
class CalendarWidget : public QWidget
{
    Q_OBJECT
public:
    CalendarWidget(KTU::Calendar *calendar, QWidget *parent = 0);

    void setEducationTerm(int years);
    void setSigns(const QList<KTU::CalendarWeekSign *> &signs);

private slots:
    void signClicked();
    void showContextMenu(const QPoint &point);
    void saveCurriculumn();
    void showTimeBudget();

private:
    CalendarView *m_calendar;
};
//------------------------------------------
class CalendarTimeBudgetDialog : public QDialog
{
    Q_OBJECT
public:
    CalendarTimeBudgetDialog(const CalendarModel *calendar, QWidget *parent = 0);

private:
    void init();
    void addColumn(KTU::CalendarWeekSign *sign);
    void removeColumn(KTU::CalendarWeekSign *sign);

private slots:
    void recalc();
    void signClicked(bool checked);

private:
    QHBoxLayout *createSignWidgets(KTU::CalendarWeekSign *sign) const;
    void sum(Qt::Orientation orientation);

private:
    const CalendarModel *m_calendar;
    QStandardItemModel *m_timeBudgetModel;
    QGridLayout *m_signsLayout;
};
//------------------------------------------
class CurriculumnHeaderModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum ItemDataRole { VerticalTextRole = Qt::UserRole + 100 };

    explicit CurriculumnHeaderModel(QObject *parent = 0);

    void setCurriculumn(KTU::Curriculumn *curriculumn);
    KTU::Curriculumn *curriculumn() const { return m_curriculumn; }

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;
    virtual QModelIndex index(int row, int column, const QModelIndex &parent) const;

signals:
    void modelInitialized();

private:
    KTU::Curriculumn *m_curriculumn;
};
//------------------------------------------
class CurriculumnItemsModel : public QAbstractItemModel
{
    Q_OBJECT
public:
//    enum RowId { Group = 1000, SubGroup, Record, Total };

    explicit CurriculumnItemsModel(QObject *parent = 0);

    void setCurriculumnHeaderModel(CurriculumnHeaderModel *model);
    CurriculumnHeaderModel *curriculumnModel() const { return m_curriculumn; }

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role);
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;
    virtual QModelIndex index(int row, int column, const QModelIndex &parent) const;
    virtual QModelIndex parent(const QModelIndex &index) const;

    void addGroup(KTU::CurriculumnSection *section);
    void addSubGroup(KTU::CurriculumnSection *section, KTU::CurriculumnGroup *group);
    void addRecord(KTU::CurriculumnSection *section, KTU::CurriculumnGroup *group, KTU::Discipline *discipline, KTU::Chair *chair);
    void removeGroup(KTU::CurriculumnDisciplineGroup *g);
    void removeSubGroup(KTU::CurriculumnDisciplineSubGroup *sg);
    void removeRecord(KTU::CurriculumnRecord *r);

signals:
    void modelInitialized();

//public:
//    void getEntities(const QModelIndex &index, KTU::CurriculumnDisciplineGroup *&group, KTU::CurriculumnDisciplineSubGroup *&subGroup, KTU::CurriculumnRecord *&record) const;

private:
    CurriculumnHeaderModel *m_curriculumn;
};
//------------------------------------------
class CurriculumnHeaderDelegate : public QItemDelegate
{
public:
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    virtual void drawDisplay(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect, const QString &text) const;

private:
    mutable QModelIndex m_currentPaintedIndex;//workaround: QStyleOptionViewItemV4::index is not set in QItemDelegate::paint
};
//------------------------------------------
class CurriculumnHeaderView : public QTableView
{
    Q_OBJECT
public:
    CurriculumnHeaderView(KTU::Curriculumn *curriculumn, QWidget *parent = 0);

    CurriculumnHeaderModel *model() const { return m_model; }

private:
    virtual void setModel(QAbstractItemModel *model);

private slots:
    void initSpans();

private:
    CurriculumnHeaderModel *m_model;
};
//------------------------------------------
class CurriculumnItemsDelegate : public QItemDelegate
{
public:
    explicit CurriculumnItemsDelegate(CurriculumnItemsView *view);

    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    virtual void drawDisplay(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect, const QString &text) const;
    virtual void drawFocus(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect) const;
    virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
    mutable QModelIndex m_currentPaintedIndex;//workaround: QStyleOptionViewItemV4::index is not set in QItemDelegate::paint
    CurriculumnItemsView *m_view;
};
//------------------------------------------
class CurriculumnItemsView : public QTreeView
{
    Q_OBJECT

public:
    CurriculumnItemsView(CurriculumnHeaderModel *model, QWidget *parent = 0);

    CurriculumnItemsModel *model() const { return m_model; }

private:
    virtual void setModel(QAbstractItemModel *model);

private:
    CurriculumnItemsModel *m_model;
};
//------------------------------------------
class CurriculumnWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CurriculumnWidget(KTU::Curriculumn *curriculumn, QWidget *parent = 0);

private slots:
    void resizeHeaderSection(int, int, int);
    void resizeItemsSection(int, int, int);
//    void scrollBarRangeChanged(int, int);
    void scrollBarValueChanged(int);
    void showContextMenu(const QPoint &point);
    void addCurriculumnSection();
    void addCurriculumnGroup();
    void addCurriculumnDiscipline();
    void removeCurriculumnSection();
    void removeCurriculumnGroup();
    void removeCurriculumnDiscipline();

private:
    CurriculumnHeaderView *m_headerView;
    CurriculumnItemsView *m_itemsView;
    SelectorDialog *m_selectorDialog;
};
//------------------------------------------
class SelectorDialog : public QDialog
{
    Q_OBJECT
public:
    enum EntityType{ Section, Group, Discipline };

    explicit SelectorDialog(QWidget *parent = 0);

    quint32 sectionId() const;
    quint32 groupId() const;
    quint32 disciplineId() const;
    quint32 chairId() const;

public slots:
    int exec(EntityType type);

private:
    void init();

private:
    QFormLayout *m_formLayout;
    QComboBox *m_cbSections;
    QComboBox *m_cbGroups;
    QComboBox *m_cbDisciplines;
    QComboBox *m_cbChairs;
};

#endif // CALENDARWIDGET_H
