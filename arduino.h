#ifndef ARDUINO_H
#define ARDUINO_H

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
#include <QSerialPortInfo>
#include<QtSerialPort>
#include<QLCDNumber>
#include<QByteArray>

class Arduino
{
public:
        Arduino();
        int connect_arduino(); // allow to connect the pc to Arduino
        int close_arduino(); // allow to close the connection
        int write_to_arduino( QByteArray ); // send data to Arduino
        QString read_from_arduino();  //receive data from Arduino
        QSerialPort* getserial();   // accessor
        QString getarduino_port_name();
     //bool checkEmp(QString ui,QSerialPort *Arduino);
private:
    QSerialPort * serial; //this object gathers informations (speed, data bits, etc.)
    //and fonctions (send, receive playback,…) on what is a serial path for Arduino.
    static const quint16 arduino_uno_vendor_id=9025;
    static const quint16 arduino_uno_producy_id= 67;
    QString arduino_port_name;
    bool arduino_is_available;
    QByteArray data;  // contain data read from Arduino
    QString serialBuffer="";
};

#endif // ARDUINO_H
