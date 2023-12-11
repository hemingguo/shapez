//
// Created by hemingguo on 2023-12-11.
//

// You may need to build the project (run Qt uic code generator) to get "ui_second.h" resolved

#include "second.h"
#include "ui_second.h"


second::second(QWidget *parent) :
        QWidget(parent), ui(new Ui::second), happy(0)
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
    scene->setSceneRect(0, 0, 600, 400);// 设置场景的大小为窗口的大小

    // 创建视图
    view = new QGraphicsView(scene, this);
    view->setSceneRect(0, 0, 600, 400); // 视图显示场景的全部
    view->setGeometry(0, 0, 600, 400); // 固定视图位置


    view->show();
    // 将水平滚动条策略设置为始终关闭
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // 将垂直滚动条策略设置为始终关闭
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    view->setMouseTracking(true);
    view->viewport()->installEventFilter(this);


    pixmapItem = new QGraphicsPixmapItem(QPixmap("../media/bin.png"));//新建方格
    pixmapItem->setPixmap(pixmapItem->pixmap().scaled(50, 50)); // 将方格缩放
    pixmapItem->setPos(0, 0);//按序放置方格
    scene->addItem(pixmapItem);// 添加方格到场景

    // 创建垃圾桶按钮---/
    binButton = new QPushButton(QIcon("../media/bin.png"), "", this);
    binButton->setIconSize(QSize(50, 50));// 设置按钮显示模式为IconOnly
    binButton->setFixedSize(50, 50);// 设置按钮大小
    binButton->move(200, 400);// 移动按钮到底部靠右位置

    connect(binButton, &QPushButton::clicked, this, &second::onBinButtonClick);// 连接按钮的点击信号到槽函数，
    //---创建垃圾桶按钮/
}


second::~second()
{
    delete ui;
}

bool second::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == view->viewport() and happy == 1)  // 检查事件是否与视图视口相关
    {
        if (event->type() == QEvent::MouseMove)
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            QPoint windowPos = mouseEvent->pos();
            qDebug() << "鼠标在窗口中移动。位置：" << windowPos;
            pixmapItem->setPos(windowPos);//按序放置方格
        }
        if (event->type() == QEvent::MouseButtonPress)
        {
            happy = 0;
        }
    }

    // 继续传播事件
    return false;
}

void second::onBinButtonClick()
{
    happy = 1;

}