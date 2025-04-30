#ifndef MANAGEMENT_H
#define MANAGEMENT_H
#include "client.h"
#include "car.h"
#include "employee.h"
#include "station.h"
#include "Account.h"
#include "invoice.h"
#include "smtp.h"
#include "calculatrice.h"
#include "exportexcelobject.h"
#include <QtCharts>
#include <QChartView>
#include <QBarSeries>
#include <QBarSet>
#include "arduino.h"
#include <QMainWindow>
#include <QDialog>
#include <QMediaPlayer>

namespace Ui {
class Management;
}

class Management : public QDialog
{
    Q_OBJECT

public:
    explicit Management(QWidget *parent = nullptr);
    ~Management();

    QString hostname() const;
          quint16 port() const;
private slots:

    void button_sound();
    //##########################################CLIENT MANAGEMENT##############################################
    void on_addButton_clicked();

    void on_deleteButton_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_EditButton_clicked();

    void on_PDFButton_clicked();

    void on_refreshButton_clicked();

    void on_sortButton_clicked();

    void on_searchButton_clicked();

    void on_qrcodeButton_clicked();

    void showTime();

    void on_historyButton_clicked();

    void updateHistoryEdit();

    void process_data(QByteArray data);

    void update_data(QByteArray data);

    //##########################################CAR MANAGEMENT##############################################
    void on_CaraddButton_clicked();

    void on_CardeleteButton_clicked();

    void on_CartableView_clicked(const QModelIndex &index);

    void on_CarEditButton_clicked();

    void on_CarsortButton_clicked();

    void on_CarsearchButton_clicked();

    void on_CarpdfButton_clicked();

    void update_label();

    void on_CarxlsButton_clicked();

    void on_CarimageButton_clicked();

    void on_CarDisplayButton_clicked();

    void display();

    //##########################################EMPLOYEE MANAGEMENT##############################################
    void on_addemp_clicked();

    void on_buttonDeleteemp_clicked();

    void on_sortemp_clicked();

    void on_searchemp_clicked();

    void on_PDFemp_clicked();

    void on_tableViewEmp_clicked(const QModelIndex &index);

    void on_editemp_clicked();

    void on_statemp_clicked();

    void on_excelemp_clicked();

    void on_pushButton_4_clicked();

    void on_logout_clicked();

    //##########################################STATION MANAGEMENT#############################################

    void on_addButtonStat_clicked();

    void on_editButtonStat_clicked();

    void on_tableViewStat_clicked(const QModelIndex &index);

    void on_deleteButtonStat_clicked();

    void on_sortbuttonStat_clicked();

    void on_searchStat_clicked();

    void on_pdfStat_clicked();

    void on_map_clicked();

    //##########################################INVOICE MANAGEMENT#############################################

    void on_AddButtonInv_clicked();

    void on_EditButtonInv_clicked();

    void on_tableViewInv_clicked(const QModelIndex &index);

    void on_deleteButtonInv_clicked();

    void on_pdfInv_clicked();

    void on_sortButtonInv_clicked();

    void on_searchButtonInv_clicked();

    //mailling
    void sendMail();

    void mailSent(QString);

    void browse();

    void on_CalculatorButton_clicked();

    void on_refreshButtonEmp_clicked();

    void on_refreshButtonCar_clicked();

    void on_refreshButtonStat_clicked();

    void on_refreshButtonInv_clicked();

private:
    Ui::Management *ui;
    client Etmp;
    car Ctmp;
    station stat;
    invoice inv;
    QStringList files;
    Employee Ep;
    QByteArray data, final, finalC; // variable containing the received data
    QString nicKey;
    arduino a,A; // temporary object
    Account acc;
};

#endif // MANAGEMENT_H
