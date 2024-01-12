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
public:
    Bin();

};

class Miner : public Facility
{
private:
    int direction;

public:
    Miner();

    void setDirection(int x);

    int getDirection();
};

class ConveyorBelt : public Facility
{
private:
    int door;

public:
    ConveyorBelt();

    std::string turn;

    void setDoor(int x);

    int getDoor();

};

class CutMachine : public Facility
{
public:
    CutMachine();

    std::string l_or_r;
    int direction;
};

#endif //SHAPEZ_FACILITY_H
