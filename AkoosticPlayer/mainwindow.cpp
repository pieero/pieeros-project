#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>

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

    this->connect(ui->AddTabButton,SIGNAL(released()),m_pBoardSelector,SLOT(addBoard()));

    loadStyleSheet(":/style/style.css");


}

MainWindow::~MainWindow()
{
    delete ui;
}
