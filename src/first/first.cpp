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
#include <QMessageBox>
#include "first.h"
#include "ui_first.h"
#include "../MyRect/MyRect.h"


first::first(QWidget *parent) :
        QWidget(parent), ui(new Ui::first)
{
    ui->setupUi(this);
    setMouseTracking(true); // 确保启用鼠标追踪

    setWindowTitle("Shapez");//重命名窗口标题

    setWindowIcon(QIcon("../media/logo.png"));//设置窗口图标

    // 获取窗口的大小
    windowWidth = this->width();
    windowHeight = this->height();


    setFixedSize(windowWidth, windowHeight);// 固定窗口大小
    // 创建场景
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 1500, 1500);// 设置场景的大小为窗口的大小
    scene->installEventFilter(this);
    // 创建视图
    view = new QGraphicsView(scene, this);
    view->setSceneRect(0, 0, 1500, 1500); // 视图显示场景的全部
    view->setGeometry(0, 0, 1500, 1500); // 固定视图位置


    view->show();
    // 将水平滚动条策略设置为始终关闭
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // 将垂直滚动条策略设置为始终关闭
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    //初始化地图---/

    //初始化空白方格---/
    const int gridSize = 30;
    const int cellSize = windowWidth / gridSize;

    for (int i = 0; i < gridSize; i++)
    {
        for (int j = 0; j < gridSize; j++)
        {

            // 绘制基本方格
            QGraphicsPixmapItem *pixmapItem = new QGraphicsPixmapItem(QPixmap("../media/basic_square.png"));//新建方格
            pixmapItem->setPixmap(pixmapItem->pixmap().scaled(100, 100)); // 将方格缩放
            pixmapItem->setPos(i * cellSize, j * cellSize);//按序放置方格
            scene->addItem(pixmapItem);// 添加方格到场景
        }
    }
    //---初始化空白方格/

    //初始化交付中心
    QGraphicsPixmapItem *pixmapItem = new QGraphicsPixmapItem(QPixmap("../media/center_0.png"));//新建方格
    pixmapItem->setPixmap(pixmapItem->pixmap().scaled(200, 200)); // 将方格缩放
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
            pixmapItem->setPixmap(pixmapItem->pixmap().scaled(50, 50)); // 将方格缩放
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
            pixmapItem->setPixmap(pixmapItem->pixmap().scaled(50, 50)); // 将方格缩放
            pixmapItem->setPos(i * cellSize, j * cellSize);//按序放置方格
            scene->addItem(pixmapItem);// 添加方格到场景
        }
    }

    //---初始化地图/



    // 创建垃圾桶按钮---/
    binButton = new QPushButton(QIcon("../media/bin.png"), "", this);
    binButton->setIconSize(QSize(70, 70));// 设置按钮显示模式为IconOnly
    binButton->setFixedSize(80, 80);// 设置按钮大小
    binButton->move(1000, 1510);// 移动按钮到底部靠右位置

    connect(binButton, &QPushButton::clicked, this, &first::onBinButtonClick);// 连接按钮的点击信号到槽函数，
    //---创建垃圾桶按钮/


    // 创建传送带按钮---/
    conveyorBeltButton = new QPushButton(QIcon("../media/conveyor_belt.png"), "", this);
    conveyorBeltButton->setIconSize(QSize(70, 70));// 设置按钮显示模式为IconOnly
    conveyorBeltButton->setFixedSize(80, 80);// 设置按钮大小
    conveyorBeltButton->move(400, 1510);// 移动按钮到底部靠右位置

    connect(conveyorBeltButton, &QPushButton::clicked, this, &first::onConveyorBeltButtonClick);// 连接按钮的点击信号到槽函数，
    //---创建传送带按钮/

    // 创建开采器按钮---/
    minerButton = new QPushButton(QIcon("../media/miner.png"), "", this);
    minerButton->setIconSize(QSize(70, 70));// 设置按钮显示模式为IconOnly
    minerButton->setFixedSize(80, 80);// 设置按钮大小
    minerButton->move(600, 1510);// 移动按钮到底部靠右位置

    connect(minerButton, &QPushButton::clicked, this, &first::onMinerButtonClick);// 连接按钮的点击信号到槽函数，
    //---创建开采器按钮/

    // 创建切割机按钮---/
    cutMachineButton = new QPushButton(QIcon("../media/cut_machine.png"), "", this);
    cutMachineButton->setIconSize(QSize(70, 70));// 设置按钮显示模式为IconOnly
    cutMachineButton->setFixedSize(80, 80);// 设置按钮大小
    cutMachineButton->move(800, 1510);// 移动按钮到底部靠右位置

    connect(cutMachineButton, &QPushButton::clicked, this, &first::onCutMachineButtonClick);// 连接按钮的点击信号到槽函数，
    //---创建切割机按钮/





    //初始化空白方格数组
    MyRect myrect[30][30];
}

first::~first()
{
    delete ui;
}

void first::onBinButtonClick()
{
    // 创建新的QGraphicsPixmapItem
    QGraphicsPixmapItem *binItem = new QGraphicsPixmapItem(QPixmap("../media/bin.png"));
    binItem->setPixmap(binItem->pixmap().scaled(50, 50)); // 设置图片缩放
    binItem->setPos(0, 0); // 设置位置为鼠标中心
    scene->addItem(binItem); // 添加到场景中
}


void first::mouseMoveEvent(QMouseEvent *event)
{
    QPoint globalMousePos = event->globalPos();

    // 将全局坐标映射到窗口内的局部坐标
    QPoint localMousePos = mapFromGlobal(globalMousePos);

    // 输出局部坐标
    qDebug() << "Local Mouse Position: " << localMousePos;
}


void first::onConveyorBeltButtonClick()
{
    // 处理按钮点击事件的逻辑

    QMessageBox::information(this, "conButton Clicked", "The conbottom button was clicked!");
}

void first::onMinerButtonClick()
{
    // 处理按钮点击事件的逻辑

    QMessageBox::information(this, "minButton Clicked", "The minbottom button was clicked!");
}

void first::onCutMachineButtonClick()
{
    // 处理按钮点击事件的逻辑

    QMessageBox::information(this, "cutButton Clicked", "The cutbottom button was clicked!");
}

