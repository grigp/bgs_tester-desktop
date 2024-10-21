#-------------------------------------------------
#
# Project created by QtCreator 2023-11-23T11:09:34
#
#-------------------------------------------------

QT       += core gui bluetooth serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = bgs_tester
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#CONFIG += c++11
CONFIG += -native-win32-bluetooth

# каталог, в котором будет располагаться результирующий исполняемый файл
DESTDIR = $$OUT_PWD/bin

MOC_DIR = moc
OBJECTS_DIR = obj
RCC_DIR = rcc
UI_DIR = uic


SOURCES += \
        bgstesterapplicaion.cpp \
        main.cpp \
        mainwindow.cpp \
        settingsprovider.cpp

HEADERS += \
        bgstesterapplicaion.h \
        mainwindow.h \
        settingsprovider.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

include(data_source/data_source_src.pri)

DISTFILES += \
    bgs_tester.qml

RESOURCES += \
    kernel.qrc

win32:RC_FILE = bgs-tester.rc
