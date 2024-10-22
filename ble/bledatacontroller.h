#ifndef BLEDATACONTROLLER_H
#define BLEDATACONTROLLER_H

#include <QObject>
#include <QThread>

/*!
 * \brief Класс, осущетсвляющий потоковое упралвение данными bluetooth The BLEDataController class
 */
class BLEDataController : public QObject
{
    Q_OBJECT
public:
    explicit BLEDataController(QObject *parent = nullptr);
    ~BLEDataController() override;

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

private slots:


private:
    void run();
    void stop();

    QThread m_thread;
};

#endif // BLEDATACONTROLLER_H
