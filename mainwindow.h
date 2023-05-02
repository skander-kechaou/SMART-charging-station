#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "invoice.h"
#include <QMainWindow>
#include "smtp.h"
#include "calculatrice.h"

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
    void on_AddButton_clicked();


    void on_EditButton_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_2_clicked();

    void on_pdf_clicked();

    void on_pushButton_clicked();



    void on_searchButton_clicked();
    //mailling
    void sendMail();
    void mailSent(QString);
    void browse();

    void on_pushButton_3_clicked();

    void on_sendBtn_clicked();

private:
    Ui::MainWindow *ui;
    invoice inv;
    QStringList files;
    calculatrice *c;


};
#endif // MAINWINDOW_H
