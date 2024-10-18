#include "mainwindow.h"
#include <QApplication>
#include <QLoggingCategory>

#include "bgstesterapplicaion.h"

int main(int argc, char *argv[])
{
    BGSTesterApplicaion a(argc, argv);
//    QApplication a(argc, argv);
    MainWindow w;
    a.setMainWindow(&w);

    //QLoggingCategory::setFilterRules(QStringLiteral("qt.bluetooth* = true"));

    w.show();

    return a.exec();
}
