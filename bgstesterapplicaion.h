#ifndef BGSTESTERAPPLICAION_H
#define BGSTESTERAPPLICAION_H

#include <QApplication>
#include <QObject>
#include <QMainWindow>

class BGSTesterApplicaion : public QApplication
{
    Q_OBJECT
public:
    BGSTesterApplicaion(int &argc, char **argv);
    ~BGSTesterApplicaion() override;

    QMainWindow* mainWindow() const;
    void setMainWindow(QMainWindow *mw);

private:
    QMainWindow *m_mw;

};

#endif // BGSTESTERAPPLICAION_H
