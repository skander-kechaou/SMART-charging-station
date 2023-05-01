#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include "car.h"
#include "image.h"
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
#include "history.h"
#include <QFile>
#include <QLineEdit>
#include <QByteArray>
#include <QThread>
#include <QSerialPort>

using namespace qrcodegen;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //##########################################CLIENT MANAGEMENT##############################################
    // INPUT CONTROL
    QRegularExpression emailRegex("^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$");
    QRegularExpression regex("[a-zA-Z]+");
    QRegularExpression creditRegex("^(0|100|200|300|400|500)$");
    ui->emailEdit->setValidator(new QRegularExpressionValidator(emailRegex, this));
    ui->pnbEdit->setValidator(new QIntValidator(10000000,99999999, this));
    ui->nicEdit->setValidator(new QIntValidator(10000000,99999999, this));
    ui->creditEdit->setValidator(new QRegularExpressionValidator(creditRegex, this));
    ui->fnameEdit->setValidator(new QRegularExpressionValidator(regex, this));
    ui->lnameEdit->setValidator(new QRegularExpressionValidator(regex, this));
    //Timer
              QTimer *timer_p=new QTimer(this);
              connect(timer_p, SIGNAL(timeout()), this,SLOT(showTime()));
              // history changes
              connect(timer_p, &QTimer::timeout, this, &MainWindow::updateHistoryEdit);
              // charts changes
              connect(timer_p, &QTimer::timeout, this, &MainWindow::updateChart);

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
    ui->Date->setAlignment(Qt::AlignRight);
    ui->time->setAlignment(Qt::AlignRight);


    // Images and Icons
    QPixmap icon("C:/Users/Skander/Documents/Client1/feedback.png");
    QPixmap client("C:/Users/Skander/Documents/Client1/client.png");
    QIcon pdf("C:/Users/Skander/Documents/Client1/pdf-file.png");
    QIcon search("C:/Users/Skander/Documents/Client1/search-interface-symbol.png");
    QPixmap sort("C:/Users/Skander/Documents/Client1/sort.png");
    QPixmap trashcan("C:/Users/Skander/Documents/Client1/trash-can.png");
    QIcon refresh("C:/Users/Skander/Documents/Client1/refresh-button.png");
    QIcon qrcode("C:/Users/Skander/Documents/Client1/qr-code.png");
    QIcon history("C:/Users/Skander/Documents/Client1/history.png");
    ui->icon->setPixmap(icon);
    ui->client->setPixmap(client);
    ui->PDFButton->setIcon(pdf);
    ui->searchButton->setIcon(search);
    ui->sortLabel->setPixmap(sort);
    ui->trashcan->setPixmap(trashcan);
    ui->refreshButton->setIcon(refresh);
    ui->qrcodeButton->setIcon(qrcode);
    ui->historyButton->setIcon(history);

    // Statistics

    QPieSeries *ClientSeries = new QPieSeries();

        ClientSeries->append("0", Etmp.count_credit("0"));
        ClientSeries->append("100", Etmp.count_credit("100"));
        ClientSeries->append("200", Etmp.count_credit("200"));
        ClientSeries->append("300", Etmp.count_credit("300"));
        ClientSeries->append("400", Etmp.count_credit("400"));
        ClientSeries->append("500", Etmp.count_credit("500"));


        QChart *ClientChart = new QChart();
        ClientChart->addSeries(ClientSeries);
        ClientChart->setTitle("Clients' Credit");
        ClientChart->setAcceptHoverEvents(true);
        ClientChart->setPreferredSize(QSize(300, 300));
        ClientChart->setMargins(QMargins(0, 0, 0, 0));
        ClientChart->setBackgroundBrush(QBrush(QColor(182, 215, 168)));
        QChartView *Clientchartview = new QChartView(ClientChart);
        Clientchartview->setParent(ui->chart);
        Clientchartview->setRubberBand(QChartView::RectangleRubberBand);
        Clientchartview->setRenderHint(QPainter::Antialiasing);
        Clientchartview->setInteractive(true);
        Clientchartview->setContentsMargins(0, 0, 0, 0);
        Clientchartview->setFixedSize(QSize(350, 200));

      // HISTORY
        QFile file("C:/Users/Skander/Documents/Client1/history.txt");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug() << "Failed to open file";
            return;
        }

        QByteArray fileData(reinterpret_cast<const char*>(file.map(0, file.size())), file.size());
        QString lastNonEmptyLine;
        if (!fileData.isEmpty())
        {
            const char *data = fileData.constData() + fileData.size() - 1;
            while (data >= fileData.constData() && (*data == '\n' || *data == '\r'))
            {
                --data;
            }
            const char *lineEnd = data + 1;
            while (data >= fileData.constData() && *data != '\n' && *data != '\r')
            {
                --data;
            }
            const char *lineStart = data + 1;
            lastNonEmptyLine = QString::fromUtf8(lineStart, lineEnd - lineStart);
        }

        ui->historyEdit->setPlainText(lastNonEmptyLine.trimmed());

        // Arduino
        QMetaObject::Connection connectionNIC;

        int ret=a.connect_arduino(); // launch the connection to arduino
            switch(ret){
            case(0):qDebug()<< "arduino is available and connected to : "<< a.getarduino_port_name();
                // Connect the signal to the slot to read data from the arduino
                 connectionNIC = QObject::connect(a.getserial(), &QSerialPort::readyRead, [=]() {
                            QByteArray data = a.read_from_arduino();
                            //process_data(data);
                            final+=data;
                            qDebug()<<"final: "<<final;
                            qDebug()<<"length: "<<final.length();
                            if((final.at(0)=='#') && (final.length()==4))
                            {
                                qDebug()<<"Inside the # if loop!";
                                finalC = final;
                                finalC.remove(0,1);
                                qDebug()<<"finalC: "<<finalC;
                                update_data(finalC);
                                QObject::disconnect(connectionNIC);
                                final.clear();
                                finalC.clear();
                            }
                            else if(final.length()==8)
                            {
                                process_data(final);
                                QObject::disconnect(connectionNIC);
                                final.clear();
                            }

                        });
                break;
            case(1):qDebug() << "arduino is available but not connected to :" <<a.getarduino_port_name();
               break;
            case(-1):qDebug() << "arduino is not available";
            }

            //##########################################CAR MANAGEMENT##############################################
            ui->CartableView->setModel(Ctmp.Read());
                ui->CartableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
                ui->CartableView->setItemDelegateForColumn(6, new ImageDelegate(ui->CartableView));
                vScrollBar->setStyleSheet("QScrollBar:vertical { background-color: #7FA39A; }");
                hScrollBar->setStyleSheet("QScrollBar:horizontal { background-color: #7FA39A; }");
                QIcon xls("C:/Users/Skander/Documents/Client1/xls-file.png");
                QIcon image("C:/Users/Skander/Documents/Client1/photo.png");

                QPieSeries *CarSeries = new QPieSeries();

                CarSeries->append("kia", Ctmp.count_brand("kia"));
                CarSeries->append("BMW", Ctmp.count_brand("BMW"));
                CarSeries->append("hyundai", Ctmp.count_brand("hyundai"));
                CarSeries->append("tesla", Ctmp.count_brand("tesla"));
                CarSeries->append("ford", Ctmp.count_brand("tesla"));


                QChart *CarChart = new QChart();
                CarChart->addSeries(CarSeries);
                CarChart->setAcceptHoverEvents(true);
                CarChart->setPreferredSize(QSize(300, 300));
                CarChart->setMargins(QMargins(0, 0, 0, 0));
                CarChart->setBackgroundBrush(QBrush(QColor(182, 215, 168)));
                QChartView *Carchartview = new QChartView(CarChart);
                Carchartview->setParent(ui->Carchart);
                Carchartview->setRubberBand(QChartView::RectangleRubberBand);
                Carchartview->setRenderHint(QPainter::Antialiasing);
                Carchartview->setInteractive(true);
                Carchartview->setContentsMargins(0, 0, 0, 0);
                Carchartview->setFixedSize(QSize(500, 300));

                ui->Caricon->setPixmap(icon);
                ui->CarpdfButton->setIcon(pdf);
                ui->CarimageButton->setIcon(image);
                ui->CarxlsButton->setIcon(xls);
                ui->CarsearchButton->setIcon(search);
                ui->CarsortLabel->setPixmap(sort);
                ui->Cartrashcan->setPixmap(trashcan);
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
            client c;
            c.setNIC(ui->nicEdit->text());
            c.setFirstName(ui->fnameEdit->text());
            c.setLastName(ui->lnameEdit->text());
            c.setEmail(ui->emailEdit->text());
            c.setPhone(ui->pnbEdit->text());
            c.setCredit(ui->creditEdit->text());
            history h(c.getNIC(),c.getFirstName(),c.getLastName(), c.getEmail(), c.getPhone(), c.getCredit(), "");
            h.saveDeleteclient();
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
            history h(c.getNIC(),c.getFirstName(),c.getLastName(), c.getEmail(), c.getPhone(), c.getCredit(), "");
            h.saveUpdateclient(c.getNIC(),c.getFirstName(),c.getLastName(), c.getEmail(), c.getPhone(), c.getCredit(), "");
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

void MainWindow::on_historyButton_clicked()
{
    QDesktopServices::openUrl(QUrl(tr("file:///C:/Users/Skander/Documents/Client1/history.txt")));
}

void MainWindow::updateHistoryEdit()
{
    QFile file("C:/Users/Skander/Documents/Client1/history.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Failed to open file";
        return;
    }

    QByteArray fileData(reinterpret_cast<const char*>(file.map(0, file.size())), file.size());
    QString lastNonEmptyLine;
    if (!fileData.isEmpty())
    {
        const char *data = fileData.constData() + fileData.size() - 1;
        while (data >= fileData.constData() && (*data == '\n' || *data == '\r'))
        {
            --data;
        }
        const char *lineEnd = data + 1;
        while (data >= fileData.constData() && *data != '\n' && *data != '\r')
        {
            --data;
        }
        const char *lineStart = data + 1;
        lastNonEmptyLine = QString::fromUtf8(lineStart, lineEnd - lineStart);
    }
    // Check if the last non-empty line has changed
    if (lastNonEmptyLine != ui->historyEdit->toPlainText())
    {
        ui->historyEdit->setPlainText(lastNonEmptyLine.trimmed());
    }

    // Close the file
    file.close();

}

void MainWindow::updateChart()
{

        QPieSeries *series = new QPieSeries();

        series->append("0", Etmp.count_credit("0"));
        series->append("100", Etmp.count_credit("100"));
        series->append("200", Etmp.count_credit("200"));
        series->append("300", Etmp.count_credit("300"));
        series->append("400", Etmp.count_credit("400"));
        series->append("500", Etmp.count_credit("500"));

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

void MainWindow::process_data(QByteArray data)
{
    nicKey = QString::fromUtf8(data).trimmed(); // convert data to QString and remove any leading/trailing whitespace
    qDebug() << "Received nicKey from Arduino: " << nicKey;
    a.get_client_info(nicKey);
}

void MainWindow::update_data(QByteArray data)
{
    QString credit = QString::fromUtf8(data).trimmed();
    qDebug() << "NICKEY: "<< nicKey;
    qDebug() << "Received credit from Arduino: " << credit;
    bool test = a.update_credit(nicKey, credit);
    if (test)
    {
        ui->tableView->setModel(Etmp.Read());
        QMessageBox::information(nullptr,QObject::tr(" OK"),
                                 QObject::tr("Update done\n"
                                             "Click Cancel to exit."),QMessageBox::Cancel);

    }
}

//####################################################CAR MANAGEMENT WINDOW#################################################################################
void MainWindow::on_CaraddButton_clicked()
{
    car c;
    c.setlc(ui->CarlcEdit->text());
    c.setbrand(ui->CarbrandEdit->text());
    c.setbatterycap(ui->CarbatteryEdit->text());
    c.setclient_id(ui->CarclientEdit->text());
    c.sethp(ui->CarhpEdit->text());
    c.settype(ui->CartypeEdit->text());
    c.setimagepath(ui->Carimagepath->text());

       bool test=c.Create(); // insert the object into the databse Student table
                             // and et the returned value of query.exec()

       if(test) // if the query is executed  ==> QMessageBox::information
       {
           // Refresh
           ui->CartableView->setModel(Ctmp.Read());

           QMessageBox::information(nullptr, QObject::tr("OK"),
                       QObject::tr("insert done \n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);

       }
       else // if the query is not executed  ==> QMessageBox::critical
           QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                       QObject::tr("insert failed.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_CardeleteButton_clicked()
{
    QString licence_plate = ui->CardeleteEdit->text();
        bool test=Ctmp.Delete(licence_plate);

        if(test)
        {
            // Refresh (Actualiser)
            ui->CartableView->setModel(Ctmp.Read());

            QMessageBox::information(nullptr, QObject::tr("OK"),
                        QObject::tr("delete done\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

        }
        else
            QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                        QObject::tr("delete failed.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_CartableView_clicked(const QModelIndex &index)
{
    ui->CarlcEdit->setText(ui->CartableView->model()->data(ui->CartableView->model()->index(index.row(),0)).toString());
    ui->CarbrandEdit->setText(ui->CartableView->model()->data(ui->CartableView->model()->index(index.row(),1)).toString());
    ui->CarbatteryEdit->setText(ui->CartableView->model()->data(ui->CartableView->model()->index(index.row(),2)).toString());
    ui->CarclientEdit->setText(ui->CartableView->model()->data(ui->CartableView->model()->index(index.row(),3)).toString());
    ui->CarhpEdit->setText(ui->CartableView->model()->data(ui->CartableView->model()->index(index.row(),4)).toString());
    ui->CartypeEdit->setText(ui->CartableView->model()->data(ui->CartableView->model()->index(index.row(),5)).toString());
    ui->CardeleteEdit->setText(ui->CartableView->model()->data(ui->CartableView->model()->index(index.row(),0)).toString());
}

void MainWindow::on_CarEditButton_clicked()
{
    car c;
    c.setlc(ui->CarlcEdit->text());
    c.setbrand(ui->CarbrandEdit->text());
    c.setbatterycap(ui->CarbatteryEdit->text());
    c.setclient_id(ui->CarclientEdit->text());
    c.sethp(ui->CarhpEdit->text());
    c.settype(ui->CartypeEdit->text());
    c.setimagepath(ui->Carimagepath->text());

        bool test= c.update();
        if(test)
        {
            ui->CartableView->setModel(Ctmp.Read());
            QMessageBox::information(nullptr,QObject::tr(" OK"),
                                     QObject::tr("Update done\n"
                                                 "Click Cancel to exit."),QMessageBox::Cancel);


        }
        else
            QMessageBox::critical(nullptr,QObject::tr("Not OK"),
                                     QObject::tr("Update failed\n"
                                                 "Click Cancel to exit."),QMessageBox::Cancel);

}

void MainWindow::on_CarsortButton_clicked()
{
    QString licence_plate="";
        QString brand="";
        QString battery="";
        QString client_id="";
        QString hp="";
        QString type="";
        QString imagepath="";

            car c(licence_plate,brand,battery,client_id,hp,type,imagepath);
            QString Option=ui->CarsortCombo->currentText();
            ui->CartableView->setModel(c.sort(Option));
}



void MainWindow::on_CarsearchButton_clicked()
{
    {
            QString licence_plate="";
            QString brand="";
            QString battery="";
            QString client_id="";
            QString hp="";
            QString type="";
            QString imagepath="";

                car c(licence_plate,brand,battery,client_id,hp,type,imagepath);
                QString Option=ui->CarcomboBox->currentText();
                QString text=ui->CarsearchEdit->text();
                ui->CartableView->setModel(c.search(Option,text));
    }

}


void MainWindow::on_CarpdfButton_clicked()
{
    {
        QPdfWriter pdf("C:/Users/Skander/Documents/Client1/PDF/listcars.pdf");

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

                      painter.drawText(3000,2700,"List of cars");

                      painter.setPen(Qt::black);
                      painter.setFont(QFont("Time New Roman", 15));
                      //painter.drawRect(100,100,9400,2500);
                      painter.drawRect(100,3300,9400,500);

                      painter.setFont(QFont("Montserrat SemiBold", 10));

                      painter.drawText(500,3600,"license plate");
                      painter.drawText(2000,3600,"brand");
                      painter.drawText(3500,3600,"battery cap");
                      painter.drawText(5000,3600,"client id");
                      painter.drawText(7000,3600,"horse power");
                      painter.drawText(8500,3600,"type");
                      painter.setFont(QFont("Montserrat", 10));
                      painter.drawRect(100,3300,9400,9000);

                      QSqlQuery query;
                      query.prepare("select * from car");
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
}

void MainWindow::on_CarxlsButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Exportation Excel"), qApp->applicationDirPath (),
                                                        tr("Files Excel (*.xls)"));
        if (fileName.isEmpty())
            return;

        ExportExcelObject obj(fileName, "mydata", ui->CartableView);

        // you can change the column order and
        // choose which colum to export
        obj.addField(0, "LICENCE_PLATE", "char(20)");
        obj.addField(1, "BRAND", "char(20)");
        obj.addField(2, "BATTERY", "char(20)");
        obj.addField(3, "CLIENT_ID", "char(20)");
        obj.addField(4, "HP", "char(20)");
        obj.addField(5, "TYPE", "char(20)");


        int retVal = obj.export2Excel();

        if( retVal > 0)
        {
            QMessageBox::information(this, tr("DONE!"),
                                     QString(tr("%1 Exported!")).arg(retVal)
                                     );
        }
}


void MainWindow::on_CarimageButton_clicked()
{
    QString imagePath = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));

           if (imagePath.isEmpty())
               return;

           ui->Carimagepath->setText(imagePath);
}


void MainWindow::update_label()
{
qDebug()<< "hi" ;
    data=A.read_from_arduino();

    if(data=="1")

       QMessageBox::information(nullptr, "Car Entered", "There is a car that entered the station.");
}

void MainWindow::on_CarDisplayButton_clicked()
{
    QSqlQuery query;
    query.exec("SELECT COUNT(*) FROM car");
    query.next();

    // Retrieve the result and format it as a string
    int count = query.value(0).toInt();
    QString countString = QString::number(count);
    qDebug() << "test";
    // Send the number of lines to the LCD
    QString data =  "there are " + countString+  " cars";
    A.write_to_arduino(data.toUtf8());
    qDebug() << data;
}

void MainWindow::display()
{

}
