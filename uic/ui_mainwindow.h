/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *btnConnect;
    QFrame *frame;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *gbDevices;
    QVBoxLayout *verticalLayout_2;
    QListView *lvDevices;
    QPushButton *btnCreate;
    QGroupBox *gbData;
    QVBoxLayout *verticalLayout_4;
    QTextEdit *teData;
    QGroupBox *gbCommand;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnCommand1;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnUpValue;
    QPushButton *btnDownValue;
    QSpacerItem *horizontalSpacer;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(633, 509);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        btnConnect = new QPushButton(centralWidget);
        btnConnect->setObjectName(QString::fromUtf8("btnConnect"));

        verticalLayout->addWidget(btnConnect);

        frame = new QFrame(centralWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(frame);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(-1, 0, -1, 0);
        gbDevices = new QGroupBox(frame);
        gbDevices->setObjectName(QString::fromUtf8("gbDevices"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(gbDevices->sizePolicy().hasHeightForWidth());
        gbDevices->setSizePolicy(sizePolicy);
        gbDevices->setMaximumSize(QSize(16777215, 150));
        verticalLayout_2 = new QVBoxLayout(gbDevices);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(1, 1, 1, 1);
        lvDevices = new QListView(gbDevices);
        lvDevices->setObjectName(QString::fromUtf8("lvDevices"));
        lvDevices->setMaximumSize(QSize(16777215, 16777215));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        lvDevices->setFont(font);

        verticalLayout_2->addWidget(lvDevices);


        verticalLayout_3->addWidget(gbDevices);

        btnCreate = new QPushButton(frame);
        btnCreate->setObjectName(QString::fromUtf8("btnCreate"));

        verticalLayout_3->addWidget(btnCreate);

        gbData = new QGroupBox(frame);
        gbData->setObjectName(QString::fromUtf8("gbData"));
        verticalLayout_4 = new QVBoxLayout(gbData);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(1, 1, 1, 1);
        teData = new QTextEdit(gbData);
        teData->setObjectName(QString::fromUtf8("teData"));
        teData->setMaximumSize(QSize(16777215, 16777215));
        teData->setFont(font);

        verticalLayout_4->addWidget(teData);


        verticalLayout_3->addWidget(gbData);

        gbCommand = new QGroupBox(frame);
        gbCommand->setObjectName(QString::fromUtf8("gbCommand"));
        horizontalLayout = new QHBoxLayout(gbCommand);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        btnCommand1 = new QPushButton(gbCommand);
        btnCommand1->setObjectName(QString::fromUtf8("btnCommand1"));

        horizontalLayout->addWidget(btnCommand1);

        horizontalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        btnUpValue = new QPushButton(gbCommand);
        btnUpValue->setObjectName(QString::fromUtf8("btnUpValue"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(btnUpValue->sizePolicy().hasHeightForWidth());
        btnUpValue->setSizePolicy(sizePolicy1);
        btnUpValue->setMaximumSize(QSize(50, 16777215));
        QFont font1;
        font1.setBold(true);
        btnUpValue->setFont(font1);

        horizontalLayout->addWidget(btnUpValue);

        btnDownValue = new QPushButton(gbCommand);
        btnDownValue->setObjectName(QString::fromUtf8("btnDownValue"));
        sizePolicy1.setHeightForWidth(btnDownValue->sizePolicy().hasHeightForWidth());
        btnDownValue->setSizePolicy(sizePolicy1);
        btnDownValue->setMaximumSize(QSize(50, 16777215));
        btnDownValue->setFont(font1);

        horizontalLayout->addWidget(btnDownValue);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout_3->addWidget(gbCommand);


        verticalLayout->addWidget(frame);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 633, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);
        QObject::connect(btnConnect, SIGNAL(clicked()), MainWindow, SLOT(on_connect()));
        QObject::connect(lvDevices, SIGNAL(activated(QModelIndex)), MainWindow, SLOT(on_selectDevice(QModelIndex)));
        QObject::connect(lvDevices, SIGNAL(clicked(QModelIndex)), MainWindow, SLOT(on_selectDevice(QModelIndex)));
        QObject::connect(btnCommand1, SIGNAL(clicked()), MainWindow, SLOT(on_command()));
        QObject::connect(btnUpValue, SIGNAL(clicked()), MainWindow, SLOT(on_valueUp()));
        QObject::connect(btnDownValue, SIGNAL(clicked()), MainWindow, SLOT(on_valueDown()));
        QObject::connect(btnCreate, SIGNAL(clicked()), MainWindow, SLOT(on_connectDevice()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        btnConnect->setText(QApplication::translate("MainWindow", "\320\237\320\276\320\264\320\272\320\273\321\216\321\207\320\270\321\202\321\214", nullptr));
        gbDevices->setTitle(QApplication::translate("MainWindow", "\320\243\321\201\321\202\321\200\320\276\320\271\321\201\321\202\320\262\320\260", nullptr));
        btnCreate->setText(QApplication::translate("MainWindow", "\320\243\321\201\321\202\320\260\320\275\320\276\320\262\320\270\321\202\321\214 \321\201\320\262\321\217\320\267\321\214", nullptr));
        gbData->setTitle(QApplication::translate("MainWindow", "\320\224\320\260\320\275\320\275\321\213\320\265", nullptr));
        gbCommand->setTitle(QApplication::translate("MainWindow", "\320\232\320\276\320\274\320\260\320\275\320\264\321\213", nullptr));
        btnCommand1->setText(QApplication::translate("MainWindow", "\320\232\320\276\320\274\320\260\320\275\320\260\320\264 1", nullptr));
        btnUpValue->setText(QApplication::translate("MainWindow", "+", nullptr));
        btnDownValue->setText(QApplication::translate("MainWindow", "-", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
