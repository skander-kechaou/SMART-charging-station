#include "management.h"
#include "ui_management.h"
#include "client.h"
#include "car.h"
#include "chat.h"
#include "image.h"
#include "employee.h"
#include "login.h"
#include "map.h"
#include "qrcode.h"
#include "smtp.h"
#include "invoice.h"
#include "history.h"
#include "calculatrice.h"
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
#include <QFile>
#include <QLineEdit>
#include <QByteArray>
#include <QThread>
#include <QSerialPort>
#include <QStandardItemModel>
#include <QtSql/QSqlQueryModel>
#include <QtPrintSupport/QPrintDialog>
#include <QPrinter>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtSvg/QSvgRenderer>
#include <QTabWidget>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDesktopServices>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include<QPixmap>
#include <QPrintDialog>
#include<QPrinter>
#include <QTextTableCell>
#include <QMediaPlayer>
using namespace QtCharts;
using namespace qrcodegen;

Management::Management(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Management)
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
              connect(timer_p, &QTimer::timeout, this, &Management::updateHistoryEdit);
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
    ui->Date->setAlignment(Qt::AlignCenter);
    ui->time->setAlignment(Qt::AlignCenter);


    // Images and Icons
    QPixmap icon("C:/Users/Skander/Desktop/Final Integration/Integration/IMG/feedback.png");
    QPixmap client("C:/Users/Skander/Desktop/Final Integration/Integration/IMG/client.png");
    QIcon pdf("C:/Users/Skander/Desktop/Final Integration/Integration/IMG/pdf-file.png");
    QIcon search("C:/Users/Skander/Desktop/Final Integration/Integration/IMG/search-interface-symbol.png");
    QPixmap sort("C:/Users/Skander/Desktop/Final Integration/Integration/IMG/sort.png");
    QPixmap trashcan("C:/Users/Skander/Desktop/Final Integration/Integration/IMG/trash-can.png");
    QIcon refresh("C:/Users/Skander/Desktop/Final Integration/Integration/IMG/refresh-button.png");
    QIcon qrcode("C:/Users/Skander/Desktop/Final Integration/Integration/IMG/qr-code.png");
    QIcon history("C:/Users/Skander/Desktop/Final Integration/Integration/IMG/history.png");
    QIcon logout("C:/Users/Skander/Desktop/Final Integration/Integration/IMG/logout.png");
    ui->icon->setPixmap(icon);
    ui->client->setPixmap(client);
    ui->PDFButton->setIcon(pdf);
    ui->searchButton->setIcon(search);
    ui->sortLabel->setPixmap(sort);
    ui->trashcan->setPixmap(trashcan);
    ui->refreshButton->setIcon(refresh);
    ui->qrcodeButton->setIcon(qrcode);
    ui->historyButton->setIcon(history);
    ui->logout->setIcon(logout);

    // Statistics

    QPieSeries *ClientSeries = new QPieSeries();

        ClientSeries->append("0", Etmp.count_credit("0"));
        ClientSeries->append("100", Etmp.count_credit("100"));
        ClientSeries->append("200", Etmp.count_credit("200"));
        ClientSeries->append("300", Etmp.count_credit("300"));
        ClientSeries->append("400", Etmp.count_credit("400"));
        //ClientSeries->append("500", Etmp.count_credit("500"));


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
        Clientchartview->setFixedSize(QSize(380, 210));

      // HISTORY
        QFile file("C:/Users/Skander/Desktop/Final Integration/Integration/history.txt");
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
                            int i=0;
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
                            else if(final.at(i)=='@')
                            {
                                final.clear();
                                QMessageBox::information(nullptr, "Car Entered", "There is a car that entered the station.");
                            }

                        });
                break;
            case(1):qDebug() << "arduino is available but not connected to :" <<a.getarduino_port_name();
               break;
            case(-1):qDebug() << "arduino is not available";
            }

//##########################################CAR MANAGEMENT##############################################
                ui->CartableView->setModel(Ctmp.Read());
                ui->CartableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
                ui->CartableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
                ui->CartableView->setItemDelegateForColumn(6, new ImageDelegate(ui->CartableView));
                QIcon xls("C:/Users/Skander/Desktop/Final Integration/Integration/IMG/xls-file.png");
                QIcon image("C:/Users/Skander/Desktop/Final Integration/Integration/IMG/photo.png");
                QPixmap car("C:/Users/Skander/Desktop/Final Integration/Integration/IMG/auto.png");

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

                ui->car->setPixmap(car);
                ui->Caricon->setPixmap(icon);
                ui->CarpdfButton->setIcon(pdf);
                ui->CarimageButton->setIcon(image);
                ui->CarxlsButton->setIcon(xls);
                ui->CarsearchButton->setIcon(search);
                ui->CarsortLabel->setPixmap(sort);
                ui->Cartrashcan->setPixmap(trashcan);
                ui->refreshButtonCar->setIcon(refresh);
                ui->CarclientEdit->addItems(Ctmp.list());

//###########################################################EMPLOYEE MANAGEMENT#############################################################
                QPixmap employee("C:/Users/Skander/Desktop/Final Integration/Integration/IMG/independant.png");
                QRegularExpression rx("^[0-9a-zA-Z]+([0-9a-zA-Z]*[-._+])*[0-9a-zA-Z]+@[0-9a-zA-Z]+([-.][0-9a-zA-Z]+)*([0-9a-zA-Z]*[.])[a-zA-Z]{2,6}$",
                                                 QRegularExpression::CaseInsensitiveOption);
                ui->mailemp->setValidator(new QRegularExpressionValidator(rx, this));
                ui->phnemp -> setValidator (new QIntValidator(0, 999999, this));
                ui->salaryemp -> setValidator (new QIntValidator(0, 999999, this));
                ui->tableViewEmp->setModel(Ep.view());
                ui->tableViewEmp->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
                ui->IdStation->addItems(Ep.list());
                ui->employee->setPixmap(employee);
                ui->iconEmp->setPixmap(icon);
                ui->PDFemp->setIcon(pdf);
                ui->excelemp->setIcon(xls);
                ui->searchemp->setIcon(search);
                ui->sortLabel_2->setPixmap(sort);
                ui->trashcan_2->setPixmap(trashcan);
                ui->refreshButtonEmp->setIcon(refresh);
                           /* QPixmap outPixmap = QPixmap();
                                 outPixmap.loadFromData(acc.fetch_image(acc.username),"JPG");
                                outPixmap = outPixmap.scaledToWidth(ui->label_2->width(),Qt::SmoothTransformation);

                               ui->label_2->setPixmap(outPixmap.scaled(outPixmap.width(),outPixmap.height(),Qt::KeepAspectRatio));
                            */

//###########################################################STATION MANAGEMENT#############################################################
                QPixmap station("C:/Users/Skander/Desktop/Final Integration/Integration/IMG/ev.png");
                QPixmap maps("C:/Users/Skander/Desktop/Final Integration/Integration/IMG/google-maps.png");
                ui->tableViewStat->setModel(stat.Read());
                ui->tableViewStat->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
                ui->stationpic->setPixmap(station);
                ui->icon_4->setPixmap(icon);
                ui->pdfStat->setIcon(pdf);
                ui->sortStat->setPixmap(sort);
                ui->trashcanS->setPixmap(trashcan);
                ui->map->setIcon(maps);
                ui->searchStat->setIcon(search);
                ui->refreshButtonStat->setIcon(refresh);
                QPieSeries *seriesStat = new QPieSeries();

                    seriesStat->append("Tunis", stat.count_location("tunis"));
                    seriesStat->append("Nabeul", stat.count_location("nabeul"));
                    seriesStat->append("Sousse", stat.count_location("sousse"));


                    QChart *chartStat = new QChart();
                        chartStat->addSeries(seriesStat);
                        chartStat->setAcceptHoverEvents(true);
                        chartStat->setPreferredSize(QSize(300, 300));
                        chartStat->setMargins(QMargins(0, 0, 0, 0));
                        chartStat->setBackgroundBrush(QBrush(QColor(182, 215, 168)));
                        QChartView *chartviewStat = new QChartView(chartStat);
                        chartviewStat->setParent(ui->chartStat);
                        chartviewStat->setRubberBand(QChartView::RectangleRubberBand);
                        chartviewStat->setRenderHint(QPainter::Antialiasing);
                        chartviewStat->setInteractive(true);
                        chartviewStat->setContentsMargins(0, 0, 0, 0);
                        chartviewStat->setFixedSize(QSize(300, 300));

//###########################################################INVOICE MANAGEMENT#############################################################
                        QPixmap invoice("C:/Users/Skander/Desktop/Final Integration/Integration/IMG/invoice.png");
                        QIcon calculator("C:/Users/Skander/Desktop/Final Integration/Integration/IMG/calculator.png");
                        ui->tableViewInv->setModel(inv.Read());
                        ui->pdfInv->setIcon(pdf);
                        ui->iconInv->setPixmap(icon);
                        ui->CalculatorButton->setIcon(calculator);
                        ui->InvPic->setPixmap(invoice);
                        ui->searchButtonInv->setIcon(search);
                        ui->sortInv->setPixmap(sort);
                        ui->refreshButtonInv->setIcon(refresh);
                        ui->licenseplInvEdit->addItems(inv.listLicense());
                        ui->NICEditInv->addItems(inv.listNIC());
                        ui->idstatEdit->addItems(inv.listStation());
                        ui->tableViewInv->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
                        ui->tableViewInv->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
                        QPieSeries *seriesInv = new QPieSeries();
                        seriesInv->append("0", inv.count_stat("0"));
                            seriesInv->append("100", inv.count_stat("100"));
                            seriesInv->append("200", inv.count_stat("200"));
                            seriesInv->append("300", inv.count_stat("300"));
                        QChart *chartInv = new QChart();
                            chartInv->addSeries(seriesInv);
                            chartInv->setAcceptHoverEvents(true);
                            chartInv->setPreferredSize(QSize(300, 300));
                            chartInv->setMargins(QMargins(0, 0, 0, 0));
                            chartInv->setBackgroundBrush(QBrush(QColor(182, 215, 168)));
                            QChartView *chartviewInv = new QChartView(chartInv);
                            chartviewInv->setParent(ui->chartInv);
                            chartviewInv->setRubberBand(QChartView::RectangleRubberBand);
                            chartviewInv->setRenderHint(QPainter::Antialiasing);
                            chartviewInv->setInteractive(true);
                            chartviewInv->setContentsMargins(0, 0, 0, 0);
                            chartviewInv->setFixedSize(QSize(300, 300));
                            //for email tab
                            connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
                            connect(ui->browseBtn, SIGNAL(clicked()), this, SLOT(browse()));
}

Management::~Management()
{
    delete ui;
}

void Management::button_sound()
{
    QMediaPlayer *button =new QMediaPlayer();
    button->setMedia(QUrl("C:/Users/Skander/Desktop/Final Integration/Integration/app-button-click-sound.mp3"));
    button->setVolume(100);
    button->play();
}
//####################################################CLIENT MANAGEMENT WINDOW###############################################################################

void Management::on_addButton_clicked()
{
    button_sound();
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

void Management::on_deleteButton_clicked()
{

    button_sound();
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

void Management::on_tableView_clicked(const QModelIndex &index)
{
    ui->nicEdit->setText(ui->tableView->model()->data(ui->tableView->model()->index(index.row(),0)).toString());
    ui->fnameEdit->setText(ui->tableView->model()->data(ui->tableView->model()->index(index.row(),1)).toString());
    ui->lnameEdit->setText(ui->tableView->model()->data(ui->tableView->model()->index(index.row(),2)).toString());
    ui->pnbEdit->setText(ui->tableView->model()->data(ui->tableView->model()->index(index.row(),3)).toString());
    ui->emailEdit->setText(ui->tableView->model()->data(ui->tableView->model()->index(index.row(),4)).toString());
    ui->creditEdit->setText(ui->tableView->model()->data(ui->tableView->model()->index(index.row(),5)).toString());
    ui->deleteEdit->setText(ui->tableView->model()->data(ui->tableView->model()->index(index.row(),0)).toString());
}

void Management::on_EditButton_clicked()
{
    button_sound();
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

void Management::on_PDFButton_clicked()
{
    button_sound();
    QPdfWriter pdf("C:/Users/Skander/Desktop/Final Integration/Integration/PDF/list_clients.pdf");

           QPainter painter(&pdf);
           int i = 4100;
          const QImage image("C:/Users/Skander/Desktop/Final Integration/Integration/IMG/logo.png");
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

                  QString filePath = "C:/Users/Skander/Desktop/Final Integration/Integration/PDF/list_clients.pdf";
                  QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));

}


void Management::on_refreshButton_clicked()
{
    button_sound();
    ui->nicEdit->setText("");
    ui->fnameEdit->setText("");
    ui->lnameEdit->setText("");
    ui->pnbEdit->setText("");
    ui->emailEdit->setText("");
    ui->creditEdit->setText("");
}

void Management::on_sortButton_clicked()
{
    button_sound();
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

void Management::on_searchButton_clicked()
{
    button_sound();
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


void Management::on_qrcodeButton_clicked()
{
    button_sound();
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

void Management::showTime()
{
    ui->time->setText(QTime::currentTime().toString("hh:mm:ss"));
}

void Management::on_historyButton_clicked()
{
    button_sound();
    QDesktopServices::openUrl(QUrl(tr("file:///C:/Users/Skander/Desktop/Final Integration/Integration/history.txt")));
}

void Management::updateHistoryEdit()
{
    QFile file("C:/Users/Skander/Desktop/Final Integration/Integration/history.txt");
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

void Management::process_data(QByteArray data)
{
    nicKey = QString::fromUtf8(data).trimmed(); // convert data to QString and remove any leading/trailing whitespace
    qDebug() << "Received nicKey from Arduino: " << nicKey;
    a.get_client_info(nicKey);
}

void Management::update_data(QByteArray data)
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
void Management::on_CaraddButton_clicked()
{
    button_sound();
    car c;
    c.setlc(ui->CarlcEdit->text());
    c.setbrand(ui->CarbrandEdit->text());
    c.setbatterycap(ui->CarbatteryEdit->text());
    c.setclient_id(ui->CarclientEdit->currentText());
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

void Management::on_refreshButtonCar_clicked()
{
    button_sound();
    ui->CarhpEdit->clear();
    ui->CarlcEdit->clear();
    ui->CartypeEdit->clear();
    ui->CarbrandEdit->clear();
    ui->CarbatteryEdit->clear();
    ui->Carimagepath->clear();
}

void Management::on_CardeleteButton_clicked()
{
    button_sound();
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

void Management::on_CartableView_clicked(const QModelIndex &index)
{
    ui->CarlcEdit->setText(ui->CartableView->model()->data(ui->CartableView->model()->index(index.row(),0)).toString());
    ui->CarbrandEdit->setText(ui->CartableView->model()->data(ui->CartableView->model()->index(index.row(),1)).toString());
    ui->CarbatteryEdit->setText(ui->CartableView->model()->data(ui->CartableView->model()->index(index.row(),2)).toString());
    ui->CarclientEdit->setCurrentText(ui->CartableView->model()->data(ui->CartableView->model()->index(index.row(),3)).toString());
    ui->CarhpEdit->setText(ui->CartableView->model()->data(ui->CartableView->model()->index(index.row(),4)).toString());
    ui->CartypeEdit->setText(ui->CartableView->model()->data(ui->CartableView->model()->index(index.row(),5)).toString());
    ui->CardeleteEdit->setText(ui->CartableView->model()->data(ui->CartableView->model()->index(index.row(),0)).toString());
}

void Management::on_CarEditButton_clicked()
{
    button_sound();
    car c;
    c.setlc(ui->CarlcEdit->text());
    c.setbrand(ui->CarbrandEdit->text());
    c.setbatterycap(ui->CarbatteryEdit->text());
    c.setclient_id(ui->CarclientEdit->currentText());
    c.sethp(ui->CarhpEdit->text());
    c.settype(ui->CartypeEdit->text());
    c.setimagepath(ui->Carimagepath->text());

        bool test= c.update();
        if(test)
        {
            ui->CartableView->setModel(Ctmp.Read());
            ui->CarclientEdit->clear();
            ui->CarclientEdit->addItems(Ctmp.list());
            QMessageBox::information(nullptr,QObject::tr(" OK"),
                                     QObject::tr("Update done\n"
                                                 "Click Cancel to exit."),QMessageBox::Cancel);


        }
        else
            QMessageBox::critical(nullptr,QObject::tr("Not OK"),
                                     QObject::tr("Update failed\n"
                                                 "Click Cancel to exit."),QMessageBox::Cancel);

}

void Management::on_CarsortButton_clicked()
{
    button_sound();
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



void Management::on_CarsearchButton_clicked()
{
    button_sound();
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


void Management::on_CarpdfButton_clicked()
{
    button_sound();
        QPdfWriter pdf("C:/Users/Skander/Desktop/Final Integration/Integration/PDF/listcars.pdf");

               QPainter painter(&pdf);
               int i = 4100;
               const QImage image("C:/Users/Skander/Desktop/Final Integration/Integration/IMG/logo.png");
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

void Management::on_CarxlsButton_clicked()
{
    button_sound();
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


void Management::on_CarimageButton_clicked()
{
    button_sound();
    QString imagePath = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));

           if (imagePath.isEmpty())
               return;

           ui->Carimagepath->setText(imagePath);
}


void Management::update_label()
{
    /*qDebug()<< "hi" ;
    data=a.read_from_arduino();

    if(data=="1")

       QMessageBox::information(nullptr, "Car Entered", "There is a car that entered the station.");*/
}

void Management::on_CarDisplayButton_clicked()
{
    button_sound();
    QSqlQuery query;
    query.exec("SELECT COUNT(*) FROM car");
    query.next();

    // Retrieve the result and format it as a string
    int count = query.value(0).toInt();
    QString countString = QString::number(count);
    qDebug() << "test";
    // Send the number of lines to the LCD
    QString data =  "there are " + countString+  " cars";
    a.write_to_arduino(data.toUtf8());
    qDebug() << data;
}

void Management::display()
{

}

//####################################################EMPLOYEE MANAGEMENT WINDOW############################################################################

void Management::on_addemp_clicked()
{
    button_sound();
        QString  ID=ui->IDEMP->text();
        QString fname=ui->fnamemp->text();
        QString lname=ui->lnamemp->text();
        QString mail=ui->mailemp->text();
        int  Phone=ui->phnemp->text().toInt();
        QString role=ui->rolemp->text();
        float  salary=ui->salaryemp->text().toFloat();
        QString idstat=ui->IdStation->currentText();
    Employee  emp(  ID, mail,fname , Phone,  lname, salary, idstat, role);


        bool test=emp.addEmp();
        if(test)
        {
            ui->tableViewEmp->setModel(Ep.view());
            QMessageBox::information(nullptr, QObject::tr("ok"),
                        QObject::tr("insert done\n"
                                    "Click ok to exit."), QMessageBox::Ok);

              ui->IDEMP->setText("");
              ui->fnamemp->setText("");
              ui->lnamemp->setText("");
              ui->mailemp->setText("");
              ui->phnemp->setText("");
              ui->rolemp->setText("");
              ui->salaryemp->setText("");



    }
        else
            QMessageBox::critical(nullptr, QObject::tr("not ok"),
                        QObject::tr("ajout non effectue\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

}

void Management::on_refreshButtonEmp_clicked()
{
    button_sound();
    ui->IDEMP->clear();
    ui->fnamemp->clear();
    ui->lnamemp->clear();
    ui->phnemp->clear();
    ui->mailemp->clear();
    ui->salaryemp->clear();
    ui->rolemp->clear();

}

void Management::on_tableViewEmp_clicked(const QModelIndex &index)
{
       ui->IDEMP->setText(ui->tableViewEmp->model()->data(ui->tableViewEmp->model()->index(index.row(),0)).toString());
       ui->mailemp->setText(ui->tableViewEmp->model()->data(ui->tableViewEmp->model()->index(index.row(),1)).toString());
       ui->fnamemp->setText(ui->tableViewEmp->model()->data(ui->tableViewEmp->model()->index(index.row(),2)).toString());
       ui->phnemp->setText(ui->tableViewEmp->model()->data(ui->tableViewEmp->model()->index(index.row(),3)).toString());
       ui->lnamemp->setText(ui->tableViewEmp->model()->data(ui->tableViewEmp->model()->index(index.row(),4)).toString());
       ui->salaryemp->setText(ui->tableViewEmp->model()->data(ui->tableViewEmp->model()->index(index.row(),5)).toString());
       ui->rolemp->setText(ui->tableViewEmp->model()->data(ui->tableViewEmp->model()->index(index.row(),7)).toString());
}


void Management::on_buttonDeleteemp_clicked()
{
    button_sound();
         QString ID=ui->IDEMP->text();
        bool test =Ep.deleteEmp(ID);
        if(test)
        {    ui->tableViewEmp->setModel(Ep.view());

            QMessageBox::information(nullptr, QObject::tr("ok"),
                        QObject::tr("deleted successfully \n"
                                    "Click Cancel to exit."), QMessageBox::Ok);

                 ui->IDEMP->setText("");

    }
        else
            QMessageBox::critical(nullptr, QObject::tr("not ok"),
                        QObject::tr("failed to delete\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);



}

void Management::on_sortemp_clicked()
{

            button_sound();
            QString choice=ui->comboBox_tri_5->currentText();
            if (choice=="Sort By First Name")
            {
                ui->tableViewEmp->setModel(Ep.sort_name());
                ui->tableViewEmp->setModel(Ep.view());
                bool test=Ep.sort_name();//sort  by fname
                if (test)
                {

            ui->tableViewEmp->setModel(Ep.sort_name());
                    QMessageBox::information(nullptr,QObject::tr("ok"),
                                             QObject::tr("sort done sucessfully\n"
                                                         "Click Cancel to exist ."),QMessageBox::Cancel);

                }
                else
                      QMessageBox::critical(nullptr, QObject::tr("no"),
                                  QObject::tr("sort failed.\n"
                                              "Click Cancel to exit."), QMessageBox::Cancel);
            }
            if (choice=="Sort By Id")
                    {
                        ui->tableViewEmp->setModel(Ep.sort_ID());
                        ui->tableViewEmp->setModel(Ep.view());
                        bool test=Ep.sort_ID();//sort by  ID
                        if (test)
                        {

                    ui->tableViewEmp->setModel(Ep.sort_ID());
                            QMessageBox::information(nullptr,QObject::tr("ok"),
                                                     QObject::tr("sort done sucessfully\n"
                                                                 "Click Cancel to exist ."),QMessageBox::Cancel);

                        }
                        else
                              QMessageBox::critical(nullptr, QObject::tr("nonnnn"),
                                          QObject::tr("sort failed.\n"
                                                      "Click Cancel to exit."), QMessageBox::Cancel);
                    }
            if (choice=="Sort By Role")
                    {
                        ui->tableViewEmp->setModel(Ep.sort_Role());
                        ui->tableViewEmp->setModel(Ep.view());
                        bool test=Ep.sort_Role();//sort by role
                        if (test)
                        {

                    ui->tableViewEmp->setModel(Ep.sort_Role());
                            QMessageBox::information(nullptr,QObject::tr("ok"),
                                                     QObject::tr("sort done sucessfully \n"
                                                                 "Click Cancel to exist ."),QMessageBox::Cancel);

                        }
                        else
                              QMessageBox::critical(nullptr, QObject::tr("nonnnn"),
                                          QObject::tr("sort failed.\n"
                                                      "Click Cancel to exit."), QMessageBox::Cancel);
                    }
}

void Management::on_searchemp_clicked()
{
    button_sound();
    QString choice=ui->comboBox_search_5->currentText();

          if (choice=="Search By First Name")
          {
              QString fname = ui->search_editEmp->text();
              ui->tableViewEmp->setModel(Ep.searchname(fname));
          }
          if (choice=="Search By Id")
          {
              QString ID= ui->search_editEmp->text();
              ui->tableViewEmp->setModel(Ep.searchID(ID));
          }

          if (choice=="Search By Role")
          {
              QString role = ui->search_editEmp->text();
              ui->tableViewEmp->setModel(Ep.searchRole(role));
          }
          ui->search_editEmp->setText("");
}



void Management::on_PDFemp_clicked()
{
    button_sound();
    QString strStream;
                                       QTextStream out(&strStream);

                                       const int rowCount = ui->tableViewEmp->model()->rowCount();
                                       const int columnCount = ui->tableViewEmp->model()->columnCount();

                                       out <<  "<html>\n"
                                           "<head>\n"
                                           "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                                           <<  QString("<title>%1</title>\n").arg("strTitle")
                                           <<  "</head>\n"
                                           "<body bgcolor=#ffffff link=#5000A0>\n"

                                          //     "<align='right'> " << datefich << "</align>"
                                           "<center> <H1>list of employees </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

                                       // headers
                                       out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
                                       for (int column = 0; column < columnCount; column++)
                                           if (!ui->tableViewEmp->isColumnHidden(column))
                                               out << QString("<th>%1</th>").arg(ui->tableViewEmp->model()->headerData(column, Qt::Horizontal).toString());
                                       out << "</tr></thead>\n";

                                       // data table
                                       for (int row = 0; row < rowCount; row++) {
                                           out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                                           for (int column = 0; column < columnCount; column++) {
                                               if (!ui->tableViewEmp->isColumnHidden(column)) {
                                                   QString data = ui->tableViewEmp->model()->data(ui->tableViewEmp->model()->index(row, column)).toString().simplified();
                                                   out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                               }
                                           }
                                           out << "</tr>\n";
                                       }
                                       out <<  "</table> </center>\n"
                                           "</body>\n"
                                           "</html>\n";

                                 QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Saved as PDF", QString(), "*.pdf");
                                   if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

                                  QPrinter printer (QPrinter::PrinterResolution);
                                   printer.setOutputFormat(QPrinter::PdfFormat);
                                  printer.setPaperSize(QPrinter::A4);
                                 printer.setOutputFileName(fileName);

                                  QTextDocument doc;
                                   doc.setHtml(strStream);
                                   doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
                                   doc.print(&printer);

   }

void Management::on_editemp_clicked()
{
    button_sound();
    QString  ID=ui->IDEMP->text();
    QString fname=ui->fnamemp->text();
    QString lname=ui->lnamemp->text();
    QString mail=ui->mailemp->text();
    int  Phone=ui->phnemp->text().toInt();
    QString role=ui->rolemp->text();
    float  salary=ui->salaryemp->text().toFloat();
    QString idstat=ui->IdStation->currentText();

            Employee  emp(ID, mail,fname , Phone,  lname, salary, idstat, role);
            bool test=emp.modify();
            if(test)
            {    ui->tableViewEmp->setModel(Ep.view());
                   ui->IdStation->clear();
         ui->IdStation->addItems(emp.list());
                QMessageBox::information(nullptr, QObject::tr("ok"),
                            QObject::tr("updated successfully \n"
                                        "Click Cancel to exit."), QMessageBox::Ok);

            }
            else
                QMessageBox::critical(nullptr, QObject::tr("not ok"),
                            QObject::tr("failed to update\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
}

void Management::on_statemp_clicked()
{
    button_sound();
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("select * from EMPLOYEE where SALARY < 1000.0 ");
        float salaire=model->rowCount();
        model->setQuery("select * from EMPLOYEE where  SALARY BETWEEN 1000.0 AND 2000.0 ");
        float salairee=model->rowCount();
        model->setQuery("select * from EMPLOYEE where SALARY > 2000.0 ");
        float salaireee=model->rowCount();
        float total=salaire+salairee+salaireee;
        QString a=QString("1000.0>salaries :"+QString::number((salaire*100)/total,'f',2)+"%" );
        QString b=QString("1000.0<salaries<2000.0 :"+QString::number((salairee*100)/total,'f',2)+"%" );
        QString c=QString("salaries>2000.0 "+QString::number((salaireee*100)/total,'f',2)+"%" );
        QPieSeries *seriesEmp = new QPieSeries();
        seriesEmp->append(a,salaire);
        seriesEmp->append(b,salairee);
        seriesEmp->append(c,salaireee);
        if (salaire!=0)
        {QPieSlice *slice = seriesEmp->slices().at(0);
            slice->setLabelVisible();
            slice->setPen(QPen());}
        if ( salairee!=0)
        {
            // Add label, explode and define brush for 2nd slice
            QPieSlice *slice1 = seriesEmp->slices().at(1);
            slice1->setLabelVisible();
        }
        if(salaireee!=0)
        {
            // Add labels to rest of slices
            QPieSlice *slice2 = seriesEmp->slices().at(2);
            slice2->setLabelVisible();
        }
        // Create the chart widget
        QChart *chartEmp = new QChart();
        // Add data to chart with title and hide legend
        chartEmp->addSeries(seriesEmp);
        chartEmp->setTitle("Percentage by salary of "+ QString::number(total)+" employees");

          //change the color of the background
         QLinearGradient backgroundGradient;

           backgroundGradient.setColorAt(0.0, QRgb(0xb6d7a8));
           backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
           chartEmp->setBackgroundBrush(backgroundGradient);
           chartEmp->legend()->hide();

        // Used to display the chart

        QChartView *chartViewEmp = new QChartView(chartEmp);
         chartViewEmp->setRenderHint(QPainter::Antialiasing);
         chartViewEmp->resize(600,200);
         chartViewEmp->setParent(ui->chartemp);
         chartViewEmp->show();
}

void Management::on_excelemp_clicked()
{
    button_sound();
    QTableView *table;
          table = ui->tableViewEmp;

          QDateTime date = QDateTime::currentDateTime();
          QString formattedTime = date.toString("dd.MM.yyyy hh:mm:ss");
          QString d="excel/list "+formattedTime;
          QString filters("xls files (*.xls);;All files (*.*)");
          QString defaultFilter("xls files (*.xls)");
          QString fileName = QFileDialog::getSaveFileName(0, "Save file",d,
                             filters, &defaultFilter);
          QFile file(fileName);
          QAbstractItemModel *model =  table->model();
          if (file.open(QFile::WriteOnly | QFile::Truncate)) {
              QTextStream data(&file);
              QStringList strList;
              for (int i = 0; i < model->columnCount(); i++) {
                  if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                     { strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
   strList.append("\t");}
                  else
                      strList.append("");
              }
              data << strList.join("") << "\n";
              for (int i = 0; i < model->rowCount(); i++) {
                  strList.clear();
                  for (int j = 0; j < model->columnCount(); j++) {

                      if (model->data(model->index(i, j)).toString().length() > 0)
                         { strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                      strList.append("\t");}
                      else
                          strList.append("");

                  }
                  data << strList.join("") + "\n";
              }
              file.close();



          }
}
void Management::on_pushButton_4_clicked()
{
    button_sound();
        Chat* w=new Chat(this);
        w->show();


}


void Management::on_logout_clicked()
{
    button_sound();
    Login *l;
    l->show();
}

//####################################################STATION MANAGEMENT WINDOW###############################################################################
void Management::on_addButtonStat_clicked()
{
    button_sound();
    // Get information entered in the 3 fields
    QString id_stat=ui->IDstatEdit->text();
    int capacity =ui->capacityStatEdit->text().toInt();
    QString nameStat = ui->NamestatEdit->text();
    QString locaStat = ui->LocationStatEdit->text();
    int nb_emp = ui->nb_empedit->text().toInt();
     QString availability = ui->availedit->text();

    station s(id_stat,nameStat,locaStat,capacity ,nb_emp,availability); // object instantiation
                              // using information entered in the interface

    bool test=s.Create(); // insert the object into the databse Student table
                          // and et the returned value of query.exec()

    if(test) // if the query is executed  ==> QMessageBox::information
    {
        // Refresh
        ui->tableViewStat->setModel(stat.Read());

        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("insert done \n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else // if the query is not executed  ==> QMessageBox::critical
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                    QObject::tr("insert failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

 }


void Management::on_editButtonStat_clicked()
{
    button_sound();
    QString id_stat=ui->IDstatEdit->text();
    int capacity =ui->capacityStatEdit->text().toInt();
    QString nameStat = ui->NamestatEdit->text();
    QString locaStat = ui->LocationStatEdit->text();
    int nb_emp = ui->nb_empedit->text().toInt();
    QString availability = ui->availedit->text();

    station s(id_stat,nameStat,locaStat,capacity ,nb_emp,availability); // object instantiation
                              // using information entered in the interface

    bool test=s.update(); // insert the object into the databse Student table
                          // and et the returned value of query.exec()

    if(test) // if the query is executed  ==> QMessageBox::information
    {
        // Refresh
        ui->tableViewStat->setModel(stat.Read());

        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("insert done \n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else // if the query is not executed  ==> QMessageBox::critical
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                    QObject::tr("insert failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);


}

void Management::on_tableViewStat_clicked(const QModelIndex &index)
{
        ui->IDstatEdit->setText(ui->tableViewStat->model()->data(ui->tableViewStat->model()->index(index.row(),0)).toString());
        ui->NamestatEdit->setText(ui->tableViewStat->model()->data(ui->tableViewStat->model()->index(index.row(),1)).toString());
        ui->LocationStatEdit->setText(ui->tableViewStat->model()->data(ui->tableViewStat->model()->index(index.row(),2)).toString());
        ui->capacityStatEdit->setText(ui->tableViewStat->model()->data(ui->tableViewStat->model()->index(index.row(),3)).toString());
        ui->nb_empedit->setText(ui->tableViewStat->model()->data(ui->tableViewStat->model()->index(index.row(),4)).toString());
        ui->availedit->setText(ui->tableViewStat->model()->data(ui->tableViewStat->model()->index(index.row(),5)).toString());
}

void Management::on_deleteButtonStat_clicked()
{
    button_sound();
    QString id_stat=ui->IDstatEdit->text();
    bool test=stat.Delete(id_stat);

    if(test)
    {
        // Refresh (Actualiser)
        ui->tableViewStat->setModel(stat.Read());

        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("delete done\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                    QObject::tr("delete failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}

void Management::on_sortbuttonStat_clicked()
{
    button_sound();
        QString id_stat="";
        QString name_stat="";
        QString location_stat="";
        int capacity=0;
        int nb_emp=0;
        QString availability="";

            station s(id_stat,name_stat,location_stat,capacity,nb_emp,availability);
            QString Option=ui->sortComboStat->currentText();
            ui->tableViewStat->setModel(s.sort(Option));
}

void Management::on_searchStat_clicked()
{
    button_sound();
    QString id_stat="";
    QString name_stat="";
    QString location_stat="";
    int capacity=0;
    int nb_emp=0;
    QString availability="";

            station s(id_stat,name_stat,location_stat,capacity,nb_emp,availability);
            QString Option=ui->searchBoxStat->currentText();
            QString text=ui->searchEdit_2->text();
            ui->tableViewStat->setModel(s.search(Option,text));
}

void Management::on_pdfStat_clicked()
{
        button_sound();
            QPdfWriter pdf("C:/Users/Skander/Desktop/Final Integration/Integration/PDF/list_station.pdf");

                   QPainter painter(&pdf);
                   int i = 4100;
                   const QImage image("C:/Users/Skander/Desktop/Final Integration/Integration/IMG/logo.png");
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

                          painter.drawText(3000,2700,"List of Stations");

                          painter.setPen(Qt::black);
                          painter.setFont(QFont("Time New Roman", 15));
                          //painter.drawRect(100,100,9400,2500);
                          painter.drawRect(100,3300,9400,500);

                          painter.setFont(QFont("Montserrat SemiBold", 10));

                          painter.drawText(500,3600," ID Station");
                          painter.drawText(2000,3600,"Name");
                          painter.drawText(3500,3600,"Location");
                          painter.drawText(5000,3600,"Capacity");
                          painter.drawText(7000,3600,"Nb. Emp");
                          painter.drawText(8500,3600,"Availability");
                          painter.setFont(QFont("Montserrat", 10));
                          painter.drawRect(100,3300,9400,9000);

                          QSqlQuery query;
                          query.prepare("select * from station");
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

// map

void Management::on_map_clicked()
{
    button_sound();
    map m;
    m.exec();

}

void Management::on_refreshButtonStat_clicked()
{
    button_sound();
    ui->IDstatEdit->clear();
    ui->nb_empedit->clear();
    ui->availedit->clear();
    ui->LocationStatEdit->clear();
    ui->NamestatEdit->clear();
    ui->capacityStatEdit->clear();
}

//####################################################INVOICE MANAGEMENT WINDOW###############################################################################
void Management::on_AddButtonInv_clicked()
{
    button_sound();
    invoice i;
    i.setreference(ui->referenceEdit->text());
    i.setNIC(ui->NICEditInv->currentText());
    i.setidstat(ui->idstatEdit->currentText());
    i.setlicensepl(ui->licenseplInvEdit->currentText());
    i.setcost(ui->costEdit->text().toInt());
    QString date=ui->date_invEdit->text();
    QDate date_inv=QDate::fromString(date,  "yyyy-MM-dd");
    i.setdate_inv(date_inv);

       bool test=i.Create(); // insert the object into the databse Student table
                             // and et the returned value of query.exec()

       if(test) // if the query is executed  ==> QMessageBox::information
       {
           // Refresh
           ui->tableViewInv->setModel(inv.Read());

           QMessageBox::information(nullptr, QObject::tr("OK"),
                       QObject::tr("insert done \n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);

       }
       else // if the query is not executed  ==> QMessageBox::critical
           QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                       QObject::tr("insert failed.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);
}



void Management::on_EditButtonInv_clicked()
{
    button_sound();
    invoice i;
    i.setreference(ui->referenceEdit->text());
    i.setNIC(ui->NICEditInv->currentText());
    i.setidstat(ui->idstatEdit->currentText());
    i.setlicensepl(ui->licenseplInvEdit->currentText());
    i.setcost(ui->costEdit->text().toInt());
    QString date=ui->date_invEdit->text();
    i.setdate_inv(QDate::fromString(date, "yyyy/MM/dd"));

       bool test=i.update(); // insert the object into the databse Student table
                             // and et the returned value of query.exec()

       if(test) // if the query is executed  ==> QMessageBox::information
       {
           // Refresh
           ui->licenseplInvEdit->clear();
           ui->NICEditInv->clear();
           ui->idstatEdit->clear();
           ui->licenseplInvEdit->addItems(inv.listLicense());
           ui->NICEditInv->addItems(inv.listNIC());
           ui->idstatEdit->addItems(inv.listStation());
           ui->tableViewInv->setModel(inv.Read());

           QMessageBox::information(nullptr, QObject::tr("OK"),
                       QObject::tr("update done \n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);

       }
       else // if the query is not executed  ==> QMessageBox::critical
           QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                       QObject::tr("update failed.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);
}

void Management::on_tableViewInv_clicked(const QModelIndex &index)
{
       ui->referenceEdit->setText(ui->tableViewInv->model()->data(ui->tableViewInv->model()->index(index.row(),0)).toString());
       ui->date_invEdit->setText(ui->tableViewInv->model()->data(ui->tableViewInv->model()->index(index.row(),1)).toString());
       ui->NICEditInv->setCurrentText(ui->tableViewInv->model()->data(ui->tableViewInv->model()->index(index.row(),2)).toString());
       ui->costEdit->setText(ui->tableViewInv->model()->data(ui->tableViewInv->model()->index(index.row(),3)).toString());
       ui->idstatEdit->setCurrentText(ui->tableViewInv->model()->data(ui->tableViewInv->model()->index(index.row(),4)).toString());
       ui->licenseplInvEdit->setCurrentText(ui->tableViewInv->model()->data(ui->tableViewInv->model()->index(index.row(),5)).toString());
       QSqlQuery query;
       query.prepare ("select MAIL from client where NIC=:NIC" );

           // Creating variables
           QString NIC=ui->NICEditInv->currentText();
           query.bindValue(":NIC",NIC);
           if(query.exec())
           {
               if(query.next())
               {
                  QString email = query.value(0).toString();
                  ui->rcpt->setText(email);
               }
           }

}

void Management::on_deleteButtonInv_clicked()
{
    button_sound();
    QString ref = ui->referenceEdit->text();
           bool test=inv.Delete(ref);

           if(test)
           {
               // Refresh (Actualiser)
               ui->tableViewInv->setModel(inv.Read());

               QMessageBox::information(nullptr, QObject::tr("OK"),
                           QObject::tr("delete done\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);

           }
           else
               QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                           QObject::tr("delete failed.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
}

void Management::on_pdfInv_clicked()
{
    button_sound();
    QPdfWriter pdf("C:/Users/Skander/Desktop/Final Integration/Integration//PDF/listinvoice.pdf");

                  QPainter painter(&pdf);
                  int i = 4100;
                  const QImage image("C:/Users/Skander/Desktop/Final Integration/Integration//logo.png");
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

void Management::on_sortButtonInv_clicked()
{
    button_sound();
        QString reference="";
        QDate date_inv=QDate::currentDate();
        QString NIC="";
        int cost=0;
        QString idstat="";
        QString licensepl="";

            invoice i(reference,NIC,idstat,licensepl,cost, date_inv);
            QString Option=ui->comboBoxInv->currentText();
            ui->tableViewInv->setModel(i.sort(Option));
}



void Management::on_searchButtonInv_clicked()
{
    button_sound();
    QString reference="";
    QDate date_inv=QDate::currentDate();
    QString NIC="";
    int cost=0;
    QString idstat="";
    QString licensepl="";

        invoice i(reference,NIC,idstat,licensepl,cost, date_inv);
        QString Option=ui->searchBoxInv->currentText();
        QString text=ui->searchEditInv->text();
        ui->tableViewInv->setModel(i.search(Option,text));
}


void Management::on_CalculatorButton_clicked()
{
    button_sound();
    calculatrice c;
    c.exec();
}

//mailing
void Management::browse()
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
void Management::sendMail()
{
    smtp *smtpI = new smtp("arij.mahouechi@esprit.tn",ui->mail_pass->text(), "smtp.gmail.com");
    connect(smtpI, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    if( !files.isEmpty() )
        smtpI->sendMail("arij.mahouechi@esprit.tn", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText(), files );
    else
        smtpI->sendMail("arij.mahouechi@esprit.tn", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
}
void Management::mailSent(QString status)
{

    if(status == "Message sent")
        QMessageBox::warning( nullptr, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
    ui->rcpt->clear();
    ui->subject->clear();
    ui->file->clear();
    ui->msg->clear();
    ui->mail_pass->clear();
}

void Management::on_refreshButtonInv_clicked()
{
    button_sound();
    ui->costEdit->clear();
    ui->date_invEdit->clear();
    ui->referenceEdit->clear();
}
