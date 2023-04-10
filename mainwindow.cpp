#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include "maildialog.h"
#include "qrcode.h"
#include "qrcodegenerator.h"
#include "qrwidget.h"
#include <QPixmap>
#include <QMessageBox>
#include <QPdfWriter>
#include <QPainter>
#include <QDate>
#include <QSound>
#include <QScrollBar>
#include <QDesktopServices>
#include <QUrl>
#include <QDate>
#include <QTime>
#include <QTimer>
#include <src/src/SmtpMime>
#include "history.h"

using namespace qrcodegen;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // INPUT CONTROL
    QRegularExpression emailRegex("^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$");
    QRegularExpression regex("[a-zA-Z]+");
    ui->emailEdit->setValidator(new QRegularExpressionValidator(emailRegex, this));
    ui->pnbEdit->setValidator(new QIntValidator(10000000,99999999, this));
    ui->nicEdit->setValidator(new QIntValidator(10000000,99999999, this));
    ui->creditEdit->setValidator(new QIntValidator(0,1000, this));
    ui->fnameEdit->setValidator(new QRegularExpressionValidator(regex, this));
    ui->lnameEdit->setValidator(new QRegularExpressionValidator(regex, this));
    //Timer
              QTimer *timer_p=new QTimer(this);
              connect(timer_p, SIGNAL(timeout()), this,SLOT(showTime()));
              timer_p->start(1000);
    //Date systeme
              QDateTime Date_p=QDateTime::currentDateTime();
              QString Date_txt=Date_p.toString("dddd dd MMMM yyyy");
              ui->Date->setText(Date_txt);

    // DISPLAY
    ui->tableView->setModel(Etmp.Read());
    // ui->tableView->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);
    QHeaderView* header = ui->tableView->horizontalHeader();
    header->setVisible(true);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    QScrollBar *vScrollBar = ui->tableView->verticalScrollBar();
    QScrollBar *hScrollBar = ui->tableView->horizontalScrollBar();
    vScrollBar->setStyleSheet("QScrollBar:vertical { background-color: #7FA39A; }");
    hScrollBar->setStyleSheet("QScrollBar:horizontal { background-color: #7FA39A; }");


    // Images and Icons
    QPixmap icon("C:/Users/Skander/Documents/Client1/feedback.png");
    QPixmap client("C:/Users/Skander/Documents/Client1/client.png");
    QIcon pdf("C:/Users/Skander/Documents/Client1/pdf-file.png");
    QIcon search("C:/Users/Skander/Documents/Client1/search-interface-symbol.png");
    QPixmap sort("C:/Users/Skander/Documents/Client1/sort.png");
    QPixmap trashcan("C:/Users/Skander/Documents/Client1/trash-can.png");
    QIcon refresh("C:/Users/Skander/Documents/Client1/refresh-button.png");
    QPixmap mail("C:/Users/Skander/Documents/Client1/email.png");
    QIcon qrcode("C:/Users/Skander/Documents/Client1/qr-code.png");
    ui->icon->setPixmap(icon);
    ui->client->setPixmap(client);
    ui->PDFButton->setIcon(pdf);
    ui->searchButton->setIcon(search);
    ui->sortLabel->setPixmap(sort);
    ui->trashcan->setPixmap(trashcan);
    ui->refreshButton->setIcon(refresh);
    ui->mailing->setPixmap(mail);
    ui->qrcodeButton->setIcon(qrcode);

    // Statistics

    QPieSeries *series = new QPieSeries();

        series->append("0", Etmp.count_credit("0"));
        series->append("100", Etmp.count_credit("100"));
        series->append("200", Etmp.count_credit("200"));
        series->append("300", Etmp.count_credit("300"));
        series->append("400", Etmp.count_credit("400"));


        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("Clients' Credit");
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
        chartview->setFixedSize(QSize(300, 200));


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
           history h(c.getNIC(), c.getFirstName(), c.getLastName(), c.getEmail(), c.getPhone(), c.getCredit(), "");
           h.saveclient();

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
           /* client c("","","","","","");
                     QSqlQuery materielInfo = c.Read();
                     materielInfo.next();
                     Historiques h(materielInfo.value(1).toString(), materielInfo.value(2).toString(), materielInfo.value(0).toString(), materielInfo.value(3).toString(), "");
                     h.saveDeletemateriel();*/
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
    ui->deleteEdit->setText(ui->tableView->model()->data(ui->tableView->model()->index(index.row(),0)).toString());
    ui->recipientEdit->setText(ui->tableView->model()->data(ui->tableView->model()->index(index.row(),4)).toString());
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

                  painter.drawText(3500,2700,"List of clients");

                  painter.setPen(Qt::black);
                  painter.setFont(QFont("Time New Roman", 15));
                  //painter.drawRect(100,100,9400,2500);
                  painter.drawRect(100,3300,9400,500);

                  painter.setFont(QFont("Montserrat SemiBold", 10));

                  painter.drawText(500,3600,"NIC");
                  painter.drawText(1500,3600,"First Name");
                  painter.drawText(3000,3600,"Last Name");
                  painter.drawText(4500,3600,"Phone Number");
                  painter.drawText(6200,3600,"E-mail Address");
                  painter.drawText(8700,3600,"Credit");
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
                      painter.drawText(1500,i,query.value(1).toString());
                      painter.drawText(3000,i,query.value(2).toString());
                      painter.drawText(4500,i,query.value(3).toString());
                      painter.drawText(6200,i,query.value(4).toString());
                      painter.drawText(8700,i,query.value(5).toString());

                     i = i + 500;
                  }
                  QMessageBox::information(nullptr,QObject::tr(" OK"),
                                           QObject::tr("PDF Generated\n"
                                                       "Click Cancel to exit."),QMessageBox::Cancel);

                  QString filePath = "C:/Users/Skander/Documents/Client1/PDF/list_clients.pdf";
                  QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));

}


void MainWindow::on_refreshButton_clicked()
{
    QSound::play("click.mp3");
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

void MainWindow::on_sendButton_clicked()
{
    client c;
    c.setEmail(ui->emailEdit->text());
    mailDialog m;
    m.setClient(c);
    m.exec();
}

void MainWindow::on_qrcodeButton_clicked()
{
    client c;
    c.setNIC(ui->nicEdit->text());
    c.setFirstName(ui->fnameEdit->text());
    c.setLastName(ui->lnameEdit->text());
    c.setEmail(ui->emailEdit->text());
    c.setPhone(ui->pnbEdit->text());
    c.setCredit(ui->creditEdit->text());
    QString ids="";
        ids="NIC: "+c.getNIC()+" First Name: "+c.getFirstName()+" Last Name: "+c.getLastName()+" Email: "+c.getEmail()+" Phone : "+c.getPhone()+" Credit: "+c.getCredit();
        QrCode qr = QrCode::encodeText(ids.toUtf8().constData(), QrCode::Ecc::HIGH);

        // Read the black & white pixels
        QImage im(qr.getSize(),qr.getSize(), QImage::Format_RGB888);
        for (int y = 0; y < qr.getSize(); y++) {
            for (int x = 0; x < qr.getSize(); x++) {
                int color = qr.getModule(x, y);  // 0 for white, 1 for black

                // You need to modify this part
                if(color==0)
                    im.setPixel(x, y,qRgb(254, 254, 254));
                else
                    im.setPixel(x, y,qRgb(0, 0, 0));
            }
        }
        im=im.scaled(120,120);
        ui->qrLabel->setPixmap(QPixmap::fromImage(im));
}

void MainWindow::showTime()
{
    ui->time->setText(QTime::currentTime().toString("hh:mm:ss"));
}
