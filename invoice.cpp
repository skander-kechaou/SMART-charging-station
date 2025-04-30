#include "invoice.h"

invoice::invoice()
{
    reference="";
    NIC="";
    idstat="";
    licensepl="";
    cost=0;
    date_inv=QDate::currentDate();
}
invoice::invoice(QString reference, QString NIC, QString idstat, QString licensepl, int cost, QDate date_inv)
{
    this->reference=reference;
    this->NIC=NIC;
    this->idstat=idstat;
    this->licensepl=licensepl;
    this->cost=cost;
    this->date_inv=date_inv;
}
void invoice::setreference(QString r)
{
    reference=r;
}
void invoice::setNIC(QString n)
{
    NIC=n;
}
void invoice::setidstat(QString s)
{
   idstat=s;
}
void invoice::setlicensepl(QString l)
{
    licensepl=l;
}
void invoice::setcost(int c)
{
   cost=c;
}
void invoice::setdate_inv(QDate d)
{
    date_inv=d;
}
QString invoice::getreference()
{
   return reference;
}
QString invoice::getNIC()
{
    return NIC;
}
QString invoice::getidstat()
{
    return idstat;
}
QString invoice::getlicensepl()
{
    return licensepl;
}
int invoice::getcost()
{
    return cost;
}
QDate invoice::getdate_inv()
{
    return date_inv;
}

bool invoice::Create()
{
    QSqlQuery query;


        //prepare() takes the query as a parameter to prepare it for execution
        query.prepare("insert into invoice (reference, date_inv, NIC, cost, idstat, licensepl)" "values (:reference, TO_DATE(:date_inv, 'YYYY-MM-DD'), :NIC, :cost, :idstat, :licensepl)");

        QString res1=date_inv.toString("yyyy-MM-dd");
        QString res2=QString::number(cost);
        // Creating variables
        query.bindValue(":reference",reference);
        query.bindValue(":NIC",NIC);
        query.bindValue(":idstat",idstat);
        query.bindValue(":licensepl",licensepl);
        query.bindValue(":date_inv",res1);
        query.bindValue(":cost", res2);

        return query.exec(); //exec() send request to be executed
}

QSqlQueryModel * invoice::Read()
{
    QSqlQueryModel * model=new QSqlQueryModel();

        model->setQuery("select * from invoice");
        model->setHeaderData(0,Qt::Horizontal,QObject::tr("Reference"));
        model->setHeaderData(1,Qt::Horizontal,QObject::tr("Date Invoice"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("NIC"));
        model->setHeaderData(3,Qt::Horizontal,QObject::tr("Cost"));
        model->setHeaderData(4,Qt::Horizontal,QObject::tr("ID Station"));
        model->setHeaderData(5,Qt::Horizontal,QObject::tr("License Plate"));

        return  model;
}

bool invoice::Delete(QString reference)
{
    QSqlQuery query;

        query.prepare("Delete from invoice where reference= :reference");

        query.bindValue(":reference",reference);

        return  query.exec();
}

bool invoice::update()
{
    QSqlQuery query;
        query.prepare ("update invoice SET date_inv = TO_DATE(:date_inv, 'YYYY-MM-DD'), NIC = :NIC, cost = :cost, idstat = :idstat, licensepl = :licensepl where reference=:reference" );

        // Creating variables
        QString res1=date_inv.toString("yyyy-MM-dd");
        QString res2=QString::number(cost);
        query.bindValue(":NIC",NIC);  //*****
        query.bindValue(":date_inv",res1); //******
        query.bindValue(":cost",res2);  //****
        query.bindValue(":idstat",idstat);
        query.bindValue(":licensepl",licensepl);//** for the search
        query.bindValue(":reference", reference);

       return query.exec();
}

QSqlQueryModel * invoice::sort(QString option)
{
    QSqlQueryModel * model=new QSqlQueryModel();
        if(option == "NIC"){
            model->setQuery("SELECT * from invoice order by NIC asc");
        }
        else if(option =="Invoice Date")
        {
            model->setQuery("SELECT * from invoice order by date_inv asc ");
        }
        else if(option =="Cost")
        {
            model->setQuery("SELECT * from invoice order by cost asc ");
        }

        model->setHeaderData(0,Qt::Horizontal,QObject::tr("Reference"));
        model->setHeaderData(1,Qt::Horizontal,QObject::tr("Date Invoice"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("NIC"));
        model->setHeaderData(3,Qt::Horizontal,QObject::tr("Cost"));
        model->setHeaderData(4,Qt::Horizontal,QObject::tr("ID Station"));
        model->setHeaderData(5,Qt::Horizontal,QObject::tr("License Plate"));

        return model;
}

QSqlQueryModel * invoice::search(QString option, QString text)
{
    QSqlQueryModel * model=new QSqlQueryModel();
        if(option == "Station ID"){
            model->setQuery("SELECT * from invoice where ( idstat like '%"+text+"%' )");
        }
        else if(option =="License Plate")
        {
            model->setQuery("SELECT * from invoice where ( licensepl like '%"+text+"%' )");
        }
        else if(option =="Invoice Date")
        {
            model->setQuery("SELECT * from invoice where ( date_inv like '%"+text+"%' ) ");
        }

        model->setHeaderData(0,Qt::Horizontal,QObject::tr("Reference"));
        model->setHeaderData(1,Qt::Horizontal,QObject::tr("Date Invoice"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("NIC"));
        model->setHeaderData(3,Qt::Horizontal,QObject::tr("Cost"));
        model->setHeaderData(4,Qt::Horizontal,QObject::tr("ID Station"));
        model->setHeaderData(5,Qt::Horizontal,QObject::tr("License Plate"));

        return model;
}
int invoice::count_stat(QString cost)
 {
   QSqlQuery qry;
   qry.prepare("select * from invoice where cost=:cost");
   qry.bindValue(":cost",cost);

   qry.exec();
   int total=0;
   while (qry.next()) total++;
   return total;

 }

QStringList invoice::listNIC()
{
    //extraire les NIC pour les afficher dans le combobox
    QSqlQuery c;
    c.prepare("select NIC from CLIENT");
    c.exec();
    QStringList l;
    while(c.next())
    {
        l<<c.value(0).toString();
    }
    return l;
}

QStringList invoice::listLicense()
{
    //extraire les License Plate pour les afficher dans le combobox
    QSqlQuery c;
    c.prepare("select LICENCE_PLATE from CAR");
    c.exec();
    QStringList l;
    while(c.next())
    {
        l<<c.value(0).toString();
    }
    return l;
}

QStringList invoice::listStation()
{
    //extraire les STATIONS pour les afficher dans le combobox
    QSqlQuery c;
    c.prepare("select ID_STAT from STATION");
    c.exec();
    QStringList l;
    while(c.next())
    {
        l<<c.value(0).toString();
    }
    return l;
}
