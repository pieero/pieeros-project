#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setAcceptDrops(true);
    m_pSoundButton = new SoundButton(ui->centralWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}
