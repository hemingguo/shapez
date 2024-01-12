//
// Created by hemingguo on 2023-12-3.
//

#include "Mine.h"

//Mine-----------
string Mine::getName()
{
    return this->name;
}

int Mine::getValue()
{
    return this->value;
}

Mine::Mine() : name("unkonwn"), value(0)
{

}

Mine::~Mine() {}

//----------------Mine



//Iron---------------
Iron::Iron()
{
    name = "iron";
    value = 5;
    divisible = false;
}

Iron::~Iron() {}

void Iron::paintIron() {}
//---------------Iron



//Copper--------------
Copper::Copper()
{
    name = "copper";
    value = 10;
    divisible = true;
}

Copper::~Copper() {}

void Copper::paintCopper() {}
//--------------Copper



//HalfCopper-------------
HalfCopper::HalfCopper()
{
    name = "halfcopper";
    value = 5;
    divisible = false;
    l_or_r = "unknown";
}

HalfCopper::~HalfCopper() {}

void HalfCopper::paintHalfCopper() {}
//-------------HalfCopper