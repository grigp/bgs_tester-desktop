#include "bgstesterapplicaion.h"

BGSTesterApplicaion::BGSTesterApplicaion(int &argc, char **argv)
    : QApplication(argc, argv)
{
    setApplicationName("bgs-tester");
    setOrganizationName("A-Med");

}

BGSTesterApplicaion::~BGSTesterApplicaion()
{

}

QMainWindow *BGSTesterApplicaion::mainWindow() const
{
    return m_mw;
}

void BGSTesterApplicaion::setMainWindow(QMainWindow *mw)
{
    m_mw = mw;
}
