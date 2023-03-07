#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "station.h"
#include <QMainWindow>
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
    void on_pushButton_create_clicked();
    void on_pushButton_delete_clicked();

private:
    Ui::MainWindow *ui;

    station stat;
};

#endif // MAINWINDOW_H
