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

#include <QDebug>

#include "curriculumndialog.h"
#include "ui_curriculumndialog.h"

CurriculumnDialog::CurriculumnDialog(QWidget *parent)
    : QDialog(parent),
    m_ui(new Ui::CurriculumnDialog)
{
    m_ui->setupUi(this);

//    connect(m_ui->sbTakingOnYear, SIGNAL(valueChanged(int)), SLOT(updateGraduationYear()));
//    connect(m_ui->cbEducationTerm, SIGNAL(currentIndexChanged(int)), SLOT(updateGraduationYear()));

    updateGraduationYear();
}

CurriculumnDialog::~CurriculumnDialog()
{
    delete m_ui;
}

void CurriculumnDialog::updateGraduationYear()
{
//    const int value = m_ui->sbTakingOnYear->value() + m_ui->cbEducationTerm->currentText().toInt();
//    m_ui->sbGraduationYear->setValue(value);
}
