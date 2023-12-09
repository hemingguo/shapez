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

QT_BEGIN_NAMESPACE
namespace Ui { class first; }
QT_END_NAMESPACE

class first : public QWidget
{
Q_OBJECT

public:
    explicit first(QWidget *parent = nullptr);

    ~first() override;


protected:
    void mouseMoveEvent(QMouseEvent *event) override;

    bool eventFilter(QObject *obj, QEvent *event) override;

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
    QLabel *dragLabel;

    QPointF mousePosition; // 用于保存鼠标位置的变量


private slots:

    void onBinButtonClick();

    void onConveyorBeltButtonClick();

    void onMinerButtonClick();

    void onCutMachineButtonClick();
};


#endif //SHAPEZ_FIRST_H
