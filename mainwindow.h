#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "station.h"
#define nullptr NULL

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_addButton_clicked();

    void on_editButton_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_deleteButton_clicked();

    void on_sortbutton_clicked();

    void on_search_clicked();

    void on_pdf_clicked();

private:
    Ui::MainWindow *ui;

    station stat;
};

#endif // MAINWINDOW_H
