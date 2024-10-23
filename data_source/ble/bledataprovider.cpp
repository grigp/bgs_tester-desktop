#include "bledataprovider.h"

#include <QBluetoothDeviceDiscoveryAgent>
#include <QDebug>

#include "datacontroller.h"

namespace
{
static const QString CustomServiceUID = "{0000ffe0-0000-1000-8000-00805f9b34fb}";
static const QString BGSDataUID = "{0000ffe1-0000-1000-8000-00805f9b34fb}";

}

BLEDataProvider::BLEDataProvider(QObject *parent) : QObject(parent)
{

}

void BLEDataProvider::getDevices()
{
    QByteArray data;

    m_deviceDiscoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);
    m_deviceDiscoveryAgent->setLowEnergyDiscoveryTimeout(15000);

    connect(m_deviceDiscoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
            this, &BLEDataProvider::addDevice);
//    connect(m_deviceDiscoveryAgent, &QBluetoothDeviceDiscoveryAgent::errorOccurred,
//            this, &DeviceFinder::scanError);

    connect(m_deviceDiscoveryAgent, &QBluetoothDeviceDiscoveryAgent::finished,
            this, &BLEDataProvider::scanFinished);
    connect(m_deviceDiscoveryAgent, &QBluetoothDeviceDiscoveryAgent::canceled,
            this, &BLEDataProvider::scanFinished);
    m_deviceDiscoveryAgent->start(QBluetoothDeviceDiscoveryAgent::LowEnergyMethod);

    emit dataReady(data);
}

void BLEDataProvider::doConnectDevice(const int idx)
{
    if (! m_control)
    {
        m_control = QLowEnergyController::createCentral(m_devices.at(idx));

        connect(m_control, &QLowEnergyController::serviceDiscovered,
                this, &BLEDataProvider::on_serviceDiscovered);
        connect(m_control, &QLowEnergyController::discoveryFinished,
                this, &BLEDataProvider::on_discoveryFinished);

        connect(m_control, static_cast<void (QLowEnergyController::*)(QLowEnergyController::Error)>(&QLowEnergyController::error),
                this, [this](QLowEnergyController::Error error)
                {
                    Q_UNUSED(error);
                    qDebug() << Q_FUNC_INFO << "Cannot connect to remote device.";
                    //setError("Cannot connect to remote device.");
                });
        connect(m_control, &QLowEnergyController::connected, this, [this]()
                {
                    qDebug() << Q_FUNC_INFO << "Controller connected. Search services...";
                    //        setInfo("Controller connected. Search services...");
                    emit deviceConnected();
                    m_control->discoverServices();
                });
        connect(m_control, &QLowEnergyController::disconnected, this, [this]()
                {
                    qDebug() << Q_FUNC_INFO << "LowEnergy controller disconnected";
                    emit deviceDisconnected();
                    //        setError("LowEnergy controller disconnected");
                });
    }

    // Connect
    m_control->connectToDevice();
}

void BLEDataProvider::doDisconnectDevice()
{
    if (m_control)
    {
        m_control->disconnectFromDevice();
        delete m_control;
        m_control = nullptr;
    }
}

void BLEDataProvider::on_setName(const QString name)
{
    if (m_service)
    {
        m_service->writeCharacteristic(m_info, DataController::setNameCommand(name));
    }
}

void BLEDataProvider::on_setBaud()
{
    if (m_service)
    {
        m_service->writeCharacteristic(m_info, DataController::setBaudCommand());
    }
}

void BLEDataProvider::on_setPIO()
{
    if (m_service)
    {
        m_service->writeCharacteristic(m_info, DataController::setPIOCommand());
    }
}

void BLEDataProvider::on_setValue(const quint8 value)
{
    if (m_service)
    {
        m_service->writeCharacteristic(m_info, DataController::setValueCommand(value));
    }
}

void BLEDataProvider::on_setModulation(const int idx)
{
    if (m_service)
    {
        m_service->writeCharacteristic(m_info, DataController::setModulationCommand(idx));
    }
}

void BLEDataProvider::on_setFrequency(const int idx)
{
    if (m_service)
    {
        m_service->writeCharacteristic(m_info, DataController::setFrequencyCommand(idx));
    }
}

void BLEDataProvider::on_setIntensivity(const int idx)
{
    if (m_service)
    {
        m_service->writeCharacteristic(m_info, DataController::setIntensivityCommand(idx));
    }
}

void BLEDataProvider::on_sendAnyCommand(const QByteArray &cmd)
{
    if (m_service)
    {
        m_service->writeCharacteristic(m_info, cmd);
    }
}

void BLEDataProvider::on_sendTextCommand(const QString &cmd)
{
    if (m_service)
    {
        m_service->writeCharacteristic(m_info, cmd.toUtf8());
    }
}

void BLEDataProvider::addDevice(const QBluetoothDeviceInfo &device)
{
    // If device is LowEnergy-device, add it to the list
    if (device.coreConfigurations() & QBluetoothDeviceInfo::LowEnergyCoreConfiguration)
    {
        ++m_dvcCount;
        m_devices << device;
        emit deviceFound(device.name(), m_dvcCount);
        qDebug() << "Found new device:" << device.name() << '(' << device.address().toString() << ')';
//        auto devInfo = new DeviceInfo(device);
//        auto it = std::find_if(m_devices.begin(), m_devices.end(),
//                               [devInfo](DeviceInfo *dev) {
//                                   return devInfo->getAddress() == dev->getAddress();
//                               });
//        if (it == m_devices.end()) {
//            m_devices.append(devInfo);
//        } else {
//            auto oldDev = *it;
//            *it = devInfo;
//            delete oldDev;
//        }
//        setInfo(tr("Low Energy device found. Scanning more..."));
    }
    //...

}

void BLEDataProvider::scanFinished()
{

}

void BLEDataProvider::on_serviceDiscovered(const QBluetoothUuid &newService)
{
    if (newService == QBluetoothUuid(CustomServiceUID))
    {
        m_foundBGSService = true;
    }
}

void BLEDataProvider::on_discoveryFinished()
{
    if (m_foundBGSService)
        m_service = m_control->createServiceObject(QBluetoothUuid(CustomServiceUID), this);

    if (m_service)
    {
        connect(m_service, &QLowEnergyService::stateChanged, this, &BLEDataProvider::on_stateChanged);
        connect(m_service, &QLowEnergyService::characteristicChanged, this, &BLEDataProvider::on_characteristicChanged);
        connect(m_service, &QLowEnergyService::descriptorWritten, this, &BLEDataProvider::on_descriptorWritten);
        m_service->discoverDetails();
    }
}

void BLEDataProvider::on_stateChanged(QLowEnergyService::ServiceState newState)
{

}

void BLEDataProvider::on_characteristicChanged(const QLowEnergyCharacteristic &info, const QByteArray &value)
{
    if (info.uuid() != QBluetoothUuid(BGSDataUID))
        return;

    m_info = info;
    emit dataReady(value);
}

void BLEDataProvider::on_descriptorWritten(const QLowEnergyDescriptor &info, const QByteArray &value)
{

}

