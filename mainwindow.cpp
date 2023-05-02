#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QMessageBox>
#include <QPdfWriter>
#include <QPainter>
#include <QDate>
#include<QtCharts>
#include<QChartView>
#include<QPieSeries>
#include<QPieSlice>
#include <QtCore>
#include <QtNetwork>
#include <QCryptographicHash>
#include <QSslSocket>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(inv.Read());
    QIcon pdf("C:/Users/USER/Documents/invoice/pdf-file.png");
    QIcon search("C:/Users/USER/Documents/invoice/search-interface-symbol.png");
    ui->pdf->setIcon(pdf);
    ui->searchButton->setIcon(search);
    QPieSeries *series = new QPieSeries();
    series->append("Ariana", inv.count_stat("12"));
        series->append("bardo", inv.count_stat("15"));
        series->append("manouba", inv.count_stat("4"));
        series->append("tunis", inv.count_stat("32"));
    QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setAcceptHoverEvents(true);
        chart->setPreferredSize(QSize(300, 300));
        chart->setMargins(QMargins(0, 0, 0, 0));
        chart->setBackgroundBrush(QBrush(QColor(182, 215, 168)));
        QChartView *chartview = new QChartView(chart);
        chartview->setParent(ui->chart);
        chartview->setRubberBand(QChartView::RectangleRubberBand);
        chartview->setRenderHint(QPainter::Antialiasing);
        chartview->setInteractive(true);
        chartview->setContentsMargins(0, 0, 0, 0);
        chartview->setFixedSize(QSize(300, 300));

        //for email tab
        connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
        connect(ui->browseBtn, SIGNAL(clicked()), this, SLOT(browse()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_AddButton_clicked()
{
    invoice i;
    i.setreference(ui->referenceEdit->text());
    i.setNIC(ui->NICEdit->text());
    i.setidstat(ui->idstatEdit->text());
    i.setlicensepl(ui->licenseplEdit->text());
    i.setcost(ui->costEdit->text().toInt());
    QString date=ui->date_invEdit->text();
    QDate date_inv=QDate::fromString(date,  "yyyy-MM-dd");
    i.setdate_inv(date_inv);

       bool test=i.Create(); // insert the object into the databse Student table
                             // and et the returned value of query.exec()

       if(test) // if the query is executed  ==> QMessageBox::information
       {
           // Refresh
           ui->tableView->setModel(inv.Read());

           QMessageBox::information(nullptr, QObject::tr("OK"),
                       QObject::tr("insert done \n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);

       }
       else // if the query is not executed  ==> QMessageBox::critical
           QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                       QObject::tr("insert failed.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);
}



void MainWindow::on_EditButton_clicked()
{
    invoice i;
    i.setreference(ui->referenceEdit->text());
    i.setNIC(ui->NICEdit->text());
    i.setidstat(ui->idstatEdit->text());
    i.setlicensepl(ui->licenseplEdit->text());
    i.setcost(ui->costEdit->text().toInt());
    QString date=ui->date_invEdit->text();
    i.setdate_inv(QDate::fromString(date, "yyyy/MM/dd"));

       bool test=i.update(); // insert the object into the databse Student table
                             // and et the returned value of query.exec()

       if(test) // if the query is executed  ==> QMessageBox::information
       {
           // Refresh
           ui->tableView->setModel(inv.Read());

           QMessageBox::information(nullptr, QObject::tr("OK"),
                       QObject::tr("update done \n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);

       }
       else // if the query is not executed  ==> QMessageBox::critical
           QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                       QObject::tr("update failed.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
       ui->referenceEdit->setText(ui->tableView->model()->data(ui->tableView->model()->index(index.row(),0)).toString());
       ui->date_invEdit->setText(ui->tableView->model()->data(ui->tableView->model()->index(index.row(),1)).toString());
       ui->NICEdit->setText(ui->tableView->model()->data(ui->tableView->model()->index(index.row(),2)).toString());
       ui->costEdit->setText(ui->tableView->model()->data(ui->tableView->model()->index(index.row(),3)).toString());
       ui->idstatEdit->setText(ui->tableView->model()->data(ui->tableView->model()->index(index.row(),4)).toString());
       ui->licenseplEdit->setText(ui->tableView->model()->data(ui->tableView->model()->index(index.row(),5)).toString());
}

void MainWindow::on_pushButton_2_clicked()
{
    QString ref = ui->referenceEdit->text();
           bool test=inv.Delete(ref);

           if(test)
           {
               // Refresh (Actualiser)
               ui->tableView->setModel(inv.Read());

               QMessageBox::information(nullptr, QObject::tr("OK"),
                           QObject::tr("delete done\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);

           }
           else
               QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                           QObject::tr("delete failed.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pdf_clicked()
{
    QPdfWriter pdf("C:/Users/USER/Documents/invoice/pdf/listinvoice.pdf");

                  QPainter painter(&pdf);
                  int i = 4100;
                  const QImage image("C:/Users/USER/Documents/invoice/logo.png");
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

                         painter.drawText(3000,2700,"List of invoices");

                         painter.setPen(Qt::black);
                         painter.setFont(QFont("Time New Roman", 15));
                         //painter.drawRect(100,100,9400,2500);
                         painter.drawRect(100,3300,9400,500);

                         painter.setFont(QFont("Montserrat SemiBold", 10));

                         painter.drawText(500,3600,"REFERENCE");
                         painter.drawText(2000,3600,"Date Invoice");
                         painter.drawText(3500,3600,"NIC");
                         painter.drawText(5000,3600,"COST");
                         painter.drawText(7000,3600,"ID Station");
                         painter.drawText(8500,3600,"License Plate");
                         painter.setFont(QFont("Montserrat", 10));
                         painter.drawRect(100,3300,9400,9000);

                         QSqlQuery query;
                         query.prepare("select * from invoice");
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

void MainWindow::on_pushButton_clicked()
{
        QString reference="";
        QDate date_inv=QDate::currentDate();
        QString NIC="";
        int cost=0;
        QString idstat="";
        QString licensepl="";

            invoice i(reference,NIC,idstat,licensepl,cost, date_inv);
            QString Option=ui->comboBox->currentText();
            ui->tableView->setModel(i.sort(Option));
}



void MainWindow::on_searchButton_clicked()
{
    QString reference="";
    QDate date_inv=QDate::currentDate();
    QString NIC="";
    int cost=0;
    QString idstat="";
     QString licensepl="";

         invoice i(reference,NIC,idstat,licensepl,cost, date_inv);
        QString Option=ui->searchBox->currentText();
        QString text=ui->searchEdit->text();
        ui->tableView->setModel(i.search(Option,text));
}

//mailing
void  MainWindow::browse()
{
    files.clear();

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

    ui->file->setText( fileListString );

}
void   MainWindow::sendMail()
{
    Smtp* smtp = new Smtp("arij.mahouechi@esprit.tn",ui->mail_pass->text(), "smtp.gmail.com");
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    if( !files.isEmpty() )
        smtp->sendMail("arij.mahouechi@esprit.tn", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText(), files );
    else
        smtp->sendMail("arij.mahouechi@esprit.tn", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
}
void   MainWindow::mailSent(QString status)
{

    if(status == "Message sent")
        QMessageBox::warning( nullptr, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
    ui->rcpt->clear();
    ui->subject->clear();
    ui->file->clear();
    ui->msg->clear();
    ui->mail_pass->clear();
}

void MainWindow::on_pushButton_3_clicked()
{
    c= new calculatrice(this);
    c->show();
}

void MainWindow::on_sendBtn_clicked()
{

}
