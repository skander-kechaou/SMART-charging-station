#include "map.h"
#include "ui_map.h"
#include <QAxBase>

map::map(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::map)
{
    ui->setupUi(this);
    ui->axWidget->setControl("Shell.Explorer.2");
    QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                           QCoreApplication::organizationName(), QCoreApplication::applicationName());

        ui->axWidget->setProperty("Silent", true);
        ui->axWidget->dynamicCall("Navigate(const QString&)", "https://www.google.com/maps/place/esprit+ecole+d\'ing%C3%A9nieurs/@36.899229,10.1874636,17z");

}

map::~map()
{
    delete ui;
}
