#include "soundboard.h"
#include "ui_soundboard.h"
#include <QGridLayout>

SoundBoard::SoundBoard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SoundBoard)
{
    ui->setupUi(this);
    QVector< SoundButton* > firstrow;
    firstrow.push_back(new SoundButton(ui->MainBoard));
    m_vect2dSoundButton.push_back(firstrow);

    m_pGridLayout = new QGridLayout(ui->MainBoard);
    m_pGridLayout->setMargin(0);
    m_pGridLayout->setMargin(0);
    m_pGridLayout->setHorizontalSpacing(0);
    m_pGridLayout->setVerticalSpacing(0);

    ui->MainBoard->setLayout(m_pGridLayout);

    m_pGridLayout->addWidget(m_vect2dSoundButton[0][0],0,0);

    this->connect(ui->AddRowButton,SIGNAL(released()),this,SLOT(addRow()));
    this->connect(ui->RemoveRawButton,SIGNAL(released()),this,SLOT(removeRow()));
    this->connect(ui->AddColumnButton,SIGNAL(released()),this,SLOT(addColumn()));
    this->connect(ui->RemoveColumnButton,SIGNAL(released()),this,SLOT(removeColumn()));

    ui->RemoveColumnButton->setEnabled(false);
    ui->RemoveRawButton->setEnabled(false);

}

SoundBoard::~SoundBoard()
{
    delete m_pGridLayout;
    delete ui;
}

void SoundBoard::changeEvent(QEvent *e)
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

void SoundBoard::addRow()
{
    if(m_vect2dSoundButton.size() < AKOOSTIC_MAX_ROW)
    {
        QVector< SoundButton* > lastrow;
        for(int i=0;i<m_vect2dSoundButton[0].size();i++)
        {
            SoundButton* tmp = new SoundButton(ui->MainBoard);
            lastrow.push_back(tmp);
            m_pGridLayout->addWidget(tmp,m_vect2dSoundButton.size(),i);;

        }
        m_vect2dSoundButton.push_back(lastrow);
        if(m_vect2dSoundButton.size() >= AKOOSTIC_MAX_ROW)
        {
            ui->AddRowButton->setEnabled(false);
        }
        ui->RemoveRawButton->setEnabled(true);
    }
}

void SoundBoard::addColumn()
{
    if(m_vect2dSoundButton[0].size() < AKOOSTIC_MAX_COL)
    {
        int nbCol = m_vect2dSoundButton[0].size();
        for(int i=0;i<m_vect2dSoundButton.size();i++)
        {
            SoundButton* tmp = new SoundButton(ui->MainBoard);
            m_vect2dSoundButton[i].push_back(tmp);
            m_pGridLayout->addWidget(tmp,i,nbCol);;

        }
        if(m_vect2dSoundButton[0].size() >= AKOOSTIC_MAX_COL)
        {
            ui->AddColumnButton->setEnabled(false);
        }
        ui->RemoveColumnButton->setEnabled(true);
    }
}

void SoundBoard::removeRow()
{
    if(m_vect2dSoundButton.size() > 1)
    {
        QVector< SoundButton* >& lastrow = m_vect2dSoundButton[m_vect2dSoundButton.size()-1];
        while(lastrow.size() > 0)
        {
            SoundButton* tmp = *(lastrow.begin());
            delete tmp;
            lastrow.pop_front();
        }
        m_vect2dSoundButton.pop_back();
        if(m_vect2dSoundButton.size() <= 1)
        {
            ui->RemoveRawButton->setEnabled(false);
        }
        ui->AddRowButton->setEnabled(true);
    }

}

void SoundBoard::removeColumn()
{
    if(m_vect2dSoundButton[0].size() > 1)
    {

        for(int i=0;i<m_vect2dSoundButton.size();i++)
        {
            SoundButton* tmp = *(m_vect2dSoundButton[i].end()-1);
            delete tmp;
            m_vect2dSoundButton[i].pop_back();
        }
        if(m_vect2dSoundButton.size() <= 1)
        {
            ui->RemoveColumnButton->setEnabled(false);
        }
        ui->AddColumnButton->setEnabled(true);
    }
}

std::ostream& SoundBoard::operator >>(std::ostream& p_rhs)
{
    p_rhs << m_vect2dSoundButton.size() << " ";
    p_rhs << m_vect2dSoundButton[0].size() << std::endl;

    for(int i=0;i<m_vect2dSoundButton.size();i++)
    {
        for(int j=0;j<m_vect2dSoundButton[i].size();j++)
        {
            *(m_vect2dSoundButton[i][j]) >> p_rhs;
            p_rhs << " ";
        }
        p_rhs << std::endl;
    }
    return p_rhs;

}

std::istream& SoundBoard::operator <<(std::istream& p_rhs)
{
    int col,row;
    p_rhs >> col;
    p_rhs >> row;
    for(int icol=1;icol<col;icol++)
    {
        addColumn();
    }
    for(int irow=1;irow<row;irow++)
    {
        addRow();
    }
    for(int i=0;i<m_vect2dSoundButton.size();i++)
    {
        for(int j=0;j<m_vect2dSoundButton[i].size();j++)
        {
            *(m_vect2dSoundButton[i][j]) << p_rhs;
        }
    }
    return p_rhs;
}
