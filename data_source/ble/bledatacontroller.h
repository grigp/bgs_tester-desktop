#ifndef BLEDATACONTROLLER_H
#define BLEDATACONTROLLER_H

#include <QObject>
#include <QThread>

#include "datacontroller.h"

/*!
 * \brief Класс, осущетсвляющий потоковое управение данными bluetooth The BLEDataController class
 */
class BLEDataController : public DataController
{
    Q_OBJECT
public:
    explicit BLEDataController(QObject *parent = nullptr);
    ~BLEDataController() override;


private:
    void run();
    void stop();

    QThread m_thread;
};

#endif // BLEDATACONTROLLER_H
