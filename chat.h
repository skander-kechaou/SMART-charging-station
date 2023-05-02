#ifndef CHAT_H
#define CHAT_H

#include <QDialog>
#include <QUdpSocket>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QTcpSocket>
#include <QtCore/QUrlQuery>
#include "ui_chat.h"

#include <QDialog>

namespace Ui {
class Chat;
}

class QUdpSocket;

class Chat : public QDialog
{
    Q_OBJECT

public:
    explicit Chat(QWidget *parent = nullptr);
    ~Chat();
    QString hostname() const;
        quint16 port() const ;

private slots:
    void on_sendbutton_clicked();

    void on_cancelbutton_clicked();

private:
    Ui::Chat *ui;
   QUdpSocket *mSocket;
    /*QString mHostname;
       quint16 mPort;
*/
};
/*inline QString Chat::hostname() const
{
    return mHostname;
}
inline quint16 Chat::port() const
{
    return  mPort;
}*/
#endif // CHAT_H
