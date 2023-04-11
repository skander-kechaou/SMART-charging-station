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
using namespace QtCharts;



#include "chat.h"
#include "ui_chat.h"
#include "login.h"

#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrinter>
#include <QObject>
#include<ctime>
#include <QTcpSocket>
#include <QDebug>
#include <QLineEdit>
#include <QMessageBox>
#include <QIntValidator>

#include<QFile>
#include<QFileDialog>

#include <QTextDocument>
#include <QPainter>
#include <QTextStream>
#include <QPdfWriter>
#include <string>
#include <QSqlError>
#include <vector>
#include<QDirModel>
#include <string>
#include <iostream>
#include <fstream>
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

#include<QPainter>
#include<QDesktopServices>
#include<QUrl>
#include <QtWidgets>
#include <QPlainTextEdit>
#include <QPrinterInfo>
#include <QTextStream>
#include <QTextStream>
#include<QPdfWriter>
#include <QWidget>
EmployeeManagement::EmployeeManagement(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EmployeeManagement)
{
    ui->setupUi(this);
    QRegularExpression rx("^[0-9a-zA-Z]+([0-9a-zA-Z]*[-._+])*[0-9a-zA-Z]+@[0-9a-zA-Z]+([-.][0-9a-zA-Z]+)*([0-9a-zA-Z]*[.])[a-zA-Z]{2,6}$",
                                 QRegularExpression::CaseInsensitiveOption);
       ui->lineEdit_4->setValidator(new QRegularExpressionValidator(rx, this));
       ui->lineEdit_5 -> setValidator (new QIntValidator(0, 999999, this));
        ui->lineEdit_7 -> setValidator (new QIntValidator(0, 999999, this));
      ui->tableView->setModel(e.view());

ui->comboBox->addItems(e.list());

            QPixmap outPixmap = QPixmap();
                 outPixmap.loadFromData(a.fetch_image(a.username),"JPG");
                outPixmap = outPixmap.scaledToWidth(ui->label_2->width(),Qt::SmoothTransformation);

               ui->label_2->setPixmap(outPixmap.scaled(outPixmap.width(),outPixmap.height(),Qt::KeepAspectRatio));


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
        QString idstat=ui->comboBox->currentText();
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

void EmployeeManagement::on_edit_clicked()
{
    QString  ID=ui->lineEdit->text();
    QString fname=ui->lineEdit_2->text();
    QString lname=ui->lineEdit_3->text();
    QString mail=ui->lineEdit_4->text();
    int  Phone=ui->lineEdit_5->text().toInt();
    QString role=ui->lineEdit_6->text();
    float  salary=ui->lineEdit_7->text().toFloat();
    QString idstat=ui->comboBox->currentText();

            Employee  emp(  ID, mail,fname , Phone,  lname, salary, idstat, role);
            bool test=emp.modify();
            if(test)
            {    ui->tableView->setModel(emp.view());
                   ui->comboBox->clear();
         ui->comboBox->addItems(emp.list());
                QMessageBox::information(nullptr, QObject::tr("ok"),
                            QObject::tr("updated successfully \n"
                                        "Click Cancel to exit."), QMessageBox::Ok);

            }
            else
                QMessageBox::critical(nullptr, QObject::tr("not ok"),
                            QObject::tr("failed to update\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
}

void EmployeeManagement::on_stat_clicked()
{
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
        QPieSeries *series = new QPieSeries();
        series->append(a,salaire);
        series->append(b,salairee);
        series->append(c,salaireee);
        if (salaire!=0)
        {QPieSlice *slice = series->slices().at(0);
            slice->setLabelVisible();
            slice->setPen(QPen());}
        if ( salairee!=0)
        {
            // Add label, explode and define brush for 2nd slice
            QPieSlice *slice1 = series->slices().at(1);
            slice1->setLabelVisible();
        }
        if(salaireee!=0)
        {
            // Add labels to rest of slices
            QPieSlice *slice2 = series->slices().at(2);
            slice2->setLabelVisible();
        }
        // Create the chart widget
        QChart *chart = new QChart();
        // Add data to chart with title and hide legend
        chart->addSeries(series);
        chart->setTitle("Percentage by salary of "+ QString::number(total)+" employees");

          //change the color of the background
         QLinearGradient backgroundGradient;

           backgroundGradient.setColorAt(0.0, QRgb(0xb6d7a8));
           backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
           chart->setBackgroundBrush(backgroundGradient);
            chart->legend()->hide();

        // Used to display the chart

        QChartView *chartView = new QChartView(chart);
         chartView->setRenderHint(QPainter::Antialiasing);
         chartView->resize(500,250);
         chartView->setParent(ui->chart);
         chartView->show();
}

void EmployeeManagement::on_excel_clicked()
{
    QTableView *table;
          table = ui->tableView;

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
void EmployeeManagement::on_pushButton_4_clicked()
{

        Chat* w=new Chat(this);
           w->show();


}


void EmployeeManagement::on_logout_clicked()
{
    Login *l;
    l->show();
}
