//
// Created by hemingguo on 2023-12-11.
//

#ifndef SHAPEZ_SECOND_H
#define SHAPEZ_SECOND_H

#include <QWidget>
#include <QDialog>
#include <QPushButton>
#include <QGraphicsView>
#include <QLabel>
#include <QMouseEvent>
#include <QGraphicsProxyWidget>
#include <QDebug>
#include <QPlainTextEdit>
#include "../DeliveryCenter/DeliveryCenter.h"
#include "../Game/Game.h"

QT_BEGIN_NAMESPACE
namespace Ui { class second; }
QT_END_NAMESPACE

class second : public QWidget
{
Q_OBJECT

public:
    explicit second(QWidget *parent = nullptr);


    ~second() override;

private:
    Ui::second *ui;
    int happy;
    int windowWidth;
    int windowHeight;
    QPlainTextEdit *money;
    QPushButton *Button1;
    QPushButton *Button2;
    QPushButton *Button3;


    QPoint windowPos;
private slots:

    void on1Click();

    void on2Click();

    void on3Click();
};


#endif //SHAPEZ_SECOND_H
