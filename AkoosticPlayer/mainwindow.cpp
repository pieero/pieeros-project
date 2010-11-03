#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QCoreApplication::setApplicationName("AkoosticPlayer");
    ui->setupUi(this);
    setAcceptDrops(true);
    m_pBoardSelector = new BoardSelector(ui->centralWidget);
    ui->centralWidget->layout()->addWidget(m_pBoardSelector);

    this->connect(ui->AddTabButton,SIGNAL(released()),m_pBoardSelector,SLOT(addBoard()));

}

MainWindow::~MainWindow()
{
    delete ui;
}
