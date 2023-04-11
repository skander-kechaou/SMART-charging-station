#ifndef SIGN_UP_H
#define SIGN_UP_H
#include<QWidget>
#include <QDialog>
#include "Account.h"
namespace Ui {
class Sign_up;
}
class QCamera;
class QCameraViewfinder;
class QCameraImageCapture;
class QVBoxLayout;
class QMenu;
class QAction;
class Sign_up : public QDialog

{
    Q_OBJECT

public:
    explicit Sign_up(QWidget *parent = nullptr);
    ~Sign_up();

private slots:


    void on_pushButton_clicked();
void on_signup_clicked();
    void on_loginbtn_clicked();

private:
    Ui::Sign_up *ui;
Sign_up *s;
QCamera *mCamera;
  QCameraViewfinder *mQCameraViewfinder;
   QCameraImageCapture *mQCameraImageCapture;
  QVBoxLayout   *mLayout;
  QMenu *mOptionsMenu;
  QAction *mEncenderAction;
  QAction *mApAction;
  QAction *mCaptureAction;
 Account a;
};

#endif // SIGN_UP_H
