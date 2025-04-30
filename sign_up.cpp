#include "sign_up.h"
#include "ui_sign_up.h"
#include "ui_login.h"
#include "login.h"
#include "Account.h"
#include "employee.h"
#include <QMessageBox>
#include <QFileDialog>

#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QVBoxLayout>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
Sign_up::Sign_up(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Sign_up)
{
    ui->setupUi(this);

    QPixmap bg("C:/Users/Skander/Desktop/Final Integration/Integration/IMG/car.png");
    ui->label_3->setPixmap(bg);
    mCamera = new QCamera(this);
          mQCameraViewfinder = new QCameraViewfinder(this);
           mQCameraImageCapture = new QCameraImageCapture(mCamera,this);
           mLayout =new QVBoxLayout;
           mOptionsMenu = new QMenu("Open Cam",this);
           mCamera->setViewfinder(mQCameraViewfinder);
           mEncenderAction =new QAction("Open Cam",this);
           mApAction =new QAction("Stop Camera",this);
           mCaptureAction =new QAction("Capture image",this);
           mOptionsMenu->addActions({mEncenderAction,mApAction,mCaptureAction});
           ui->cam->setMenu(mOptionsMenu);
           mLayout->addWidget(mQCameraViewfinder);
           mLayout->setMargin(0);
           ui->scrollArea->setLayout(mLayout);
           connect(mEncenderAction,&QAction::triggered,[&](){
               mCamera->start();
           });
           connect(mApAction,&QAction::triggered,[&](){
               mCamera->stop();
           });
     connect(mCaptureAction,&QAction::triggered,[&](){
        auto filename =QFileDialog ::getSaveFileName(this,"Capture","/","Image(*.jpg;*.jpeg)");
        if(filename.isEmpty()){
            return;
        }
                mQCameraImageCapture->setCaptureDestination(QCameraImageCapture::CaptureToFile);
         QImageEncoderSettings ImageEncoderSettings;
         ImageEncoderSettings.setCodec("image/jpeg");
         ImageEncoderSettings.setResolution(1600,1200);
         mQCameraImageCapture->setEncodingSettings(ImageEncoderSettings);
         mCamera->setCaptureMode(QCamera::CaptureStillImage);
         mCamera->start();
         mQCameraImageCapture->capture(filename);
         mCamera->unlock();
     });




ui->pwd->setEchoMode(QLineEdit::Password);
ui->confirm->setEchoMode(QLineEdit::Password);
}

Sign_up::~Sign_up()
{
    delete ui;
}

void Sign_up::on_signup_clicked()
{
    button_sound();
    QString username = ui->name->text();
    QString pwd = ui->pwd->text();
     QString role = ui->role->text();
 QString idemp = ui->idemp->text();

Account a(username,pwd);



     bool confirm_pwd=ui->pwd->text()==ui->confirm->text();
     if( confirm_pwd)
     {       bool test=a.sign_up(username, pwd, role,idemp);
         if(test){qDebug()<<"a";}
               a.ajouter_image(a.username);
                /*  QPixmap outPixmap = QPixmap();
                     outPixmap.loadFromData(a.fetch_image(username),"JPG");
                    outPixmap = outPixmap.scaledToWidth(ui->label_2->width(),Qt::SmoothTransformation);

                   ui->label_2->setPixmap(outPixmap.scaled(outPixmap.width(),outPixmap.height(),Qt::KeepAspectRatio));
                */
         Login l;
         l.show();
         QMessageBox::information(nullptr, QObject::tr("ok"),
                     QObject::tr("Welcome to our desktop application!\n"
                                 "Click ok to exit."), QMessageBox::Ok);


           ui->name->setText("");
           ui->pwd->setText("");
           ui->confirm->setText("");
           ui->role->setText("");
           ui->idemp->setText("");
 }
     else
     {
         if (!confirm_pwd)
         {
           ui->confirm->setStyleSheet("color: red");


     QMessageBox::critical(nullptr, QObject::tr("not ok"),
                  QObject::tr("the two passwords are not identical\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

          }
     }
}

