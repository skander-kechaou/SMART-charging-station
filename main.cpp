#include "login.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"
#include <QSslSocket>
#include "management.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /* w.show();
    return a.exec();*/
    connection c;
    QString opensslVersionString = QSslSocket::sslLibraryBuildVersionString();
    qDebug() << "OpenSSL version: " << opensslVersionString;        bool test=c.createconnect();
        Login w;
        if(test)
        {w.show();
            QMessageBox::information(nullptr, QObject::tr("database is open"),
                        QObject::tr("connection successful.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

    }
        else
            QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                        QObject::tr("connection failed.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);



        return a.exec();
}
