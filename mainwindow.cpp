#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QMessageBox>
#include <QPdfWriter>
#include <QPainter>
#include <QDate>
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
    QIcon pdf("C:/Users/Skander/Documents/Client1/pdf-file.png");
    QIcon search("C:/Users/Skander/Documents/Client1/search-interface-symbol.png");
    QPixmap sort("C:/Users/Skander/Documents/Client1/sort.png");
    QPixmap trashcan("C:/Users/Skander/Documents/Client1/trash-can.png");
    QIcon refresh("C:/Users/Skander/Documents/Client1/refresh-button.png");
    ui->icon->setPixmap(icon);
    ui->client->setPixmap(client);
    ui->PDFButton->setIcon(pdf);
    ui->searchButton->setIcon(search);
    ui->sortLabel->setPixmap(sort);
    ui->trashcan->setPixmap(trashcan);
    ui->refreshButton->setIcon(refresh);
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
                                     QObject::tr("Update done\n"
                                                 "Click Cancel to exit."),QMessageBox::Cancel);


        }
        else
            QMessageBox::critical(nullptr,QObject::tr("Not OK"),
                                     QObject::tr("Update failed\n"
                                                 "Click Cancel to exit."),QMessageBox::Cancel);

}

void MainWindow::on_PDFButton_clicked()
{
    QPdfWriter pdf("C:/Users/Skander/Documents/Client1/PDF/list_clients.pdf");

           QPainter painter(&pdf);
           int i = 4100;
          const QImage image("C:/Users/Skander/Documents/Client1/logo.png");
                       const QPoint imageCoordinates(155,0);
                       int width1 = 1600;
                       int height1 = 1600;
                       QImage img=image.scaled(width1,height1);
                       painter.drawImage(imageCoordinates, img );


                  QColor dateColor(255,0,0);
                  painter.setPen(dateColor);

                  painter.setFont(QFont("Montserrat SemiBold", 11));
                  QDate cd = QDate::currentDate();
                  painter.drawText(8400,250,cd.toString("Tunis"));
                  painter.drawText(8100,500,cd.toString("dd/MM/yyyy"));

                  QColor titleColor(0x341763);
                  painter.setPen(titleColor);
                  painter.setFont(QFont("Montserrat SemiBold", 25));

                  painter.drawText(3000,2700,"Liste of clients");

                  painter.setPen(Qt::black);
                  painter.setFont(QFont("Time New Roman", 15));
                  //painter.drawRect(100,100,9400,2500);
                  painter.drawRect(100,3300,9400,500);

                  painter.setFont(QFont("Montserrat SemiBold", 10));

                  painter.drawText(500,3600,"NIC");
                  painter.drawText(2000,3600,"First Name");
                  painter.drawText(3500,3600,"Last Name");
                  painter.drawText(5000,3600,"Phone Number");
                  painter.drawText(7000,3600,"E-mail Address");
                  painter.drawText(8500,3600,"Credit");
                  painter.setFont(QFont("Montserrat", 10));
                  painter.drawRect(100,3300,9400,9000);

                  QSqlQuery query;
                  query.prepare("select * from client");
                  query.exec();
                  int y=4300;
                  while (query.next())
                  {
                      painter.drawLine(100,y,9490,y);
                      y+=500;
                      painter.drawText(500,i,query.value(0).toString());
                      painter.drawText(2000,i,query.value(1).toString());
                      painter.drawText(3500,i,query.value(2).toString());
                      painter.drawText(5000,i,query.value(3).toString());
                      painter.drawText(7000,i,query.value(4).toString());
                      painter.drawText(8500,i,query.value(5).toString());

                     i = i + 500;
                  }
                  QMessageBox::information(this, QObject::tr("Saved PDF!"),
                  QObject::tr("Saved PDF!.\n" "Click Cancel to exit."), QMessageBox::Cancel);

}


void MainWindow::on_refreshButton_clicked()
{
    ui->nicEdit->setText("");
    ui->fnameEdit->setText("");
    ui->lnameEdit->setText("");
    ui->pnbEdit->setText("");
    ui->emailEdit->setText("");
    ui->creditEdit->setText("");
}

void MainWindow::on_sortButton_clicked()
{
    QString NIC="";
    QString fname="";
    QString lname="";
    QString mail="";
    QString phonec="";
    QString credit="";

        client c(NIC,fname,lname,mail,phonec,credit);
        QString Option=ui->sortCombo->currentText();
        ui->tableView->setModel(c.sort(Option));
}

void MainWindow::on_searchButton_clicked()
{
    QString NIC="";
    QString fname="";
    QString lname="";
    QString mail="";
    QString phonec="";
    QString credit="";

        client c(NIC,fname,lname,mail,phonec,credit);
        QString Option=ui->searchCombo->currentText();
        QString text=ui->searchEdit->text();
        ui->tableView->setModel(c.search(Option,text));
}
