#ifndef BOARDSELECTOR_H
#define BOARDSELECTOR_H

#include <QWidget>
#include "soundboard.h"
#include <vector>
#include <iostream>

namespace Ui {
    class BoardSelector;
}

class BoardSelector : public QWidget {
    Q_OBJECT
public:
    BoardSelector(QWidget *parent = 0);
    ~BoardSelector();
    std::ostream& operator >>(std::ostream& p_rhs);
    std::istream& operator <<(std::istream& p_rhs);

public slots:
    void addBoard(QString p_name="vide");
    void closeBoard(int p_index);


protected:
    void changeEvent(QEvent *e);

private:
    Ui::BoardSelector *ui;
    std::vector<SoundBoard*> m_vpSoundBoards;
};

#endif // BOARDSELECTOR_H
