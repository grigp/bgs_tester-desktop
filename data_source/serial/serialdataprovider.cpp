#include "serialdataprovider.h"

#include <QDebug>

#include "datacontroller.h"

SerialDataProvider::SerialDataProvider(QObject *parent) : QObject(parent)
{

}

SerialDataProvider::~SerialDataProvider()
{
    emit finishedPort(); // Сигнал о завершении работы
}

void SerialDataProvider::processPort()
{
    // подключаем проверку ошибок порта
    connect(&m_nativePort, &QSerialPort::errorOccurred, this, &SerialDataProvider::handleError);
    // подключаем чтение с порта по сигналу readyRead()
    connect(&m_nativePort, &QSerialPort::readyRead, this, &SerialDataProvider::readPort);
}

void SerialDataProvider::disconnectPort()
{
    if(m_nativePort.isOpen())
    {
        m_nativePort.close();
        emit errorOnDevice(m_name + " " + tr("закрыт!"));
    }
}

void SerialDataProvider::connectPort()
{
    m_nativePort.setPortName(m_name);
    if (m_nativePort.open(QIODevice::ReadWrite))
    {
        if (m_nativePort.setBaudRate(m_baudRate)
                && m_nativePort.setDataBits(m_dataBits)
                && m_nativePort.setParity(m_parity)
                && m_nativePort.setStopBits(m_stopBits)
                && m_nativePort.setFlowControl(m_flowControl))
        {
            if (m_nativePort.isOpen())
            {
        //        error_((m_SettingsPort.name+ " >> Открыт!"));
            }
        }
        else
        {
            m_nativePort.close();
            errorOnDevice(m_nativePort.errorString());
        }
    }
    else
    {
        m_nativePort.close();
        errorOnDevice(m_nativePort.errorString());
    }
}

void SerialDataProvider::writeSettingsPort(QString name, int baudrate, int DataBits, int Parity, int StopBits, int FlowControl)
{
    m_name = name;
    m_baudRate = static_cast<QSerialPort::BaudRate>(baudrate);
    m_dataBits = static_cast<QSerialPort::DataBits>(DataBits);
    m_parity = static_cast<QSerialPort::Parity>(Parity);
    m_stopBits = static_cast<QSerialPort::StopBits>(StopBits);
    m_flowControl = static_cast<QSerialPort::FlowControl>(FlowControl);
}

void SerialDataProvider::writeToPort(QByteArray data)
{
    if(m_nativePort.isOpen())
    {
        m_nativePort.write(data);
    }
}

void SerialDataProvider::on_setName(const QString name)
{
    writeToPort(DataController::setNameCommand(name));
}

void SerialDataProvider::on_setBaud()
{
    writeToPort(DataController::setBaudCommand());
}

void SerialDataProvider::on_setPIO()
{
    writeToPort(DataController::setPIOCommand());
}

void SerialDataProvider::on_sendTextCommand(const QString &cmd)
{
    qDebug() << Q_FUNC_INFO << cmd;
    writeToPort(cmd.toUtf8());
}

void SerialDataProvider::handleError(QSerialPort::SerialPortError error)
{
    if ( (m_nativePort.isOpen()) && (error == QSerialPort::ResourceError))
    {
        auto s = m_nativePort.errorString();
        emit errorOnDevice(s);
        disconnectPort();
    }
}

void SerialDataProvider::readPort()
{
    QByteArray data;
    data.append(m_nativePort.readAll());
    outPortData(data);
}
