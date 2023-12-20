//
// Created by hemingguo on 2023-12-3.
//

#include "Facility.h"

//Facility
std::string Facility::getName()
{
    return name;
}

void Facility::setName(std::string str)
{
    name = str;
}


//ConveyorBelt
ConveyorBelt::ConveyorBelt()
{
    setName("conveyorbelt");
    turn = "null";
}

int ConveyorBelt::getDoor()
{
    return door;
}

void ConveyorBelt::setDoor(int x)
{
    door = x;
}

//Miner
Miner::Miner()
{
    setName("miner");
}

int Miner::getDirection()
{
    return direction;
}

void Miner::setDirection(int x)
{
    direction = x;
}


//Bin
Bin::Bin()
{
    setName("bin");
}
