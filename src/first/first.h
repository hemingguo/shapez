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
#include <QPainter>
#include "../Toolbar/Toolbar.h"
#include "../MyRect/MyRect.h"
#include "../Facility/Facility.h"
#include "../Game/Game.h"
#include "../DeliveryCenter/DeliveryCenter.h"

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

    DeliveryCenter *center;

    Game *game;
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
    QPoint windowPos;

    bool bin;
    bool conveyorBelt;
    bool miner;
    bool cutMachine;
    bool press;

    std::vector<int> previous;
    int direction;

private slots:

    void onBinButtonClick();

    void onConveyorBeltButtonClick();

    void onMinerButtonClick();

    void onCutMachineButtonClick();
};


#endif //SHAPEZ_FIRST_H
