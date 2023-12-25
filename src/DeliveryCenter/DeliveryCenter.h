//
// Created by hemingguo on 2023-12-3.
//

#ifndef SHAPEZ_DELIVERYCENTER_H
#define SHAPEZ_DELIVERYCENTER_H

#include <QObject>
#include <QDebug>

#include <QWidget>
#include <QTimerEvent>
#include <QGraphicsPixmapItem>

class DeliveryCenter : public QWidget
{
Q_OBJECT
public :
    DeliveryCenter();

    void timerEvent(QTimerEvent *event) override;

    void timeStart(int time);

    void arrival(std::string mineName, int distance, int i, int j);

    QGraphicsPixmapItem *deliveryCenter;
private:
    int id;
    int total_value;

    int copper_num;
    int iron_num;
    int half_copper_num;


};


#endif //SHAPEZ_DELIVERYCENTER_H
