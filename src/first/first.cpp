//
// Created by hemingguo on 2023-12-1.
//

// You may need to build the project (run Qt uic code generator) to get "ui_first.h" resolved
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QtMultimedia/QMediaPlayer>
#include <QDir>
#include <QMovie>
#include <QLabel>
#include <QTimer>
#include <QMenuBar>
#include "first.h"
#include "ui_first.h"
#include "../MyRect/MyRect.h"


first::first(QWidget *parent) :
        QWidget(parent), ui(new Ui::first)
{
    ui->setupUi(this);
    setWindowTitle("Shapez");//重命名窗口标题

    setWindowIcon(QIcon("../media/logo.png"));//设置窗口图标

    // 获取窗口的大小
    windowWidth = this->width();
    windowHeight = this->height();


    setFixedSize(windowWidth, windowHeight);// 固定窗口大小
    // 创建场景
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, windowWidth * 2, windowHeight * 2);// 设置场景的大小为窗口的大小4倍

    // 创建视图
    QGraphicsView *view = new QGraphicsView(scene, this);
    view->setSceneRect(0, 0, windowWidth * 2, windowHeight * 2); // 视图显示场景的全部
    view->setGeometry(0, 0, windowWidth, windowHeight); // 固定视图大小
    view->show();


    //初始化地图---/

    //初始化空白方格---/
    const int gridSize = 15;
    const int cellSize = windowWidth / gridSize;

    for (int i = 0; i < gridSize * 2; i++)
    {
        for (int j = 0; j < gridSize * 2; j++)
        {

            // 绘制基本方格
            QGraphicsPixmapItem *pixmapItem = new QGraphicsPixmapItem(QPixmap("../media/basic_square.png"));//新建方格
            pixmapItem->setPixmap(pixmapItem->pixmap().scaled(100, 100)); // 将方格缩放为100x100
            pixmapItem->setPos(i * cellSize, j * cellSize);//按序放置方格
            scene->addItem(pixmapItem);// 添加方格到场景
        }
    }
    //---初始化空白方格/

    //初始化交付中心
    QGraphicsPixmapItem *pixmapItem = new QGraphicsPixmapItem(QPixmap("../media/center_0.png"));//新建方格
    pixmapItem->setPixmap(pixmapItem->pixmap().scaled(400, 400)); // 将方格缩放为400x400
    pixmapItem->setPos(13 * cellSize, 13 * cellSize);//按序放置方格
    scene->addItem(pixmapItem);// 添加方格到场景

    //初始化矿物
    //铜(圆形,可切割)
    for (int i = 4; i < 8; i++)
    {
        for (int j = 4; j < 8; j++)
        {

            // 绘制基本方格
            QGraphicsPixmapItem *pixmapItem = new QGraphicsPixmapItem(QPixmap("../media/copper.png"));//新建方格
            pixmapItem->setPixmap(pixmapItem->pixmap().scaled(100, 100)); // 将方格缩放为100x100
            pixmapItem->setPos(i * cellSize, j * cellSize);//按序放置方格
            scene->addItem(pixmapItem);// 添加方格到场景
        }
    }
    //铁(方形,不可切割)
    for (int i = 22; i < 26; i++)
    {
        for (int j = 22; j < 26; j++)
        {

            // 绘制基本方格
            QGraphicsPixmapItem *pixmapItem = new QGraphicsPixmapItem(QPixmap("../media/iron.png"));//新建方格
            pixmapItem->setPixmap(pixmapItem->pixmap().scaled(100, 100)); // 将方格缩放为100x100
            pixmapItem->setPos(i * cellSize, j * cellSize);//按序放置方格
            scene->addItem(pixmapItem);// 添加方格到场景
        }
    }








    //---初始化地图/

    //初始化空白方格数组
    MyRect myrect[15][15];
}

first::~first()
{
    delete ui;
}
