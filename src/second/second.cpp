//
// Created by hemingguo on 2023-12-11.
//

// You may need to build the project (run Qt uic code generator) to get "ui_second.h" resolved

#include <QFontDatabase>
#include <QMessageBox>
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


    //升级1
    Button1 = new QPushButton(this);
    Button1->setObjectName(QStringLiteral("pushButton1"));
    Button1->setText("200金币升级交付中心大小4*4->5*5");// 设置按钮的文本
    Button1->setGeometry(100, 50, 400, 100);// 设置按钮的大小和位置

    //按钮事件绑定
    connect(Button1, &QPushButton::clicked, this, &second::on1Click);

    //自定义字体
    QString fontPath = "../media/方正宋刻本秀楷简.TTF";  // 替换为字体文件路径
    int fontId = QFontDatabase::addApplicationFont(fontPath);
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
    QFont customFont(fontFamilies.first(), 10);  // 替换字体名称和字号
    Button1->setFont(customFont);





// 设置样式
    Button1->setStyleSheet("QPushButton {"
                           "border-radius: 50px;"  // 设置圆角半径
                           "background-color:  #98F5FF;"  // 设置按钮背景颜色
                           "color: blue;"  // 设置文字颜色
                           "}"
                           "QPushButton:hover {"
                           "background-color: #96CDCD;"  // 鼠标悬停时的背景颜色
                           "}");
    Button1->show();// 显示按钮


//升级2
    Button2 = new QPushButton(this);
    Button2->setObjectName(QStringLiteral("pushButton2"));
    Button2->setText("400金币升级矿物价值（翻倍！）");// 设置按钮的文本
    Button2->setGeometry(100, 200, 400, 100);// 设置按钮的大小和位置

    //按钮事件绑定
    connect(Button2, &QPushButton::clicked, this, &second::on2Click);

    //自定义字体

    Button2->setFont(customFont);





// 设置样式
    Button2->setStyleSheet("QPushButton {"
                           "border-radius: 50px;"  // 设置圆角半径
                           "background-color:  #98F5FF;"  // 设置按钮背景颜色
                           "color: blue;"  // 设置文字颜色
                           "}"
                           "QPushButton:hover {"
                           "background-color: #96CDCD;"  // 鼠标悬停时的背景颜色
                           "}");
    Button2->show();// 显示按钮

    //升级3
    Button3 = new QPushButton(this);
    Button3->setObjectName(QStringLiteral("pushButton3"));
    Button3->setText("300金币升级矿物地大小2*2->4*4");// 设置按钮的文本
    Button3->setGeometry(100, 350, 400, 100);// 设置按钮的大小和位置

    //按钮事件绑定
    connect(Button3, &QPushButton::clicked, this, &second::on3Click);

    //自定义字体

    Button3->setFont(customFont);





// 设置样式
    Button3->setStyleSheet("QPushButton {"
                           "border-radius: 50px;"  // 设置圆角半径
                           "background-color:  #98F5FF;"  // 设置按钮背景颜色
                           "color: blue;"  // 设置文字颜色
                           "}"
                           "QPushButton:hover {"
                           "background-color: #96CDCD;"  // 鼠标悬停时的背景颜色
                           "}");
    Button3->show();// 显示按钮


// 当前金币数
    money = new QPlainTextEdit(this);
    money->setPlainText("Your current money is : " + QString::number(DeliveryCenter::total_value));
    money->setStyleSheet(
            "color: green; font-style: italic; font-weight: bold;font-family: '../media/方正宋刻本秀楷简.TTF';font-size: 12pt;");

    money->setGeometry(100, 500, 400, 50);
}


second::~second()
{
    delete ui;
}

void second::on1Click()
{
    if (Game::DC_update)
    {
        QMessageBox::information(this, "Information", "已经...已经升级过啦，笨蛋！");
    } else if (DeliveryCenter::total_value >= 200)
    {

        DeliveryCenter::total_value -= 200;
        delete money;
        money = new QPlainTextEdit(this);
        money->setPlainText("Your current money is : " + QString::number(DeliveryCenter::total_value));
        money->setStyleSheet(
                "color: green; font-style: italic; font-weight: bold;font-family: '../media/方正宋刻本秀楷简.TTF';font-size: 12pt;");

        money->setGeometry(100, 500, 400, 50);
        money->show();
        Game::DC_update = true;


    } else
    {
        QMessageBox::information(this, "Information", "金币不足噢-v-,交付矿物获取金币叭QAQ");
    }
}

void second::on2Click()
{
    if (DeliveryCenter::hasDouble == 2)
    {
        QMessageBox::information(this, "Information", "已经...已经升级过啦，笨蛋！");
    } else if (DeliveryCenter::total_value >= 400)
    {


        DeliveryCenter::total_value -= 400;
        DeliveryCenter::hasDouble = 2;
        delete money;
        money = new QPlainTextEdit(this);
        money->setPlainText("Your current money is : " + QString::number(DeliveryCenter::total_value));
        money->setStyleSheet(
                "color: green; font-style: italic; font-weight: bold;font-family: '../media/方正宋刻本秀楷简.TTF';font-size: 12pt;");

        money->setGeometry(100, 500, 400, 50);
        money->show();

    } else
    {
        QMessageBox::information(this, "Information", "金币不足噢-v-,交付矿物获取金币叭QAQ");
    }

}

void second::on3Click()
{
    if (Game::Mine_update)
    {
        QMessageBox::information(this, "Information", "已经...已经升级过啦，笨蛋！");
    } else if (DeliveryCenter::total_value >= 300)
    {


        DeliveryCenter::total_value -= 300;
        delete money;
        money = new QPlainTextEdit(this);
        money->setPlainText("Your current money is : " + QString::number(DeliveryCenter::total_value));
        money->setStyleSheet(
                "color: green; font-style: italic; font-weight: bold;font-family: '../media/方正宋刻本秀楷简.TTF';font-size: 12pt;");

        money->setGeometry(100, 500, 400, 50);
        money->show();
        Game::Mine_update = true;

    } else
    {
        QMessageBox::information(this, "Information", "金币不足噢-v-,交付矿物获取金币叭QAQ");
    }
}