#include "soundbutton.h"
#include "ui_soundbutton.h"

SoundButton::SoundButton(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SoundButton)
{
    ui->setupUi(this);
    m_pmediaobject = new Phonon::MediaObject(this);
    this->connect(this->m_pmediaobject,SIGNAL(finished()),this,SLOT(uncheckButton()));
    ui->button->setAcceptDrops(true);
}

SoundButton::~SoundButton()
{
    delete ui;
    delete m_pmediaobject;
}

void SoundButton::dropEvent(QDropEvent *event)
    {
        QString url = event->mimeData()->text();
        //mimeTypeCombo->clear();
        //mimeTypeCombo->addItems(event->mimeData()->formats());

        event->acceptProposedAction();
    }

void SoundButton::toggleSound()
{
    if(ui->button->isChecked())
    {
        m_pmediaobject->play();
    }
    else
    {
        m_pmediaobject->stop();
    }
}

void SoundButton::uncheckButton()
{
    ui->button->setChecked(false);
}


void SoundButton::setSource(QString p_path)
{
    m_pmediaobject->stop();
    m_pmediaobject->clear();
    m_source = Phonon::MediaSource(p_path);
    m_pmediaobject->setCurrentSource(m_source);
}
