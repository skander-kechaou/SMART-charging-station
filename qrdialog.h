#ifndef QRDIALOG_H
#define QRDIALOG_H

#include <QDialog>

namespace Ui {
class qrDialog;
}

class qrDialog : public QDialog
{
    Q_OBJECT

public:
    explicit qrDialog(QWidget *parent = nullptr);
    ~qrDialog();

private:
    Ui::qrDialog *ui;
};

#endif // QRDIALOG_H
