//
// Created by hemingguo on 2023-12-3.
//

#ifndef SHAPEZ_MYRECT_H
#define SHAPEZ_MYRECT_H


#include <QGraphicsPixmapItem>
#include "../Mine/Mine.h"
#include "../Facility/Facility.h"

class MyRect
{
private :
    QPoint position;
    Mine *mine;


public:
    bool isMineExist;
    bool isFacilityExist;

    Facility *facility;
    QGraphicsPixmapItem *pixmapMineItem;
    QGraphicsPixmapItem *pixmapFacilityItem;

    MyRect();

    ~MyRect();

    void setPosition(int x, int y);

    QPoint getPosition();

    void setMine(string name);

    Mine *getMine();


};


#endif //SHAPEZ_MYRECT_H
