//
// Created by hemingguo on 2023-12-3.
//

#include "MyRect.h"


void MyRect::setPosition(int x, int y)
{
    position.setX(x);
    position.setY(y);
}

QPoint MyRect::getPosition()
{
    return position;
}