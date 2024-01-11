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


class Around
{
public:
    std::string mineName;
    bool isWork;
    int id;

    Around();
};


class DeliveryCenter : public QWidget
{
Q_OBJECT
public :
    explicit DeliveryCenter();

    explicit DeliveryCenter(QGraphicsScene *s, QGraphicsView *v);

    void timerEvent(QTimerEvent *event) override;

    void arrival(std::string mineName, int distance, int i, int j);

    int examine(MyRect myrect[30][30], int i, int j);

    int test(MyRect myrect[30][30], int i, int j, int sign);

    void around_examine(MyRect myrect[30][30]);

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

private:
    Around around[30][30]; // 表示交付中心最外层的格子（用于接受货物）
    int total_value;

    int copper_num;
    int iron_num;
    int half_copper_num;


};


#endif //SHAPEZ_DELIVERYCENTER_H
