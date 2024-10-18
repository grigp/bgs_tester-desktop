INCLUDEPATH += $$PWD

include(ble/ble_src.pri)
include(rs232/rs232_src.pri)

HEADERS += \
    $$PWD/datacontroller.h

SOURCES += \
    $$PWD/datacontroller.cpp

FORMS += \

