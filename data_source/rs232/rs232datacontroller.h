#ifndef RS232DATACONTROLLER_H
#define RS232DATACONTROLLER_H

#include <QObject>
#include <QThread>

#include "datacontroller.h"

/*!
 * \brief Класс, осущетсвляющий потоковое управение данными через rs232 The RS232DataController class
 */
class RS232DataController : public DataController
{
public:
    RS232DataController();
    ~RS232DataController() override;

private:
    void run();
    void stop();

    QThread m_thread;
};

#endif // RS232DATACONTROLLER_H
