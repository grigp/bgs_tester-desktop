#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QBluetoothDeviceInfo>
#include <QLowEnergyController>
#include <QStandardItemModel>
#include <QCloseEvent>

namespace Ui {
class MainWindow;
}

class BLEDataController;
class SerialDataController;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    enum DevicesDataRoles
    {
        DeviceIdxRole = Qt::UserRole + 1
    };

signals:
    void setName(const QString name);
    void setBaud();
    void setPIO();
    void setValue(const quint8 value);
    void setModulation(const int idx);
    void setFrequency(const int idx);
    void setIntensivity(const int idx);
    void sendAnyCommand(const QByteArray &cmd);
    void sendTextCommand(const QString &cmd);

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_connect();
    void on_deviceFound(const QString& name, const int idx);
    void on_dataReady(const QByteArray& data);

    void on_selectDevice(QModelIndex index);
    void on_connectDevice();

    void on_connectSerial();
    void on_communicationError(const QString &drvName, const QString &port, const QString error);

    void on_setName();
    void on_setBaud();
    void on_setPIO();
    void on_valueUp();
    void on_valueDown();
    void on_setModulation();
    void on_setFrequency();
    void on_setIntensivity();
    void on_sendAnyCommand();
    void on_sendTextCommand();

    void on_dataClear();

    void on_deviceConnected();
    void on_deviceDisconnected();

private:
    Ui::MainWindow *ui;

    BLEDataController *m_bleDataController {nullptr};
    SerialDataController *m_serialDataController {nullptr};

    QStandardItemModel m_mdlDevices;
    int m_deviceNum {-1};
    bool m_isConnected {false};

    quint8 m_value {0};
};

#endif // MAINWINDOW_H
