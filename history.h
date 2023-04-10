#ifndef HISTORY_H
#define HISTORY_H

#include<QString>
#include<QMessageBox>
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QDebug>

class history
{
    QString NIC, fname, lname, mail, phoneC, credit, tmp;
public:

    history();
    history(QString NIC, QString fname, QString lname, QString mail, QString phoneC, QString credit, QString tmp);
    void saveclient();
    QString loadclients();
    void saveUpdateclient(QString NIC, QString fname, QString lname, QString mail, QString phoneC, QString credit, QString tmp);
    void saveDeleteclient();
};

#endif // HISTORY_H
