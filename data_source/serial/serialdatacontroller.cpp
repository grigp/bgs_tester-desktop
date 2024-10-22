#include "serialdatacontroller.h"

#include <QDebug>

#include "serialdataprovider.h"
#include "serialportutils.h"

SerialDataController::SerialDataController(SerialPortDefines::Ports port, QObject *parent)
    : DataController (parent)
    , m_port(port)
{
    run();
}

SerialDataController::~SerialDataController()
{
    stop();
}

void SerialDataController::on_readData(const QByteArray data)
{
    emit sendData(data);
}

void SerialDataController::on_error(const QString &err)
{
    emit communicationError("SerialPort", getSerialPortName(m_port), err);
}

void SerialDataController::run()
{
    SerialDataProvider *dpv = new SerialDataProvider;
    dpv->moveToThread(&m_thread);

    connect(&m_thread, &QThread::finished, dpv, &QObject::deleteLater);

    connect(dpv, &SerialDataProvider::errorOnDevice, this, &SerialDataController::on_error);
    connect(&m_thread, &QThread::started, dpv, &SerialDataProvider::processPort);
    connect(dpv, &SerialDataProvider::finishedPort, &m_thread, &QThread::quit);
    connect(&m_thread, &QThread::finished, dpv, &SerialDataProvider::deleteLater);
    connect(dpv, &SerialDataProvider::finishedPort, &m_thread, &QThread::deleteLater);
    connect(this, &SerialDataController::setPortSettings, dpv, &SerialDataProvider::writeSettingsPort);
    connect(this, &SerialDataController::connectPort, dpv, &SerialDataProvider::connectPort);
    connect(this, &SerialDataController::disconnectPort, dpv, &SerialDataProvider::disconnectPort);
    connect(dpv, &SerialDataProvider::outPortData, this, &SerialDataController::on_readData);
    connect(this, &SerialDataController::writeData, dpv, &SerialDataProvider::writeToPort);
    connect(this, &SerialDataController::setName, dpv, &SerialDataProvider::on_setName);
    connect(this, &SerialDataController::setBaud, dpv, &SerialDataProvider::on_setBaud);
    connect(this, &SerialDataController::setPIO, dpv, &SerialDataProvider::on_setPIO);
    connect(this, &SerialDataController::sendTextCommand, dpv, &SerialDataProvider::on_sendTextCommand);

    emit setPortSettings(getSerialPortName(m_port),
                         QSerialPort::Baud115200,
                         QSerialPort::Data8,
                         QSerialPort::NoParity,
                         QSerialPort::OneStop,
                         QSerialPort::NoFlowControl);
    emit connectPort();

    m_thread.start();
}

void SerialDataController::stop()
{
    m_thread.quit();
    m_thread.wait();
}
