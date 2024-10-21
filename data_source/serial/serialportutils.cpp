#include "serialportutils.h"

QString getSerialPortName(const SerialPortDefines::Ports port)
{
    if (static_cast<int>(port) > 0)
        return QString("COM%1").arg(static_cast<int>(port));
    return QString("");
}


