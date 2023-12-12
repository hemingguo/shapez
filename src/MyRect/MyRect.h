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
    Facility *facility;
    bool isMineExist;
    bool isFacilityExist;
    QGraphicsPixmapItem *pixmapMineItem;
    QGraphicsPixmapItem *pixmapFacilityItem;

public:
    void setPosition(int x, int y);

    QPoint getPosition();
};


#endif //SHAPEZ_MYRECT_H
