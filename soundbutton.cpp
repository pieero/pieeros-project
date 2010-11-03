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
    m_paudioOutput = new Phonon::AudioOutput(Phonon::MusicCategory, this);
    Phonon::createPath(m_pmediaobject,m_paudioOutput);

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
    QString mimetext = event->mimeData()->text();
    mimetext.replace("\r\n","");
    std::string memstr = mimetext.toStdString();
    QString path = QUrl(mimetext).toLocalFile();
    std::string pathstr = path.toStdString();
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
    m_path = p_path;
    m_pmediaobject->stop();
    m_pmediaobject->clearQueue();
    m_source = Phonon::MediaSource(m_path);
    m_pmediaobject->setCurrentSource(m_source);
    ui->button->setEnabled(true);
}
