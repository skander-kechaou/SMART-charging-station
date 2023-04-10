#ifndef MAILDIALOG_H
#define MAILDIALOG_H

#include <QDialog>

namespace Ui {
class mailDialog;
}

class mailDialog : public QDialog
{
    Q_OBJECT

public:
    explicit mailDialog(QWidget *parent = nullptr);
    ~mailDialog();

private:
    Ui::mailDialog *ui;
};

#endif // MAILDIALOG_H
