//
// Created by hemingguo on 2023-11-20.
//

/* Description of the document:
 * this file named "mainwindow" is used to initialize the origin window for the game.
 * its basic logic is that it will first play the start_video, then it will
 * present the initial screen window of the game, which include a big shapez [logo],
 * a [button] to start the game with a brief explanatory [text] below it,
 * and the [glassed-in background].
 */


#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QtMultimedia/QMediaPlayer>
#include <QDir>
#include <QMovie>
#include <QLabel>
#include <QTimer>
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
        QWidget(parent), ui(new Ui::MainWindow), movie(nullptr), label(nullptr)
{
    ui->setupUi(this);

    // 获取窗口的大小
    int windowWidth = this->width();
    int windowHeight = this->height();

    // 获取当前应用程序的路径(控制台调试用)
    //QString currentPath = QCoreApplication::applicationDirPath();
    //qDebug() << "当前工作目录：" << currentPath;

    //播放：[开始加载gif动画--3秒后销毁]
    playVideo( "../media/loading.gif");  //相对路径
    // 连接停止信号到槽函数
    connect(this, &MainWindow::videoStopped, this, &MainWindow::onVideoStopped);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete label;

}


// 播放开始加载动画
void MainWindow::playVideo(const QString &filePath)
{
    // 创建QLabel用于显示GIF
    label = new QLabel(this);

    // 创建QMovie并设置到QLabel
    movie = new QMovie(filePath);
    label->setMovie(movie);

    // 设置QLabel的大小策略，保持原本大小
    label->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    // 播放GIF
    movie->start();

    // 设置布局管理器
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(label);
    layout->setAlignment(label, Qt::AlignCenter);  // 让label在布局中居中
    setLayout(layout);

    // 设置定时器，3秒后停止播放GIF
    QTimer::singleShot(3000, this, [this]() {
        stopVideo();
    });

}

// 停止播放GIF，并销毁QMovie对象
void MainWindow::stopVideo()
{
    if (movie) {
        movie->stop();
        delete movie;
        label->clear();  // 清除label中的内容
        label->close();  // 关闭label

        // 发出停止信号
        emit videoStopped();
    }
}

// loading加载完毕后，呈现开始游戏的画面
void MainWindow::onVideoStopped()
{
    QWidget *blueLayer = new QWidget(this);
    blueLayer->setGeometry(0, 0, 1600, 1200);
    blueLayer->setStyleSheet("background-color: white;");
    blueLayer->show();
}