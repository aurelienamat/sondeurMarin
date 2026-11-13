#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_sondeurMarin.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <qdebug.h>
#include <string>

class sondeurMarin : public QMainWindow
{
    Q_OBJECT

public:
    sondeurMarin(QWidget *parent = nullptr);
    ~sondeurMarin();

public slots :
    void onSerialPortButtonClicked();
    void onSerialPortReadyRead();
    void onSerialPortButtonCloseClicked();

private:
    Ui::sondeurMarinClass ui;
    QSerialPort* port;
    int j = 0;
    std::string identification[6];
};

