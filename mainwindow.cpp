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
#include "exportexcelobject.h"
#include "car.h"
#include "image.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(Etmp.Read());
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setItemDelegateForColumn(6, new ImageDelegate(ui->tableView));
    QScrollBar *vScrollBar = ui->tableView->verticalScrollBar();
    QScrollBar *hScrollBar = ui->tableView->horizontalScrollBar();
    vScrollBar->setStyleSheet("QScrollBar:vertical { background-color: #7FA39A; }");
    hScrollBar->setStyleSheet("QScrollBar:horizontal { background-color: #7FA39A; }");
    QPixmap icon("D:/Documents/projectcpp/feedback.png");
    QPixmap client("client.png");
    QIcon pdf("D:/Documents/projectcpp/pdf-file.png");
    QIcon xls("D:/Documents/projectcpp/xls-file.png");
    QIcon search("D:/Documents/projectcpp/search-interface-symbol.png");
    QIcon image("D:/Documents/projectcpp/photo.png");
    QPixmap sort("D:/Documents/projectcpp/sort.png");
    QPixmap trashcan("D:/Documents/projectcpp/trash-can.png");

    QPieSeries *series = new QPieSeries();

    series->append("kia", Etmp.count_brand("kia"));
    series->append("BMW", Etmp.count_brand("BMW"));
    series->append("hyundai", Etmp.count_brand("hyundai"));
    series->append("tesla", Etmp.count_brand("tesla"));
    series->append("ford", Etmp.count_brand("tesla"));


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

    ui->icon->setPixmap(icon);
    ui->pdfButton->setIcon(pdf);
    ui->imageButton->setIcon(image);
    ui->xlsButton->setIcon(xls);
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
    car c;
    c.setlc(ui->lcEdit->text());
    c.setbrand(ui->brandEdit->text());
    c.setbatterycap(ui->batteryEdit->text());
    c.setclient_id(ui->clientEdit->text());
    c.sethp(ui->hpEdit->text());
    c.settype(ui->typeEdit->text());
    c.setimagepath(ui->imagepath->text());

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
    QString licence_plate = ui->deleteEdit->text();
        bool test=Etmp.Delete(licence_plate);

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
    ui->lcEdit->setText(ui->tableView->model()->data(ui->tableView->model()->index(index.row(),0)).toString());
    ui->brandEdit->setText(ui->tableView->model()->data(ui->tableView->model()->index(index.row(),1)).toString());
    ui->batteryEdit->setText(ui->tableView->model()->data(ui->tableView->model()->index(index.row(),2)).toString());
    ui->clientEdit->setText(ui->tableView->model()->data(ui->tableView->model()->index(index.row(),3)).toString());
    ui->hpEdit->setText(ui->tableView->model()->data(ui->tableView->model()->index(index.row(),4)).toString());
    ui->typeEdit->setText(ui->tableView->model()->data(ui->tableView->model()->index(index.row(),5)).toString());
    ui->deleteEdit->setText(ui->tableView->model()->data(ui->tableView->model()->index(index.row(),0)).toString());    
}

void MainWindow::on_EditButton_clicked()
{
    car c;
    c.setlc(ui->lcEdit->text());
    c.setbrand(ui->brandEdit->text());
    c.setbatterycap(ui->batteryEdit->text());
    c.setclient_id(ui->clientEdit->text());
    c.sethp(ui->hpEdit->text());
    c.settype(ui->typeEdit->text());
    c.setimagepath(ui->imagepath->text());

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

void MainWindow::on_sortButton_clicked()
{
    QString licence_plate="";
        QString brand="";
        QString battery="";
        QString client_id="";
        QString hp="";
        QString type="";
        QString imagepath="";

            car c(licence_plate,brand,battery,client_id,hp,type,imagepath);
            QString Option=ui->sortCombo->currentText();
            ui->tableView->setModel(c.sort(Option));
}



void MainWindow::on_searchButton_clicked()
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
                QString Option=ui->comboBox->currentText();
                QString text=ui->searchEdit->text();
                ui->tableView->setModel(c.search(Option,text));
    }

}


void MainWindow::on_pdfButton_clicked()
{
    {
        QPdfWriter pdf("D:/Documents/projectcpp/PDF/listcars.pdf");

               QPainter painter(&pdf);
               int i = 4100;
               const QImage image("D:/Documents/projectcpp/charging station logo1.png");
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

                      painter.drawText(3000,2700,"Liste of cars");

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

void MainWindow::on_xlsButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Exportation Excel"), qApp->applicationDirPath (),
                                                        tr("Files Excel (*.xls)"));
        if (fileName.isEmpty())
            return;

        ExportExcelObject obj(fileName, "mydata", ui->tableView);

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


void MainWindow::on_imageButton_clicked()
{
    QString imagePath = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));

           if (imagePath.isEmpty())
               return;

           ui->imagepath->setText(imagePath);
}
