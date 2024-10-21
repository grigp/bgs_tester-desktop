#ifndef SERIALDATAPROVIDER_H
#define SERIALDATAPROVIDER_H

#include <QObject>
#include <QSerialPort>

/*!
 * \brief Класс, выполняющий работы с последовательным портом The SerialDataProvider class
 */
class SerialDataProvider : public QObject
{
    Q_OBJECT
public:
    explicit SerialDataProvider(QObject *parent = nullptr);
    ~SerialDataProvider() override;

signals:
    /*!
     * \brief Сигнал закрытия класса
     */
    void finishedPort();
    /*!
     * \brief Сигнал ошибок порта
     */
    void errorOnDevice(const QString &err);
    /*!
     * \brief Сигнал вывода полученных данных
     */
    void outPortData(const QByteArray data);

public slots:
    void processPort();

    /*!
     * \brief Слот отключения порта
     */
    void disconnectPort();

    /*!
     * \brief Слот подключения порта
     */
    void connectPort(void);

    /*!
     * \brief Слот занесение настроек порта в класс
     */
    void writeSettingsPort(QString name, int baudrate, int DataBits, int Parity, int StopBits, int FlowControl);

    /*!
     * \brief Слот отправки данных в порт
     */
    void writeToPort(QByteArray data);

private slots:
    /*!
     * \brief Слот обработки ошибок
     */
    void handleError(QSerialPort::SerialPortError error);
    /*!
     * \brief Слот чтения из порта по ReadyRead
     */
    void readPort();

private:
    QSerialPort m_nativePort;
    QString m_name {""};
    QSerialPort::BaudRate m_baudRate {QSerialPort::Baud115200};
    QSerialPort::DataBits m_dataBits {QSerialPort::Data8};
    QSerialPort::Parity m_parity {QSerialPort::NoParity};
    QSerialPort::StopBits m_stopBits {QSerialPort::OneStop};
    QSerialPort::FlowControl m_flowControl {QSerialPort::NoFlowControl};
};

#endif // SERIALDATAPROVIDER_H
