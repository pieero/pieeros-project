#include "soundbutton.h"
#include "ui_soundbutton.h"
#include <QFileInfo>
#include <QUrl>

SoundButton::SoundButton(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SoundButton)
{
    ui->setupUi(this);
    m_pmediaobject = new Phonon::MediaObject(this);
    this->connect(this->m_pmediaobject,SIGNAL(finished()),this,SLOT(uncheckButton()));
    this->connect(ui->button,SIGNAL(clicked()),this,SLOT(toggleSound()));
    this->setAcceptDrops(true);
}

SoundButton::~SoundButton()
{
    delete ui;
    delete m_pmediaobject;
}

void SoundButton::dragEnterEvent(QDragEnterEvent *event)
{
    //if (event->mimeData()->hasFormat("text/plain"))
    //ui->button->setText(QString(event->mimeData()->text()));
        event->acceptProposedAction();
}

void SoundButton::dropEvent(QDropEvent *event)
{
    QString path = QUrl::fromLocalFile(event->mimeData()->text()).toString();
    QString name = QFileInfo(path).baseName();
    ui->button->setText(name);
    setSource(path);
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
    ui->button->setEnabled(true);
}
