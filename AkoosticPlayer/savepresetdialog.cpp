#include "savepresetdialog.h"
#include "ui_savepresetdialog.h"
#include <QPushButton>

SavePresetDialog::SavePresetDialog(QWidget *parent, QStringList p_existingPresets) :
    QDialog(parent),
    ui(new Ui::SavePresetDialog),
    m_existingPresets(p_existingPresets)
{
    ui->setupUi(this);
    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(validatePresetName()));
    connect(ui->lineEdit,SIGNAL(textChanged(QString)),SLOT(textChange(QString)));
    QPushButton* pSaveButton = ui->buttonBox->button(QDialogButtonBox::Save);
    if(pSaveButton != 0)
    {
        pSaveButton->setEnabled(false);
    }
    connect(ui->overwriteExistingCB,SIGNAL(toggled(bool)),this,SLOT(checkOverwrite(bool)));
}

SavePresetDialog::~SavePresetDialog()
{
    delete ui;
}

void SavePresetDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void SavePresetDialog::validatePresetName()
{
    emit savePresetAs(ui->lineEdit->text());
}

void SavePresetDialog::textChange(QString p_string)
{
    ui->overwriteExistingCB->setEnabled(m_existingPresets.contains(p_string));
    ui->overwriteExistingCB->setChecked(false);
    QPushButton* pSaveButton = ui->buttonBox->button(QDialogButtonBox::Save);
    if(pSaveButton != 0)
    {
        pSaveButton->setEnabled(p_string.length() > 0 && ( !ui->overwriteExistingCB->isEnabled() || ui->overwriteExistingCB->isChecked()));
    }

}

void SavePresetDialog::checkOverwrite(bool p_checked)
{
    QPushButton* pSaveButton = ui->buttonBox->button(QDialogButtonBox::Save);
    if(pSaveButton != 0)
    {
        pSaveButton->setEnabled(p_checked);
    }
}
