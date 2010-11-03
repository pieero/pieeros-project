#ifndef SOUNDBOARD_H
#define SOUNDBOARD_H

#include <QWidget>
#include "soundbutton.h"
#include <QVector2D>
#include <QGridLayout>
#include <iostream>

#define AKOOSTIC_MAX_ROW 10
#define AKOOSTIC_MAX_COL 10

namespace Ui {
    class SoundBoard;
}

class SoundBoard : public QWidget {
    Q_OBJECT
public:
    SoundBoard(QWidget *parent = 0);
    ~SoundBoard();
    std::ostream& operator >>(std::ostream& p_rhs);
    std::istream& operator <<(std::istream& p_rhs);


protected:
    void changeEvent(QEvent *e);

protected slots:
    void addRow();
    void addColumn();
    void removeRow();
    void removeColumn();

private:
    Ui::SoundBoard *ui;
    QVector< QVector<SoundButton*> > m_vect2dSoundButton;
    QGridLayout* m_pGridLayout;
};

#endif // SOUNDBOARD_H
