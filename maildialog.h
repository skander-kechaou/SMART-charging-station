#ifndef MAILDIALOG_H
#define MAILDIALOG_H

#include <QDialog>
#include "client.h"

namespace Ui {
class mailDialog;
}

class mailDialog : public QDialog
{
    Q_OBJECT

public:
    explicit mailDialog(QWidget *parent = nullptr);
    void setClient(client c);
    ~mailDialog();

private slots:
    void on_sendButton_clicked();

private:
    Ui::mailDialog *ui;
};

#endif // MAILDIALOG_H
