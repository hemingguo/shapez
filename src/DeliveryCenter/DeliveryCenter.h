//
// Created by hemingguo on 2023-12-3.
//

#ifndef SHAPEZ_DELIVERYCENTER_H
#define SHAPEZ_DELIVERYCENTER_H

#include <QObject>
#include <QDebug>

#include <QWidget>
#include <QTimerEvent>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include "../MyRect/MyRect.h"


class DeliveryCenter : public QWidget
{
Q_OBJECT
public :
    explicit DeliveryCenter();

    explicit DeliveryCenter(QGraphicsScene *s, QGraphicsView *v);


    void acc(std::string mineName);


    QGraphicsView *first_view;
    QGraphicsScene *first_scene;

    QGraphicsPixmapItem *deliveryCenter;

    // 三个货物的图片及数量指针
    QGraphicsPixmapItem *copper_p;
    QGraphicsPixmapItem *copper_p_gewei;
    QGraphicsPixmapItem *copper_p_shiwei;

    QGraphicsPixmapItem *iron_p;
    QGraphicsPixmapItem *iron_p_gewei;
    QGraphicsPixmapItem *iron_p_shiwei;

    QGraphicsPixmapItem *half_copper_p;
    QGraphicsPixmapItem *half_copper_p_gewei;
    QGraphicsPixmapItem *half_copper_p_shiwei;

    //第几个关卡（任务）图片指针
    QGraphicsPixmapItem *grade;
    static int grade_n;
    static int total_value;
    static int up;
    static int hasDouble;
private:


    int copper_num;
    int iron_num;
    int half_copper_num;
    QGraphicsTextItem textItem;


};


#endif //SHAPEZ_DELIVERYCENTER_H
