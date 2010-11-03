#ifndef SOUNDBUTTON_H
#define SOUNDBUTTON_H

#include <QWidget>
#include <QDropEvent>
#include <phonon/MediaSource>
#include <phonon/MediaObject>
#include <phonon/AudioOutput>

namespace Ui {
    class SoundButton;
}

class SoundButton : public QWidget
{
    Q_OBJECT

public:
    explicit SoundButton(QWidget *parent = 0);
    ~SoundButton();
    void dropEvent(QDropEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);


public slots:
    void setSource(QString p_path);

protected slots:
    void toggleSound();
    void uncheckButton();

private:
    Ui::SoundButton *ui;
    QString m_path;
    Phonon::MediaSource m_source;
    Phonon::MediaObject* m_pmediaobject;
    Phonon::AudioOutput* m_paudioOutput;
};

#endif // SOUNDBUTTON_H
