#include "car.h"
#include "management.h"
#include "ui_management.h"
#include "image.h"
#include <QPixmap>
#include <QMessageBox>
#include <QPdfWriter>
#include <QPainter>
#include <QDate>
#include<QtCharts>
#include<QChartView>
#include<QPieSeries>
#include<QPieSlice>
#include <QPainter>

car::car()
{
    licence_plate="";
    brand="";
    type="";
    batterycap="";
    hp="";
    client_id="";
    imagepath="";
}

car::car(QString l, QString b, QString t, QString h, QString bat, QString c,QString i)

{
licence_plate=l;
brand=b;
type=t;
hp=h;
batterycap=bat;
client_id=c;
imagepath=i;
}

bool car::Create()
{
    QSqlQuery query;



        //prepare() takes the query as a parameter to prepare it for execution
        query.prepare("insert into car (licence_plate,  brand,  battery,  client_id,  hp, type,imagepath)" "values (:licence_plate, :brand,  :battery,  :client_id,  :hp, :type,:imagepath)");

        // Creating variables
        query.bindValue(":licence_plate",licence_plate);
        query.bindValue(":brand",brand);
        query.bindValue(":battery",batterycap);
        query.bindValue(":client_id",client_id);
        query.bindValue(":hp",hp);
        query.bindValue(":type", type);
        query.bindValue(":imagepath",imagepath);

        return query.exec(); //exec() send request to be executed
}

QSqlQueryModel * car::Read()
{

    QSqlQueryModel * model=new QSqlQueryModel();

        model->setQuery("select * from car");
        model->setHeaderData(0,Qt::Horizontal,QObject::tr("License"));
        model->setHeaderData(1,Qt::Horizontal,QObject::tr("Brand"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("Battery"));
        model->setHeaderData(3,Qt::Horizontal,QObject::tr("client ID"));
        model->setHeaderData(4,Qt::Horizontal,QObject::tr("HP"));
        model->setHeaderData(5,Qt::Horizontal,QObject::tr("Type"));
        model->setHeaderData(6,Qt::Horizontal,QObject::tr("#"));

        QTableView *tableView = new QTableView();

        // populate model...

        ImageDelegate *delegate = new ImageDelegate(tableView);
        tableView->setItemDelegateForColumn(6, delegate);
        tableView->setModel(model);

        return  model;
}

bool car::Delete(QString licence_plate)
{
    QSqlQuery query;

        query.prepare("Delete from car where licence_plate= :licence_plate");

        query.bindValue(":licence_plate",licence_plate);

        return  query.exec();
}
int car::count_brand(QString brand)
 {
   QSqlQuery qry;
   qry.prepare("select * from car where brand=:brand");
   qry.bindValue(":brand",brand);

   qry.exec();
   int total=0;
   while (qry.next()) total++;
   return total;

 }
bool car::update()
{
    QSqlQuery query;
        query.prepare ("update car SET  brand = :brand, battery = :battery, client_id = :client_id, hp = :hp, type = :type where licence_plate = :licence_plate" );

        // Creating variables
        query.bindValue(":licence_plate",licence_plate);
        query.bindValue(":brand",brand);
        query.bindValue(":battery",batterycap);
        query.bindValue(":client_id",client_id);
        query.bindValue(":hp",hp);
        query.bindValue(":type", type);

       return query.exec();
}
QSqlQueryModel * car::sort(QString option)
{
    QSqlQueryModel * model=new QSqlQueryModel();
        if(option == "battery capacity"){
            model->setQuery("SELECT * from car order by battery asc");
        }
        else if(option =="type")
        {
            model->setQuery("SELECT * from car order by type asc ");
        }
        else if(option =="hp")
        {
            model->setQuery("SELECT * from car order by hp asc ");
        }

        model->setHeaderData(0,Qt::Horizontal,QObject::tr("License"));
        model->setHeaderData(1,Qt::Horizontal,QObject::tr("Brand"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("Battery"));
        model->setHeaderData(3,Qt::Horizontal,QObject::tr("client ID"));
        model->setHeaderData(4,Qt::Horizontal,QObject::tr("HP"));
        model->setHeaderData(5,Qt::Horizontal,QObject::tr("Type"));
        model->setHeaderData(6,Qt::Horizontal,QObject::tr("#"));
        return model;
}
QSqlQueryModel * car::search(QString option, QString text)
{
    QSqlQueryModel * model=new QSqlQueryModel();
        if(option == "license plate"){
            model->setQuery("SELECT * from car where ( licence_plate like '%"+text+"%' )");
        }
        else if(option =="brand")
        {
            model->setQuery("SELECT * from car where ( brand like '%"+text+"%' )");
        }
        else if(option =="client id")
        {
            model->setQuery("SELECT * from car where ( client_id like '%"+text+"%' ) ");
        }

        model->setHeaderData(0,Qt::Horizontal,QObject::tr("License"));
        model->setHeaderData(1,Qt::Horizontal,QObject::tr("Brand"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("Battery"));
        model->setHeaderData(3,Qt::Horizontal,QObject::tr("client ID"));
        model->setHeaderData(4,Qt::Horizontal,QObject::tr("HP"));
        model->setHeaderData(5,Qt::Horizontal,QObject::tr("Type"));
        model->setHeaderData(6,Qt::Horizontal,QObject::tr("#"));
        return model;
}

QStringList car::list()
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
void car::setlc(QString c){
    licence_plate=c;
}
void car::setbrand(QString b){
    brand=b;
}
void car::setclient_id(QString id){
    client_id=id;
}
void car::setbatterycap(QString e){
    batterycap=e;
}
void car::settype(QString t)
{
    type=t;
}
void car::setimagepath(QString i)
{
    imagepath=i;
}
void car::sethp(QString h)
{
    hp=h;
}
QString car::getlc(){
    return licence_plate;
}
QString car::getbrand(){
    return brand;
}
QString car::getbatterycap(){
    return batterycap;
}
QString car::getimagepath(){
    return imagepath;
}

