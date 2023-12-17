//
// Created by hemingguo on 2023-12-3.
//

#include "Facility.h"

std::string Facility::getName()
{
    return name;
}

void Facility::setName(std::string str)
{
    name = str;
}

ConveyorBelt::ConveyorBelt()
{
    setName("conveyorbelt");
}