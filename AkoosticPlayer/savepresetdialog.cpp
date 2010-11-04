#include "savepresetdialog.h"
#include "ui_savepresetdialog.h"

SavePresetDialog::SavePresetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SavePresetDialog)
{
    ui->setupUi(this);
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
