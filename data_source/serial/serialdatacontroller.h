#ifndef SERIALDATACONTROLLER_H
#define SERIALDATACONTROLLER_H

#include <QObject>
#include <QThread>

#include "datacontroller.h"
#include "serialportdefines.h"


/*!
 * \brief Класс, осущетсвляющий потоковое управение данными через rs232 The RS232DataController class
 */
class SerialDataController : public DataController
{
    Q_OBJECT
public:
    SerialDataController(SerialPortDefines::Ports port, QObject *parent = nullptr);
    ~SerialDataController() override;

signals:
    void started();
    void stopped();

    void sendData(const QByteArray data);
    void communicationError(const QString &drvName, const QString &port, const QString error);

    void connectPort();
    void disconnectPort();

    void setPortSettings(const QString &name,
                         const int baudrate, const int DataBits, const int Parity,
                         const int StopBits, const int FlowControl);
    void writeData(const QByteArray data);

private slots:
    virtual void on_readData(const QByteArray data);
    virtual void on_error(const QString &err);

private:
    void run();
    void stop();

    QThread m_thread;
    SerialPortDefines::Ports m_port {SerialPortDefines::pcNone};
};

#endif // SERIALDATACONTROLLER_H
