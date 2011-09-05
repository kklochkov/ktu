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


#ifndef CURRICULUMNDIALOG_H
#define CURRICULUMNDIALOG_H

#include <QDialog>

namespace Ui {
    class CurriculumnDialog;
}

class CurriculumnDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CurriculumnDialog(QWidget *parent = 0);
    ~CurriculumnDialog();

private slots:
    void updateGraduationYear();

private:
    Ui::CurriculumnDialog *m_ui;
};

#endif // CURRICULUMNDIALOG_H
