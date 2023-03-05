#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QMessageBox>
#include "client.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap icon("C:/Users/Skander/Documents/Client1/feedback (2).png");
    QPixmap client("C:/Users/Skander/Documents/Client1/client (1).png");
    QPixmap pdf("C:/Users/Skander/Documents/Client1/pdf-file (1).png");
    QIcon search("C:/Users/Skander/Documents/Client1/search-interface-symbol.png");
    QPixmap sort("C:/Users/Skander/Documents/Client1/sort.png");
    ui->icon->setPixmap(icon);
    ui->client->setPixmap(client);
    ui->pdf->setPixmap(pdf);
    ui->searchButton->setIcon(search);
    ui->sortLabel->setPixmap(sort);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_addButton_clicked()
{
    client c;
    c.setNIC(ui->nicEdit->text());
    c.setFirstName(ui->fnameEdit->text());
    c.setLastName(ui->lnameEdit->text());
    c.setEmail(ui->emailEdit->text());
    c.setPhone(ui->pnbEdit->text());
}
