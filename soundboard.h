#ifndef SOUNDBOARD_H
#define SOUNDBOARD_H

#include <QWidget>
#include "soundbutton.h"

namespace Ui {
    class SoundBoard;
}

class SoundBoard : public QWidget {
    Q_OBJECT
public:
    SoundBoard(QWidget *parent = 0);
    ~SoundBoard();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::SoundBoard *ui;
    QList<SoundButton> m_soundButtonList;
};

#endif // SOUNDBOARD_H
