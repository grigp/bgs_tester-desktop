#include "bledatacontroller.h"

#include "bledataprovider.h"

BLEDataController::BLEDataController(QObject *parent) : QObject(parent)
{
    run();
}

BLEDataController::~BLEDataController()
{
    stop();
}

void BLEDataController::run()
{
    BLEDataProvider *ble_dpv = new BLEDataProvider;
    ble_dpv->moveToThread(&m_thread);

    connect(&m_thread, &QThread::finished, ble_dpv, &QObject::deleteLater);
    connect(this, &BLEDataController::getDevices, ble_dpv, &BLEDataProvider::getDevices);
    connect(this, &BLEDataController::connectDevice, ble_dpv, &BLEDataProvider::doConnectDevice);
    connect(this, &BLEDataController::disconnectDevice, ble_dpv, &BLEDataProvider::doDisconnectDevice);
    connect(ble_dpv, &BLEDataProvider::dataReady, this, &BLEDataController::dataReady);
    connect(ble_dpv, &BLEDataProvider::deviceFound, this, &BLEDataController::deviceFound);

    connect(this, &BLEDataController::setName, ble_dpv, &BLEDataProvider::on_setName);
    connect(this, &BLEDataController::setBaud, ble_dpv, &BLEDataProvider::on_setBaud);
    connect(this, &BLEDataController::setPIO, ble_dpv, &BLEDataProvider::on_setPIO);
    connect(this, &BLEDataController::setValue, ble_dpv, &BLEDataProvider::on_setValue);
    connect(this, &BLEDataController::setModulation, ble_dpv, &BLEDataProvider::on_setModulation);
    connect(this, &BLEDataController::setFrequency, ble_dpv, &BLEDataProvider::on_setFrequency);
    connect(this, &BLEDataController::setIntensivity, ble_dpv, &BLEDataProvider::on_setIntensivity);
    connect(this, &BLEDataController::sendAnyCommand, ble_dpv, &BLEDataProvider::on_sendAnyCommand);

    connect(ble_dpv, &BLEDataProvider::deviceConnected, this, &BLEDataController::deviceConnected);
    connect(ble_dpv, &BLEDataProvider::deviceDisconnected, this, &BLEDataController::deviceDisconnected);

    m_thread.start();
}

void BLEDataController::stop()
{
    m_thread.quit();
    m_thread.wait();
}
