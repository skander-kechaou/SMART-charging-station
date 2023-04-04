#ifndef SIGN_UP_H
#define SIGN_UP_H

#include <QWidget>

namespace Ui {
class Sign_up;
}

class Sign_up : public QWidget
{
    Q_OBJECT

public:
    explicit Sign_up(QWidget *parent = nullptr);
    ~Sign_up();

private:
    Ui::Sign_up *ui;
};

#endif // SIGN_UP_H
