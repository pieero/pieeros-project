#include "newsoundboarddialog.h"
#include "ui_newsoundboarddialog.h"

NewSoundBoardDialog::NewSoundBoardDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewSoundBoardDialog)
{
    ui->setupUi(this);
    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(validateSoundBoardName()));
    //connect(ui->buttonBox,SIGNAL(rejected()),this,SLOT(close()));
}

NewSoundBoardDialog::~NewSoundBoardDialog()
{
    delete ui;
}

void NewSoundBoardDialog::changeEvent(QEvent *e)
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

void NewSoundBoardDialog::validateSoundBoardName()
{
    emit addSoundBoardAs(ui->lineEdit->text());
}
