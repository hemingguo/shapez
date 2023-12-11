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

QT_BEGIN_NAMESPACE
namespace Ui { class second; }
QT_END_NAMESPACE

class second : public QWidget
{
Q_OBJECT

public:
    explicit second(QWidget *parent = nullptr);

    bool eventFilter(QObject *obj, QEvent *event) override;

    ~second() override;

private:
    Ui::second *ui;
    int happy;
    int windowWidth;
    int windowHeight;
    QGraphicsView *view;
    QGraphicsScene *scene;
    QPushButton *binButton;
    QGraphicsPixmapItem *pixmapItem;
private slots:

    void onBinButtonClick();
};


#endif //SHAPEZ_SECOND_H
