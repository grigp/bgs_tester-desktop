#include "rs232datacontroller.h"

RS232DataController::RS232DataController(QObject *parent)
    : DataController (parent)
{
    run();
}

RS232DataController::~RS232DataController()
{
    stop();
}

void RS232DataController::run()
{

}

void RS232DataController::stop()
{

}
