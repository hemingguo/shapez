//
// Created by hemingguo on 2023-11-20.
//

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description of the document:(文件作用说明)                                            *
 * this file named "mainwindow" is used to initialize the origin window for the game.  *
 * its basic logic is that it will first play the loading video, then it will          *
 * present the initial screen window of the game, which include a big shapez [logo],   *
 * a [button] to start the game with a brief explanatory [text] below it,              *
 * and the [glassed-in background].                                                    *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QtMultimedia/QMediaPlayer>
#include <QDir>
#include <QMovie>
#include <QLabel>
#include <QTimer>
#include <QMenuBar>
#include "mainwindow.h"
#include "ui_mainwindow.h"

//主窗口构造函数
MainWindow::MainWindow(QWidget *parent) :
        QWidget(parent), ui(new Ui::MainWindow), movie(nullptr), label(nullptr), layout(nullptr)
{

    //主窗口基本设置---/

    ui->setupUi(this);

    setWindowTitle("Shapez");//重命名窗口标题

    setWindowIcon(QIcon("../media/logo.png"));//设置窗口图标

    // 获取窗口的大小
    windowWidth = this->width();
    windowHeight = this->height();


    setFixedSize(windowWidth, windowHeight);// 固定窗口大小

    // 获取当前应用程序的路径(控制台调试用)
    //QString currentPath = QCoreApplication::applicationDirPath();
    //qDebug() << "当前工作目录：" << currentPath;

    //---主窗口基本设置/

    playVideo("../media/loading.gif"); //播放：[开始加载gif动画--2秒后销毁]

    // 连接[停止信号]到[槽函数]
    connect(this, &MainWindow::videoStopped, this, &MainWindow::onVideoStopped);//呈现开始游戏画面

}

//主窗口析构函数
MainWindow::~MainWindow()
{
    delete ui;
}

//清空布局管理器
void MainWindow::clearLayout(QLayout *layout)
{
    if (!layout)
        return;

    QLayoutItem *item;
    while ((item = layout->takeAt(0)) != nullptr)
    {
        QWidget *widget = item->widget();
        if (widget)
        {
            widget->hide();  // 隐藏部件，避免窗口闪烁
            delete widget;   // 删除布局中的部件
        }
        delete item;  // 删除布局项
    }

    delete layout;  // 删除现有的布局管理器
}


// 播放开始加载动画
void MainWindow::playVideo(const QString &filePath)
{

    label = new QLabel(this);// 创建QLabel用于显示GIF
    movie = new QMovie(filePath);// 创建QMovie并设置到QLabel

    label->setMovie(movie);
    label->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);// 设置QLabel的大小策略，保持原本大小
    movie->start();// 播放GIF

    // 设置布局管理器
    layout = new QVBoxLayout(this);
    layout->addWidget(label);
    layout->setAlignment(label, Qt::AlignCenter);  // 让label在布局中居中
    setLayout(layout);

    // 设置定时器，2秒后停止播放GIF
    QTimer::singleShot(2000, this, [this]()
    {
        stopVideo();
    });

}


// 停止播放GIF，并销毁QMovie对象
void MainWindow::stopVideo()
{
    if (movie)
    {
        movie->stop();
        delete movie;
        movie = nullptr;
        delete label;
        label = nullptr;
        // 发出停止信号
        emit videoStopped();
    }
}


// loading加载完毕后，呈现开始游戏的画面
void MainWindow::onVideoStopped()
{
    // 断开信号槽连接
    disconnect(this, &MainWindow::videoStopped, this, &MainWindow::onVideoStopped);

    //初始化布局管理器
    if (layout)
    {
        clearLayout(layout);
    }


    // 创建场景
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, windowWidth * 2, windowHeight * 2);// 设置场景的大小为窗口的大小4倍

    // 创建视图
    QGraphicsView *view = new QGraphicsView(scene, this);
    view->setSceneRect(0, 0, windowWidth * 2, windowHeight * 2); // 视图显示场景的全部
    view->setGeometry(0, 0, windowWidth, windowHeight); // 固定视图大小
    view->show();


    //初始化地图---/
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

    //---初始化地图/

}