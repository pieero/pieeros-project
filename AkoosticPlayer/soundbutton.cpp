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
