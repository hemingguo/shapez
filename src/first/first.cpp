//
// Created by hemingguo on 2023-12-1.
//


#include <vector>

#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QtMultimedia/QMediaPlayer>

#include <QMovie>
#include <QLabel>
#include <QTimer>
#include <QMenuBar>

#include "first.h"
#include "ui_first.h"


first::first(QWidget *parent) :
        QWidget(parent), ui(new Ui::first), pixmapItem(nullptr), press(false), direction(0)
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

    // 创建视图
    view = new QGraphicsView(scene, this);
    view->setSceneRect(0, 0, 1500, 1500); // 视图显示场景的全部
    view->setGeometry(0, 0, 1500, 1500); // 固定视图位置

    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);  //关闭滚动条

    view->show();

    view->setMouseTracking(true);

    view->viewport()->installEventFilter(this);
    installEventFilter(this); // 给窗口先安装一个事件接收器


    center = new DeliveryCenter();//初始化交付中心（数据部分）

    game = new Game(center);  //初始化游戏指针

    //初始化地图---/

    //初始化空白方格---/
    const int gridSize = 30;
    const int cellSize = windowWidth / gridSize;

    for (int i = 0; i < gridSize; i++)
    {
        for (int j = 0; j < gridSize; j++)
        {

            // 绘制基本方格
            pixmapItem = new QGraphicsPixmapItem(QPixmap("../media/basic_square.png"));//新建方格
            pixmapItem->setPixmap(pixmapItem->pixmap().scaled(100, 100)); // 将方格缩放
            pixmapItem->setPos(i * cellSize, j * cellSize);//按序放置方格
            scene->addItem(pixmapItem);// 添加方格到场景
            pixmapItem = nullptr;
        }
    }
    //---初始化空白方格/

    //初始化空白方格数组(包括矿物填充和交付中心)

    for (int i = 0; i < 30; ++i)
    {
        for (int j = 0; j < 30; ++j)
        {
            myrect[i][j].setPosition(i * 50, j * 50);


            if (i >= 22 && i <= 25 && j >= 22 && j <= 25)
            {
                myrect[i][j].isMineExist = true;
                myrect[i][j].setMine("iron");

            } else if (i >= 4 && i <= 7 && j >= 4 && j <= 7)
            {
                myrect[i][j].isMineExist = true;
                myrect[i][j].setMine("copper");
            } else if (i >= 13 && i <= 16 && j >= 13 && j <= 16)
            {
                myrect[i][j].isFacilityExist = true;
                myrect[i][j].isDelivery = true;
            }
        }

    }

    //初始化交付中心（图形部分）
    pixmapItem = new QGraphicsPixmapItem(QPixmap("../media/center_0.png"));//新建方格
    pixmapItem->setPixmap(pixmapItem->pixmap().scaled(200, 200)); // 将方格缩放
    pixmapItem->setPos(13 * cellSize, 13 * cellSize);//按序放置方格

    scene->addItem(pixmapItem);// 添加方格到场景
    center->deliveryCenter = pixmapItem;


    //初始化矿物
    //铜(圆形,可切割)
    for (int i = 4; i < 8; i++)
    {
        for (int j = 4; j < 8; j++)
        {
            pixmapItem = new QGraphicsPixmapItem(QPixmap("../media/copper.png"));//新建方格
            pixmapItem->setPixmap(pixmapItem->pixmap().scaled(50, 50)); // 将方格缩放
            pixmapItem->setPos(i * cellSize, j * cellSize);//按序放置方格


            scene->addItem(pixmapItem);// 添加方格到场景
            myrect[i][j].pixmapMineItem = pixmapItem;
            pixmapItem = nullptr;

        }
    }
    //铁(方形,不可切割)
    for (int i = 22; i < 26; i++)
    {
        for (int j = 22; j < 26; j++)
        {
            pixmapItem = new QGraphicsPixmapItem(QPixmap("../media/iron.png"));//新建方格
            pixmapItem->setPixmap(pixmapItem->pixmap().scaled(50, 50)); // 将方格缩放
            pixmapItem->setPos(i * cellSize, j * cellSize);//按序放置方格
            scene->addItem(pixmapItem);// 添加方格到场景
            myrect[i][j].pixmapMineItem = pixmapItem;
            pixmapItem = nullptr;
        }
    }

    //---初始化地图/



    // 创建垃圾桶按钮---/
    binButton = new QPushButton(QIcon("../media/bin.png"), "", this);
    binButton->setIconSize(QSize(70, 70));// 设置按钮显示模式为IconOnly
    binButton->setFixedSize(80, 80);// 设置按钮大小
    binButton->move(1000, 1510);// 移动按钮到底部靠右位置

    bin = false;

    connect(binButton, &QPushButton::clicked, this, &first::onBinButtonClick);// 连接按钮的点击信号到槽函数，
    //---创建垃圾桶按钮/


    // 创建传送带按钮---/
    conveyorBeltButton = new QPushButton(QIcon("../media/conveyor_belt.png"), "", this);
    conveyorBeltButton->setIconSize(QSize(70, 70));// 设置按钮显示模式为IconOnly
    conveyorBeltButton->setFixedSize(80, 80);// 设置按钮大小
    conveyorBeltButton->move(400, 1510);// 移动按钮到底部靠右位置

    conveyorBelt = false;

    connect(conveyorBeltButton, &QPushButton::clicked, this, &first::onConveyorBeltButtonClick);// 连接按钮的点击信号到槽函数，
    //---创建传送带按钮/

    // 创建开采器按钮---/
    minerButton = new QPushButton(QIcon("../media/miner.png"), "", this);
    minerButton->setIconSize(QSize(70, 70));// 设置按钮显示模式为IconOnly
    minerButton->setFixedSize(80, 80);// 设置按钮大小
    minerButton->move(600, 1510);// 移动按钮到底部靠右位置

    miner = false;

    connect(minerButton, &QPushButton::clicked, this, &first::onMinerButtonClick);// 连接按钮的点击信号到槽函数，
    //---创建开采器按钮/

    // 创建切割机按钮---/
    cutMachineButton = new QPushButton(QIcon("../media/cut_machine.png"), "", this);
    cutMachineButton->setIconSize(QSize(70, 70));// 设置按钮显示模式为IconOnly
    cutMachineButton->setFixedSize(80, 80);// 设置按钮大小
    cutMachineButton->move(800, 1510);// 移动按钮到底部靠右位置

    cutMachine = false;

    connect(cutMachineButton, &QPushButton::clicked, this, &first::onCutMachineButtonClick);// 连接按钮的点击信号到槽函数，
    //---创建切割机按钮/






}

first::~first()
{
    delete ui;
}


void first::onBinButtonClick()
{

    bin = true;
    conveyorBelt = false;
    miner = false;
    cutMachine = false;
    if (pixmapItem != nullptr)
    {
        delete pixmapItem;
        pixmapItem = nullptr;
    }
    pixmapItem = new QGraphicsPixmapItem(QPixmap("../media/_bin.png"));
    pixmapItem->setPixmap(pixmapItem->pixmap().scaled(50, 50));
    pixmapItem->setVisible(false);
    scene->addItem(pixmapItem);
}


void first::onConveyorBeltButtonClick()
{
    direction = 0;
    bin = false;
    conveyorBelt = true;
    miner = false;
    cutMachine = false;
    if (pixmapItem != nullptr)
    {
        delete pixmapItem;
        pixmapItem = nullptr;
    }
    pixmapItem = new QGraphicsPixmapItem(QPixmap("../media/_belt.jpg"));
    pixmapItem->setPixmap(pixmapItem->pixmap().scaled(50, 50));
    pixmapItem->setVisible(false);
    scene->addItem(pixmapItem);

}

void first::onMinerButtonClick()
{
    direction = 0;
    bin = false;
    conveyorBelt = false;
    miner = true;
    cutMachine = false;
    if (pixmapItem != nullptr)
    {
        delete pixmapItem;
        pixmapItem = nullptr;
    }

    pixmapItem = new QGraphicsPixmapItem(QPixmap("../media/_miner.png"));
    pixmapItem->setPixmap(pixmapItem->pixmap().scaled(50, 50));
    pixmapItem->setVisible(false);

    scene->addItem(pixmapItem);
}

void first::onCutMachineButtonClick()
{
    direction = 0;
    bin = false;
    conveyorBelt = false;
    miner = false;
    cutMachine = true;
    if (pixmapItem != nullptr)
    {
        delete pixmapItem;
        pixmapItem = nullptr;
    }
}


bool first::eventFilter(QObject *obj, QEvent *event)
{

    // 按Esc取消放置 or 按下R旋转
    if (obj == this && event->type() == QEvent::KeyPress)
    {
        auto keyEvent = dynamic_cast<QKeyEvent *>(event);
        if (keyEvent->key() == Qt::Key_Escape)
        {
            if (pixmapItem)
            {
                delete pixmapItem;
                pixmapItem = nullptr;
                bin = false;
                miner = false;
                cutMachine = false;
                conveyorBelt = false;
            }

            direction = 0;
            event->accept();
            // 表示事件已经被处理
        }
        if (keyEvent->key() == Qt::Key_R)  // 按R旋转
        {
            if (pixmapItem && miner)
            {
                // 获取当前变换并进行平移，使得旋转中心在图像中心
                QTransform currentTransform = pixmapItem->transform();
                QRectF boundingRect = pixmapItem->boundingRect(); // 获取图像的边界矩形
                currentTransform.translate(boundingRect.width() / 2, boundingRect.height() / 2);
                currentTransform.rotate(90);
                currentTransform.translate(-boundingRect.width() / 2, -boundingRect.height() / 2);

                // 设置新的变换
                pixmapItem->setTransform(currentTransform);
                event->accept();

                //方向改变
                direction = (direction + 1) % 4;

            }
        }

    }



    // 鼠标左键单击删除设备或长按连续删除
    if (!bin && !miner && !cutMachine && !conveyorBelt)
    {
        if (obj == view->viewport() &&
            (event->type() == QEvent::MouseButtonPress ||
             event->type() == QEvent::MouseMove && press))
        {
            press = true;
            auto mouseEvent = dynamic_cast<QMouseEvent *>(event);
            windowPos = mouseEvent->pos();
            int i = windowPos.x() / 50;
            int j = windowPos.y() / 50;


            if (myrect[i][j].isFacilityExist && !myrect[i][j].isDelivery)
            {
                //qDebug() << "hello" << i << ", " << j;
                delete myrect[i][j].pixmapFacilityItem;
                myrect[i][j].pixmapFacilityItem = nullptr;

                delete myrect[i][j].facility;
                myrect[i][j].facility = nullptr;

                myrect[i][j].isFacilityExist = false;
            }
        }
        if (obj == view->viewport() && event->type() == QEvent::MouseButtonRelease)
        {
            press = false;
        }
        event->accept();
    }

    //放置开采器和垃圾桶设备
    if (obj == view->viewport() && (bin || miner))
    {
        //鼠标按下放置
        if (event->type() == QEvent::MouseButtonPress)
        {
            windowPos.setX((windowPos.x() + 25) / 50 * 50);
            windowPos.setY((windowPos.y() + 25) / 50 * 50);
            int i = windowPos.x() / 50;
            int j = windowPos.y() / 50;

            if (!myrect[i][j].isFacilityExist && (!myrect[i][j].isMineExist || miner))
            {
                if (bin)
                {
                    bin = false;
                    myrect[i][j].setFacility("bin");
                    pixmapItem->setPos(windowPos);
                    myrect[i][j].isFacilityExist = true;
                    myrect[i][j].pixmapFacilityItem = pixmapItem;
                }
                if (miner)
                {
                    miner = false;
                    myrect[i][j].setFacility("miner");
                    static_cast<Miner *>(myrect[i][j].facility)->setDirection(direction);

                    pixmapItem->setPos(windowPos);
                    myrect[i][j].isFacilityExist = true;
                    myrect[i][j].pixmapFacilityItem = pixmapItem;
                    game->check(myrect);
                }


                if (pixmapItem)
                {
                    pixmapItem = nullptr;
                }
            }
            event->accept();
        } else if (event->type() == QEvent::MouseMove)  //鼠标移动
        {

            auto mouseEvent = dynamic_cast<QMouseEvent *>(event);
            windowPos = mouseEvent->pos();
            windowPos.setX(windowPos.x() - 25);
            windowPos.setY(windowPos.y() - 25);

            if (!(pixmapItem->isVisible()))
            {
                pixmapItem->setVisible(true);
            }
            //qDebug() << "位置：" << windowPos;
            pixmapItem->setPos(windowPos);

            event->accept();
        }
    }

    // 放置传送带
    if (obj == view->viewport() && conveyorBelt)
    {


        if (event->type() == QEvent::MouseButtonPress)
        {
            direction = 0;
            windowPos.setX((windowPos.x() + 25) / 50 * 50);
            windowPos.setY((windowPos.y() + 25) / 50 * 50);
            int i = windowPos.x() / 50;
            int j = windowPos.y() / 50;

            if (!myrect[i][j].isFacilityExist && !myrect[i][j].isMineExist)
            {
                press = true;

                myrect[i][j].setFacility("conveyorbelt");
                pixmapItem->setPos(windowPos);
                myrect[i][j].isFacilityExist = true;
                myrect[i][j].pixmapFacilityItem = pixmapItem;
                static_cast<ConveyorBelt *>(myrect[i][j].facility)->setDoor(direction);

                if (pixmapItem)
                {
                    pixmapItem = nullptr;
                }

                previous.push_back(i);
                previous.push_back(j);

                game->check(myrect);
            } else
            {
                conveyorBelt = false;
                press = false;
                if (pixmapItem)
                {
                    delete pixmapItem;
                    pixmapItem = nullptr;
                }
            }


        }

        if (event->type() == QEvent::MouseButtonRelease)
        {
            if (pixmapItem)
            {
                pixmapItem = nullptr;
            }
            press = false;
            conveyorBelt = false;
            previous.clear();
            direction = 0;
        }

        if (event->type() == QEvent::MouseMove)
        {

            if (press == false) // 未按下，只是移动
            {
                auto mouseEvent = dynamic_cast<QMouseEvent *>(event);
                windowPos = mouseEvent->pos();
                windowPos.setX(windowPos.x() - 25);
                windowPos.setY(windowPos.y() - 25);

                if (!(pixmapItem->isVisible()))
                {
                    pixmapItem->setVisible(true);
                }
                //qDebug() << "位置：" << windowPos;
                pixmapItem->setPos(windowPos);


            } else
            {
                // 先确定位置
                auto mouseEvent = dynamic_cast<QMouseEvent *>(event);
                windowPos = mouseEvent->pos();


                // 再安放

                int i = windowPos.x() / 50;
                int j = windowPos.y() / 50;


                if (((!myrect[i][j].isFacilityExist && !myrect[i][j].isMineExist)) || myrect[i][j].isDelivery)
                {
                    windowPos.setX(windowPos.x() / 50 * 50);
                    windowPos.setY(windowPos.y() / 50 * 50);


                    // 考虑拐弯
                    if (previous.size() < 4)
                    {
                        previous.push_back(i);
                        previous.push_back(j);

                        // 如果开始的两个是横着拖动的，那么改变方向
                        if (previous[1] == previous[3])
                        {
                            if (previous[0] < previous[2])
                            {
                                direction = (direction + 1) % 4;
                                delete myrect[previous[0]][previous[1]].pixmapFacilityItem;
                                myrect[previous[0]][previous[1]].pixmapFacilityItem = new QGraphicsPixmapItem(
                                        QPixmap("../media/_belt_h.png"));
                                myrect[previous[0]][previous[1]].pixmapFacilityItem->setPixmap(
                                        myrect[previous[0]][previous[1]].pixmapFacilityItem->pixmap().scaled(50, 50));
                                myrect[previous[0]][previous[1]].pixmapFacilityItem->setPos(windowPos.x() - 50,
                                                                                            windowPos.y());
                                static_cast<ConveyorBelt *>(myrect[previous[0]][previous[1]].facility)->setDoor(
                                        direction);

                                scene->addItem(myrect[previous[0]][previous[1]].pixmapFacilityItem);
                            } else
                            {
                                direction = (direction + 1) % 4;
                                delete myrect[previous[0]][previous[1]].pixmapFacilityItem;
                                myrect[previous[0]][previous[1]].pixmapFacilityItem = new QGraphicsPixmapItem(
                                        QPixmap("../media/_belt_h.png"));
                                myrect[previous[0]][previous[1]].pixmapFacilityItem->setPixmap(
                                        myrect[previous[0]][previous[1]].pixmapFacilityItem->pixmap().scaled(50, 50));
                                myrect[previous[0]][previous[1]].pixmapFacilityItem->setPos(windowPos.x() + 50,
                                                                                            windowPos.y());
                                static_cast<ConveyorBelt *>(myrect[previous[0]][previous[1]].facility)->setDoor(
                                        direction);

                                scene->addItem(myrect[previous[0]][previous[1]].pixmapFacilityItem);
                            }
                        }

                    } else
                    {
                        if (!(previous[0] == previous[2] && previous[2] == i) &&
                            !(previous[1] == previous[3] && previous[3] == j))
                        {
                            direction = (direction + 1) % 4;
                            // 左下->上->右
                            if (previous[0] == previous[2] && previous[2] + 1 == i && previous[1] - 1 == previous[3] &&
                                previous[3] == j)
                            {
                                delete myrect[previous[2]][previous[3]].pixmapFacilityItem;
                                myrect[previous[2]][previous[3]].pixmapFacilityItem = new QGraphicsPixmapItem(
                                        QPixmap("../media/dr.png"));
                                myrect[previous[2]][previous[3]].pixmapFacilityItem->setPixmap(
                                        myrect[previous[2]][previous[3]].pixmapFacilityItem->pixmap().scaled(50, 50));
                                myrect[previous[2]][previous[3]].pixmapFacilityItem->setPos(windowPos.x() - 50,
                                                                                            windowPos.y());

                                scene->addItem(myrect[previous[2]][previous[3]].pixmapFacilityItem);

                                static_cast<ConveyorBelt *>(myrect[previous[2]][previous[3]].facility)->turn = "DownR";
                            }
                                // 左下->右->上
                            else if (previous[0] + 1 == previous[2] && previous[2] == i &&
                                     previous[1] == previous[3] &&
                                     previous[3] - 1 == j)
                            {
                                delete myrect[previous[2]][previous[3]].pixmapFacilityItem;
                                myrect[previous[2]][previous[3]].pixmapFacilityItem = new QGraphicsPixmapItem(
                                        QPixmap("../media/ul.png"));
                                myrect[previous[2]][previous[3]].pixmapFacilityItem->setPixmap(
                                        myrect[previous[2]][previous[3]].pixmapFacilityItem->pixmap().scaled(50, 50));
                                myrect[previous[2]][previous[3]].pixmapFacilityItem->setPos(windowPos.x(),
                                                                                            windowPos.y() + 50);

                                scene->addItem(myrect[previous[2]][previous[3]].pixmapFacilityItem);

                                static_cast<ConveyorBelt *>(myrect[previous[2]][previous[3]].facility)->turn = "UpL";
                            }

                                // 左上->下->右
                            else if (previous[0] == previous[2] && previous[2] + 1 == i &&
                                     previous[1] + 1 == previous[3] &&
                                     previous[3] == j)
                            {
                                delete myrect[previous[2]][previous[3]].pixmapFacilityItem;
                                myrect[previous[2]][previous[3]].pixmapFacilityItem = new QGraphicsPixmapItem(
                                        QPixmap("../media/ur.png"));
                                myrect[previous[2]][previous[3]].pixmapFacilityItem->setPixmap(
                                        myrect[previous[2]][previous[3]].pixmapFacilityItem->pixmap().scaled(50, 50));
                                myrect[previous[2]][previous[3]].pixmapFacilityItem->setPos(windowPos.x() - 50,
                                                                                            windowPos.y());

                                scene->addItem(myrect[previous[2]][previous[3]].pixmapFacilityItem);

                                static_cast<ConveyorBelt *>(myrect[previous[2]][previous[3]].facility)->turn = "UpR";
                            }
                                // 左上->右->下
                            else if (previous[0] + 1 == previous[2] && previous[2] == i &&
                                     previous[1] == previous[3] &&
                                     previous[3] + 1 == j)
                            {
                                delete myrect[previous[2]][previous[3]].pixmapFacilityItem;
                                myrect[previous[2]][previous[3]].pixmapFacilityItem = new QGraphicsPixmapItem(
                                        QPixmap("../media/dl.png"));
                                myrect[previous[2]][previous[3]].pixmapFacilityItem->setPixmap(
                                        myrect[previous[2]][previous[3]].pixmapFacilityItem->pixmap().scaled(50, 50));
                                myrect[previous[2]][previous[3]].pixmapFacilityItem->setPos(windowPos.x(),
                                                                                            windowPos.y() - 50);

                                scene->addItem(myrect[previous[2]][previous[3]].pixmapFacilityItem);
                                static_cast<ConveyorBelt *>(myrect[previous[2]][previous[3]].facility)->turn = "DownL";
                            }
                                // 右上->下->左
                            else if (previous[0] == previous[2] && previous[2] - 1 == i &&
                                     previous[1] + 1 == previous[3] &&
                                     previous[3] == j)
                            {
                                delete myrect[previous[2]][previous[3]].pixmapFacilityItem;
                                myrect[previous[2]][previous[3]].pixmapFacilityItem = new QGraphicsPixmapItem(
                                        QPixmap("../media/ul.png"));
                                myrect[previous[2]][previous[3]].pixmapFacilityItem->setPixmap(
                                        myrect[previous[2]][previous[3]].pixmapFacilityItem->pixmap().scaled(50, 50));
                                myrect[previous[2]][previous[3]].pixmapFacilityItem->setPos(windowPos.x() + 50,
                                                                                            windowPos.y());

                                scene->addItem(myrect[previous[2]][previous[3]].pixmapFacilityItem);
                                static_cast<ConveyorBelt *>(myrect[previous[2]][previous[3]].facility)->turn = "UpL";
                            }
                                // 右上->左->下
                            else if (previous[0] == previous[2] + 1 && previous[2] == i &&
                                     previous[1] == previous[3] &&
                                     previous[3] + 1 == j)
                            {
                                delete myrect[previous[2]][previous[3]].pixmapFacilityItem;
                                myrect[previous[2]][previous[3]].pixmapFacilityItem = new QGraphicsPixmapItem(
                                        QPixmap("../media/dr.png"));
                                myrect[previous[2]][previous[3]].pixmapFacilityItem->setPixmap(
                                        myrect[previous[2]][previous[3]].pixmapFacilityItem->pixmap().scaled(50, 50));
                                myrect[previous[2]][previous[3]].pixmapFacilityItem->setPos(windowPos.x(),
                                                                                            windowPos.y() - 50);

                                scene->addItem(myrect[previous[2]][previous[3]].pixmapFacilityItem);
                                static_cast<ConveyorBelt *>(myrect[previous[2]][previous[3]].facility)->turn = "DownR";
                            }
                                // 右下->上->左
                            else if (previous[0] == previous[2] && previous[2] - 1 == i &&
                                     previous[1] - 1 == previous[3] &&
                                     previous[3] == j)
                            {
                                delete myrect[previous[2]][previous[3]].pixmapFacilityItem;
                                myrect[previous[2]][previous[3]].pixmapFacilityItem = new QGraphicsPixmapItem(
                                        QPixmap("../media/dl.png"));
                                myrect[previous[2]][previous[3]].pixmapFacilityItem->setPixmap(
                                        myrect[previous[2]][previous[3]].pixmapFacilityItem->pixmap().scaled(50, 50));
                                myrect[previous[2]][previous[3]].pixmapFacilityItem->setPos(windowPos.x() + 50,
                                                                                            windowPos.y());

                                scene->addItem(myrect[previous[2]][previous[3]].pixmapFacilityItem);
                                static_cast<ConveyorBelt *>(myrect[previous[2]][previous[3]].facility)->turn = "DownL";
                            }
                                // 右下->左->上
                            else if (previous[0] == previous[2] + 1 && previous[2] == i &&
                                     previous[1] == previous[3] &&
                                     previous[3] - 1 == j)
                            {
                                delete myrect[previous[2]][previous[3]].pixmapFacilityItem;
                                myrect[previous[2]][previous[3]].pixmapFacilityItem = new QGraphicsPixmapItem(
                                        QPixmap("../media/ur.png"));
                                myrect[previous[2]][previous[3]].pixmapFacilityItem->setPixmap(
                                        myrect[previous[2]][previous[3]].pixmapFacilityItem->pixmap().scaled(50, 50));
                                myrect[previous[2]][previous[3]].pixmapFacilityItem->setPos(windowPos.x(),
                                                                                            windowPos.y() + 50);

                                scene->addItem(myrect[previous[2]][previous[3]].pixmapFacilityItem);
                                static_cast<ConveyorBelt *>(myrect[previous[2]][previous[3]].facility)->turn = "UpR";
                            }
                        }

                        //更新previous
                        previous[0] = previous[2];
                        previous[1] = previous[3];
                        previous[2] = i;
                        previous[3] = j;
                    }
                    if (!myrect[i][j].isDelivery)
                    {
                        // 放置当前传送带
                        myrect[i][j].setFacility("conveyorbelt");
                        myrect[i][j].isFacilityExist = true;
                        if (direction == 0 || direction == 2)
                        {
                            myrect[i][j].pixmapFacilityItem = new QGraphicsPixmapItem(QPixmap("../media/_belt.jpg"));
                        } else
                        {
                            myrect[i][j].pixmapFacilityItem = new QGraphicsPixmapItem(QPixmap("../media/_belt_h.png"));
                        }

                        myrect[i][j].pixmapFacilityItem->setPixmap(
                                myrect[i][j].pixmapFacilityItem->pixmap().scaled(50, 50));
                        myrect[i][j].pixmapFacilityItem->setVisible(true);
                        myrect[i][j].pixmapFacilityItem->setPos(windowPos);
                        scene->addItem(myrect[i][j].pixmapFacilityItem);


                        static_cast<ConveyorBelt *>(myrect[i][j].facility)->setDoor(direction);


                    } else
                    {
                        if (pixmapItem)
                        {
                            pixmapItem = nullptr;
                        }
                        press = false;
                        conveyorBelt = false;
                        previous.clear();
                        direction = 0;
                    }
                    game->check(myrect);
                }


            }

        }
    }

    return false;
}
