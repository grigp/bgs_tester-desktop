#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "bledatacontroller.h"
#include "settingsprovider.h"

#include <QMessageBox>
#include <QStringList>
#include <QDebug>

#include "serialportdefines.h"
#include "serialportutils.h"
#include "serialdatacontroller.h"

namespace
{
const QStringList Modulations = QStringList() << "без модуляции" << "3:1" << "5:1" << "1:1";
const QStringList Frequencies = QStringList() << "15 Гц" << "30 Гц" << "60 Гц" << "90 Гц"
                                              << "120 Гц" << "180 Гц" << "350 Гц" << "Fm";
const QStringList Intensivity = QStringList() << "1" << "2" << "3" << "4";
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto val = SettingsProvider::valueFromRegAppCopy("MainWindow", "Geometry").toByteArray();
    restoreGeometry(val);

    ui->lvDevices->setModel(&m_mdlDevices);

    for (int i = 0; i < Modulations.size(); ++i)
        ui->cbModulation->addItem(Modulations.at(i));
    for (int i = 0; i < Frequencies.size(); ++i)
        ui->cbFrequency->addItem(Frequencies.at(i));
    for (int i = 0; i < Intensivity.size(); ++i)
        ui->cbIntensivity->addItem(Intensivity.at(i));

    for (int i = SerialPortDefines::pcCom1; i <= SerialPortDefines::pcCom127; ++i)
    {
        ui->cbPort->addItem(getSerialPortName(static_cast<SerialPortDefines::Ports>(i)), i);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    SettingsProvider::setValueToRegAppCopy("MainWindow", "Geometry", saveGeometry());
    event->accept();
}

void MainWindow::on_connect()
{
    if (!m_bleDataController)
    {
        m_bleDataController = new BLEDataController(this);
        m_mdlDevices.clear();
        connect(m_bleDataController, &BLEDataController::deviceFound, this, &MainWindow::on_deviceFound);
        connect(m_bleDataController, &BLEDataController::dataReady, this, &MainWindow::on_dataReady);
        connect(this, &MainWindow::setName, m_bleDataController, &BLEDataController::setName);
        connect(this, &MainWindow::setBaud, m_bleDataController, &BLEDataController::setBaud);
        connect(this, &MainWindow::setPIO, m_bleDataController, &BLEDataController::setPIO);
        connect(this, &MainWindow::setValue, m_bleDataController, &BLEDataController::setValue);
        connect(this, &MainWindow::setModulation, m_bleDataController, &BLEDataController::setModulation);
        connect(this, &MainWindow::setFrequency, m_bleDataController, &BLEDataController::setFrequency);
        connect(this, &MainWindow::setIntensivity, m_bleDataController, &BLEDataController::setIntensivity);
        connect(this, &MainWindow::sendAnyCommand, m_bleDataController, &BLEDataController::sendAnyCommand);

        connect(m_bleDataController, &BLEDataController::deviceConnected, this, &MainWindow::on_deviceConnected);
        connect(m_bleDataController, &BLEDataController::deviceDisconnected, this, &MainWindow::on_deviceDisconnected);

        emit m_bleDataController->getDevices();
        ui->btnConnect->setText(tr("Очистить список устройств"));
    }
    else
    {
        delete m_bleDataController;
        m_bleDataController = nullptr;
        m_mdlDevices.clear();
        ui->btnConnect->setText(tr("Получить список устройств"));
    }
}

void MainWindow::on_deviceFound(const QString& name, const int idx)
{
    QStandardItem *item = new QStandardItem(name);
    item->setData(idx, DeviceIdxRole);
    item->setEditable(false);
    m_mdlDevices.appendRow(item);
}

void MainWindow::on_dataReady(const QByteArray &data)
{
    QString s = "";
    for (int i = 0; i < data.size(); ++i)
    {
        if (i == 5)
            m_value = data.at(i);
        quint8 b = static_cast<quint8>(data.at(i));
        s = s + "x" + QString::number(b, 16) + " ";
    }
    ui->teData->append(s);
}

void MainWindow::on_selectDevice(QModelIndex index)
{
    m_deviceNum = index.row();
}


void MainWindow::on_connectDevice()
{
    if (m_bleDataController)
    {
        if (! m_isConnected)
        {
            if (m_deviceNum >= 0)
                emit m_bleDataController->connectDevice(m_deviceNum);
            else
                QMessageBox::information(nullptr, "Предупреждение", "Сначала необходимо выбрать одно из устройств");
        }
        else
        {
            emit m_bleDataController->disconnectDevice();
        }
    }
    else
        QMessageBox::information(nullptr, "Предупреждение", "Сначала необходимо получить список устройств и выбрать одно из них");
}

void MainWindow::on_connectSerial()
{
    if (!m_serialDataController)
    {
        m_serialDataController = new SerialDataController(static_cast<SerialPortDefines::Ports>(ui->cbPort->currentData().toInt()), this);

        ui->btnConnectSerial->setText(tr("Отключить"));
    }
    else
    {
        delete m_serialDataController;
        m_serialDataController = nullptr;
        ui->btnConnectSerial->setText(tr("Подключить"));
    }
}

void MainWindow::on_setName()
{
    if (m_isConnected)
    {
        if (ui->edName->text() != "")
        {
            emit setName(ui->edName->text());
        }
        else
            QMessageBox::information(nullptr, "Предупреждение", "Не введено название устройства");
    }
    else
        QMessageBox::information(nullptr, "Предупреждение", "Необходимо сначала установить связь с устройством");
}

void MainWindow::on_setBaud()
{
    if (m_isConnected)
    {
        emit setBaud();
    }
    else
        QMessageBox::information(nullptr, "Предупреждение", "Необходимо сначала установить связь с устройством");
}

void MainWindow::on_setPIO()
{
    if (m_isConnected)
    {
        emit setPIO();
    }
    else
        QMessageBox::information(nullptr, "Предупреждение", "Необходимо сначала установить связь с устройством");
}

void MainWindow::on_valueUp()
{
    if (m_isConnected)
    {
        if (m_value < 125)
            ++m_value;
        emit setValue(m_value);
    }
    else
        QMessageBox::information(nullptr, "Предупреждение", "Необходимо сначала установить связь с устройством");
}

void MainWindow::on_valueDown()
{
    if (m_isConnected)
    {
        if (m_value > 0)
                --m_value;
        emit setValue(m_value);
    }
    else
        QMessageBox::information(nullptr, "Предупреждение", "Необходимо сначала установить связь с устройством");
}

void MainWindow::on_setModulation()
{
    if (m_isConnected)
    {
        emit setModulation(ui->cbModulation->currentIndex());
    }
    else
        QMessageBox::information(nullptr, "Предупреждение", "Необходимо сначала установить связь с устройством");
}

void MainWindow::on_setFrequency()
{
    if (m_isConnected)
    {
        emit setFrequency(ui->cbFrequency->currentIndex());
    }
    else
        QMessageBox::information(nullptr, "Предупреждение", "Необходимо сначала установить связь с устройством");
}

void MainWindow::on_setIntensivity()
{
    if (m_isConnected)
    {
        emit setIntensivity(ui->cbIntensivity->currentIndex());
    }
    else
        QMessageBox::information(nullptr, "Предупреждение", "Необходимо сначала установить связь с устройством");
}

void MainWindow::on_sendAnyCommand()
{
    if (m_isConnected)
    {
        QByteArray cmd;
        QString sCmd = "";
        QStringList slBytes = ui->edCmd->text().split(' ');
        for (int i = 0; i < slBytes.size(); ++i)
        {
                QString sb = slBytes.at(i);
                quint8 b = sb.toInt(nullptr, 16);
                cmd.append(b);
                sCmd = sCmd + "0x" + QString::number(b, 16) + " ";
                //        qDebug() << i << sb << b;
        }

        auto mr = QMessageBox::information(nullptr, "Предупреждение", "Передать команду (" + sCmd + ")?",
                                           QMessageBox::Yes | QMessageBox::No);
        if (mr == QMessageBox::Yes)
        {
                emit sendAnyCommand(cmd);
        }
    }
    else
        QMessageBox::information(nullptr, "Предупреждение", "Необходимо сначала установить связь с устройством");
}

void MainWindow::on_deviceConnected()
{
    m_isConnected = true;
    ui->btnConnect->setEnabled(false);
    ui->lvDevices->setEnabled(false);
    ui->btnCreate->setText("Прекратить связь");
}

void MainWindow::on_deviceDisconnected()
{
    m_isConnected = false;
    ui->btnConnect->setEnabled(true);
    ui->lvDevices->setEnabled(true);
    ui->btnCreate->setText("Установить связь");
}
