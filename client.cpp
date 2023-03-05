#include "client.h"

client::client()
{
NIC="";
fnameC="";
lnameC="";
mailC="";
phoneC="";
credit="";
}
void client::setNIC(QString c){
    NIC=c;
}
void client::setFirstName(QString fn){
    fnameC=fn;
}
void client::setLastName(QString ln){
    lnameC=ln;
}
void client::setEmail(QString e){
    mailC=e;
}
void client::setPhone(QString p){
    phoneC=p;
}
void client::setCredit(QString cr){
    credit=cr;
}
QString client::getNIC(){
    return NIC;
}
QString client::getFirstName(){
    return fnameC;
}
QString client::getLastName(){
    return lnameC;
}
QString client::getEmail(){
    return mailC;
}
QString client::getPhone(){
    return phoneC;
}
QString client::getCredit(){
    return credit;
}


