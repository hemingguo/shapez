//
// Created by hemingguo on 2023-12-3.
//

#include "DeliveryCenter.h"


int DeliveryCenter::grade_n = 1;
int DeliveryCenter::total_value = 0;
int DeliveryCenter::up = 0;
int DeliveryCenter::hasDouble = 1;

DeliveryCenter::DeliveryCenter() : copper_num(0), iron_num(0), half_copper_num(0)
{
    deliveryCenter = nullptr;
    copper_p = nullptr;
    copper_p_gewei = nullptr;
    copper_p_shiwei = nullptr;

    iron_p = nullptr;
    iron_p_gewei = nullptr;
    iron_p_shiwei = nullptr;

    half_copper_p = nullptr;
    half_copper_p_gewei = nullptr;
    half_copper_p_shiwei = nullptr;

    grade = nullptr;
}

DeliveryCenter::DeliveryCenter(QGraphicsScene *s, QGraphicsView *v) : copper_num(0), iron_num(0),
                                                                      half_copper_num(0)
{
    first_scene = s;
    first_view = v;
    deliveryCenter = nullptr;
    copper_p = nullptr;
    copper_p_gewei = nullptr;
    copper_p_shiwei = nullptr;

    iron_p = nullptr;
    iron_p_gewei = nullptr;
    iron_p_shiwei = nullptr;

    half_copper_p = nullptr;
    half_copper_p_gewei = nullptr;
    half_copper_p_shiwei = nullptr;

    QString name = "../media/grade" + QString::number(grade_n) + ".png";
    grade = new QGraphicsPixmapItem(QPixmap(name));
    grade->setPixmap(grade->pixmap().scaled(20, 25));
    grade->setPos(13 * 50 + 32, 13 * 50 + 27);
    first_scene->addItem(grade);
    grade->setZValue(10);

    textItem.setPlainText("money: " + QString::number(total_value));
    QFont font("Arial", 10);
    font.setBold(true);
    font.setItalic(true);
    textItem.setFont(font);
    textItem.setPos(680, 780);
    textItem.setZValue(10);
    first_scene->addItem(&textItem);
}


void DeliveryCenter::acc(std::string mineName)
{

    if (mineName == "copper")
    {
        copper_num++;
        total_value += 10 * DeliveryCenter::hasDouble;

        delete copper_p_gewei;
        delete copper_p_shiwei;
        int gewei = copper_num % 10;
        int shiwei = copper_num / 10;
        QString name_g = "../media/" + QString::number(gewei) + ".png";
        QString name_s = "../media/" + QString::number(shiwei) + ".png";
        copper_p_gewei = new QGraphicsPixmapItem(QPixmap(name_g));
        copper_p_gewei->setPixmap(copper_p_gewei->pixmap().scaled(30, 30));
        copper_p_gewei->setPos(15 * 50 + 40, 13 * 50 + 30);
        first_scene->addItem(copper_p_gewei);

        copper_p_shiwei = new QGraphicsPixmapItem(QPixmap(name_s));
        copper_p_shiwei->setPixmap(copper_p_shiwei->pixmap().scaled(30, 30));
        copper_p_shiwei->setPos(15 * 50 + 10, 13 * 50 + 30);
        first_scene->addItem(copper_p_shiwei);


    } else if (mineName == "iron")
    {
        iron_num++;
        total_value += 5 * DeliveryCenter::hasDouble;

        delete iron_p_gewei;
        delete iron_p_shiwei;
        int gewei = iron_num % 10;
        int shiwei = iron_num / 10;
        QString name_g = "../media/" + QString::number(gewei) + ".png";
        QString name_s = "../media/" + QString::number(shiwei) + ".png";
        iron_p_gewei = new QGraphicsPixmapItem(QPixmap(name_g));
        iron_p_gewei->setPixmap(iron_p_gewei->pixmap().scaled(30, 30));
        iron_p_gewei->setPos(15 * 50 + 40, 14 * 50 + 15);
        first_scene->addItem(iron_p_gewei);

        iron_p_shiwei = new QGraphicsPixmapItem(QPixmap(name_s));
        iron_p_shiwei->setPixmap(iron_p_shiwei->pixmap().scaled(30, 30));
        iron_p_shiwei->setPos(15 * 50 + 10, 14 * 50 + 15);
        first_scene->addItem(iron_p_shiwei);
    } else if (mineName == "halfcopper")
    {
        half_copper_num++;
        total_value += 5 * DeliveryCenter::hasDouble;

        delete half_copper_p_gewei;
        delete half_copper_p_shiwei;
        int gewei = half_copper_num % 10;
        int shiwei = half_copper_num / 10;
        QString name_g = "../media/" + QString::number(gewei) + ".png";
        QString name_s = "../media/" + QString::number(shiwei) + ".png";
        half_copper_p_gewei = new QGraphicsPixmapItem(QPixmap(name_g));
        half_copper_p_gewei->setPixmap(half_copper_p_gewei->pixmap().scaled(30, 30));
        half_copper_p_gewei->setPos(15 * 50 + 40, 15 * 50);
        first_scene->addItem(half_copper_p_gewei);

        half_copper_p_shiwei = new QGraphicsPixmapItem(QPixmap(name_s));
        half_copper_p_shiwei->setPixmap(half_copper_p_shiwei->pixmap().scaled(30, 30));
        half_copper_p_shiwei->setPos(15 * 50 + 10, 15 * 50);
        first_scene->addItem(half_copper_p_shiwei);
    }
    textItem.setPlainText("money: " + QString::number(total_value));
    QFont font("Arial", 10);
    font.setBold(true);
    font.setItalic(true);
    textItem.setFont(font);
    textItem.setPos(680, 780);
    textItem.setZValue(10);
    first_scene->addItem(&textItem);


    if (grade_n == 1 && copper_num >= 20)
    {
        DeliveryCenter::grade_n = 2;
        up++;
        QString name = "../media/grade" + QString::number(grade_n) + ".png";
        delete grade;
        grade = new QGraphicsPixmapItem(QPixmap(name));
        grade->setPixmap(grade->pixmap().scaled(20, 25));
        grade->setPos(13 * 50 + 32, 13 * 50 + 27);
        first_scene->addItem(grade);
        grade->setZValue(10);
        grade->show();
    }
    if (grade_n == 2 && iron_num >= 30)
    {
        DeliveryCenter::grade_n = 3;
        up++;
        QString name = "../media/grade" + QString::number(grade_n) + ".png";
        delete grade;
        grade = new QGraphicsPixmapItem(QPixmap(name));
        grade->setPixmap(grade->pixmap().scaled(20, 25));
        grade->setPos(13 * 50 + 32, 13 * 50 + 27);
        first_scene->addItem(grade);
        grade->setZValue(10);
        grade->show();
    }
    if (grade_n == 3 && half_copper_num >= 50)
    {
        DeliveryCenter::grade_n = 4;
        up++;
        QString name = "../media/grade" + QString::number(grade_n) + ".png";
        delete grade;

    }
    qDebug() << total_value;
    qDebug() << "copper: " << copper_num << ", iron: " << iron_num << ", half_copper: " << half_copper_num;
}



