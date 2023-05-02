#include "history.h"

history::history()
{

}

history::history(QString NIC, QString fname, QString lname, QString mail, QString phoneC, QString credit, QString tmp)
{
    this->NIC=NIC;
    this->fname=fname;
    this->lname=lname;
    this->mail=mail;
    this->phoneC=phoneC;
    this->credit=credit;
    this->tmp=tmp;
}

void history::saveclient()
{
    QFile file ("C:/Users/Skander/Documents/Client1/history.txt");
        if (!file.open(QIODevice::WriteOnly|  QIODevice::Append | QIODevice::Text))
            return;

        QTextStream out(&file);
        out.setCodec("UTF-8");
        QString sDate = QDateTime::currentDateTime().toString("dddd dd MMMM yyyy hh:mm:ss.zzz");
        out << "\n User : "+NIC + " " +fname+ " " +lname +" " +mail+" "+phoneC+" "+credit<< " ✔️ ADDED on " +sDate << "\n";
}

void history::saveUpdateclient(QString NIC, QString fname, QString lname, QString mail, QString phoneC, QString credit, QString tmp)
{
    QFile file ("C:/Users/Skander/Documents/Client1/history.txt");
        if (!file.open(QIODevice::WriteOnly|  QIODevice::Append | QIODevice::Text))
            return;

        QTextStream out(&file);
        out.setCodec("UTF-8");
        QString sDate = QDateTime::currentDateTime().toString("dddd dd MMMM yyyy hh:mm:ss.zzz");
        out << "\n User : "+NIC + " " +fname+ " " +lname +" " +mail+" "+phoneC+" "+credit<< " 🔄 UPDATED on " +sDate << "\n";

}

void history::saveDeleteclient()
{
    QFile file ("C:/Users/Skander/Documents/Client1/history.txt");
        if (!file.open(QIODevice::WriteOnly|  QIODevice::Append | QIODevice::Text))
            return;

        QTextStream out(&file);
        out.setCodec("UTF-8");
        QString sDate = QDateTime::currentDateTime().toString("dddd dd MMMM yyyy hh:mm:ss.zzz");
        out << "\n User : "+NIC + " " +fname+ " " +lname +" " +mail+" "+phoneC+" "+credit<< " ❌ DELETED on " +sDate << "\n";
}
