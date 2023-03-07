#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "station.h"
#include <QMessageBox>



void MainWindow::on_pushButton_create_clicked()
{
   // Get information entered in the 3 fields
   int id_stat=ui->lineEdit_ID->text().toInt();
   int capacity =ui->lineEdit_->text().toInt();
   QString nameStat = ui->lineEdit_nameStat->text();
   QString locaStat = ui->lineEdit_locaStat->text();

   station S(id_stat,capacity,nameStat,locaStat); // object instantiation
                             // using information entered in the interface

   bool test=E.Create(); // insert the object into the databse Student table
                         // and et the returned value of query.exec()

   if(test) // if the query is executed  ==> QMessageBox::information
   {
       // Refresh
       ui->tableView->setModel(stat.Read());

       QMessageBox::information(nullptr, QObject::tr("OK"),
                   QObject::tr("insert done \n"
                               "Click Cancel to exit."), QMessageBox::Cancel);

   }
   else // if the query is not executed  ==> QMessageBox::critical
       QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                   QObject::tr("insert failed.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_pushButton_delete_clicked()
{
    int id =ui->lineEdit_IDS->text().toInt();
    bool test=stat.Delete(id);

    if(test)
    {
        // Refresh (Actualiser)
        ui->tableView->setModel(stat.Read());

        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("delete done\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                    QObject::tr("delete failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}
