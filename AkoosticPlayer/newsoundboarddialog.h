#ifndef NEWSOUNDBOARDDIALOG_H
#define NEWSOUNDBOARDDIALOG_H

#include <QDialog>

namespace Ui {
    class NewSoundBoardDialog;
}

class NewSoundBoardDialog : public QDialog {
    Q_OBJECT
public:
    NewSoundBoardDialog(QWidget *parent = 0);
    ~NewSoundBoardDialog();

signals:
    void addSoundBoardAs(QString);

protected slots:
    void validateSoundBoardName();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::NewSoundBoardDialog *ui;
};

#endif // NEWSOUNDBOARDDIALOG_H
