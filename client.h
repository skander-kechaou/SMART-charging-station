#ifndef CLIENT_H
#define CLIENT_H

#include <QString>
class client
{
public:
    client();
        void setNIC(QString);
        void setFirstName(QString);
        void setLastName(QString);
        void setEmail(QString);
        void setPhone(QString);
        void setCredit(QString);
        QString getNIC();
        QString getFirstName();
        QString getLastName();
        QString getEmail();
        QString getPhone();
        QString getCredit();
    private:
        QString NIC, fnameC, lnameC, mailC, phoneC, credit;
};

#endif // CLIENT_H
