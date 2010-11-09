#ifndef SAVEPRESETDIALOG_H
#define SAVEPRESETDIALOG_H

#include <QDialog>

namespace Ui {
    class SavePresetDialog;
}

class SavePresetDialog : public QDialog {
    Q_OBJECT
public:
    SavePresetDialog(QWidget *parent = 0, QStringList p_existingPresets = QStringList());
    ~SavePresetDialog();

signals:
    void savePresetAs(QString);

protected slots:
    void validatePresetName();
    void textChange(QString);
    void checkOverwrite(bool);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::SavePresetDialog *ui;
    QStringList m_existingPresets;

};

#endif // SAVEPRESETDIALOG_H
