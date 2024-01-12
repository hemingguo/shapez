//
// Created by hemingguo on 2023-12-3.
//

#ifndef SHAPEZ_MINE_H
#define SHAPEZ_MINE_H

#include <string>

using namespace std;

class Mine
{
protected:
    string name; //矿物名称
    int value;  //矿物价值
    Mine();  //构造函数
    ~Mine(); //析构函数
public:
    bool divisible;  //矿物是否可以被切割
    string getName();  //返回矿物名称
    int getValue();   //返回矿物价值


};


class Iron : public Mine
{
protected:

    ~Iron();

public:
    void paintIron();

    Iron();
};


class Copper : public Mine
{


protected:


    ~Copper();

public:
    void paintCopper();

    Copper();
};


class HalfCopper : public Copper
{


    ~HalfCopper();

public:
    void paintHalfCopper();

    std::string l_or_r;

    HalfCopper();
};


#endif //SHAPEZ_MINE_H
