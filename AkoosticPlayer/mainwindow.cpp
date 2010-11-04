#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include "newsoundboarddialog.h"
#include "savepresetdialog.h"

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
