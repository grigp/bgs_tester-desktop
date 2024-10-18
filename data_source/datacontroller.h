#ifndef DATACONTROLLER_H
#define DATACONTROLLER_H

#include <QObject>

/*!
 * \brief Суперкласс, осущетсвляющий потоковое управение данными The DataController class
 */
class DataController : public QObject
{
    Q_OBJECT
public:
    explicit DataController(QObject *parent = nullptr);

    static QByteArray setNameCommand(const QString name);
    static QByteArray setBaudCommand();
    static QByteArray setPIOCommand();
    static QByteArray setValueCommand(const quint8 value);

    static QByteArray setModulationCommand(const int idx);
    static QByteArray setFrequencyCommand(const int idx);
    static QByteArray setIntensivityCommand(const int idx);

signals:
    void getDevices();
    void connectDevice(const int idx);
    void disconnectDevice();
    void deviceFound(const QString& name, const int idx);

    void dataReady(const QByteArray& data);

    void setName(const QString name);
    void setBaud();
    void setPIO();
    void setValue(const quint8 value);
    void setModulation(const int idx);
    void setFrequency(const int idx);
    void setIntensivity(const int idx);
    void sendAnyCommand(const QByteArray &cmd);

    void deviceConnected();
    void deviceDisconnected();

public slots:
};

#endif // DATACONTROLLER_H
