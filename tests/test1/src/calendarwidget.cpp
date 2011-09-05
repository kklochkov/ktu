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
#include <QDebug>

#include "calendarwidget.h"

#include <KtuCurriculumn>

static QString decimalToLatin(int number)
{
    QString res;
    switch (number) {
    case 1: res = QLatin1String("I");
        break;
    case 2: res = QLatin1String("II");
        break;
    case 3: res = QLatin1String("III");
        break;
    case 4: res = QLatin1String("IV");
        break;
    case 5: res = QLatin1String("V");
        break;
    case 6: res = QLatin1String("VI");
        break;
    }
    return res;
}

static QColor colorForMonth(int month)
{
    static QList<QColor> colors;
    if (colors.isEmpty()) {
        QColor color;

        color.setHsv(210, 255, 255);//jan
        colors << color;

        color.setHsv(240, 255, 255);//feb
        colors << color;

        color.setHsv(160, 255, 255);//mar
        colors << color;

        color.setHsv(140, 255, 245);//apr
        colors << color;

        color.setHsv(120, 255, 235);//may
        colors << color;

        color.setHsv(80, 255, 255);//june
        colors << color;

        color.setHsv(70, 255, 255);//july
        colors << color;

        color.setHsv(60, 255, 255);//aug
        colors << color;

        color.setHsv(50, 255, 255);//sep
        colors << color;

        color.setHsv(40, 255, 255);//oct
        colors << color;

        color.setHsv(0, 255, 255);//nov
        colors << color;

        color.setHsv(200, 255, 255);//dec
        colors << color;
    }
    return colors.at(month - 1);
}
//-------------------------------------------
CalendarDelegate::CalendarDelegate(QObject *parent)
    : QItemDelegate(parent)
{

}

QWidget *CalendarDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);

    const CalendarModel *model = qobject_cast<const CalendarModel *>(index.model());

    if (!model)
        return 0;

    QComboBox *comboBox = new QComboBox(parent);
    connect(comboBox, SIGNAL(currentIndexChanged(int)), SLOT(signActivated(int)));

    const QList<KTU::CalendarWeekSign *> signs = model->signs();
    foreach (KTU::CalendarWeekSign *sign, signs)
        comboBox->addItem(sign->sign(), qVariantFromValue(sign));

    return comboBox;
}

void CalendarDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    m_currentPaintedIndex = index;//workaround: QStyleOptionViewItemV4::index is not set in QItemDelegate::paint
    QItemDelegate::paint(painter, option, index);
}

void CalendarDelegate::drawDisplay(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect, const QString &text) const
{
    if (m_currentPaintedIndex.row() == CalendarModel::Dates) {
        const int xOffset = qRound(option.fontMetrics.height() / 2.0);
        const int yOffset = qRound(option.fontMetrics.width(text) / 2.0);
        painter->save();
        painter->translate(rect.topLeft() + QPoint(rect.width() / 2 + xOffset, rect.height() / 2 + yOffset));
        painter->rotate(-90);
        painter->drawText(0, 0, text);
        painter->restore();
        return;
    }

    QItemDelegate::drawDisplay(painter, option, rect, text);
}

QSize CalendarDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    const int row = index.row();
    const int marging = 5;
    if (row == CalendarModel::Dates)
        return QSize(option.fontMetrics.height() + 3 * marging, option.fontMetrics.width(index.data().toString()) + 2 * marging);
    return QSize(4 * marging, option.fontMetrics.height() + 2 * marging);
}

void CalendarDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    if (!editor)
        return;
    editor->setGeometry(option.rect);
}

void CalendarDelegate::signActivated(int index)
{
    QComboBox *comboBox = qobject_cast<QComboBox *>(sender());
    if (!comboBox)
        return;
    emit signSelected(qvariant_cast<KTU::CalendarWeekSign *>(comboBox->itemData(index)));
    emit commitData(comboBox);
    emit closeEditor(comboBox);
}

void CalendarDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *comboBox = qobject_cast<QComboBox *>(editor);
    if (!comboBox || !model || !index.isValid())
        return;
    model->setData(index, comboBox->itemData(comboBox->currentIndex()));
}

void CalendarDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QComboBox *comboBox = qobject_cast<QComboBox *>(editor);
    if (!comboBox || !index.isValid())
        return;
    const int idx = comboBox->findText(index.data().toString());
    comboBox->setCurrentIndex(idx);
}
//-------------------------------------------
CalendarModel::CalendarModel(QObject *parent)
    : QAbstractTableModel(parent),
    m_calendar(0)
{
}

void CalendarModel::setCalendar(KTU::Calendar *calendar)
{
    m_calendar = calendar;
    init();
}

void CalendarModel::clear()
{
    if (!m_calendar)
        return;

    m_calendar->clear();
    reset();
}

void CalendarModel::setEducationTerm(int years)
{
    if (!m_calendar)
        return;

    m_calendar->curriculumn()->setEducationTerm(years);
    init();
}

int CalendarModel::educationTerm() const
{
    if (!m_calendar)
        return 0;
    return m_calendar->curriculumn()->educationTerm();
}

void CalendarModel::init()
{
    if (!m_calendar)
        return;

    reset();
    if (m_calendar->coursesCount())
        emit modelInitialized();
}

int CalendarModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return educationTerm() + Size;
}

int CalendarModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    if (!m_calendar)
        return 0;
    return m_calendar->weeksCount();
}

bool CalendarModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!m_calendar)
        return false;

    if (role == Qt::EditRole) {
        KTU::CalendarWeek *week = static_cast<KTU::CalendarWeek *>(index.internalPointer());
        if (week) {
            KTU::CalendarWeekSign *sign = qvariant_cast<KTU::CalendarWeekSign *>(value);
            week->setSign(sign);
            emit dataChanged(index, index);
            return true;
        }
    }
    return false;
}

QVariant CalendarModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !m_calendar)
        return QVariant();

    const int row = index.row();
    KTU::CalendarWeek *week = static_cast<KTU::CalendarWeek *>(index.internalPointer());
    KTU::CalendarSemester *semester = this->semester(course(index.row()), week->number());

    if (week) {
        if (role == Qt::DisplayRole || role == Qt::EditRole) {
            if (row == Semesters && semester) {
                return semester->number();
            } else if (row == Monthes) {
                return week->startDate().toString("MMMM");
            } else if (row == Dates) {
                return QString("%1-%2").arg(week->startDate().toString("d")).arg(week->endDate().toString("d"));
            } else {
                KTU::CalendarWeekSign *sign = week->sign();
                if (sign)
                    return sign->sign();
            }
        }

        if (role == Qt::BackgroundColorRole) {
            if (row == Monthes || row == Dates) {
                return colorForMonth(week->startDate().month());
            } else if (row == Semesters && semester) {
                return colorForMonth(semester->week(semester->startWeek())->startDate().month());
            }
        }
    }

    if (role == Qt::TextAlignmentRole)
        return Qt::AlignCenter;

    return QVariant();
}

KTU::CalendarWeek *CalendarModel::week(int course, int weekNumber) const
{
    if (!m_calendar)
        return 0;
    return m_calendar->week(course, weekNumber);
}

KTU::CalendarSemester *CalendarModel::semester(int course, int weekNumber) const
{
    if (!m_calendar)
        return 0;
    return m_calendar->semester(course, weekNumber);
}

int CalendarModel::course(int row) const
{
    if (row == Semesters || row == Monthes || row == Dates)
        return 1;
    return 1 + (row - Size);
}

QVariant CalendarModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Vertical) {
            if (section == Semesters) {
                return tr("Semester");
            } else if (section == Monthes) {
                return tr("Month");
            } else if (section == Dates) {
                return tr("Date");
            } else {
                return decimalToLatin(course(section));
            }
        }
    }

    if (role == Qt::TextAlignmentRole)
        return Qt::AlignCenter;

    return QAbstractTableModel::headerData(section, orientation, role);
}

Qt::ItemFlags CalendarModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    Qt::ItemFlags res = Qt::ItemIsEnabled;

    if (index.row() >= Size)
        res |= Qt::ItemIsSelectable | Qt::ItemIsEditable;

    return res;
}

QModelIndex CalendarModel::index(int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    KTU::CalendarWeek *week = this->week(course(row), column + 1);
    if (!week)
        return QModelIndex();
    return QAbstractItemModel::createIndex(row, column, week);
}

void CalendarModel::setSign(const QModelIndexList &list, KTU::CalendarWeekSign *sign)
{
    if (!sign || list.isEmpty())
        return;
    const bool isBlocked = blockSignals(true);
    foreach (const QModelIndex &index, list)
        setData(index, qVariantFromValue(sign));
    blockSignals(isBlocked);
    emit dataChanged(list.first(), list.last());
}
//-------------------------------------------
CalendarView::CalendarView(KTU::Calendar *calendar, QWidget *parent)
    : QTableView(parent),
    m_model(new CalendarModel(this))
{
    QTableView::setModel(m_model);
    QTableView::setItemDelegate(new CalendarDelegate(this));

    verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
    horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);

    connect(m_model, SIGNAL(modelInitialized()), SLOT(initSpans()));

    m_model->setCalendar(calendar);
}

void CalendarView::setModel(QAbstractItemModel *model)
{
    Q_UNUSED(model);
    qWarning() << Q_FUNC_INFO << "setting new model is not allowed.";
}

void CalendarView::initSpans(CalendarModel::FixedRows fixedRow)
{
    int count = 0;
    const int course = CalendarModel::Size;
    int startColumn = 0;
    for (int column = 0; column < model()->columnCount() - 1; ++column) {
        if (fixedRow == CalendarModel::Monthes) {
            const KTU::CalendarWeek *currentWeek = model()->week(course, column + 1);
            const KTU::CalendarWeek *nextWeek = model()->week(course, column + 2);
            if (!currentWeek || !nextWeek)
                continue;
            if ((currentWeek->startDate().month() == nextWeek->startDate().month())) {
                ++count;
            } else {
                setSpan(fixedRow, startColumn, 1, ++count);
                count = 0;
                startColumn = column + 1;
            }
        } else if (fixedRow == CalendarModel::Semesters) {
            const KTU::CalendarSemester *currentSemester = model()->semester(course, column + 1);
            const KTU::CalendarSemester *nextSemester = model()->semester(course, column + 2);
            if (!currentSemester || !nextSemester)
                continue;
            if ((currentSemester->number() == nextSemester->number())) {
                ++count;
            } else {
                setSpan(fixedRow, startColumn, 1, ++count);
                count = 0;
                startColumn = column + 1;
            }
        }
    }
    setSpan(fixedRow, startColumn, 1, ++count);

    int totalWidth = verticalHeader()->width() + 2;
    int totalHeight = 2 * horizontalHeader()->height() - 3;
    for (int c = 0; c < horizontalHeader()->count(); ++c)
        totalWidth += horizontalHeader()->sectionSize(c);
    for (int c = 0; c < verticalHeader()->count(); ++c)
        totalHeight += verticalHeader()->sectionSize(c);
    setMaximumSize(totalWidth, totalHeight);
}

void CalendarView::initSpans()
{
    reset();

    initSpans(CalendarModel::Semesters);
    initSpans(CalendarModel::Monthes);
}

void CalendarView::setSigns(const QList<KTU::CalendarWeekSign *> &signs)
{
    m_model->setSigns(signs);
}
//-------------------------------------------
CalendarWidget::CalendarWidget(KTU::Calendar *calendar, QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    m_calendar = new CalendarView(calendar, this);

    mainLayout->addWidget(m_calendar);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSizeConstraint(QLayout::SetMaximumSize);

    m_calendar->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(m_calendar, SIGNAL(customContextMenuRequested(const QPoint &)), SLOT(showContextMenu(const QPoint &)));
}

void CalendarWidget::setEducationTerm(int years)
{
    m_calendar->model()->setEducationTerm(years);
}

void CalendarWidget::setSigns(const QList<KTU::CalendarWeekSign *> &signs)
{
    m_calendar->setSigns(signs);
}

void CalendarWidget::signClicked()
{
    QAction *obj = qobject_cast<QAction *>(sender());
    if (!obj)
        return;
    KTU::CalendarWeekSign *sign = qvariant_cast<KTU::CalendarWeekSign *>(obj->property("sign"));
    m_calendar->model()->setSign(m_calendar->selectionModel()->selectedIndexes(), sign);
}

void CalendarWidget::showContextMenu(const QPoint &point)
{
    QMenu menu(this);

    QList<KTU::CalendarWeekSign *> signs = m_calendar->model()->signs();
    for (int i = 0; i < signs.count(); ++i) {
        KTU::CalendarWeekSign *sign = signs.at(i);
        QAction *action = menu.addAction(QString("%1 - %2").arg(sign->sign()).arg(sign->description()), this, SLOT(signClicked()));
        action->setProperty("sign", qVariantFromValue(sign));
    }
    menu.addSeparator();
    menu.addAction(tr("Save curriculumn"), this, SLOT(saveCurriculumn()));
    menu.addAction(tr("Show time budget"), this, SLOT(showTimeBudget()));
//    menu.addAction(tr("Generate curriculumn"), this, SLOT(generateCurriculumn()));

    menu.exec(m_calendar->mapToGlobal(point));
}

void CalendarWidget::saveCurriculumn()
{
    QFile file("test.dat");
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);
    KTU::Curriculumn *curriculumn = m_calendar->model()->calendar()->curriculumn();
    out << *(curriculumn);
}

void CalendarWidget::showTimeBudget()
{
    CalendarTimeBudgetDialog ctbd(m_calendar->model(), this);
    ctbd.exec();
}

//void CalendarWidget::generateCurriculumn()
//{
//    static int worksCount = 4;
//    const KTU::Calendar *calendar = m_calendar->model()->calendar();

//    QString curriculumnHTML(QString("<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\"\n"
//                        "\"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">\n"
//                        "<html lang=\"ru-RU\" xml:lang=\"ru-RU\" xmlns=\"http://www.w3.org/1999/xhtml\">\n"
//                        "<head>\n"
//                        "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />\n"
//                        "<title></title>\n"
//                        "<style type=\"text/css\">\n"
//                        "table.c1 { font-size:12px; border-collapse: collapse; border: solid 1px black; width: 100%; }"
//                        "</style>\n"
//                        "</head>\n"
//                        "<body>\n"
//                        "<table border=\"1\" class=\"c1\">\n"
//                        "<tr>\n"
//                        "<th rowspan=\"9\">Дисциплина</th>\n"
//                        "<th colspan=\"4\">� аспределение по семестрам</th>\n"
//                        "<th colspan=\"7\">Количество часов</th>\n"
//                        "<th colspan=\"%1\">� аспределение аудиторных часов на неделю по курсам и семестрам</th>\n"
//                        "<th rowspan=\"9\">Кафедра</th>\n"
//                        "</tr>\n"
//                        "<tr>\n"
//                        "<th rowspan=\"8\">Экзамены</th>\n"
//                        "<th rowspan=\"8\">Зачеты</th>\n"
//                        "<th colspan=\"2\">Курсовые</th>\n"
//                        "<th rowspan=\"8\">Общий объем</th>\n"
//                        "<th rowspan=\"8\">Количество Кредитов ECTS</th>\n"
//                        "<th colspan=\"4\">аудиторные</th>\n"
//                        "<th rowspan=\"8\">Самостоятельная работа</th>\n"
//                        "<th colspan=\"%1\">Курс</th>\n"
//                        "</tr>\n"
//                        "<tr>\n"
//                        "<th rowspan=\"7\">проекты</th>\n"
//                        "<th rowspan=\"7\">роботы</th>\n"
//                        "<th rowspan=\"7\">Всего</th>\n"
//                        "<th colspan=\"3\">в том числе</th>\n"
//                        ).arg(worksCount * calendar->semestersCount()));

//    QList<KTU::CalendarSemester *> semesters;
//    for (quint32 i = 1; i <= calendar->coursesCount(); ++i) {
//        KTU::CalendarCourse *course = calendar->course(i);
//        semesters << course->semesters();
//        curriculumnHTML += QString("<th colspan=\"%1\">%2</th>\n").arg(worksCount * course->semestersCount()).arg(course->number());
//    }
//    curriculumnHTML += QString("</tr>\n"
//                               "<tr>\n"
//                               "<th rowspan=\"6\">Лекции</th>\n"
//                               "<th rowspan=\"6\">Лабораторные</th>\n"
//                               "<th rowspan=\"6\">Практические</th>\n"
//                               "<th colspan=\"%1\">Семестры</th>\n"
//                               "</tr>"
//                               "<tr>").arg(worksCount * calendar->semestersCount());
//    foreach (KTU::CalendarSemester *semester, semesters)
//        curriculumnHTML += QString("<th colspan=\"4\">%1</th>\n").arg(semester->number());
//    curriculumnHTML += QString("</tr>\n"
//                               "<tr>\n"
//                               "<th colspan=\"%1\">Количество недель в семестре</th>\n"
//                               "</tr>\n"
//                               "<tr>\n").arg(worksCount * calendar->semestersCount());
//    foreach (KTU::CalendarSemester *semester, semesters)
//        curriculumnHTML += QString("<th colspan=\"4\">%1</th>\n").arg(semester->workWeeksCount());
//    curriculumnHTML += QString("</tr>\n"
//                               "<tr>\n"
//                               "<th colspan=\"%1\">Виды занятий</th>\n"
//                               "</tr>\n"
//                               "<tr>").arg(worksCount * calendar->semestersCount());
//    for (quint32 i = 0; i < calendar->semestersCount(); ++i)
//        curriculumnHTML += "<th>ЛК</th>\n"
//                           "<th>ЛЗ</th>\n"
//                           "<th>ПЗ</th>\n"
//                           "<th>ККС</th>\n";
//    curriculumnHTML += "</tr>\n"
//                       "</table>\n"
//                        "</body>\n"
//                        "</html>\n";

//    if (QFile::exists("curriculumn.html"))
//        QFile::remove("curriculumn.html");

//    QFile file("curriculumn.html");
//    file.open(QIODevice::WriteOnly);
//    QTextStream out(&file);
//    out.setCodec("UTF-8");
//    out << curriculumnHTML;
//    file.close();

//    emit curriculumnGenerated();
//}
//------------------------------------
CalendarTimeBudgetDialog::CalendarTimeBudgetDialog(const CalendarModel *calendar, QWidget *parent)
    : QDialog(parent),
    m_calendar(calendar),
    m_timeBudgetModel(new QStandardItemModel(this))
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QTableView *table = new QTableView(this);
    table->setModel(m_timeBudgetModel);

    m_signsLayout = new QGridLayout();
    mainLayout->addWidget(table);
    mainLayout->addLayout(m_signsLayout);

    m_signsLayout->setVerticalSpacing(0);
    mainLayout->setSpacing(5);

    init();
}

void CalendarTimeBudgetDialog::init()
{
    if (!m_calendar)
        return;

    const QList<KTU::CalendarWeekSign *> signs = m_calendar->signs();

    m_timeBudgetModel->clear();

    m_timeBudgetModel->setRowCount(m_calendar->calendar()->coursesCount() + 1);
    m_timeBudgetModel->setColumnCount(1);

    QStringList verticalLabels;

    const int lastRow = m_timeBudgetModel->rowCount() - 1;
    for (int row = 0; row < lastRow; ++row)
        verticalLabels << decimalToLatin(row + 1);

    m_timeBudgetModel->setVerticalHeaderItem(lastRow, new QStandardItem(tr("Overall total")));
    m_timeBudgetModel->setHorizontalHeaderItem(0, new QStandardItem(tr("Overall total")));
    m_timeBudgetModel->setVerticalHeaderLabels(verticalLabels);

    int row = 0;
    for (int i = 0; i < signs.count(); ++i) {
        const int column = i % 4;
        KTU::CalendarWeekSign *sign = signs.at(i);
        if (!sign)
            continue;

        m_signsLayout->addLayout(createSignWidgets(sign), row, column);
        if (column == 3)
            ++row;

        addColumn(sign);
    }
}

QHBoxLayout *CalendarTimeBudgetDialog::createSignWidgets(KTU::CalendarWeekSign *sign) const
{
    if (!sign)
        return 0;

    QHBoxLayout *hbl = new QHBoxLayout();

    QPushButton *pbSign = new QPushButton(sign->sign());
    pbSign->setStyleSheet("QPushButton {"
        "border: 2px solid black;"
        "max-width: 20px;"
        "max-height: 20px;"
        "min-width: 20px;"
        "min-height: 20px;"
        "}"
        "QPushButton:pressed {"
        "background-color: gray;"
        "}"
        "QPushButton:checked {"
        "background-color: gray;"
        "}");
    pbSign->setProperty("sign", qVariantFromValue(sign));
    pbSign->setCheckable(true);
    pbSign->setChecked(true);
    connect(pbSign, SIGNAL(toggled(bool)), SLOT(signClicked(bool)));

    QLabel *lDescription = new QLabel(sign->description());
    lDescription->setWordWrap(true);

    hbl->addWidget(pbSign);
    hbl->addWidget(lDescription);

    return hbl;
}

void CalendarTimeBudgetDialog::addColumn(KTU::CalendarWeekSign *sign)
{
    if (!sign)
        return;

    QList<QStandardItem *> items;
    for (int row = 0; row < m_timeBudgetModel->rowCount(); ++row) {
        const quint32 sum = m_calendar->calendar()->sum(row + 1, sign);
        items << new QStandardItem(QString::number(sum));
    }

    const int column = m_timeBudgetModel->columnCount()  - 1;
    m_timeBudgetModel->insertColumn(column, items);
    m_timeBudgetModel->setHorizontalHeaderItem(column, new QStandardItem(sign->sign()));
    recalc();
}

void CalendarTimeBudgetDialog::removeColumn(KTU::CalendarWeekSign *sign)
{
    if (!sign)
        return;

    for (int column = 0; column < m_timeBudgetModel->columnCount(); ++column) {
        if (m_timeBudgetModel->horizontalHeaderItem(column)->text() == sign->sign()) {
            m_timeBudgetModel->removeColumn(column);
            break;
        }
    }
    recalc();
}

void CalendarTimeBudgetDialog::recalc()
{
    sum(Qt::Horizontal);
    sum(Qt::Vertical);
}

void CalendarTimeBudgetDialog::signClicked(bool checked)
{
    if (!sender())
        return;
    KTU::CalendarWeekSign *sign = qvariant_cast<KTU::CalendarWeekSign *>(sender()->property("sign"));
    checked ? addColumn(sign) : removeColumn(sign);
}

void CalendarTimeBudgetDialog::sum(Qt::Orientation orientation)
{
    const int lastRow = m_timeBudgetModel->rowCount() - 1;
    const int lastCol = m_timeBudgetModel->columnCount() - 1;

    const int endI = orientation == Qt::Horizontal ? lastRow : lastCol;
    const int endJ = orientation == Qt::Horizontal ? lastCol : lastRow;

    quint32 autidoriumTotal = 0;
    for (int i = 0; i < endI; ++i) {
        quint32 sum = 0;
        int row = 0;
        int column = 0;
        for (int j = 0; j < endJ; ++j) {
            row = orientation == Qt::Horizontal  ? i : j;
            column = orientation == Qt::Horizontal  ? j : i;
            sum += m_timeBudgetModel->data(m_timeBudgetModel->index(row, column)).toInt();
        }
        row = orientation == Qt::Horizontal  ? i : lastRow;
        column = orientation == Qt::Horizontal  ? lastCol : i;
        m_timeBudgetModel->setData(m_timeBudgetModel->index(row, column), sum);
        m_timeBudgetModel->setData(m_timeBudgetModel->index(row, column), Qt::green, Qt::BackgroundColorRole);
        autidoriumTotal += sum;
    }

    m_timeBudgetModel->setData(m_timeBudgetModel->index(lastRow, lastCol), autidoriumTotal);
    m_timeBudgetModel->setData(m_timeBudgetModel->index(lastRow, lastCol), Qt::red, Qt::BackgroundColorRole);
}
//------------------------------------
CurriculumnHeaderModel::CurriculumnHeaderModel(QObject *parent)
    : QAbstractTableModel(parent),
    m_curriculumn(0)
{

}

void CurriculumnHeaderModel::setCurriculumn(KTU::Curriculumn *curriculumn)
{
    if (!curriculumn || m_curriculumn == curriculumn)
        return;
    m_curriculumn = curriculumn;
    reset();
    if (m_curriculumn->calendar()->coursesCount())
        emit modelInitialized();
}

int CurriculumnHeaderModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 7;
}

int CurriculumnHeaderModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    if (!m_curriculumn)
        return 13;
    static int worksCount = 4;
    return 13 + (worksCount * m_curriculumn->calendar()->semestersCount());
}

QVariant CurriculumnHeaderModel::data(const QModelIndex &index, int role) const
{
    if (!m_curriculumn || !index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole) {
        if (index.row() <= 7) {
            if (!index.column()) {
                return tr("Discipline");
            } else if (index.column() == 1) {
                if (!index.row()) {
                    return tr("Arrangment by semester");
                } else if (index.row() == 1) {
                    return tr("Exams");
                }
            } else if (index.column() == 2) {
                if (!index.row()) {
                    return tr("Arrangment by semester");
                } else if (index.row() == 1) {
                    return tr("Tests");
                }
            } else if (index.column() == 3) {
                if (index.row() == 1) {
                    return tr("Course");
                } else {
                    return tr("Projects");
                }
            } else if (index.column() == 4) {
                if (index.row() == 1) {
                    return tr("Course");
                } else {
                    return tr("Works");
                }
            } else if (index.column() == 5) {
                if (!index.row()) {
                    return tr("Hours");
                } else {
                    return tr("Total");
                }
            } else if (index.column() == 6) {
                if (!index.row()) {
                    return tr("Hours");
                } else {
                    return tr("ECTS");
                }
            } else if (index.column() == 7) {
                if (!index.row()) {
                    return tr("Hours");
                } else if (index.row() == 1) {
                    return tr("Auditoriums");
                } else {
                    return tr("Total");
                }
            } else if (index.column() == 8) {
                if (!index.row()) {
                    return tr("Hours");
                } else if (index.row() == 1) {
                    return tr("Auditoriums");
                } else if (index.row() == 2) {
                    return tr("Including:");
                } else {
                    return tr("Lections");
                }
            }  else if (index.column() == 9) {
                if (!index.row()) {
                    return tr("Hours");
                } else if (index.row() == 1) {
                    return tr("Auditoriums");
                } else if (index.row() == 2) {
                    return tr("Including");
                } else {
                    return tr("Labs");
                }
            } else if (index.column() == 10) {
                if (!index.row()) {
                    return tr("Hours");
                } else if (index.row() == 1) {
                    return tr("Auditoriums");
                } else if (index.row() == 2) {
                    return tr("Including:");
                } else {
                    return tr("Practices");
                }
            } else if (index.column() == 11) {
                if (!index.row()) {
                    return tr("Hours");
                } else {
                    return tr("Individual Work");
                }
            } else if (index.column() > 11 && index.column() < (columnCount() - 1)) {
                if (!index.row())
                    return tr("Arrangement hours by courses, semesters and weeks");

                static int worksCount = 4;
                KTU::Calendar *calendar = m_curriculumn->calendar();

                if (index.row() == 1) {
                    const quint32 count = calendar->coursesCount();
                    for (quint32 i = 0; i < count; ++i) {
                        const KTU::CalendarCourse *course = calendar->course(i + 1);
                        const int idx = 12 + i * worksCount * course->semestersCount();
                        if (index.column() == idx)
                            return QString("%1").arg(course->number());
                    }
                } else if (index.row() == 2) {
                    return tr("Semesters");
                } else if (index.row() == 3 || index.row() == 5) {
                    const quint32 count = calendar->coursesCount();
                    int j = 0;
                    for (quint32 i = 0; i < count; ++i) {
                        const KTU::CalendarCourse *course = calendar->course(i + 1);
                        foreach (const KTU::CalendarSemester *semester, course->semesters()) {
                            const int idx = 12 + j * worksCount;
                            ++j;
                            if (index.column() == idx) {
                                if (index.row() == 3) {
                                    return semester->number();
                                } else if (index.row() == 5) {
                                    return semester->workWeeksCount();
                                }
                            }
                        }
                    }
                } else if (index.row() == 4) {
                    return tr("Weeks");
                } else if (index.row() == rowCount() - 1) {
                    const int idx = index.column() % worksCount;
                    if (!idx) {
                        return tr("Lec");
                    } else if (idx == 1) {
                        return tr("Lab");
                    } else if (idx == 2) {
                        return tr("Prac");
                    }  else if (idx == 3) {
                        return tr("KKS");
                    }
                }
            } else if (index.column() == columnCount() - 1) {
                return tr("Chair");
            }
        }
    }

    if (role == VerticalTextRole) {
        if (index.column() == 1) {
            if (index.row() == 1)
                return true;
        } else if (index.column() == 2) {
            if (index.row() == 1)
                return true;
        } else if (index.column() == 3) {
            if (index.row() > 1)
                return true;
        } else if (index.column() == 4) {
            if (index.row() > 1)
                return true;
        } else if (index.column() == 5) {
            if (index.row() > 0)
                return true;
        } else if (index.column() == 6) {
            if (index.row() > 0)
                return true;
        } else if (index.column() == 7) {
            if (index.row() > 1)
                return true;
        } else if (index.column() == 8) {
            if (index.row() > 2)
                return true;
        }  else if (index.column() == 9) {
            if (index.row() > 2)
                return true;
        } else if (index.column() == 10) {
            if (index.row() > 2)
                return true;
        } else if (index.column() == 11) {
            if (index.row() > 0)
                return true;
        }
    }

    if (role == Qt::TextAlignmentRole)
        return Qt::AlignCenter;

    return QVariant();
}

Qt::ItemFlags CurriculumnHeaderModel::flags(const QModelIndex &index) const
{
    Q_UNUSED(index);
    return Qt::ItemIsEnabled;
}

QModelIndex CurriculumnHeaderModel::index(int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return QAbstractItemModel::createIndex(row, column);
}
//------------------------------------
CurriculumnItemsModel::CurriculumnItemsModel(QObject *parent)
    : QAbstractItemModel(parent),
    m_curriculumn(0)
{

}

void CurriculumnItemsModel::setCurriculumnHeaderModel(CurriculumnHeaderModel *model)
{
    if (!model || m_curriculumn == model)
        return;
    m_curriculumn = model;
    reset();

    connect(model, SIGNAL(modelInitialized()), SIGNAL(modelInitialized()));
    emit modelInitialized();
}

//void CurriculumnItemsModel::getEntities(const QModelIndex &index, KTU::CurriculumnDisciplineGroup *&group, KTU::CurriculumnDisciplineSubGroup *&subGroup, KTU::CurriculumnRecord *&record) const
//{
//    KTU::Curriculumn *curriculumn = m_curriculumn->curriculumn();
//    switch (index.internalId()) {
//        case Group: {
//            group = curriculumn->group(index.row());
//        } break;
//        case SubGroup: {
//            group = curriculumn->group(index.parent().row());
//            if (group)
//                subGroup = group->subGroup(index.row());
//        } break;
//        case Record: {
//            group = curriculumn->group(index.parent().parent().row());
//            if (group)
//                subGroup = group->subGroup(index.parent().row());
//            if (subGroup)
//                record = subGroup->record(index.row());
//        } break;
//    }
//}

int CurriculumnItemsModel::rowCount(const QModelIndex &parent) const
{
//    KTU::CurriculumnDisciplineGroup *group = 0;
//    KTU::CurriculumnDisciplineSubGroup *subGroup = 0;
//    KTU::CurriculumnRecord *record = 0;
//    getEntities(parent, group, subGroup, record);

//    if (!parent.isValid())
//        return m_curriculumn->curriculumn()->groups().count();

//    if (parent.internalId() == Group && group)
//        return group->subGroups().count();

//    if (parent.internalId() == SubGroup && subGroup)
//        return subGroup->records().count() + 1;




    if (!parent.isValid())
        return m_curriculumn->curriculumn()->groups().count();

    KTU::CurriculumnDisciplineGroup *group = static_cast<KTU::CurriculumnDisciplineGroup *>(parent.internalPointer());
    if (group && group->className() == QLatin1String("CurriculumnDisciplineGroup"))
        return group->subGroups().count();

    KTU::CurriculumnDisciplineSubGroup *subGroup = static_cast<KTU::CurriculumnDisciplineSubGroup *>(parent.internalPointer());
    if (subGroup && subGroup->className() == QLatin1String("CurriculumnDisciplineSubGroup"))
        return subGroup->records().count() + 1;//TODO: +1 for totalls

    return 0;
}

int CurriculumnItemsModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    if (!m_curriculumn)
        return 0;
    return m_curriculumn->columnCount();
}

Qt::ItemFlags CurriculumnItemsModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags res = Qt::ItemIsEnabled;
    KTU::CurriculumnRecord *record = static_cast<KTU::CurriculumnRecord *>(index.internalPointer());
    if (record && record->className() == QLatin1String("CurriculumnRecord")) {//TODO: totalls
//    if (index.internalId() == Record) {
        res |= Qt::ItemIsSelectable;
        if ((index.row() < rowCount(index.parent()) - 1) &&
            ((index.column() > 0 &&
            index.column() <= 5) ||
            (index.column() >= 12 &&
            index.column() <= (columnCount() - 1))))
        res |= Qt::ItemIsEditable;
    }
    return res;
}

QModelIndex CurriculumnItemsModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    if (!parent.isValid()) {
        KTU::CurriculumnDisciplineGroup *group = m_curriculumn->curriculumn()->group(row);
        if (group)
            return createIndex(row, column, group);
    }

    KTU::CurriculumnDisciplineGroup *group = static_cast<KTU::CurriculumnDisciplineGroup *>(parent.internalPointer());
    if (group && group->className() == QLatin1String("CurriculumnDisciplineGroup")) {
        KTU::CurriculumnDisciplineSubGroup *subGroup = group->subGroup(row);
        if (subGroup)
            return createIndex(row, column, subGroup);
    }

    KTU::CurriculumnDisciplineSubGroup *subGroup = static_cast<KTU::CurriculumnDisciplineSubGroup *>(parent.internalPointer());
    if (subGroup && subGroup->className() == QLatin1String("CurriculumnDisciplineSubGroup")) {
        int r = row;
        if (row == rowCount(parent) - 1)//TODO: totalls
            --r;
        KTU::CurriculumnRecord *record = subGroup->record(r);
        if (record)
            return createIndex(row, column, record);
    }


//    if (!parent.isValid())
//        return createIndex(row, column, Group);

//    const qint64 rId = parent.internalId();

//    if (rId == Group)
//        return createIndex(row, column, SubGroup);

//    if (rId == SubGroup)
//        return createIndex(row, column, Record);

    return QModelIndex();
}

QModelIndex CurriculumnItemsModel::parent(const QModelIndex &index) const
{
//    if (!index.isValid())
//        return QModelIndex();

//    const qint64 rId = index.internalId();

//    if (rId == Group)
//        return QModelIndex();

//    KTU::CurriculumnDisciplineGroup *group = 0;
//    KTU::CurriculumnDisciplineSubGroup *subGroup = 0;
//    KTU::CurriculumnRecord *record = 0;
//    getEntities(index, group, subGroup, record);

//    if (rId == SubGroup) {
//        const int row = subGroup->group()->indexOf(subGroup);
//        if (row < 0)
//            return QModelIndex();
//        return createIndex(row, 0, Group);
//    }

//    if (rId == Record) {
//        int row = record->subGroup()->indexOf(record);
//        if (row > index.row())
//            ++row;
//        if (row < 0)
//            return QModelIndex();
//        return createIndex(row, 0, SubGroup);
//    }

    KTU::CurriculumnDisciplineGroup *group = static_cast<KTU::CurriculumnDisciplineGroup *>(index.internalPointer());
    if (group && group->className() == QLatin1String("CurriculumnDisciplineGroup"))
        return QModelIndex();

    KTU::CurriculumnDisciplineSubGroup *subGroup = static_cast<KTU::CurriculumnDisciplineSubGroup *>(index.internalPointer());
    if (subGroup && subGroup->className() == QLatin1String("CurriculumnDisciplineSubGroup")) {
        const int row = subGroup->group()->indexOf(subGroup);
        if (row < 0)
            return QModelIndex();
        return createIndex(row, index.column(), subGroup->group());
    }

    KTU::CurriculumnRecord *record = static_cast<KTU::CurriculumnRecord *>(index.internalPointer());
    if (record && record->className() == QLatin1String("CurriculumnRecord")) {
        int row = record->subGroup()->indexOf(record);
        if (row > index.row())//TODO: totalls
            ++row;
        if (row < 0)
            return QModelIndex();
        return createIndex(row, index.column(), record->subGroup());
    }

    return QModelIndex();
}

QString uint32ListToString(const QList<quint32> &list)
{
    QString res;
    foreach (quint32 item, list)
        res += QString("%1,").arg(item);
    res = res.remove(res.length() - 1, 1);
    return res;
}

QList<quint32> stringToUint32List(const QString &string)
{
    const QStringList list = string.simplified().trimmed().split(',');
    QList<quint32> res;
    foreach (const QString &item, list) {
        quint32 v = item.toUInt();
        if (v)
            res << item.toUInt();
    }
    return res;
}

bool CurriculumnItemsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!m_curriculumn || !index.isValid())
        return false;

    if (role == Qt::EditRole || role == Qt::DisplayRole) {
        KTU::CurriculumnRecord *record = static_cast<KTU::CurriculumnRecord *>(index.internalPointer());
//        KTU::CurriculumnDisciplineGroup *group = 0;
//        KTU::CurriculumnDisciplineSubGroup *subGroup = 0;
//        KTU::CurriculumnRecord *record = 0;
//        getEntities(index, group, subGroup, record);

        if (/*index.internalId() == Record && */record && record->className() == QLatin1String("CurriculumnRecord") &&
                index.row() < rowCount(index.parent()) - 1) {//TODO: skip totalls
            if (index.column() == 1) {
                record->setExams(stringToUint32List(value.toString()));
            } else if (index.column() == 2) {
                record->setTests(stringToUint32List(value.toString()));
            } else if (index.column() == 3) {
                record->setCourseProjects(stringToUint32List(value.toString()));
            } else if (index.column() == 4) {
                record->setCourseWorks(stringToUint32List(value.toString()));
            } else if (index.column() == 5) {
                record->setTotalByPlan(value.toFloat());
            } else if (index.column() >= 12 && index.column() < (columnCount() - 1)) {
                const quint32 semesterNumber = 1 + ((index.column() - 12) / 4);
                const quint32 kindOfWork = index.column() % 4;
                const qreal v = value.toFloat();
                KTU::CurriculumnSemester *semester = record->semester(semesterNumber);
                if (semester) {
                    switch (kindOfWork) {
                        case 0: semester->setLectionsHours(v);
                            break;
                        case 1: semester->setLabsHours(v);
                            break;
                        case 2: semester->setPracticesHours(v);
                            break;
                        case 3: semester->setKKSHours(v);
                            break;
                    }
                }
            }
        }
    }

    return true;
}

QVariant CurriculumnItemsModel::data(const QModelIndex &index, int role) const
{
    if (!m_curriculumn || !index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole) {
        KTU::CurriculumnDisciplineGroup *group = static_cast<KTU::CurriculumnDisciplineGroup *>(index.internalPointer());
        KTU::CurriculumnDisciplineSubGroup *subGroup = static_cast<KTU::CurriculumnDisciplineSubGroup *>(index.internalPointer());
        KTU::CurriculumnRecord *record = static_cast<KTU::CurriculumnRecord *>(index.internalPointer());

//        KTU::CurriculumnDisciplineGroup *group = 0;
//        KTU::CurriculumnDisciplineSubGroup *subGroup = 0;
//        KTU::CurriculumnRecord *record = 0;
//        getEntities(index, group, subGroup, record);

        if (/*index.internalId() == Group && */group && group->className() == QLatin1String("CurriculumnDisciplineGroup") && group->curriculumnSection())
            return group->curriculumnSection()->name();

        if (/*index.internalId() == SubGroup && */subGroup && subGroup->className() == QLatin1String("CurriculumnDisciplineSubGroup") && subGroup->curriculumnGroup())
            return subGroup->curriculumnGroup()->name();

        if (/*index.internalId() == Record && */record && record->className() == QLatin1String("CurriculumnRecord")) {
            if (index.row() < rowCount(index.parent()) - 1) {//TODO: totalls
                if (!index.column()) {
                    if (record->discipline())
                        return record->discipline()->name();
                } else if (index.column() == 1) {
                    return uint32ListToString(record->exams());
                } else if (index.column() == 2) {
                    return uint32ListToString(record->tests());
                } else if (index.column() == 3) {
                    return uint32ListToString(record->courseProjects());
                } else if (index.column() == 4) {
                    return uint32ListToString(record->courseWorks());
                } else if (index.column() == 5) {
                    const qreal v = record->totalByPlan();
                    if (v)
                        return v;
                } else if (index.column() == 6) {
                    const qreal v = record->ects();
                    if (v)
                        return v;
                } else if (index.column() == 7) {
                    const qreal v = record->autidoriumTotal();
                    if (v)
                        return v;
                } else if (index.column() == 8) {
                    const qreal v = record->lectionsHoursTotal();
                    if (v)
                        return v;
                } else if (index.column() == 9) {
                    const qreal v = record->labsHoursTotal();
                    if (v)
                        return v;
                } else if (index.column() == 10) {
                    const qreal v = record->practicesHoursTotal();
                    if (v)
                        return v;
                } else if (index.column() == 11) {
                    const qreal v = record->individualWork();
                    if (v)
                        return v;
                } else if (index.column() >= 12 && index.column() < (columnCount() - 1)) {
                    const quint32 semesterNumber = 1 + ((index.column() - 12) / 4);
                    const quint32 kindOfWork = index.column() % 4;
                    qreal v = 0;
                    switch (kindOfWork) {
                        case 0: v = record->lectionsHours(semesterNumber);
                            break;
                        case 1: v = record->labsHours(semesterNumber);
                            break;
                        case 2: v = record->practicesHours(semesterNumber);
                            break;
                        case 3: v = record->kksHours(semesterNumber);
                            break;
                    }
                    if (v)
                        return v;
                } else if (index.column() == (columnCount() - 1)) {
                    if (record->chair())
                        return record->chair()->name();
                }
            } else {//TODO: totalls
                if (!index.column()) {
                    return tr("Totalls by cycle:");
                } else if (index.column() == 1) {
                    return record->subGroup()->exams();
                } else if (index.column() == 2) {
                    return record->subGroup()->tests();
                } else if (index.column() == 3) {
                    return record->subGroup()->courseProjects();
                } else if (index.column() == 4) {
                    return record->subGroup()->courseWorks();
                } else if (index.column() == 5) {
                    return record->subGroup()->totalByPlan();
                } else if (index.column() == 6) {
                    return record->subGroup()->ects();
                } else if (index.column() == 7) {
                    return record->subGroup()->autidoriumTotal();
                } else if (index.column() == 8) {
                    return record->subGroup()->lectionsHoursTotal();
                } else if (index.column() == 9) {
                    return record->subGroup()->labsHoursTotal();
                } else if (index.column() == 10) {
                    return record->subGroup()->practicesHoursTotal();
                } else if (index.column() == 11) {
                    return record->subGroup()->individualWork();
                } else if (index.column() >= 12 && index.column() < (columnCount() - 1)) {
                    const quint32 semesterNumber = 1 + ((index.column() - 12) / 4);
                    const quint32 kindOfWork = index.column() % 4;
                    qreal v = 0;
                    switch (kindOfWork) {
                        case 0: v = record->subGroup()->lectionsHours(semesterNumber);
                            break;
                        case 1: v = record->subGroup()->labsHours(semesterNumber);
                            break;
                        case 2: v = record->subGroup()->practicesHours(semesterNumber);
                            break;
                        case 3: v = record->subGroup()->kksHours(semesterNumber);
                            break;
                    }
                    return v;
                }
            }
        }
    }

    if (role == Qt::TextAlignmentRole)
        return Qt::AlignCenter;

    return QVariant();
}

void CurriculumnItemsModel::addGroup(KTU::CurriculumnSection *section)
{
    Q_ASSERT(m_curriculumn || section);
    if (!m_curriculumn || !section)
        return;
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_curriculumn->curriculumn()->addGroup(section);
    endInsertRows();
}

void CurriculumnItemsModel::addSubGroup(KTU::CurriculumnSection *section, KTU::CurriculumnGroup *group)
{
    Q_ASSERT(m_curriculumn || section || group);
    if (!m_curriculumn || !section || !group)
        return;

    QList<KTU::CurriculumnDisciplineGroup *> groups = m_curriculumn->curriculumn()->groups();
    foreach (KTU::CurriculumnDisciplineGroup *g, groups) {
        if (g->curriculumnSection() == section) {
            const int row = m_curriculumn->curriculumn()->indexOf(g);
            QModelIndex parent = this->index(row, 0, QModelIndex());
            if (!parent.isValid())
                return;
            beginInsertRows(parent, rowCount(parent), rowCount(parent));
            g->addSubGroup(group);
            endInsertRows();
            break;
        }
    }
}

void CurriculumnItemsModel::addRecord(KTU::CurriculumnSection *section, KTU::CurriculumnGroup *group, KTU::Discipline *discipline, KTU::Chair *chair)
{
    Q_ASSERT(m_curriculumn || section || group);
    if (!m_curriculumn || !section || !group)
        return;
    QList<KTU::CurriculumnDisciplineGroup *> groups = m_curriculumn->curriculumn()->groups();
    foreach (KTU::CurriculumnDisciplineGroup *g, groups) {
        if (g->curriculumnSection() == section) {
            QList<KTU::CurriculumnDisciplineSubGroup *> subGroups = g->subGroups();
            foreach (KTU::CurriculumnDisciplineSubGroup *sg, subGroups) {
                if (sg->curriculumnGroup() == group) {
                    QModelIndex grandParent = this->index(m_curriculumn->curriculumn()->indexOf(g), 0, QModelIndex());
                    if (!grandParent.isValid())
                        return;
                    QModelIndex parent = this->parent(this->index(g->indexOf(sg), 0, grandParent));
                    if (!parent.isValid())
                        return;
                    beginInsertRows(parent, rowCount(parent), rowCount(parent));
                    KTU::CurriculumnRecord *record = sg->addRecord();
                    record->setDiscipline(discipline);
                    record->setChair(chair);
                    endInsertRows();
                    break;
                }
            }
        }
    }
}

void CurriculumnItemsModel::removeGroup(KTU::CurriculumnDisciplineGroup *g)
{
    Q_ASSERT(m_curriculumn || g);
    if (!m_curriculumn || !g)
        return;
    const int row = m_curriculumn->curriculumn()->indexOf(g);
    beginRemoveRows(QModelIndex(), row, row);
    m_curriculumn->curriculumn()->removeGroup(g);
    endRemoveRows();
}

void CurriculumnItemsModel::removeSubGroup(KTU::CurriculumnDisciplineSubGroup *sg)
{
    Q_ASSERT(m_curriculumn || sg);
    if (!m_curriculumn || !sg)
        return;
    KTU::CurriculumnDisciplineGroup *g = sg->group();
    QModelIndex parent = index(m_curriculumn->curriculumn()->indexOf(g), 0, QModelIndex());
    if (!parent.isValid())
        return;
    const int row = g->indexOf(sg);
    beginRemoveRows(parent, row, row);
    g->removeSubGroup(sg);
    endRemoveRows();
}

void CurriculumnItemsModel::removeRecord(KTU::CurriculumnRecord *r)
{
    Q_ASSERT(m_curriculumn || r);
    if (!m_curriculumn || !r)
        return;
    KTU::CurriculumnDisciplineSubGroup *sg = r->subGroup();
    KTU::CurriculumnDisciplineGroup *g = sg->group();
    QModelIndex grandParent = index(m_curriculumn->curriculumn()->indexOf(g), 0, QModelIndex());
    if (!grandParent.isValid())
        return;
    QModelIndex parent = this->parent(index(g->indexOf(sg), 0, grandParent));
    if (!parent.isValid())
        return;
    const int row = sg->indexOf(r);
    beginRemoveRows(parent, row, row);
    sg->removeRecord(r);
    endRemoveRows();
}
//------------------------------------------
void CurriculumnHeaderDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    m_currentPaintedIndex = index;//workaround: QStyleOptionViewItemV4::index is not set in QItemDelegate::paint
    QItemDelegate::paint(painter, option, index);
}

void CurriculumnHeaderDelegate::drawDisplay(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect, const QString &text) const
{
    if (m_currentPaintedIndex.isValid() && m_currentPaintedIndex.data(CurriculumnHeaderModel::VerticalTextRole).toBool()) {
        const int xOffset = qRound(option.fontMetrics.height() / 2.0);
        const int yOffset = qRound(option.fontMetrics.width(text) / 2.0);
        painter->save();
        painter->translate(rect.topLeft() + QPoint(rect.width() / 2 + xOffset, rect.height() / 2 + yOffset));
        painter->rotate(-90);
        painter->drawText(0, 0, text);
        painter->restore();
        return;
    }

    QItemDelegate::drawDisplay(painter, option, rect, text);
}
//------------------------------------------
CurriculumnHeaderView::CurriculumnHeaderView(KTU::Curriculumn *curriculumn, QWidget *parent)
    : QTableView(parent),
    m_model(new CurriculumnHeaderModel(this))
{
    QTableView::setItemDelegate(new CurriculumnHeaderDelegate());
    QTableView::setModel(m_model);
    connect(m_model, SIGNAL(modelInitialized()), SLOT(initSpans()));

    m_model->setCurriculumn(curriculumn);

    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    verticalHeader()->hide();
}

void CurriculumnHeaderView::setModel(QAbstractItemModel *model)
{
    Q_UNUSED(model);
    qWarning() << Q_FUNC_INFO << "setting new model is not allowed.";
}

void CurriculumnHeaderView::initSpans()
{
    setSpan(0, 0, 7, 1);
    setSpan(0, 1, 1, 4);
    setSpan(1, 1, 6, 1);
    setSpan(1, 2, 6, 1);
    setSpan(1, 3, 1, 2);
    setSpan(2, 3, 5, 1);
    setSpan(2, 4, 5, 1);
    setSpan(0, 5, 1, 7);
    setSpan(1, 5, 6, 1);
    setSpan(1, 6, 6, 1);
    setSpan(1, 7, 1, 4);
    setSpan(2, 7, 5, 1);
    setSpan(2, 8, 1, 3);
    setSpan(3, 8, 4, 1);
    setSpan(3, 9, 4, 1);
    setSpan(3, 10, 4, 1);
    setSpan(1, 11, 6, 1);
    if (m_model->columnCount() > 13) {
        setSpan(0, 12, 1, m_model->columnCount() - 13);

        static int worksCount = 4;
        KTU::Calendar *calendar = m_model->curriculumn()->calendar();

        const quint32 count = calendar->coursesCount();
        for (quint32 i = 0; i < count; ++i) {
            const KTU::CalendarCourse *course = calendar->course(i + 1);
            const int idx = 12 + i * worksCount * course->semestersCount();
            setSpan(1, idx, 1, worksCount * course->semestersCount());
            foreach (const KTU::CalendarSemester *semester, course->semesters()) {
                setSpan(3, 12 + (semester->number() - 1) * worksCount, 1, worksCount);
                setSpan(5, 12 + (semester->number() - 1) * worksCount, 1, worksCount);
            }
        }

        setSpan(2, 12, 1, m_model->columnCount() - 13);
        setSpan(4, 12, 1, m_model->columnCount() - 13);
    }
    setSpan(0, m_model->columnCount() - 1, 7, 1);

    int totalHeight = horizontalHeader()->height() + 1;
    for (int c = 0; c < verticalHeader()->count(); ++c)
        totalHeight += verticalHeader()->sectionSize(c);
    setMaximumHeight(totalHeight);
}
//------------------------------------------
CurriculumnItemsDelegate::CurriculumnItemsDelegate(CurriculumnItemsView *view)
    : QItemDelegate(view),
      m_view(view)
{

}

void CurriculumnItemsDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    m_currentPaintedIndex = index;//workaround: QStyleOptionViewItemV4::index is not set in QItemDelegate::paint
    QItemDelegate::paint(painter, option, index);

    qDrawShadeLine(painter, QPoint(0, option.rect.top()), option.rect.topRight(), option.palette);
    qDrawShadeLine(painter, QPoint(0, option.rect.bottom() + 1), option.rect.bottomRight() + QPoint(0, 1), option.palette);

    KTU::CurriculumnRecord *record = static_cast<KTU::CurriculumnRecord *>(index.internalPointer());
    if (record && (record->className() == QLatin1String("CurriculumnRecord"))) {
//    if (index.internalId() == CurriculumnItemsModel::Record) {
        qDrawShadeLine(painter, QPoint(0, option.rect.top()), option.rect.bottomLeft(), option.palette);
        qDrawShadeLine(painter, option.rect.topRight(), option.rect.bottomRight(), option.palette);
    }
}

void CurriculumnItemsDelegate::drawDisplay(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect, const QString &text) const
{
    QRect r = rect;
    QStyleOptionViewItem o(option);
    if (m_currentPaintedIndex.isValid()) {
        KTU::CurriculumnRecord *record = static_cast<KTU::CurriculumnRecord *>(m_currentPaintedIndex.internalPointer());
        if (!record || record->className() != QLatin1String("CurriculumnRecord")) {
//        if (m_currentPaintedIndex.internalId() != CurriculumnItemsModel::Record) {
            r = m_view->visualRect(m_currentPaintedIndex.sibling(m_currentPaintedIndex.row(), 0));
            r.setWidth(m_view->viewport()->width());
            o.rect = r;
        }
    }

    QItemDelegate::drawDisplay(painter, o, r, text);
}

void CurriculumnItemsDelegate::drawFocus(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect) const
{
    QRect r = rect;
    QStyleOptionViewItem o(option);
    if (m_currentPaintedIndex.isValid()) {
        KTU::CurriculumnRecord *record = static_cast<KTU::CurriculumnRecord *>(m_currentPaintedIndex.internalPointer());
        if (!record || record->className() != QLatin1String("CurriculumnRecord")) {
//        if (m_currentPaintedIndex.internalId() != CurriculumnItemsModel::Record) {
            r = m_view->visualRect(m_currentPaintedIndex.sibling(m_currentPaintedIndex.row(), 0));
            r.setWidth(m_view->viewport()->width());
            o.rect = r;
        }
    }

    QItemDelegate::drawFocus(painter, o, r);
}

QSize CurriculumnItemsDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QSize size = QItemDelegate::sizeHint(option, index);
    size.setHeight(30);
    return size;
}
//------------------------------------------
CurriculumnItemsView::CurriculumnItemsView(CurriculumnHeaderModel *model, QWidget *parent)
    : QTreeView(parent)
{
    m_model = new CurriculumnItemsModel(this);
    m_model->setCurriculumnHeaderModel(model);
    QTreeView::setModel(m_model);
    setAllColumnsShowFocus(true);
    setItemDelegate(new CurriculumnItemsDelegate(this));
    setIndentation(0);
    header()->hide();

    setSelectionBehavior(SelectItems);
    expandAll();
}

void CurriculumnItemsView::setModel(QAbstractItemModel *model)
{
    Q_UNUSED(model);
    qWarning() << Q_FUNC_INFO << "setting new model is not allowed.";
}
//------------------------------------------
CurriculumnWidget::CurriculumnWidget(KTU::Curriculumn *curriculumn, QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    m_headerView = new CurriculumnHeaderView(curriculumn, this);
    m_itemsView = new CurriculumnItemsView(m_headerView->model(), this);
    m_itemsView->setContextMenuPolicy(Qt::CustomContextMenu);

    mainLayout->addWidget(m_headerView);
    mainLayout->addWidget(m_itemsView);
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);

    connect(m_headerView->horizontalHeader(), SIGNAL(sectionResized(int,int,int)), SLOT(resizeItemsSection(int, int, int)));
    connect(m_itemsView->header(), SIGNAL(sectionResized(int,int,int)), SLOT(resizeHeaderSection(int, int, int)));
    connect(m_itemsView->horizontalScrollBar(), SIGNAL(valueChanged(int)), SLOT(scrollBarValueChanged(int)));
    connect(m_itemsView, SIGNAL(customContextMenuRequested(const QPoint &)), SLOT(showContextMenu(const QPoint &)));

    m_selectorDialog = new SelectorDialog(this);
}

void CurriculumnWidget::resizeHeaderSection(int section, int newSize, int)
{
    const bool isBlocked = m_headerView->horizontalHeader()->blockSignals(true);
    m_headerView->horizontalHeader()->resizeSection(section, newSize);
    m_headerView->horizontalHeader()->blockSignals(isBlocked);
    m_headerView->update();
}

void CurriculumnWidget::resizeItemsSection(int section, int newSize, int)
{
    const bool isBlocked = m_itemsView->header()->blockSignals(true);
    m_itemsView->header()->resizeSection(section, newSize);
    m_itemsView->header()->blockSignals(isBlocked);
    m_itemsView->update();
}

void CurriculumnWidget::scrollBarValueChanged(int value)
{
    m_headerView->horizontalScrollBar()->setValue(qRound(value / qRound(m_itemsView->horizontalScrollBar()->maximum() / (double)m_headerView->horizontalScrollBar()->maximum())));
}

void CurriculumnWidget::showContextMenu(const QPoint &point)
{
    QMenu menu(this);

    QModelIndex index = m_itemsView->indexAt(point);
    KTU::CurriculumnDisciplineGroup *group = static_cast<KTU::CurriculumnDisciplineGroup *>(index.internalPointer());
    KTU::CurriculumnDisciplineSubGroup *subGroup = static_cast<KTU::CurriculumnDisciplineSubGroup *>(index.internalPointer());
    KTU::CurriculumnRecord *record = static_cast<KTU::CurriculumnRecord *>(index.internalPointer());
//    m_itemsView->model()->getEntities(index, group, subGroup, record);

    if (!index.isValid()) {
        menu.addAction(tr("Add curriculumn section"), this, SLOT(addCurriculumnSection()));
    } else if (group && group->className() == QLatin1String("CurriculumnDisciplineGroup")) {
        menu.addAction(tr("Add curriculumn group"), this, SLOT(addCurriculumnGroup()));
        QAction *action = menu.addAction(tr("Remove curriculumn section"), this, SLOT(removeCurriculumnSection()));
        action->setProperty("group", qVariantFromValue(group));
    } else if (subGroup && subGroup->className() == QLatin1String("CurriculumnDisciplineSubGroup")) {
        menu.addAction(tr("Add discipline"), this, SLOT(addCurriculumnDiscipline()));
        QAction *action = menu.addAction(tr("Remove curriculumn group"), this, SLOT(removeCurriculumnGroup()));
        action->setProperty("subGgroup", qVariantFromValue(subGroup));
    } else if (record && record->className() == QLatin1String("CurriculumnRecord")) {
        QAction *action = menu.addAction(tr("Remove discipline"), this, SLOT(removeCurriculumnDiscipline()));
        action->setProperty("record", qVariantFromValue(record));
    }

    menu.exec(m_itemsView->mapToGlobal(point));
}

void CurriculumnWidget::addCurriculumnSection()
{
    m_selectorDialog->setWindowTitle(tr("Add curriculumn section"));
    if (!m_selectorDialog->exec(SelectorDialog::Section))
        return;

    KTU::CurriculumnSection *section = constantsFactory->curriculumnSection(m_selectorDialog->sectionId());
    if (!section)
        return;
    KTU::CurriculumnDisciplineGroup *group = m_itemsView->model()->curriculumnModel()->curriculumn()->group(section);
    if (group) {
        QMessageBox::information(this, tr("Information"), tr("The group<br><span style=\"color:red\">'%1'</span> already has been created.").arg(section->name()));
        return;
    }

    m_itemsView->model()->addGroup(section);
    m_itemsView->expandAll();
}

void CurriculumnWidget::addCurriculumnGroup()
{
    m_selectorDialog->setWindowTitle(tr("Add curriculumn group"));
    if (!m_selectorDialog->exec(SelectorDialog::Group))
        return;

    KTU::CurriculumnSection *section = constantsFactory->curriculumnSection(m_selectorDialog->sectionId());
    KTU::CurriculumnGroup *group = constantsFactory->curriculumnGroup(m_selectorDialog->groupId());
    if (!section || !group)
        return;

    KTU::CurriculumnDisciplineGroup *g = m_itemsView->model()->curriculumnModel()->curriculumn()->group(section);
    if (!g)
        return;
    KTU::CurriculumnDisciplineSubGroup *sg = g->subGroup(group);
    if (sg) {
        QMessageBox::information(this, tr("Information"), tr("The sub group<br><span style=\"color:red\">'%1'</span> already has been created.").arg(group->name()));
        return;
    }

    m_itemsView->model()->addSubGroup(section, group);
    m_itemsView->expandAll();
}

void CurriculumnWidget::addCurriculumnDiscipline()
{
    m_selectorDialog->setWindowTitle(tr("Add discipline"));
    if (!m_selectorDialog->exec(SelectorDialog::Discipline))
        return;

    KTU::CurriculumnSection *section = constantsFactory->curriculumnSection(m_selectorDialog->sectionId());
    KTU::CurriculumnGroup *group = constantsFactory->curriculumnGroup(m_selectorDialog->groupId());
    KTU::Discipline *discipline = constantsFactory->discipline(m_selectorDialog->disciplineId());
    KTU::Chair *chair = constantsFactory->chair(m_selectorDialog->chairId());
    if (!section || !group || !discipline || !chair)
        return;

    m_itemsView->model()->addRecord(section, group, discipline, chair);
    m_itemsView->expandAll();
}

void CurriculumnWidget::removeCurriculumnSection()
{
    QAction *action = qobject_cast<QAction *>(sender());
    if (!action)
        return;
    KTU::CurriculumnDisciplineGroup *group = qvariant_cast<KTU::CurriculumnDisciplineGroup *>(action->property("group"));
    if (!group)
        return;
    const int ret = QMessageBox::question(this, tr("Remove curriculumn section"),
                                          tr("Are you sure you want to delete<br><span style=\"color:red\">'%1'</span>?").arg(group->curriculumnSection()->name()),
                                          QMessageBox::Yes | QMessageBox::No);
    if (ret == QMessageBox::No)
        return;
    m_itemsView->model()->removeGroup(group);
}

void CurriculumnWidget::removeCurriculumnGroup()
{
    QAction *action = qobject_cast<QAction *>(sender());
    if (!action)
        return;
    KTU::CurriculumnDisciplineSubGroup *subGroup = qvariant_cast<KTU::CurriculumnDisciplineSubGroup *>(action->property("subGgroup"));
    if (!subGroup)
        return;
    const int ret = QMessageBox::question(this, tr("Remove curriculumn group"),
                                          tr("Are you sure you want to delete<br><span style=\"color:red\">'%1'</span>?").arg(subGroup->curriculumnGroup()->name()),
                                          QMessageBox::Yes | QMessageBox::No);
    if (ret == QMessageBox::No)
        return;
    m_itemsView->model()->removeSubGroup(subGroup);
}

void CurriculumnWidget::removeCurriculumnDiscipline()
{
    QAction *action = qobject_cast<QAction *>(sender());
    if (!action)
        return;
    KTU::CurriculumnRecord *record = qvariant_cast<KTU::CurriculumnRecord *>(action->property("record"));
    if (!record)
        return;
    const int ret = QMessageBox::question(this, tr("Remove discipline"),
                                          tr("Are you sure you want to delete<br><span style=\"color:red\">'%1'</span>?").arg(record->discipline()->name()),
                                          QMessageBox::Yes | QMessageBox::No);
    if (ret == QMessageBox::No)
        return;
    m_itemsView->model()->removeRecord(record);
}
//------------------------------------------
SelectorDialog::SelectorDialog(QWidget *parent)
    : QDialog(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    m_formLayout = new QFormLayout();
    m_formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);

    m_cbSections = new QComboBox(this);
    m_cbGroups = new QComboBox(this);
    m_cbDisciplines = new QComboBox(this);
    m_cbChairs = new QComboBox(this);

    m_formLayout->addRow(tr("Section: "), m_cbSections);
    m_formLayout->addRow(tr("Group: "), m_cbGroups);
    m_formLayout->addRow(tr("Discipline: "), m_cbDisciplines);
    m_formLayout->addRow(tr("Chair: "), m_cbChairs);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(this);
    buttonBox->addButton(QDialogButtonBox::Yes);
    buttonBox->addButton(QDialogButtonBox::No);

    mainLayout->addLayout(m_formLayout);
    mainLayout->addStretch(1);
    mainLayout->addWidget(buttonBox);

    connect(buttonBox, SIGNAL(accepted()), SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), SLOT(reject()));

    init();
}

void SelectorDialog::init()
{
    QList<KTU::CurriculumnSection *> sections = constantsFactory->curriculumnSections();
    foreach (KTU::CurriculumnSection *section, sections)
        m_cbSections->addItem(section->name(), section->id());

    QList<KTU::CurriculumnGroup *> groups = constantsFactory->curriculumnGroups();
    foreach (KTU::CurriculumnGroup *group, groups)
        m_cbGroups->addItem(group->name(), group->id());

    QList<KTU::Discipline *> disciplines = constantsFactory->disciplines();
    foreach (KTU::Discipline *discipline, disciplines)
        m_cbDisciplines->addItem(discipline->name(), discipline->id());

    QList<KTU::Chair *> chairs = constantsFactory->chairs();
    foreach (KTU::Chair *chair, chairs)
        m_cbChairs->addItem(chair->name(), chair->id());
}

int SelectorDialog::exec(EntityType type)
{
    m_cbGroups->setVisible(type == Group || type == Discipline);
    m_formLayout->labelForField(m_cbGroups)->setVisible(type == Group || type == Discipline);
    m_cbDisciplines->setVisible(type == Discipline);
    m_formLayout->labelForField(m_cbDisciplines)->setVisible(type == Discipline);
    m_cbChairs->setVisible(type == Discipline);
    m_formLayout->labelForField(m_cbChairs)->setVisible(type == Discipline);
    return QDialog::exec();
}

quint32 SelectorDialog::sectionId() const
{
    return m_cbSections->itemData(m_cbSections->currentIndex()).toUInt();
}

quint32 SelectorDialog::groupId() const
{
    return m_cbGroups->itemData(m_cbGroups->currentIndex()).toUInt();
}

quint32 SelectorDialog::disciplineId() const
{
    return m_cbDisciplines->itemData(m_cbDisciplines->currentIndex()).toUInt();
}

quint32 SelectorDialog::chairId() const
{
    return m_cbChairs->itemData(m_cbChairs->currentIndex()).toUInt();
}
