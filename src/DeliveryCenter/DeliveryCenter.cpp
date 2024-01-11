//
// Created by hemingguo on 2023-12-3.
//

#include "DeliveryCenter.h"

Around::Around() : id(0), isWork(false) {}

DeliveryCenter::DeliveryCenter() : total_value(0), copper_num(0), iron_num(0), half_copper_num(0)
{
    deliveryCenter = nullptr;
    copper_p = nullptr;
    copper_p_gewei = nullptr;
    copper_p_shiwei = nullptr;

    iron_p = nullptr;
    iron_p_gewei = nullptr;
    iron_p_shiwei = nullptr;

    half_copper_p = nullptr;
    half_copper_p_gewei = nullptr;
    half_copper_p_shiwei = nullptr;
}

DeliveryCenter::DeliveryCenter(QGraphicsScene *s, QGraphicsView *v) : total_value(0), copper_num(0), iron_num(0),
                                                                      half_copper_num(0)
{
    first_scene = s;
    first_view = v;
    deliveryCenter = nullptr;
    copper_p = nullptr;
    copper_p_gewei = nullptr;
    copper_p_shiwei = nullptr;

    iron_p = nullptr;
    iron_p_gewei = nullptr;
    iron_p_shiwei = nullptr;

    half_copper_p = nullptr;
    half_copper_p_gewei = nullptr;
    half_copper_p_shiwei = nullptr;
}


void DeliveryCenter::timerEvent(QTimerEvent *event)
{

    for (int i = 13; i <= 16; i++)
    {
        for (int j = 13; j <= 16; j++)
        {

            if (around[i][j].isWork && event->timerId() == around[i][j].id)
            {
                if (around[i][j].mineName == "copper")
                {
                    copper_num++;
                    total_value += 10;

                    delete copper_p_gewei;
                    delete copper_p_shiwei;
                    int gewei = copper_num % 10;
                    int shiwei = copper_num / 10;
                    QString name_g = "../media/" + QString::number(gewei) + ".png";
                    QString name_s = "../media/" + QString::number(shiwei) + ".png";
                    copper_p_gewei = new QGraphicsPixmapItem(QPixmap(name_g));
                    copper_p_gewei->setPixmap(copper_p_gewei->pixmap().scaled(30, 30));
                    copper_p_gewei->setPos(15 * 50 + 40, 13 * 50 + 30);
                    first_scene->addItem(copper_p_gewei);

                    copper_p_shiwei = new QGraphicsPixmapItem(QPixmap(name_s));
                    copper_p_shiwei->setPixmap(copper_p_shiwei->pixmap().scaled(30, 30));
                    copper_p_shiwei->setPos(15 * 50 + 10, 13 * 50 + 30);
                    first_scene->addItem(copper_p_shiwei);


                } else if (around[i][j].mineName == "iron")
                {
                    iron_num++;
                    total_value += 5;

                    delete iron_p_gewei;
                    delete iron_p_shiwei;
                    int gewei = iron_num % 10;
                    int shiwei = iron_num / 10;
                    QString name_g = "../media/" + QString::number(gewei) + ".png";
                    QString name_s = "../media/" + QString::number(shiwei) + ".png";
                    iron_p_gewei = new QGraphicsPixmapItem(QPixmap(name_g));
                    iron_p_gewei->setPixmap(iron_p_gewei->pixmap().scaled(30, 30));
                    iron_p_gewei->setPos(15 * 50 + 40, 14 * 50 + 15);
                    first_scene->addItem(iron_p_gewei);

                    iron_p_shiwei = new QGraphicsPixmapItem(QPixmap(name_s));
                    iron_p_shiwei->setPixmap(iron_p_shiwei->pixmap().scaled(30, 30));
                    iron_p_shiwei->setPos(15 * 50 + 10, 14 * 50 + 15);
                    first_scene->addItem(iron_p_shiwei);
                } else if (around[i][j].mineName == "halfcopper")
                {
                    half_copper_num++;
                    total_value += 5;
                }
                qDebug() << total_value;
                qDebug() << "copper: " << copper_num << ", iron: " << iron_num;
            }

        }
    }


}

void DeliveryCenter::arrival(std::string mineName, int distance, int i, int j)
{
    // 货物成功运达
    if (!around[i][j].isWork)
    {
        around[i][j].mineName = mineName;
        around[i][j].isWork = true;
        around[i][j].id = startTimer(distance * 100);
        qDebug() << "start_working!";
    }
}

int DeliveryCenter::examine(MyRect myrect[30][30], int i, int j)
{
    if (around[i][j].isWork == false)
    {
        return 0;
    } else
    {
        // 执行回头路径完整性检查
        if (i == 13 && j == 13) // 左上角
        {
            if (myrect[i - 1][j].isFacilityExist &&
                myrect[i - 1][j].getFacility()->getName() == "conveyorbelt" &&
                static_cast<ConveyorBelt *>(myrect[i - 1][j].facility)->getDoor() % 2 == 1)
            {
                return test(myrect, i - 1, j, 3);
            } else if (myrect[i][j - 1].isFacilityExist &&
                       myrect[i][j - 1].getFacility()->getName() == "conveyorbelt" &&
                       static_cast<ConveyorBelt *>(myrect[i][j - 1].facility)->getDoor() % 2 == 0)
            {
                return test(myrect, i, j - 1, 0);
            } else { return 1; }
        } else if (i == 13 && j == 16) // 左下角
        {

            if (myrect[i - 1][j].isFacilityExist &&
                myrect[i - 1][j].getFacility()->getName() == "conveyorbelt" &&
                static_cast<ConveyorBelt *>(myrect[i - 1][j].facility)->getDoor() % 2 == 1)
            {
                return test(myrect, i - 1, j, 3);
            } else if (myrect[i][j + 1].isFacilityExist &&
                       myrect[i][j + 1].getFacility()->getName() == "conveyorbelt" &&
                       static_cast<ConveyorBelt *>(myrect[i][j + 1].facility)->getDoor() % 2 == 0)
            {
                return test(myrect, i, j + 1, 2);
            } else { return 1; }
        } else if (i == 16 && j == 13) // 右上角
        {
            if (myrect[i][j - 1].isFacilityExist &&
                myrect[i][j - 1].getFacility()->getName() == "conveyorbelt" &&
                static_cast<ConveyorBelt *>(myrect[i][j - 1].facility)->getDoor() % 2 == 0)
            {
                return test(myrect, i, j - 1, 0);
            } else if (myrect[i + 1][j].isFacilityExist &&
                       myrect[i + 1][j].getFacility()->getName() == "conveyorbelt" &&
                       static_cast<ConveyorBelt *>(myrect[i + 1][j].facility)->getDoor() % 2 == 1)
            {
                return test(myrect, i + 1, j, 1);
            } else { return 1; }
        } else if (i == 16 && j == 16)  // 右下角
        {
            if (myrect[i + 1][j].isFacilityExist &&
                myrect[i + 1][j].getFacility()->getName() == "conveyorbelt" &&
                static_cast<ConveyorBelt *>(myrect[i + 1][j].facility)->getDoor() % 2 == 1)
            {
                return test(myrect, i + 1, j, 1);
            } else if (myrect[i][j + 1].isFacilityExist &&
                       myrect[i][j + 1].getFacility()->getName() == "conveyorbelt" &&
                       static_cast<ConveyorBelt *>(myrect[i][j + 1].facility)->getDoor() % 2 == 0)
            {
                return test(myrect, i, j + 1, 2);
            } else { return 1; }

        }


            //单边的处理
        else if (i == 13)  // 左边
        {
            if (myrect[i - 1][j].isFacilityExist &&
                myrect[i - 1][j].getFacility()->getName() == "conveyorbelt" &&
                static_cast<ConveyorBelt *>(myrect[i - 1][j].facility)->getDoor() % 2 == 1)
            {
                return test(myrect, i - 1, j, 3);
            } else { return 1; }
        } else if (i == 16) // 右边
        {
            if (myrect[i + 1][j].isFacilityExist &&
                myrect[i + 1][j].getFacility()->getName() == "conveyorbelt" &&
                static_cast<ConveyorBelt *>(myrect[i + 1][j].facility)->getDoor() % 2 == 1)
            {
                return test(myrect, i + 1, j, 1);
            } else { return 1; }
        } else if (j == 13) // 上边
        {
            if (myrect[i][j - 1].isFacilityExist &&
                myrect[i][j - 1].getFacility()->getName() == "conveyorbelt" &&
                static_cast<ConveyorBelt *>(myrect[i][j - 1].facility)->getDoor() % 2 == 0)
            {
                return test(myrect, i, j - 1, 0);
            } else { return 1; }
        } else if (j == 16) // 下边
        {
            if (myrect[i][j + 1].isFacilityExist &&
                myrect[i][j + 1].getFacility()->getName() == "conveyorbelt" &&
                static_cast<ConveyorBelt *>(myrect[i][j + 1].facility)->getDoor() % 2 == 0)
            {
                return test(myrect, i, j + 1, 2);
            } else { return 1; }
        }

    }
}

int DeliveryCenter::test(MyRect myrect[30][30], int i, int j, int sign)
{
    if (static_cast<ConveyorBelt *>(myrect[i][j].facility)->turn == "null")  // 如果该传送带不转弯，即为直的
    {
        if (sign == 0 && j - 1 >= 0)  //从下方 向上 传过来的
        {
            if (myrect[i][j - 1].isFacilityExist && myrect[i][j - 1].isMineExist &&
                myrect[i][j - 1].getFacility()->getName() == "miner")
            {
                cout << "the path is fine.";
                return 0;
            } else if (myrect[i][j - 1].isFacilityExist &&
                       myrect[i][j - 1].getFacility()->getName() == "conveyorbelt")
            {
                // 上方可以接受的条件是，上方是垂直直立的 或是 下右 下左 弯
                if ((static_cast<ConveyorBelt *>(myrect[i][j - 1].facility)->turn == "null" &&
                     static_cast<ConveyorBelt *>(myrect[i][j - 1].facility)->getDoor() % 2 == 0) ||
                    (static_cast<ConveyorBelt *>(myrect[i][j - 1].facility)->turn == "DownR" ||
                     static_cast<ConveyorBelt *>(myrect[i][j - 1].facility)->turn == "DownL"))
                {
                    return test(myrect, i, j - 1, sign);
                }
            } else { return 1; }

        } else if (sign == 1 && i + 1 < 30)  // 从左边 向右 传过来的
        {
            if (myrect[i + 1][j].isFacilityExist && myrect[i + 1][j].isMineExist &&
                myrect[i + 1][j].getFacility()->getName() == "miner")
            {
                cout << "the path is fine.";
                return 0;
            } else if (myrect[i + 1][j].isFacilityExist &&
                       myrect[i + 1][j].getFacility()->getName() == "conveyorbelt")
            {
                //右方可以接受的条件是，右方是水平直立的 或是 上左 下左 弯
                if ((static_cast<ConveyorBelt *>(myrect[i + 1][j].facility)->turn == "null" &&
                     static_cast<ConveyorBelt *>(myrect[i + 1][j].facility)->getDoor() % 2 == 1) ||
                    (static_cast<ConveyorBelt *>(myrect[i + 1][j].facility)->turn == "UpL" ||
                     static_cast<ConveyorBelt *>(myrect[i + 1][j].facility)->turn == "DownL"))
                {
                    return test(myrect, i + 1, j, sign);
                }
            } else { return 1; }

        } else if (sign == 2 && j + 1 < 30) // 从上边 向下 传过来的
        {
            if (myrect[i][j + 1].isFacilityExist && myrect[i][j + 1].isMineExist &&
                myrect[i][j + 1].getFacility()->getName() == "miner")
            {
                cout << "the path is fine.";
                return 0;
            } else if (myrect[i][j + 1].isFacilityExist &&
                       myrect[i][j + 1].getFacility()->getName() == "conveyorbelt")
            {
                //下方可以接受的条件是，下方是垂直直立的 或是 上左 上右 弯
                if ((static_cast<ConveyorBelt *>(myrect[i][j + 1].facility)->turn == "null" &&
                     static_cast<ConveyorBelt *>(myrect[i][j + 1].facility)->getDoor() % 2 == 0) ||
                    (static_cast<ConveyorBelt *>(myrect[i][j + 1].facility)->turn == "UpL" ||
                     static_cast<ConveyorBelt *>(myrect[i][j + 1].facility)->turn == "UpR"))
                {
                    return test(myrect, i, j + 1, sign);
                }
            } else { return 1; }
        } else if (sign == 3 && i - 1 >= 0)// 从右边 向左 传过来的
        {
            if (myrect[i - 1][j].isFacilityExist && myrect[i - 1][j].isMineExist &&
                myrect[i - 1][j].getFacility()->getName() == "miner")
            {
                cout << "the path is fine.";
                return 0;
            } else if (myrect[i - 1][j].isFacilityExist &&
                       myrect[i - 1][j].getFacility()->getName() == "conveyorbelt")
            {
                //左方可以接受的条件是，左方是水平直立的 或是 上右 下右 弯
                if ((static_cast<ConveyorBelt *>(myrect[i - 1][j].facility)->turn == "null" &&
                     static_cast<ConveyorBelt *>(myrect[i - 1][j].facility)->getDoor() % 2 == 1) ||
                    (static_cast<ConveyorBelt *>(myrect[i - 1][j].facility)->turn == "UpR" ||
                     static_cast<ConveyorBelt *>(myrect[i - 1][j].facility)->turn == "DownR"))
                {
                    return test(myrect, i - 1, j, sign);
                }
            } else { return 1; }
        }
    } else if (static_cast<ConveyorBelt *>(myrect[i][j].facility)->turn == "DownL") // 该传送带呈现下和左方向弯曲
    {
        if (sign % 2 == 0) // 从下方向左方传递
        {
            if (myrect[i - 1][j].isFacilityExist && myrect[i - 1][j].isMineExist &&
                myrect[i - 1][j].getFacility()->getName() == "miner")
            {
                cout << "the path is fine.";
                return 0;
            } else if (myrect[i - 1][j].isFacilityExist &&
                       myrect[i - 1][j].getFacility()->getName() == "conveyorbelt")
            {
                //左方可以接受的条件是，左方是水平直立的 或是 上右 下右 弯
                if ((static_cast<ConveyorBelt *>(myrect[i - 1][j].facility)->turn == "null" &&
                     static_cast<ConveyorBelt *>(myrect[i - 1][j].facility)->getDoor() % 2 == 1) ||
                    (static_cast<ConveyorBelt *>(myrect[i - 1][j].facility)->turn == "UpR" ||
                     static_cast<ConveyorBelt *>(myrect[i - 1][j].facility)->turn == "DownR"))
                {
                    return test(myrect, i - 1, j, 3);
                }
            } else { return 1; }
        } else // 从左方向下传递
        {
            if (myrect[i][j + 1].isFacilityExist && myrect[i][j + 1].isMineExist &&
                myrect[i][j + 1].getFacility()->getName() == "miner")
            {
                cout << "the path is fine.";
                return 0;
            } else if (myrect[i][j + 1].isFacilityExist &&
                       myrect[i][j + 1].getFacility()->getName() == "conveyorbelt")
            {
                //下方可以接受的条件是，下方是垂直直立的 或是 上左 上右 弯
                if ((static_cast<ConveyorBelt *>(myrect[i][j + 1].facility)->turn == "null" &&
                     static_cast<ConveyorBelt *>(myrect[i][j + 1].facility)->getDoor() % 2 == 0) ||
                    (static_cast<ConveyorBelt *>(myrect[i][j + 1].facility)->turn == "UpL" ||
                     static_cast<ConveyorBelt *>(myrect[i][j + 1].facility)->turn == "UpR"))
                {
                    return test(myrect, i, j + 1, 2);
                }
            } else { return 1; }
        }

    } else if (static_cast<ConveyorBelt *>(myrect[i][j].facility)->turn == "DownR") // 该传送带呈现下和右方向弯曲
    {
        if (sign % 2 == 0) // 从下方向右方传递
        {
            if (myrect[i + 1][j].isFacilityExist && myrect[i + 1][j].isMineExist &&
                myrect[i + 1][j].getFacility()->getName() == "miner")
            {
                cout << "the path is fine.";
                return 0;
            } else if (myrect[i + 1][j].isFacilityExist &&
                       myrect[i + 1][j].getFacility()->getName() == "conveyorbelt")
            {
                //右方可以接受的条件是，右方是水平直立的 或是 上左 下左 弯
                if ((static_cast<ConveyorBelt *>(myrect[i + 1][j].facility)->turn == "null" &&
                     static_cast<ConveyorBelt *>(myrect[i + 1][j].facility)->getDoor() % 2 == 1) ||
                    (static_cast<ConveyorBelt *>(myrect[i + 1][j].facility)->turn == "UpL" ||
                     static_cast<ConveyorBelt *>(myrect[i + 1][j].facility)->turn == "DownL"))
                {
                    return test(myrect, i + 1, j, 1);
                }
            } else { return 1; }
        } else // 从右方向下传递
        {
            if (myrect[i][j + 1].isFacilityExist && myrect[i][j + 1].isMineExist &&
                myrect[i][j + 1].getFacility()->getName() == "miner")
            {
                cout << "the path is fine.";
                return 0;
            } else if (myrect[i][j + 1].isFacilityExist &&
                       myrect[i][j + 1].getFacility()->getName() == "conveyorbelt")
            {
                //下方可以接受的条件是，下方是垂直直立的 或是 上左 上右 弯
                if ((static_cast<ConveyorBelt *>(myrect[i][j + 1].facility)->turn == "null" &&
                     static_cast<ConveyorBelt *>(myrect[i][j + 1].facility)->getDoor() % 2 == 0) ||
                    (static_cast<ConveyorBelt *>(myrect[i][j + 1].facility)->turn == "UpL" ||
                     static_cast<ConveyorBelt *>(myrect[i][j + 1].facility)->turn == "UpR"))
                {
                    return test(myrect, i, j + 1, 2);
                }
            } else { return 1; }
        }
    } else if (static_cast<ConveyorBelt *>(myrect[i][j].facility)->turn == "UpL") // 该传送带呈现上和左方向弯曲
    {
        if (sign % 2 == 0) // 从上方向左传递
        {
            if (myrect[i - 1][j].isFacilityExist && myrect[i - 1][j].isMineExist &&
                myrect[i - 1][j].getFacility()->getName() == "miner")
            {
                cout << "the path is fine.";
                return 0;
            } else if (myrect[i - 1][j].isFacilityExist &&
                       myrect[i - 1][j].getFacility()->getName() == "conveyorbelt")
            {
                //左方可以接受的条件是，左方是水平直立的 或是 上右 下右 弯
                if ((static_cast<ConveyorBelt *>(myrect[i - 1][j].facility)->turn == "null" &&
                     static_cast<ConveyorBelt *>(myrect[i - 1][j].facility)->getDoor() % 2 == 1) ||
                    (static_cast<ConveyorBelt *>(myrect[i - 1][j].facility)->turn == "UpR" ||
                     static_cast<ConveyorBelt *>(myrect[i - 1][j].facility)->turn == "DownR"))
                {
                    return test(myrect, i - 1, j, 3);
                }
            } else { return 1; }
        } else // 从左向上传递
        {
            if (myrect[i][j - 1].isFacilityExist && myrect[i][j - 1].isMineExist &&
                myrect[i][j - 1].getFacility()->getName() == "miner")
            {
                cout << "the path is fine.";
                return 0;
            } else if (myrect[i][j - 1].isFacilityExist &&
                       myrect[i][j - 1].getFacility()->getName() == "conveyorbelt")
            {
                // 上方可以接受的条件是，上方是垂直直立的 或是 下右 下左 弯
                if ((static_cast<ConveyorBelt *>(myrect[i][j - 1].facility)->turn == "null" &&
                     static_cast<ConveyorBelt *>(myrect[i][j - 1].facility)->getDoor() % 2 == 0) ||
                    (static_cast<ConveyorBelt *>(myrect[i][j - 1].facility)->turn == "DownR" ||
                     static_cast<ConveyorBelt *>(myrect[i][j - 1].facility)->turn == "DownL"))
                {
                    return test(myrect, i, j - 1, 0);
                }
            } else { return 1; }
        }
    } else if (static_cast<ConveyorBelt *>(myrect[i][j].facility)->turn == "UpR") // 该传送带呈现上和右方向弯曲
    {
        if (sign % 2 == 0) // 从上方向右传递
        {
            if (myrect[i + 1][j].isFacilityExist && myrect[i + 1][j].isMineExist &&
                myrect[i + 1][j].getFacility()->getName() == "miner")
            {
                cout << "the path is fine.";
                return 0;
            } else if (myrect[i + 1][j].isFacilityExist &&
                       myrect[i + 1][j].getFacility()->getName() == "conveyorbelt")
            {
                //右方可以接受的条件是，右方是水平直立的 或是 上左 下左 弯
                if ((static_cast<ConveyorBelt *>(myrect[i + 1][j].facility)->turn == "null" &&
                     static_cast<ConveyorBelt *>(myrect[i + 1][j].facility)->getDoor() % 2 == 1) ||
                    (static_cast<ConveyorBelt *>(myrect[i + 1][j].facility)->turn == "UpL" ||
                     static_cast<ConveyorBelt *>(myrect[i + 1][j].facility)->turn == "DownL"))
                {
                    return test(myrect, i + 1, j, 1);
                }
            } else { return 1; }
        } else // 从右向上传递
        {
            if (myrect[i][j - 1].isFacilityExist && myrect[i][j - 1].isMineExist &&
                myrect[i][j - 1].getFacility()->getName() == "miner")
            {
                cout << "the path is fine.";
                return 0;
            } else if (myrect[i][j - 1].isFacilityExist &&
                       myrect[i][j - 1].getFacility()->getName() == "conveyorbelt")
            {
                // 上方可以接受的条件是，上方是垂直直立的 或是 下右 下左 弯
                if ((static_cast<ConveyorBelt *>(myrect[i][j - 1].facility)->turn == "null" &&
                     static_cast<ConveyorBelt *>(myrect[i][j - 1].facility)->getDoor() % 2 == 0) ||
                    (static_cast<ConveyorBelt *>(myrect[i][j - 1].facility)->turn == "DownR" ||
                     static_cast<ConveyorBelt *>(myrect[i][j - 1].facility)->turn == "DownL"))
                {
                    return test(myrect, i, j - 1, 0);
                }
            } else { return 1; }
        }
    } else { return 1; }
}

void DeliveryCenter::around_examine(MyRect myrect[30][30])
{
    for (int i = 13; i <= 16; i++)
    {
        for (int j = 13; j <= 16; j++)
        {
            if (examine(myrect, i, j) == 1)
            {
                around[i][j].isWork = false;
                killTimer(around[i][j].id);
                around[i][j].id = 0;
            }
        }
    }
}