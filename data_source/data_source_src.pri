INCLUDEPATH += $$PWD

include(ble/ble_src.pri)
include(serial/serial_src.pri)

HEADERS += \
    $$PWD/datacontroller.h

SOURCES += \
    $$PWD/datacontroller.cpp

FORMS += \

