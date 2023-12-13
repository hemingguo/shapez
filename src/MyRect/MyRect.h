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


public:
    bool isMineExist;
    bool isFacilityExist;
    Mine *mine;
    Facility *facility;
    QGraphicsPixmapItem *pixmapMineItem;
    QGraphicsPixmapItem *pixmapFacilityItem;

    MyRect();

    ~MyRect();

    void setPosition(int x, int y);

    QPoint getPosition();

    void setMine(string name);

    Mine *getMine();

    void setFacility(string name);

    Facility *getFacility();

};


#endif //SHAPEZ_MYRECT_H
