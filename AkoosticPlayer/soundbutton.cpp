#include "soundbutton.h"
#include "ui_soundbutton.h"
#include <QFileInfo>
#include <QUrl>
#include <QTextCodec>

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
    QString mimetext;
    const QMimeData* mimeData = event->mimeData();
    if (mimeData->hasImage()) {
             //setPixmap(qvariant_cast<QPixmap>(mimeData->imageData()));
        mimetext = "Image";
         } else if (mimeData->hasHtml()) {
            mimetext = mimeData->html();
            // setTextFormat(Qt::RichText);
         } else if (mimeData->hasText()) {
           mimetext = mimeData->text();
          //   setTextFormat(Qt::PlainText);
         } else if (mimeData->hasUrls()) {
             QList<QUrl> urlList = mimeData->urls();
             QString text;
             for (int i = 0; i < urlList.size() && i < 32; ++i) {
                 QString url = urlList.at(i).path();
                 mimetext = url;
                 break;
                 text += url + QString("\n");
             }
            // setText(text);
         } else {
             mimetext = "NULL";
            // setText(tr("Cannot display data"));
         }


    mimetext.replace("\r\n","");

    QByteArray block(mimetext.toAscii());

    std::string memstr = mimetext.toStdString();

    QString irl = QUrl::fromPercentEncoding(block);
    std::string irlstr = irl.toStdString();
    QString path = QUrl(irl).toLocalFile();
    std::string pathstr = path.toStdString();
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
    QString name = QFileInfo(p_path).baseName();
    ui->button->setText(name);
}

void SoundButton::resetSource()
{
    m_path = "";
    m_pmediaobject->stop();
    m_pmediaobject->clearQueue();
    ui->button->setEnabled(false);
    ui->button->setText("No Sound");
}

std::ostream& SoundButton::operator >>(std::ostream& p_rhs)
{
    QString tmp = m_path;
    if(tmp.size() == 0)
    {
        tmp = "NULL";
    }
    tmp.replace(" ","&nbsp;");
    p_rhs << tmp.toStdString();
    return p_rhs;

}

std::istream& SoundButton::operator <<(std::istream& p_rhs)
{
    std::string tmpstr;
    p_rhs >> tmpstr;
    QString tmp(tmpstr.c_str());
    tmp.replace("&nbsp;"," ");
    if(tmp.compare("NULL") != 0)
    {
        setSource(tmp);
    }
    return p_rhs;
}
