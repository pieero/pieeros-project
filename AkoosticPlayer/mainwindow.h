#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "boardselector.h"


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void savePresetAs(QString p_presetName);
    void addSoundBoardAs(QString);

protected slots:
    void savePreset();
    void loadPreset(QString p_presetName);
    void addSoundBoard();

private:
    Ui::MainWindow *ui;
    BoardSelector* m_pBoardSelector;
};

#endif // MAINWINDOW_H
