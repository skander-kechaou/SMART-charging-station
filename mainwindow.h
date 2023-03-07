#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "client.h"

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
    void on_addButton_clicked();
    void on_deleteButton_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_EditButton_clicked();

private:
    Ui::MainWindow *ui;
    client Etmp;
};
#endif // MAINWINDOW_H
