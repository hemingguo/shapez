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

    QGraphicsView *first_view;
    QGraphicsScene *first_scene;

    QGraphicsPixmapItem *deliveryCenter;
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
    Around around[30][30];
    int total_value;

    int copper_num;
    int iron_num;
    int half_copper_num;


};


#endif //SHAPEZ_DELIVERYCENTER_H
