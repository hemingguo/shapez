//
// Created by hemingguo on 2023-12-1.
//

#ifndef SHAPEZ_FIRST_H
#define SHAPEZ_FIRST_H

#include <QWidget>
#include <QDialog>
#include <QPushButton>
#include <QGraphicsView>
#include <QLabel>
#include <QMouseEvent>
#include <QGraphicsProxyWidget>
#include "../Toolbar/Toolbar.h"
#include "../MyRect/MyRect.h"
#include <QPainter>

QT_BEGIN_NAMESPACE
namespace Ui { class first; }
QT_END_NAMESPACE

class first : public QWidget
{
Q_OBJECT

public:
    explicit first(QWidget *parent = nullptr);

    ~first() override;

    bool eventFilter(QObject *obj, QEvent *event) override;

    MyRect myrect[30][30];

private:

    Ui::first *ui;
    int windowWidth;
    int windowHeight;
    QGraphicsView *view;
    QGraphicsScene *scene;

    QPushButton *binButton;
    QPushButton *conveyorBeltButton;
    QPushButton *minerButton;
    QPushButton *cutMachineButton;
    QGraphicsPixmapItem *pixmapItem;
    bool bin;
    bool conveyorBelt;
    bool miner;
    bool cutMachine;
    QGraphicsPixmapItem *deliveryCenter;

    QPoint windowPos;


private slots:

    void onBinButtonClick();

    void onConveyorBeltButtonClick();

    void onMinerButtonClick();

    void onCutMachineButtonClick();
};


#endif //SHAPEZ_FIRST_H
