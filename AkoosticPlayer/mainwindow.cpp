#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include "newsoundboarddialog.h"
#include "savepresetdialog.h"
#include <QDir>

//! \brief qss file loading for ihm appearance
//! \param qss file path
void loadStyleSheet(const char* p_stylename) {
    /* Let's use QFile and point to a resource... */
    QFile data(p_stylename);
    QString style;
    /* ...to open the file */
    if(data.open(QFile::ReadOnly)) {
        /* QTextStream... */
        QTextStream styleIn(&data);
        /* ...read file to a string. */
        style = styleIn.readAll();
        data.close();
        /* We'll use qApp macro to get the QApplication pointer
         * and set the style sheet application wide. */
        qApp->setStyleSheet(style);
    }
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QCoreApplication::setApplicationName("AkoosticPlayer");
    ui->setupUi(this);
    setAcceptDrops(true);
    m_pBoardSelector = new BoardSelector(ui->centralWidget);
    ui->centralWidget->layout()->addWidget(m_pBoardSelector);

    this->connect(ui->AddTabButton,SIGNAL(released()),this,SLOT(addSoundBoard()));
    this->connect(ui->savePresetButton,SIGNAL(released()),this,SLOT(savePreset()));

    loadStyleSheet(":/style/style.css");

    loadPresetList();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::savePreset()
{
    SavePresetDialog presetDialog(this);
    connect(&presetDialog,SIGNAL(savePresetAs(QString)),this,SLOT(savePresetAs(QString)));
    presetDialog.setModal(true);
    presetDialog.exec();
}

void MainWindow::savePresetAs(QString p_presetName)
{
    QFile presetFile;
    presetFile.setFileName(m_presetFolder.absoluteFilePath(p_presetName));
    presetFile.open(QFile::WriteOnly);
    presetFile.write("");
    presetFile.close();
}

void MainWindow::loadPreset(QString p_presetName)
{

}

void MainWindow::addSoundBoard()
{
    NewSoundBoardDialog newSoundBoardDialog(this);
    connect(&newSoundBoardDialog,SIGNAL(addSoundBoardAs(QString)),this,SLOT(addSoundBoardAs(QString)));
    newSoundBoardDialog.setModal(true);
    newSoundBoardDialog.exec();

}

void  MainWindow::addSoundBoardAs(QString p_name)
{
    m_pBoardSelector->addBoard(p_name);
}

void MainWindow::loadPresetList()
{
    char * pPath;
    QDir m_presetFolder,HomeFolder;
    bool ret = false;
    do{
      pPath = getenv ("HOME");
      if (pPath!=NULL) // Home is for Linux
      {
           HomeFolder.setPath(QString(pPath));
           m_presetFolder.setPath(HomeFolder.absolutePath() + ".AkoosticPlayer/presets");
           if(!m_presetFolder.exists())
           {
               ret = HomeFolder.mkdir(".AkoosticPlayer");
               QDir tmp = HomeFolder;
               ret = tmp.cd(".AkoosticPlayer");
               ret = tmp.mkdir("presets");
           }
           break;
      }
      pPath = getenv ("APPDATA");
      if (pPath!=NULL) // Home is for Linux
      {
          HomeFolder.setPath(QString(pPath));
          m_presetFolder.setPath(HomeFolder.absolutePath() + "AkoosticPlayer/presets");
          if(!m_presetFolder.exists())
          {
              ret = HomeFolder.mkdir("AkoosticPlayer");
              QDir tmp = HomeFolder;
              ret = tmp.cd(".AkoosticPlayer");
              ret = tmp.mkdir("presets");
          }
          break;
      }
  }while(false);




  QStringList fileList = m_presetFolder.entryList();

  ui->Presets->clear();
  for(QStringList::iterator it = fileList.begin(); it < fileList.end(); it++)
  {
    ui->Presets->addItem(*it);
  }

}
