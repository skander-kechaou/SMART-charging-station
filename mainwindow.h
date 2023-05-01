#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "client.h"
#include "car.h"
#include "exportexcelobject.h"
#include <QtCharts>
#include <QChartView>
#include <QBarSeries>
#include <QBarSet>
#include "arduino.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

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

    void updateChart();

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

private:
    Ui::MainWindow *ui;
    client Etmp;
    car Ctmp;
    QByteArray data, final, finalC; // variable containing the received data
    QString nicKey;
    arduino a,A; // temporary object
};
#endif // MAINWINDOW_H
