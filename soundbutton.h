#ifndef SOUNDBUTTON_H
#define SOUNDBUTTON_H

#include <QWidget>
#include <phonon/MediaSource>
#include <phonon/MediaObject>

namespace Ui {
    class SoundButton;
}

class SoundButton : public QWidget
{
    Q_OBJECT

public:
    explicit SoundButton(QWidget *parent = 0);
    ~SoundButton();

public slots:
    void setSource(QString p_path);

protected slots:
    void toggleSound();
    void uncheckButton();

private:
    Ui::SoundButton *ui;
    Phonon::MediaSource m_source;
    Phonon::MediaObject* m_pmediaobject;
};

#endif // SOUNDBUTTON_H
