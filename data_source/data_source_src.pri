INCLUDEPATH += $$PWD

include(ble/ble_src.pri)
include(serial/serial_src.pri)

HEADERS += \
    $$PWD/datacontroller.h \
    $$PWD/datadefines.h

SOURCES += \
    $$PWD/datacontroller.cpp

FORMS += \

