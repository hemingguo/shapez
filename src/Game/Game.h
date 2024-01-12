//
// Created by hemingguo on 2023-12-14.
//

#ifndef SHAPEZ_GAME_H
#define SHAPEZ_GAME_H

#include<iostream>
#include<QDebug>
#include <QTimer>
#include"../MyRect/MyRect.h"
#include"../Facility/Facility.h"
#include"../Mine/Mine.h"
#include"../DeliveryCenter/DeliveryCenter.h"


class Game
{
public:

    static float miner_speed;
    static float belt_speed;
    static float cut_speed;

    DeliveryCenter *center;

    explicit Game(DeliveryCenter *x = nullptr, QGraphicsScene *s = nullptr);

    void check(MyRect myrect[30][30]);

    void dig(MyRect myrect[30][30], int i, int j);

    //void pass(MyRect myrect[30][30], int i, int j, int sign, int oi, int oj, string mineName, int distance);

    QGraphicsScene *scene;
};


#endif //SHAPEZ_GAME_H
