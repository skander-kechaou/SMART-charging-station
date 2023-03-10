#include "employeemanagement.h"
#include "ui_employeemanagement.h"
#include "employee.h"
#include <QMessageBox>
#include <QGroupBox>
#include <QStandardItemModel>
#include <QtSql/QSqlQueryModel>


#include<QIntValidator>
#include <QtPrintSupport/QPrintDialog>
#include <QDebug>
#include <QtSql/QSqlError>
#include<QIntValidator>
#include <QCloseEvent>

#include <QFileDialog>
#include <QTextStream>
#include <QTextDocument>
#include<QSystemTrayIcon>
#include <QPrinter>
#include <QString>
#include <QMouseEvent>
#include <QScrollArea>
#include <QDesktopServices>
    #include <QPdfWriter>
EmployeeManagement::EmployeeManagement(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EmployeeManagement)
{
    ui->setupUi(this);
    QRegularExpression rx("^[0-9a-zA-Z]+([0-9a-zA-Z]*[-._+])*[0-9a-zA-Z]+@[0-9a-zA-Z]+([-.][0-9a-zA-Z]+)*([0-9a-zA-Z]*[.])[a-zA-Z]{2,6}$",
                                 QRegularExpression::CaseInsensitiveOption);
       ui->lineEdit_4->setValidator(new QRegularExpressionValidator(rx, this));
      ui->tableView->setModel(e.view());

}

EmployeeManagement::~EmployeeManagement()
{
    delete ui;
}



void EmployeeManagement::on_add_clicked()
{
        QString  ID=ui->lineEdit->text();
        QString fname=ui->lineEdit_2->text();
        QString lname=ui->lineEdit_3->text();
        QString mail=ui->lineEdit_4->text();
        int  Phone=ui->lineEdit_5->text().toInt();
        QString role=ui->lineEdit_6->text();
        float  salary=ui->lineEdit_7->text().toFloat();
        QString idstat=ui->lineEdit_8->text();
    Employee  emp(  ID, mail,fname , Phone,  lname, salary, idstat, role);


        bool test=emp.addEmp();
        if(test)
        {
            ui->tableView->setModel(e.view());
            QMessageBox::information(nullptr, QObject::tr("ok"),
                        QObject::tr("insert done\n"
                                    "Click ok to exit."), QMessageBox::Ok);

              ui->lineEdit->setText("");
              ui->lineEdit_2->setText("");
              ui->lineEdit_3->setText("");
              ui->lineEdit_4->setText("");
              ui->lineEdit_5->setText("");
              ui->lineEdit_6->setText("");
              ui->lineEdit_7->setText("");
              ui->lineEdit_8->setText("");


    }
        else
            QMessageBox::critical(nullptr, QObject::tr("not ok"),
                        QObject::tr("ajout non effectue\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

}

void EmployeeManagement::on_tableView_clicked(const QModelIndex &index)
{
        ui->lineEdit->setText(ui->tableView->model()->data(ui->tableView->model()->index(index.row(),0)).toString());
       ui->lineEdit_4->setText(ui->tableView->model()->data(ui->tableView->model()->index(index.row(),1)).toString());
       ui->lineEdit_2->setText(ui->tableView->model()->data(ui->tableView->model()->index(index.row(),2)).toString());
       ui->lineEdit_5->setText(ui->tableView->model()->data(ui->tableView->model()->index(index.row(),3)).toString());
       ui->lineEdit_3->setText(ui->tableView->model()->data(ui->tableView->model()->index(index.row(),4)).toString());
       ui->lineEdit_7->setText(ui->tableView->model()->data(ui->tableView->model()->index(index.row(),5)).toString());
       ui->lineEdit_8->setText(ui->tableView->model()->data(ui->tableView->model()->index(index.row(),6)).toString());
       ui->lineEdit_6->setText(ui->tableView->model()->data(ui->tableView->model()->index(index.row(),7)).toString());
}


void EmployeeManagement::on_buttonDelete_clicked()
{
         QString ID=ui->lineEdit_9->text();
        bool test =e.deleteEmp(ID);
        if(test)
        {    ui->tableView->setModel(e.view());

            QMessageBox::information(nullptr, QObject::tr("ok"),
                        QObject::tr("deleted successfully \n"
                                    "Click Cancel to exit."), QMessageBox::Ok);

                 ui->lineEdit_9->setText("");

    }
        else
            QMessageBox::critical(nullptr, QObject::tr("not ok"),
                        QObject::tr("failed to delete\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);



}
/*
void EmployeeManagement::on_pushButton12_clicked()
{
    QString  ID=ui->lineEdit->text();
    QString fname=ui->lineEdit_2->text();
    QString lname=ui->lineEdit_3->text();
    QString mail=ui->lineEdit_4->text();
    int  Phone=ui->lineEdit_5->text().toInt();
    QString role=ui->lineEdit_6->text();
    float  salary=ui->lineEdit_7->text().toFloat();
    QString idstat=ui->lineEdit_8->text();

            Employee  emp(  ID, mail,fname , Phone,  lname, salary, idstat, role);
            bool test=emp.modify();
            if(test)
            {    ui->tableView->setModel(emp.view());

                QMessageBox::information(nullptr, QObject::tr("ok"),
                            QObject::tr("updated successfully \n"
                                        "Click Cancel to exit."), QMessageBox::Ok);

            }
            else
                QMessageBox::critical(nullptr, QObject::tr("not ok"),
                            QObject::tr("failed to update\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);

}
*/
void EmployeeManagement::on_sort_clicked()
{


            QString choice=ui->comboBox_tri->currentText();
            if (choice=="Sort By First Name")
            {
                ui->tableView->setModel(e.sort_name());
                ui->tableView->setModel(e.view());
                bool test=e.sort_name();//sort  by fname
                if (test)
                {

            ui->tableView->setModel(e.sort_name());
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
                        ui->tableView->setModel(e.sort_ID());
                        ui->tableView->setModel(e.view());
                        bool test=e.sort_ID();//sort by  ID
                        if (test)
                        {

                    ui->tableView->setModel(e.sort_ID());
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
                        ui->tableView->setModel(e.sort_Role());
                        ui->tableView->setModel(e.view());
                        bool test=e.sort_Role();//sort by role
                        if (test)
                        {

                    ui->tableView->setModel(e.sort_Role());
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

void EmployeeManagement::on_search_clicked()
{
    QString choice=ui->comboBox_search->currentText();

          if (choice=="Search By First Name")
          {
              QString fname = ui->lineEdit_search->text();
              ui->tableView->setModel(e.searchname(fname));
          }
          if (choice=="Search By Id")
          {
              QString ID= ui->lineEdit_search->text();
              ui->tableView->setModel(e.searchID(ID));
          }

          if (choice=="Search By Role")
          {
              QString role = ui->lineEdit_search->text();
              ui->tableView->setModel(e.searchRole(role));
          }
          ui->lineEdit_search->setText("");
}



void EmployeeManagement::on_PDF_clicked()
{
    QString strStream;
                                       QTextStream out(&strStream);

                                       const int rowCount = ui->tableView->model()->rowCount();
                                       const int columnCount = ui->tableView->model()->columnCount();

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
                                           if (!ui->tableView->isColumnHidden(column))
                                               out << QString("<th>%1</th>").arg(ui->tableView->model()->headerData(column, Qt::Horizontal).toString());
                                       out << "</tr></thead>\n";

                                       // data table
                                       for (int row = 0; row < rowCount; row++) {
                                           out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                                           for (int column = 0; column < columnCount; column++) {
                                               if (!ui->tableView->isColumnHidden(column)) {
                                                   QString data = ui->tableView->model()->data(ui->tableView->model()->index(row, column)).toString().simplified();
                                                   out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                               }
                                           }
                                           out << "</tr>\n";
                                       }
                                       out <<  "</table> </center>\n"
                                           "</body>\n"
                                           "</html>\n";

                                 QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Sauvegarder en PDF", QString(), "*.pdf");
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



/*
void Employee::stat(QCustomPlot *customPlot)
{
    QSqlQuery query,query1;
    // set dark background gradient:
    QLinearGradient gradient(0, 0, 0, 400);
    gradient.setColorAt(0, QColor(90, 90, 90));
    gradient.setColorAt(0.38, QColor(105, 105, 105));
    gradient.setColorAt(1, QColor(70, 70, 70));
    customPlot->clearPlottables();
    customPlot->clearGraphs();
    customPlot->replot();

    customPlot->setBackground(QBrush(gradient));


    QCPBars *fossil = new QCPBars(customPlot->xAxis, customPlot->yAxis);

    fossil->setAntialiased(false);

    fossil->setStackingGap(1);
    // set names and colors:
    fossil->setName("AGE");
    fossil->setPen(QPen(QColor(111, 9, 176).lighter(170)));
    fossil->setBrush(QColor(111, 9, 176));

    QVector<double> ticks;
    QVector<QString> labels;
    query.prepare("SELECT COUNT(DISTINCT cin_e) FROM EMPLOYES where age between 18 and 23");////////////////
    query.exec();
    int un;
    while(query.next())
    {
        un=query.value(0).toInt();
        qDebug()<<un;
    }
    query.prepare("SELECT COUNT(DISTINCT cin_e) FROM EMPLOYES where age between 23 and 31");/////////////////
    query.exec();
    int deux;
    while(query.next())
    {
        deux=query.value(0).toInt();
    }

    query.prepare("SELECT COUNT(DISTINCT cin_e) FROM EMPLOYES where age between 31 and 50");///////////////
    query.exec();
    int trois;
    while(query.next())
    {
        trois=query.value(0).toInt();
    }





    ticks << 1 << 2 << 3 ;
    labels << "[18,23]" << "[23,31]" << "[31,50]" ;///////////////////////////////
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    customPlot->xAxis->setTicker(textTicker);
    customPlot->xAxis->setTickLabelRotation(60);
    customPlot->xAxis->setSubTicks(false);
    customPlot->xAxis->setTickLength(0, 4);
    customPlot->xAxis->setRange(0, 8);
    customPlot->xAxis->setBasePen(QPen(Qt::white));
    customPlot->xAxis->setTickPen(QPen(Qt::white));
    customPlot->xAxis->grid()->setVisible(true);
    customPlot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    customPlot->xAxis->setTickLabelColor(Qt::white);
    customPlot->xAxis->setLabelColor(Qt::green);

    // prepare y axis:
    customPlot->yAxis->setRange(0, 20);
    customPlot->yAxis->setPadding(5);
    customPlot->yAxis->setLabel("Employe");//////////////////
    customPlot->yAxis->setBasePen(QPen(Qt::white));
    customPlot->yAxis->setTickPen(QPen(Qt::white));
    customPlot->yAxis->setSubTickPen(QPen(Qt::white));
    customPlot->yAxis->grid()->setSubGridVisible(true);
    customPlot->yAxis->setTickLabelColor(Qt::white);
    customPlot->yAxis->setLabelColor(Qt::white);
    customPlot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    customPlot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

    // Add data:
    QVector<double> fossilData, nuclearData, regenData;
    fossilData  << un << deux << trois;
   // nuclearData << 0.08*10.5 << 0.12*5.5 << 0.12*5.5 << 0.40*5.8 << 0.09*5.2 << 0.00*4.2 << 0.07*11.2;
    regenData   << 0.06*10.5 << 0.05*5.5 << 0.04*5.5 << 0.06*5.8 << 0.02*5.2 << 0.07*4.2 << 0.25*11.2;
    fossil->setData(ticks, fossilData);
  //  nuclear->setData(ticks, nuclearData);
 //   regen->setData(ticks, regenData);

    // setup legend:
    customPlot->legend->setVisible(true);
    customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    customPlot->legend->setBrush(QColor(255, 255, 255, 100));
    customPlot->legend->setBorderPen(Qt::NoPen);
    QFont legendFont = QFont();
    legendFont.setPointSize(10);
    customPlot->legend->setFont(legendFont);
    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

}*/


void EmployeeManagement::on_edit_clicked()
{
    QString  ID=ui->lineEdit->text();
    QString fname=ui->lineEdit_2->text();
    QString lname=ui->lineEdit_3->text();
    QString mail=ui->lineEdit_4->text();
    int  Phone=ui->lineEdit_5->text().toInt();
    QString role=ui->lineEdit_6->text();
    float  salary=ui->lineEdit_7->text().toFloat();
    QString idstat=ui->lineEdit_8->text();

            Employee  emp(  ID, mail,fname , Phone,  lname, salary, idstat, role);
            bool test=emp.modify();
            if(test)
            {    ui->tableView->setModel(emp.view());

                QMessageBox::information(nullptr, QObject::tr("ok"),
                            QObject::tr("updated successfully \n"
                                        "Click Cancel to exit."), QMessageBox::Ok);

            }
            else
                QMessageBox::critical(nullptr, QObject::tr("not ok"),
                            QObject::tr("failed to update\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
}
