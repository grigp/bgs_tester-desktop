#ifndef BLEDATAPROVIDER_H
#define BLEDATAPROVIDER_H

#include <QObject>
#include <QBluetoothDeviceInfo>
#include <QLowEnergyController>

class QBluetoothDeviceDiscoveryAgent;

/*!
 * \brief Класс, выполняющий работы с bluetooth The BLEDataProvider class
 */
class BLEDataProvider : public QObject
{
    Q_OBJECT
public:
    explicit BLEDataProvider(QObject *parent = nullptr);

signals:
    void deviceFound(const QString& name, const int idx);
    void dataReady(const QByteArray& data);

    void deviceConnected();
    void deviceDisconnected();

public slots:
    void getDevices();
    void doConnectDevice(const int idx);
    void doDisconnectDevice();

    void on_setName(const QString name);
    void on_setBaud();
    void on_setPIO();
    void on_setValue(const quint8 value);
    void on_setModulation(const int idx);
    void on_setFrequency(const int idx);
    void on_setIntensivity(const int idx);
    void on_sendAnyCommand(const QByteArray &cmd);

private slots:
    void addDevice(const QBluetoothDeviceInfo &device);
    void scanFinished();

    void on_serviceDiscovered(const QBluetoothUuid &newService);
    void on_discoveryFinished();

    void on_stateChanged(QLowEnergyService::ServiceState newState);
    void on_characteristicChanged(const QLowEnergyCharacteristic &info, const QByteArray &value);
    void on_descriptorWritten(const QLowEnergyDescriptor &info, const QByteArray &value);

private:
    QBluetoothDeviceDiscoveryAgent* m_deviceDiscoveryAgent {nullptr};
    QList<QBluetoothDeviceInfo> m_devices;
    int m_dvcCount {-1};
    QLowEnergyController *m_control {nullptr};
    bool m_foundBGSService {false};
    QLowEnergyService *m_service {nullptr};
    QLowEnergyCharacteristic m_info;
};

#endif // BLEDATAPROVIDER_H
