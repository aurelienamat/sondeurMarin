#include "sondeurMarin.h"

sondeurMarin::sondeurMarin(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    QList<QSerialPortInfo> availablePorts = QSerialPortInfo::availablePorts();

    for (int i = 0; i < availablePorts.size();i++) {
        ui.comboBoxPort->addItem(availablePorts[i].portName());
    }

}

sondeurMarin::~sondeurMarin()
{}

void sondeurMarin::onSerialPortButtonClicked() {
    qDebug() << "clicked";
    if (ui.comboBoxPort->currentIndex() >= 0) {
        port = new QSerialPort(ui.comboBoxPort->currentText());
        QObject::connect(port, SIGNAL(readyRead()), this, SLOT(onSerialPortReadyRead()));
        port->setBaudRate(ui.lineEditBauds->text().toInt());
        port->setDataBits(QSerialPort::DataBits::Data8);
        port->setParity(QSerialPort::Parity::NoParity);
        port->setStopBits(QSerialPort::StopBits::OneStop);
        if (port->open(QIODevice::OpenModeFlag::ExistingOnly | QIODevice::OpenModeFlag::ReadWrite)) {
            ui.labelStatus->setText("Ouvert");
        }
    }
}

void gestionIdentification(std::string chaine[]) {
    if (*chaine == "$SDMTW") {
        qDebug() << "Température";
    }
    //////////////////////////////////////////////////////////
}

void afficheChaine(std::string chaine[], int size) {
    qDebug() << size;
    for (int i = 0; i < size; i++) {
        qDebug() << chaine[i];
    }
}

void sondeurMarin::onSerialPortReadyRead() {
    QByteArray data = port->read(port->bytesAvailable());
    qDebug() << data;
    if (data.size() == 8) {
        for (int i = 0; i < 8;i++) {
            if (data.at(i) == '$' || j != 0) {
                for (int a = i;a < 8;a++) {
                    identification[j] = data.at(a);
                    j++;
                    qDebug() << data.at(a);
                    if (j == 6) {
                        qDebug() << "Chaine pleine";
                        afficheChaine(identification, j);
                        j = 0;
                        gestionIdentification(identification);
                        break;
                    }
                }
            }
        }
    }
    qDebug();
}

void sondeurMarin::onSerialPortButtonCloseClicked() {
    port->disconnect();
}

