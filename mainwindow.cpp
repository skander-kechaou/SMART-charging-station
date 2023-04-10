#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "station.h"
#include <QMessageBox>
#include<QtCharts>
#include<QChartView>
#include<QPieSeries>
#include<QPieSlice>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(stat.Read());
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    QPixmap icon("C:/Users/hp/Documents/station1/feedback.png");
        QIcon pdf("C:/Users/hp/Documents/station1/pdf-file.png");
        QIcon search("C:/Users/hp/Documents/station1/search-interface-symbol.png");
        QPixmap sort("C:/Users/hp/Documents/station1/sort.png");
        QPixmap trashcan("C:/Users/hp/Documents/station1/trash-can.png");
        QIcon refresh("C:/Users/hp/Documents/station1/refresh-button.png");
        QPieSeries *series = new QPieSeries();

            series->append("nasr", stat.count_location("nasr"));
            series->append("aouina", stat.count_location("aouina"));
            series->append("soukra", stat.count_location("soukra"));


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
        ui->pdf->setIcon(pdf);
        ui->search->setIcon(search);
        ui->sort->setPixmap(sort);
        ui->trashcan->setPixmap(trashcan);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addButton_clicked()
{
    // Get information entered in the 3 fields
    QString id_stat=ui->IDstatEdit->text();
    int capacity =ui->capacityEdit->text().toInt();
    QString nameStat = ui->NamestatEdit->text();
    QString locaStat = ui->LocationEdit->text();
    int nb_emp = ui->nb_empedit->text().toInt();
     QString availability = ui->availedit->text();

    station s(id_stat,nameStat,locaStat,capacity ,nb_emp,availability); // object instantiation
                              // using information entered in the interface

    bool test=s.Create(); // insert the object into the databse Student table
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


void MainWindow::on_editButton_clicked()
{
    QString id_stat=ui->IDstatEdit->text();
    int capacity =ui->capacityEdit->text().toInt();
    QString nameStat = ui->NamestatEdit->text();
    QString locaStat = ui->LocationEdit->text();
    int nb_emp = ui->nb_empedit->text().toInt();
    QString availability = ui->availedit->text();

    station s(id_stat,nameStat,locaStat,capacity ,nb_emp,availability); // object instantiation
                              // using information entered in the interface

    bool test=s.update(); // insert the object into the databse Student table
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

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
        ui->IDstatEdit->setText(ui->tableView->model()->data(ui->tableView->model()->index(index.row(),0)).toString());
        ui->NamestatEdit->setText(ui->tableView->model()->data(ui->tableView->model()->index(index.row(),1)).toString());
        ui->LocationEdit->setText(ui->tableView->model()->data(ui->tableView->model()->index(index.row(),2)).toString());
        ui->capacityEdit->setText(ui->tableView->model()->data(ui->tableView->model()->index(index.row(),3)).toString());
        ui->nb_empedit->setText(ui->tableView->model()->data(ui->tableView->model()->index(index.row(),4)).toString());
        ui->availedit->setText(ui->tableView->model()->data(ui->tableView->model()->index(index.row(),4)).toString());
}

void MainWindow::on_deleteButton_clicked()
{
    QString id_stat=ui->IDstatEdit->text();
    bool test=stat.Delete(id_stat);

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

void MainWindow::on_sortbutton_clicked()
{
        QString id_stat="";
        QString name_stat="";
        QString location_stat="";
        int capacity=0;
        int nb_emp=0;
        QString availability="";

            station s(id_stat,name_stat,location_stat,capacity,nb_emp,availability);
            QString Option=ui->sortCombo->currentText();
            ui->tableView->setModel(s.sort(Option));
}

void MainWindow::on_search_clicked()
{
    QString id_stat="";
    QString name_stat="";
    QString location_stat="";
    int capacity=0;
    int nb_emp=0;
    QString availability="";

             station s(id_stat,name_stat,location_stat,capacity,nb_emp,availability);
            QString Option=ui->searchBox->currentText();
            QString text=ui->searchEdit->text();
            ui->tableView->setModel(s.search(Option,text));
}

void MainWindow::on_pdf_clicked()
{
    {
            QPdfWriter pdf("C:/Users/hp/Documents/station/station/station.pdf");

                   QPainter painter(&pdf);
                   int i = 4100;
                   const QImage image("C:/Users/hp/Documents/station/station/logo.png");
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

                          painter.drawText(3000,2700,"Liste of station");

                          painter.setPen(Qt::black);
                          painter.setFont(QFont("Time New Roman", 15));
                          //painter.drawRect(100,100,9400,2500);
                          painter.drawRect(100,3300,9400,500);

                          painter.setFont(QFont("Montserrat SemiBold", 10));

                          painter.drawText(500,3600," id_stat");
                          painter.drawText(2000,3600,"name_stat");
                          painter.drawText(3500,3600,"location_stat");
                          painter.drawText(5000,3600,"capacity");
                          painter.drawText(7000,3600,"nb_emp");
                          painter.drawText(8500,3600,"availability");
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

}
