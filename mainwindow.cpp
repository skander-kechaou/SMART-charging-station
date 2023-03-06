#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QMessageBox>
#include <QApplication>
MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent) , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(Ctmp.readcar());
    QPixmap pix("C:/Users/youss/Downloads/add-image.png");
    ui->image_upload->setPixmap(pix.scaled(100,100,Qt::KeepAspectRatio));
    QPixmap home("C:/Users/youss/Downloads/home.png");
    ui->home->setPixmap(home.scaled(100,100,Qt::KeepAspectRatio));
    QPixmap client("C:/Users/youss/Downloads/customer.png");
    ui->client->setPixmap(client.scaled(100,100,Qt::KeepAspectRatio));
    QPixmap station("C:/Users/youss/Downloads/charging.png");
    ui->station->setPixmap(station.scaled(100,100,Qt::KeepAspectRatio));
    QPixmap invoice("C:/Users/youss/Downloads/invoice.png");
    ui->invoice->setPixmap(invoice.scaled(100,100,Qt::KeepAspectRatio));
    QPixmap employee("C:/Users/youss/Downloads/employee.png");
    ui->employee->setPixmap(employee.scaled(100,100,Qt::KeepAspectRatio));
    QPixmap barchart("C:/Users/youss/Downloads/barchart.png");
    ui->barchart->setPixmap(barchart.scaled(400,400,Qt::KeepAspectRatio));

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_addcar_clicked()
{
    car c;
   c.setbrand(ui->lineEdit_3->text());
   c.setownerid(ui->lineEdit_5->text());
   c.setlicenceplate(ui->lineEdit_2->text());
   c.setbatterycap(ui->lineEdit_4->text().toFloat());
   bool test=c.createcar();
   if(test)
   {
       ui->tableView->setModel(Ctmp.readcar());
       QMessageBox::information(nullptr,QObject::tr("OK"),QObject::tr("insert done\n"),QMessageBox::Cancel);

   }
   else
       QMessageBox::critical(nullptr,QObject::tr("Not OK"),QObject::tr("insert faild\n"),QMessageBox::Cancel);
}
void MainWindow::on_pushButton_delete_clicked()
{
    QString licenceplate;
    bool test=Ctmp.deletecar(licenceplate);

    if(test)
    {
        // Refresh (Actualiser)
        ui->tableView->setModel(Ctmp.readcar());

        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("delete done\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                    QObject::tr("delete failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}


