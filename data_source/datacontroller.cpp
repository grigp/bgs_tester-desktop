#include "datacontroller.h"

DataController::DataController(QObject *parent) : QObject(parent)
{

}

QByteArray DataController::setNameCommand(const QString name)
{
    QByteArray command("AT+NAME");
    command.append("BG_" + name);
    return command;
}

QByteArray DataController::setBaudCommand()
{
    return QByteArray("AT+BAUD4");
}

QByteArray DataController::setPIOCommand()
{
    return QByteArray("AT+PIO11");
}

QByteArray DataController::setValueCommand(const quint8 value)
{
    QByteArray command;
    command.append(static_cast<char>(0x91));
    command.append(static_cast<char>(value));
    return command;
}

QByteArray DataController::setModulationCommand(const int idx)
{
    QByteArray command;
    command.append(static_cast<char>(0xA1));
    command.append(static_cast<char>(idx));
    return command;
}

QByteArray DataController::setFrequencyCommand(const int idx)
{
    QByteArray command;
    command.append(static_cast<char>(0xA2));
    command.append(static_cast<char>(idx));
    return command;
}

QByteArray DataController::setIntensivityCommand(const int idx)
{
    QByteArray command;
    command.append(static_cast<char>(0xA3));
    command.append(static_cast<char>(idx));
    return command;
}
