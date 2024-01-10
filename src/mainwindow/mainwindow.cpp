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
#include <QFontDatabase>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../first/first.h"
#include "../second/second.h"

//主窗口构造函数
MainWindow::MainWindow(QWidget *parent) :
        QWidget(parent), ui(new Ui::MainWindow), movie(nullptr), label(nullptr), layout(nullptr)
{

    //主窗口基本设置---------------------/

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

    //---------------------------主窗口基本设置/

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
    QTimer::singleShot(100, this, [this]()
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


    //开始游戏按钮-------------------/

    pushButton = new QPushButton(this);
    pushButton->setObjectName(QStringLiteral("pushButton"));
    pushButton->setText("开始游戏");// 设置按钮的文本
    pushButton->setGeometry(400, 500, 700, 200);// 设置按钮的大小和位置

    //按钮事件绑定
    connect(pushButton, &QPushButton::clicked, this, &MainWindow::onPushButtonClicked);

    //自定义字体
    QString fontPath = "../media/方正宋刻本秀楷简.TTF";  // 替换为字体文件路径
    int fontId = QFontDatabase::addApplicationFont(fontPath);
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
    QFont customFont(fontFamilies.first(), 35);  // 替换字体名称和字号
    pushButton->setFont(customFont);


// 设置样式
    pushButton->setStyleSheet("QPushButton {"
                              "border-radius: 50px;"  // 设置圆角半径
                              "background-color:  #32CD32;"  // 设置按钮背景颜色
                              "color: white;"  // 设置文字颜色
                              "}"
                              "QPushButton:hover {"
                              "background-color: #45a049;"  // 鼠标悬停时的背景颜色
                              "}");
    pushButton->show();// 显示按钮

    //----------------------开始游戏按钮/


    //放置logo图片---------------------/

    QLabel *imageLabel = new QLabel(this);
    imageLabel->setGeometry(400, 100, 700, 300);
    QPixmap originalImage("../media/big_logo.png");  // 替换为你的图片路径
    QPixmap scaledImage = originalImage.scaled(700, 300, Qt::KeepAspectRatio);
    imageLabel->setPixmap(scaledImage);
    imageLabel->show();

    //----------------------放置logo图片/


    //文字说明---------------------/
    QLabel *descriptionLabel = new QLabel(this);
    descriptionLabel->setText("欢迎来到异形工厂，尽情发挥你的聪明才智吧！");
    descriptionLabel->setGeometry(400, 1000, 700, 50);
    descriptionLabel->setFont(QFont("Arial", 16));
    descriptionLabel->setStyleSheet("color: rgb(0, 216, 230);");
    descriptionLabel->setAlignment(Qt::AlignCenter);
    descriptionLabel->show();
    //---------------------文字说明/
}

// 开始游戏按钮点击事件槽函数
void MainWindow::onPushButtonClicked()
{
    // 创建新窗口对象
    first *firstWindow = new first();
    // 显示新窗口
    firstWindow->show();

    // 关闭当前窗口
    close();
}