//
// Created by hemingguo on 2023-12-3.
//

#ifndef SHAPEZ_FACILITY_H
#define SHAPEZ_FACILITY_H

#include<iostream>

class Facility
{

    std::string name;
public:
    std::string getName();

    void setName(std::string str);
};

class Bin : public Facility
{

};

class Miner : public Facility
{
};

class ConveyorBelt : public Facility
{
public:
    ConveyorBelt();


};

class CutMachine : public Facility
{

};

#endif //SHAPEZ_FACILITY_H
