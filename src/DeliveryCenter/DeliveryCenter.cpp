//
// Created by hemingguo on 2023-12-3.
//

#include "DeliveryCenter.h"

Around::Around() : id(0), isWork(false) {}

DeliveryCenter::DeliveryCenter() : total_value(0), copper_num(0), iron_num(0), half_copper_num(0)
{
    deliveryCenter = nullptr;
    copper_p = nullptr;
    copper_p_gewei = nullptr;
    copper_p_shiwei = nullptr;

    iron_p = nullptr;
    iron_p_gewei = nullptr;
    iron_p_shiwei = nullptr;

    half_copper_p = nullptr;
    half_copper_p_gewei = nullptr;
    half_copper_p_shiwei = nullptr;
}

DeliveryCenter::DeliveryCenter(QGraphicsScene *s, QGraphicsView *v) : total_value(0), copper_num(0), iron_num(0),
                                                                      half_copper_num(0)
{
    first_scene = s;
    first_view = v;
    deliveryCenter = nullptr;
    copper_p = nullptr;
    copper_p_gewei = nullptr;
    copper_p_shiwei = nullptr;

    iron_p = nullptr;
    iron_p_gewei = nullptr;
    iron_p_shiwei = nullptr;

    half_copper_p = nullptr;
    half_copper_p_gewei = nullptr;
    half_copper_p_shiwei = nullptr;
}


void DeliveryCenter::timerEvent(QTimerEvent *event)
{

    for (int i = 13; i <= 16; i++)
    {
        for (int j = 13; j <= 16; j++)
        {

            if (around[i][j].isWork && event->timerId() == around[i][j].id)
            {
                if (around[i][j].mineName == "copper")
                {
                    copper_num++;
                    total_value += 10;
                    
                    delete iron_p_gewei;
                    delete iron_p_shiwei;
                    int gewei = copper_num % 10;
                    int shiwei = copper_num / 10;
                    QString name_g = "../media/" + QString::number(gewei) + ".png";
                    QString name_s = "../media/" + QString::number(shiwei) + ".png";
                    copper_p_gewei = new QGraphicsPixmapItem(QPixmap(name_g));
                    copper_p_gewei->setPixmap(copper_p_gewei->pixmap().scaled(30, 30));
                    copper_p_gewei->setPos(15 * 50 + 40, 13 * 50 + 30);
                    first_scene->addItem(copper_p_gewei);

                    copper_p_shiwei = new QGraphicsPixmapItem(QPixmap(name_s));
                    copper_p_shiwei->setPixmap(copper_p_shiwei->pixmap().scaled(30, 30));
                    copper_p_shiwei->setPos(15 * 50 + 10, 13 * 50 + 30);
                    first_scene->addItem(copper_p_shiwei);


                } else if (around[i][j].mineName == "iron")
                {
                    iron_num++;
                    total_value += 5;
                } else if (around[i][j].mineName == "halfcopper")
                {
                    half_copper_num++;
                    total_value += 5;
                }
                qDebug() << total_value;
                qDebug() << "copper: " << copper_num << ", iron: " << iron_num;
            }

        }
    }


}

void DeliveryCenter::arrival(std::string mineName, int distance, int i, int j)
{
    if (!around[i][j].isWork)
    {
        around[i][j].mineName = mineName;
        around[i][j].isWork = true;
        around[i][j].id = startTimer(distance * 100);
        qDebug() << "start_working!";
    }
}

