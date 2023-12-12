//
// Created by hemingguo on 2023-12-3.
//

#include "MyRect.h"

MyRect::MyRect() : mine(nullptr), facility(nullptr), pixmapMineItem(nullptr), pixmapFacilityItem(nullptr), isMineExist(
        false), isFacilityExist(false)
{

}

MyRect::~MyRect()
{
    delete pixmapMineItem;
    delete pixmapFacilityItem;

    pixmapMineItem = nullptr;
    pixmapFacilityItem = nullptr;
}

void MyRect::setPosition(int x, int y)
{
    position.setX(x);
    position.setY(y);
}

QPoint MyRect::getPosition()
{
    return position;
}

void MyRect::setMine(string name)
{
    if (name == "iron")
    {
        mine = new Iron();
    } else if (name == "copper")
    {
        mine = new Copper();
    }
}

Mine *MyRect::getMine()
{
    return mine;
}
