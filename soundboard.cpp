#include "soundboard.h"
#include "ui_soundboard.h"

SoundBoard::SoundBoard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SoundBoard)
{
    ui->setupUi(this);
    m_soundButtonList.push_back(SoundButton(ui->MainBoard));;
}

SoundBoard::~SoundBoard()
{
    delete ui;
}

void SoundBoard::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
