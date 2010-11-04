#ifndef SAVEPRESETDIALOG_H
#define SAVEPRESETDIALOG_H

#include <QDialog>

namespace Ui {
    class SavePresetDialog;
}

class SavePresetDialog : public QDialog {
    Q_OBJECT
public:
    SavePresetDialog(QWidget *parent = 0);
    ~SavePresetDialog();

signals:
    void savePresetAs(QString);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::SavePresetDialog *ui;
};

#endif // SAVEPRESETDIALOG_H
