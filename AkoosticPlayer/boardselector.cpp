#include "boardselector.h"
#include "ui_boardselector.h"
#include "soundboard.h"

BoardSelector::BoardSelector(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BoardSelector)
{
    ui->setupUi(this);
    this->connect(ui->tabWidget,SIGNAL(tabCloseRequested(int)),this,SLOT(closeBoard(int)));
}

BoardSelector::~BoardSelector()
{
    delete ui;
}

void BoardSelector::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void BoardSelector::addBoard(QString p_name)
{
    SoundBoard* sb = new SoundBoard(ui->tabWidget);
    m_vpSoundBoards.push_back(sb);
    int index;
    index = ui->tabWidget->addTab(sb,p_name);

}

void BoardSelector::closeBoard(int p_index)
{
    ui->tabWidget->removeTab(p_index);
    std::vector<SoundBoard*>::iterator it = m_vpSoundBoards.begin();
    it += p_index;
    if(it < m_vpSoundBoards.end())
    {
        delete (*(it));
        m_vpSoundBoards.erase(it);
    }
}

std::ostream& BoardSelector::operator >>(std::ostream& p_rhs)
{
    p_rhs << m_vpSoundBoards.size() << std::endl;
    for(unsigned int i=0;i<m_vpSoundBoards.size();i++)
    {
        p_rhs << ui->tabWidget->tabText(i).toStdString() << std::endl;
        *(m_vpSoundBoards[i]) >> p_rhs;
    }
    return p_rhs;

}

std::istream& BoardSelector::operator <<(std::istream& p_rhs)
{
    while(m_vpSoundBoards.size() != 0)
    {
        delete (*(m_vpSoundBoards.begin()));
        m_vpSoundBoards.erase(m_vpSoundBoards.begin());
    }

    unsigned int nbBoard;
    p_rhs >> nbBoard;
    for(unsigned int i=0;i<nbBoard;i++)
    {
        std::string name;
        p_rhs >> name;
        addBoard(QString(name.c_str()));
        *(m_vpSoundBoards[m_vpSoundBoards.size()-1]) << p_rhs;
    }
    return p_rhs;

}
