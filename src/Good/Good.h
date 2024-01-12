//
// Created by hemingguo on 2024-1-12.
//

#ifndef SHAPEZ_GOOD_H
#define SHAPEZ_GOOD_H

#include<iostream>
#include<QDebug>
#include <QTimer>
#include"../MyRect/MyRect.h"
#include"../Facility/Facility.h"
#include"../Mine/Mine.h"
#include"../DeliveryCenter/DeliveryCenter.h"

class Good : public QObject
{
Q_OBJECT
public:
    float miner_speed;
    float belt_speed;
    float cut_speed;
    DeliveryCenter *center;
    int oi;
    int oj;
    int i;
    int j;
    int sign;


    std::string name;
    QTimer *timer;
    QGraphicsPixmapItem *mine_pix;
    QGraphicsScene *scene;

    Good(DeliveryCenter *cen, MyRect myrect[30][30], QGraphicsScene *s, int xi, int xj, int si, std::string mineName);

    void state(int ori, int orj, int ii, int jj, int si, std::string na);

public slots:

    void pass(MyRect myrect[30][30]);


};


#endif //SHAPEZ_GOOD_H
