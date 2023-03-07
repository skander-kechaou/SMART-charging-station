#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QMessageBox>
#include "client.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(Etmp.Read());
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    QPixmap icon("C:/Users/Skander/Documents/Client1/feedback.png");
    QPixmap client("C:/Users/Skander/Documents/Client1/client.png");
    QPixmap pdf("C:/Users/Skander/Documents/Client1/pdf-file.png");
    QIcon search("C:/Users/Skander/Documents/Client1/search-interface-symbol.png");
    QPixmap sort("C:/Users/Skander/Documents/Client1/sort.png");
    QPixmap trashcan("C:/Users/Skander/Documents/Client1/trash-can.png");
    ui->icon->setPixmap(icon);
    ui->client->setPixmap(client);
    ui->pdf->setPixmap(pdf);
    ui->searchButton->setIcon(search);
    ui->sortLabel->setPixmap(sort);
    ui->trashcan->setPixmap(trashcan);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_addButton_clicked()
{
    client c;
    c.setNIC(ui->nicEdit->text());
    c.setFirstName(ui->fnameEdit->text());
    c.setLastName(ui->lnameEdit->text());
    c.setEmail(ui->emailEdit->text());
    c.setPhone(ui->pnbEdit->text());
    c.setCredit(ui->creditEdit->text());

       bool test=c.Create(); // insert the object into the databse Student table
                             // and et the returned value of query.exec()

       if(test) // if the query is executed  ==> QMessageBox::information
       {
           // Refresh
           ui->tableView->setModel(Etmp.Read());

           QMessageBox::information(nullptr, QObject::tr("OK"),
                       QObject::tr("insert done \n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);

       }
       else // if the query is not executed  ==> QMessageBox::critical
           QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                       QObject::tr("insert failed.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_deleteButton_clicked()
{
    QString nic = ui->deleteEdit->text();
        bool test=Etmp.Delete(nic);

        if(test)
        {
            // Refresh (Actualiser)
            ui->tableView->setModel(Etmp.Read());

            QMessageBox::information(nullptr, QObject::tr("OK"),
                        QObject::tr("delete done\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

        }
        else
            QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                        QObject::tr("delete failed.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    ui->nicEdit->setText(ui->tableView->model()->data(ui->tableView->model()->index(index.row(),0)).toString());
    ui->fnameEdit->setText(ui->tableView->model()->data(ui->tableView->model()->index(index.row(),1)).toString());
    ui->lnameEdit->setText(ui->tableView->model()->data(ui->tableView->model()->index(index.row(),2)).toString());
    ui->pnbEdit->setText(ui->tableView->model()->data(ui->tableView->model()->index(index.row(),3)).toString());
    ui->emailEdit->setText(ui->tableView->model()->data(ui->tableView->model()->index(index.row(),4)).toString());
    ui->creditEdit->setText(ui->tableView->model()->data(ui->tableView->model()->index(index.row(),5)).toString());
}

void MainWindow::on_EditButton_clicked()
{
    client c;
    c.setNIC(ui->nicEdit->text());
    c.setFirstName(ui->fnameEdit->text());
    c.setLastName(ui->lnameEdit->text());
    c.setEmail(ui->emailEdit->text());
    c.setPhone(ui->pnbEdit->text());
    c.setCredit(ui->creditEdit->text());

        bool test= c.update();
        if(test)
        {
            ui->tableView->setModel(Etmp.Read());
            QMessageBox::information(nullptr,QObject::tr(" OK"),
                                     QObject::tr("Update failed\n"
                                                 "Click Cancel to exit."),QMessageBox::Cancel);


        }
        else
            QMessageBox::critical(nullptr,QObject::tr("Not OK"),
                                     QObject::tr("Update done\n"
                                                 "Click Cancel to exit."),QMessageBox::Cancel);

}
