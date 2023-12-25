//
// Created by hemingguo on 2023-12-3.
//

#include "DeliveryCenter.h"


DeliveryCenter::DeliveryCenter() : total_value(0), copper_num(0), iron_num(0), half_copper_num(0)
{

}

void DeliveryCenter::timeStart(int time)
{
    id = startTimer(time);

}

void DeliveryCenter::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == id)
    {
        copper_num++;
        qDebug() << copper_num;
    }
    if (copper_num == 10)
    {
        killTimer(id);
    }
}

void DeliveryCenter::arrival(std::string mineName, int distance, int i, int j)
{
    if (mineName == "copper")
    {
        timeStart(distance * 100);
    } else if (mineName == "iron")
    {
        timeStart(distance * 100);

    } else if (mineName == "halfcopper")
    {
        timeStart(distance * 100);

    }
}

