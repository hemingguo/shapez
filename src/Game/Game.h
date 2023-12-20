//
// Created by hemingguo on 2023-12-14.
//

#ifndef SHAPEZ_GAME_H
#define SHAPEZ_GAME_H

#include<iostream>
#include<QDebug>
#include"../MyRect/MyRect.h"
#include"../Facility/Facility.h"
#include"../Mine/Mine.h"


class Game
{
public:


    void dig(MyRect myrect[30][30], int i, int j);

    void pass(MyRect myrect[30][30], int i, int j, int sign, int oi, int oj);
};


#endif //SHAPEZ_GAME_H
