//
// Created by hemingguo on 2024-1-12.
//

#include "Good.h"


Good::Good(DeliveryCenter *cen, MyRect myrect[30][30], QGraphicsScene *s, int xi, int xj, int si, std::string mineName)
        : oi(0), oj(0),
          mine_pix(nullptr)
{

    //qDebug() << Good::belt_speed;
    name = mineName;
    i = xi;
    j = xj;
    sign = si;
    center = cen;
    timer = new QTimer(this);
    scene = s;
    cut_speed = Game::cut_speed;
    belt_speed = Game::belt_speed;
    connect(timer, &QTimer::timeout, this, std::bind(&Good::pass, this, myrect));
    timer->start(50);

}

void Good::pass(MyRect myrect[30][30])
{
    belt_speed = Game::belt_speed;
    cut_speed = Game::cut_speed;
    if (mine_pix != nullptr)
    {
        mine_pix->setZValue(10);


        if (myrect[i][j].isFacilityExist)
        {
            if (myrect[i][j].getFacility()->getName() == "miner")
            {

                if (sign == 0 && j - 1 >= 0)  //从下方 向上 传过来的
                {

                    if (myrect[i][j - 1].isDelivery)
                    {

                        center->acc(name);
                        delete this->mine_pix;
                        delete this;
                    } else if (myrect[i][j - 1].isFacilityExist &&
                               myrect[i][j - 1].getFacility()->getName() == "conveyorbelt")
                    {
                        // 上方可以接受的条件是，上方是垂直直立的 或是 下右 下左 弯
                        if ((static_cast<ConveyorBelt *>(myrect[i][j - 1].facility)->turn == "null" &&
                             static_cast<ConveyorBelt *>(myrect[i][j - 1].facility)->getDoor() % 2 == 0) ||
                            (static_cast<ConveyorBelt *>(myrect[i][j - 1].facility)->turn == "DownR" ||
                             static_cast<ConveyorBelt *>(myrect[i][j - 1].facility)->turn == "DownL"))
                        {

                            mine_pix->setPos(mine_pix->pos().x(), mine_pix->pos().y() - 2 * belt_speed);
                            j = mine_pix->pos().y() / 50 + 1;
                        }

                    }

                } else if (sign == 1 && i + 1 < 30)  // 从左边 向右 传过来的
                {
                    if (myrect[i + 1][j].isDelivery)
                    {

                        center->acc(name);
                        delete this->mine_pix;
                        delete this;
                    } else if (myrect[i + 1][j].isFacilityExist &&
                               myrect[i + 1][j].getFacility()->getName() == "conveyorbelt")
                    {
                        //右方可以接受的条件是，右方是水平直立的 或是 上左 下左 弯
                        if ((static_cast<ConveyorBelt *>(myrect[i + 1][j].facility)->turn == "null" &&
                             static_cast<ConveyorBelt *>(myrect[i + 1][j].facility)->getDoor() % 2 == 1) ||
                            (static_cast<ConveyorBelt *>(myrect[i + 1][j].facility)->turn == "UpL" ||
                             static_cast<ConveyorBelt *>(myrect[i + 1][j].facility)->turn == "DownL"))
                        {
                            mine_pix->setPos(mine_pix->pos().x() + 2 * belt_speed, mine_pix->pos().y());
                            i = mine_pix->pos().x() / 50;
                        }
                    }

                } else if (sign == 2 && j + 1 < 30) // 从上边 向下 传过来的
                {
                    if (myrect[i][j + 1].isDelivery)
                    {

                        center->acc(name);
                        delete this->mine_pix;
                        delete this;
                    } else if (myrect[i][j + 1].isFacilityExist &&
                               myrect[i][j + 1].getFacility()->getName() == "conveyorbelt")
                    {
                        //下方可以接受的条件是，下方是垂直直立的 或是 上左 上右 弯
                        if ((static_cast<ConveyorBelt *>(myrect[i][j + 1].facility)->turn == "null" &&
                             static_cast<ConveyorBelt *>(myrect[i][j + 1].facility)->getDoor() % 2 == 0) ||
                            (static_cast<ConveyorBelt *>(myrect[i][j + 1].facility)->turn == "UpL" ||
                             static_cast<ConveyorBelt *>(myrect[i][j + 1].facility)->turn == "UpR"))
                        {
                            mine_pix->setPos(mine_pix->pos().x(), mine_pix->pos().y() + 2 * belt_speed);
                            j = mine_pix->pos().y() / 50;
                        }
                    }
                } else if (sign == 3 && i - 1 >= 0)// 从右边 向左 传过来的
                {
                    if (myrect[i - 1][j].isDelivery)
                    {

                        center->acc(name);
                        delete this->mine_pix;
                        delete this;
                    } else if (myrect[i - 1][j].isFacilityExist &&
                               myrect[i - 1][j].getFacility()->getName() == "conveyorbelt")
                    {
                        //左方可以接受的条件是，左方是水平直立的 或是 上右 下右 弯
                        if ((static_cast<ConveyorBelt *>(myrect[i - 1][j].facility)->turn == "null" &&
                             static_cast<ConveyorBelt *>(myrect[i - 1][j].facility)->getDoor() % 2 == 1) ||
                            (static_cast<ConveyorBelt *>(myrect[i - 1][j].facility)->turn == "UpR" ||
                             static_cast<ConveyorBelt *>(myrect[i - 1][j].facility)->turn == "DownR"))
                        {
                            mine_pix->setPos(mine_pix->pos().x() - 2 * belt_speed, mine_pix->pos().y());
                            i = mine_pix->pos().x() / 50 + 1;
                        }
                    }
                }
            }
            if (myrect[i][j].getFacility()->getName() == "cutmachine")// 如果当前设备为切割机
            {
                if (name != "halfcopper")
                {
                    name = "halfcopper";
                    delete mine_pix;

                    mine_pix = new QGraphicsPixmapItem(QPixmap("../media/half_copper_mine.png"));
                    mine_pix->setPixmap(mine_pix->pixmap().scaled(50, 50)); // 缩放
                    mine_pix->setPos(i * 50, j * 50);//放置
                    scene->addItem(mine_pix);// 添加到场景
                    mine_pix->setZValue(10);
                }
                if (sign == 0 && j - 1 >= 0)  //从下方 向上 传过来的
                {
                    if (myrect[i][j - 1].isDelivery)
                    {

                        center->acc(name);
                        delete this->mine_pix;
                        delete this;
                    } else if (myrect[i][j - 1].isFacilityExist &&
                               myrect[i][j - 1].getFacility()->getName() == "conveyorbelt")
                    {
                        // 上方可以接受的条件是，上方是垂直直立的 或是 下右 下左 弯
                        if ((static_cast<ConveyorBelt *>(myrect[i][j - 1].facility)->turn == "null" &&
                             static_cast<ConveyorBelt *>(myrect[i][j - 1].facility)->getDoor() % 2 == 0) ||
                            (static_cast<ConveyorBelt *>(myrect[i][j - 1].facility)->turn == "DownR" ||
                             static_cast<ConveyorBelt *>(myrect[i][j - 1].facility)->turn == "DownL"))
                        {

                            if (myrect[i + 1][j - 1].isFacilityExist &&
                                myrect[i + 1][j - 1].getFacility()->getName() == "bin")
                            {
                                mine_pix->setPos(mine_pix->pos().x(), mine_pix->pos().y() - 2 * cut_speed);
                                j = mine_pix->pos().y() / 50 + 1;
                            }

                        }

                    }

                } else if (sign == 1 && i + 1 < 30)  // 从左边 向右 传过来的
                {
                    if (myrect[i + 1][j].isDelivery)
                    {

                        center->acc(name);
                        delete this->mine_pix;
                        delete this;
                    } else if (myrect[i + 1][j].isFacilityExist &&
                               myrect[i + 1][j].getFacility()->getName() == "conveyorbelt")
                    {
                        //右方可以接受的条件是，右方是水平直立的 或是 上左 下左 弯
                        if ((static_cast<ConveyorBelt *>(myrect[i + 1][j].facility)->turn == "null" &&
                             static_cast<ConveyorBelt *>(myrect[i + 1][j].facility)->getDoor() % 2 == 1) ||
                            (static_cast<ConveyorBelt *>(myrect[i + 1][j].facility)->turn == "UpL" ||
                             static_cast<ConveyorBelt *>(myrect[i + 1][j].facility)->turn == "DownL"))
                        {
                            if (myrect[i + 1][j + 1].isFacilityExist &&
                                myrect[i + 1][j + 1].getFacility()->getName() == "bin")
                            {
                                mine_pix->setPos(mine_pix->pos().x() + 2 * cut_speed, mine_pix->pos().y());
                                i = mine_pix->pos().x() / 50;
                            }
                        }
                    }

                } else if (sign == 2 && j + 1 < 30) // 从上边 向下 传过来的
                {
                    if (myrect[i][j + 1].isDelivery)
                    {

                        center->acc(name);
                        delete this->mine_pix;
                        delete this;
                    } else if (myrect[i][j + 1].isFacilityExist &&
                               myrect[i][j + 1].getFacility()->getName() == "conveyorbelt")
                    {
                        //下方可以接受的条件是，下方是垂直直立的 或是 上左 上右 弯
                        if ((static_cast<ConveyorBelt *>(myrect[i][j + 1].facility)->turn == "null" &&
                             static_cast<ConveyorBelt *>(myrect[i][j + 1].facility)->getDoor() % 2 == 0) ||
                            (static_cast<ConveyorBelt *>(myrect[i][j + 1].facility)->turn == "UpL" ||
                             static_cast<ConveyorBelt *>(myrect[i][j + 1].facility)->turn == "UpR"))
                        {
                            if (myrect[i - 1][j + 1].isFacilityExist &&
                                myrect[i - 1][j + 1].getFacility()->getName() == "bin")
                            {
                                mine_pix->setPos(mine_pix->pos().x(), mine_pix->pos().y() + 2 * cut_speed);
                                j = mine_pix->pos().y() / 50;
                            }
                        }
                    }
                } else if (sign == 3 && i - 1 >= 0)// 从右边 向左 传过来的
                {
                    if (myrect[i - 1][j].isDelivery)
                    {

                        center->acc(name);
                        delete this->mine_pix;
                        delete this;
                    } else if (myrect[i - 1][j].isFacilityExist &&
                               myrect[i - 1][j].getFacility()->getName() == "conveyorbelt")
                    {
                        //左方可以接受的条件是，左方是水平直立的 或是 上右 下右 弯
                        if ((static_cast<ConveyorBelt *>(myrect[i - 1][j].facility)->turn == "null" &&
                             static_cast<ConveyorBelt *>(myrect[i - 1][j].facility)->getDoor() % 2 == 1) ||
                            (static_cast<ConveyorBelt *>(myrect[i - 1][j].facility)->turn == "UpR" ||
                             static_cast<ConveyorBelt *>(myrect[i - 1][j].facility)->turn == "DownR"))
                        {
                            if (myrect[i - 1][j - 1].isFacilityExist &&
                                myrect[i - 1][j - 1].getFacility()->getName() == "bin")
                            {
                                mine_pix->setPos(mine_pix->pos().x() - 2 * cut_speed, mine_pix->pos().y());
                                i = mine_pix->pos().x() / 50 + 1;
                            }

                        }
                    }
                }
            }


            if (myrect[i][j].getFacility()->getName() == "conveyorbelt")// 如果当前设备为传送带
            {
                if (static_cast<ConveyorBelt *>(myrect[i][j].facility)->turn == "null")  // 如果该传送带不转弯，即为直的
                {
                    if (sign == 0 && j - 1 >= 0)  //从下方 向上 传过来的
                    {
                        if (myrect[i][j - 1].isDelivery)
                        {

                            center->acc(name);
                            delete this->mine_pix;
                            delete this;

                        } else if (myrect[i][j - 1].isFacilityExist &&
                                   myrect[i][j - 1].getFacility()->getName() == "conveyorbelt")
                        {
                            // 上方可以接受的条件是，上方是垂直直立的 或是 下右 下左 弯
                            if ((static_cast<ConveyorBelt *>(myrect[i][j - 1].facility)->turn == "null" &&
                                 static_cast<ConveyorBelt *>(myrect[i][j - 1].facility)->getDoor() % 2 == 0) ||
                                (static_cast<ConveyorBelt *>(myrect[i][j - 1].facility)->turn == "DownR" ||
                                 static_cast<ConveyorBelt *>(myrect[i][j - 1].facility)->turn == "DownL"))
                            {

                                mine_pix->setPos(mine_pix->pos().x(), mine_pix->pos().y() - 2 * belt_speed);
                                j = mine_pix->pos().y() / 50 + 1;
                            }
                        } else if (name == "copper" && myrect[i][j - 1].isFacilityExist &&
                                   myrect[i][j - 1].getFacility()->getName() == "cutmachine" &&
                                   static_cast<CutMachine *>(myrect[i][j - 1].facility)->l_or_r == "left" &&
                                   static_cast<CutMachine *>(myrect[i][j - 1].facility)->direction == 0)
                        {
                            mine_pix->setPos(mine_pix->pos().x(), mine_pix->pos().y() - 2 * belt_speed);
                            j = mine_pix->pos().y() / 50 + 1;

                        }

                    } else if (sign == 1 && i + 1 < 30)  // 从左边 向右 传过来的
                    {
                        if (myrect[i + 1][j].isDelivery)
                        {

                            center->acc(name);
                            delete this->mine_pix;
                            delete this;
                        } else if (myrect[i + 1][j].isFacilityExist &&
                                   myrect[i + 1][j].getFacility()->getName() == "conveyorbelt")
                        {
                            //右方可以接受的条件是，右方是水平直立的 或是 上左 下左 弯
                            if ((static_cast<ConveyorBelt *>(myrect[i + 1][j].facility)->turn == "null" &&
                                 static_cast<ConveyorBelt *>(myrect[i + 1][j].facility)->getDoor() % 2 == 1) ||
                                (static_cast<ConveyorBelt *>(myrect[i + 1][j].facility)->turn == "UpL" ||
                                 static_cast<ConveyorBelt *>(myrect[i + 1][j].facility)->turn == "DownL"))
                            {
                                mine_pix->setPos(mine_pix->pos().x() + 2 * belt_speed, mine_pix->pos().y());
                                i = mine_pix->pos().x() / 50;
                            }
                        } else if (name == "copper" && myrect[i + 1][j].isFacilityExist &&
                                   myrect[i + 1][j].getFacility()->getName() == "cutmachine" &&
                                   static_cast<CutMachine *>(myrect[i + 1][j].facility)->l_or_r == "left" &&
                                   static_cast<CutMachine *>(myrect[i + 1][j].facility)->direction == 1)
                        {
                            mine_pix->setPos(mine_pix->pos().x() + 2 * belt_speed, mine_pix->pos().y());
                            i = mine_pix->pos().x() / 50;
                        }

                    } else if (sign == 2 && j + 1 < 30) // 从上边 向下 传过来的
                    {
                        if (myrect[i][j + 1].isDelivery)
                        {

                            center->acc(name);
                            delete this->mine_pix;
                            delete this;
                        } else if (myrect[i][j + 1].isFacilityExist &&
                                   myrect[i][j + 1].getFacility()->getName() == "conveyorbelt")
                        {
                            //下方可以接受的条件是，下方是垂直直立的 或是 上左 上右 弯
                            if ((static_cast<ConveyorBelt *>(myrect[i][j + 1].facility)->turn == "null" &&
                                 static_cast<ConveyorBelt *>(myrect[i][j + 1].facility)->getDoor() % 2 == 0) ||
                                (static_cast<ConveyorBelt *>(myrect[i][j + 1].facility)->turn == "UpL" ||
                                 static_cast<ConveyorBelt *>(myrect[i][j + 1].facility)->turn == "UpR"))
                            {
                                mine_pix->setPos(mine_pix->pos().x(), mine_pix->pos().y() + 2 * belt_speed);
                                j = mine_pix->pos().y() / 50;
                            }
                        } else if (name == "copper" && myrect[i][j + 1].isFacilityExist &&
                                   myrect[i][j + 1].getFacility()->getName() == "cutmachine" &&
                                   static_cast<CutMachine *>(myrect[i][j + 1].facility)->l_or_r == "left" &&
                                   static_cast<CutMachine *>(myrect[i][j + 1].facility)->direction == 2)
                        {
                            mine_pix->setPos(mine_pix->pos().x(), mine_pix->pos().y() + 2 * belt_speed);
                            j = mine_pix->pos().y() / 50;
                        }
                    } else if (sign == 3 && i - 1 >= 0)// 从右边 向左 传过来的
                    {
                        if (myrect[i - 1][j].isDelivery)
                        {

                            center->acc(name);
                            delete this->mine_pix;
                            delete this;
                        } else if (myrect[i - 1][j].isFacilityExist &&
                                   myrect[i - 1][j].getFacility()->getName() == "conveyorbelt")
                        {
                            //左方可以接受的条件是，左方是水平直立的 或是 上右 下右 弯
                            if ((static_cast<ConveyorBelt *>(myrect[i - 1][j].facility)->turn == "null" &&
                                 static_cast<ConveyorBelt *>(myrect[i - 1][j].facility)->getDoor() % 2 == 1) ||
                                (static_cast<ConveyorBelt *>(myrect[i - 1][j].facility)->turn == "UpR" ||
                                 static_cast<ConveyorBelt *>(myrect[i - 1][j].facility)->turn == "DownR"))
                            {
                                mine_pix->setPos(mine_pix->pos().x() - 2 * belt_speed, mine_pix->pos().y());
                                i = mine_pix->pos().x() / 50 + 1;
                            }
                        } else if (name == "copper" && myrect[i - 1][j].isFacilityExist &&
                                   myrect[i - 1][j].getFacility()->getName() == "cutmachine" &&
                                   static_cast<CutMachine *>(myrect[i - 1][j].facility)->l_or_r == "left" &&
                                   static_cast<CutMachine *>(myrect[i - 1][j].facility)->direction == 3)
                        {
                            mine_pix->setPos(mine_pix->pos().x() - 2 * belt_speed, mine_pix->pos().y());
                            i = mine_pix->pos().x() / 50 + 1;
                        }
                    }
                }












                    //传送带是弯的
                else if (static_cast<ConveyorBelt *>(myrect[i][j].facility)->turn == "DownL") // 该传送带呈现下和左方向弯曲
                {
                    if (sign % 2 == 0) // 从下方向左方传递
                    {

                        if (myrect[i - 1][j].isDelivery)
                        {

                            center->acc(name);
                            delete this->mine_pix;
                            delete this;
                        } else if (myrect[i - 1][j].isFacilityExist &&
                                   myrect[i - 1][j].getFacility()->getName() == "conveyorbelt")
                        {
                            //左方可以接受的条件是，左方是水平直立的 或是 上右 下右 弯
                            if ((static_cast<ConveyorBelt *>(myrect[i - 1][j].facility)->turn == "null" &&
                                 static_cast<ConveyorBelt *>(myrect[i - 1][j].facility)->getDoor() % 2 == 1) ||
                                (static_cast<ConveyorBelt *>(myrect[i - 1][j].facility)->turn == "UpR" ||
                                 static_cast<ConveyorBelt *>(myrect[i - 1][j].facility)->turn == "DownR"))
                            {
                                mine_pix->setPos(mine_pix->pos().x() - 2 * belt_speed, mine_pix->pos().y());
                                i = mine_pix->pos().x() / 50 + 1;
                                if (static_cast<ConveyorBelt *>(myrect[i][j].facility)->turn != "DownL")
                                {
                                    sign = 3;
                                }
                            }
                        } else if (name == "copper" && myrect[i - 1][j].isFacilityExist &&
                                   myrect[i - 1][j].getFacility()->getName() == "cutmachine" &&
                                   static_cast<CutMachine *>(myrect[i - 1][j].facility)->l_or_r == "left" &&
                                   static_cast<CutMachine *>(myrect[i - 1][j].facility)->direction == 3)
                        {
                            mine_pix->setPos(mine_pix->pos().x() - 2 * belt_speed, mine_pix->pos().y());
                            i = mine_pix->pos().x() / 50 + 1;
                            if (myrect[i][j].getFacility()->getName() == "cutmachine")
                            {
                                sign = 3;
                            }
                        }

                    } else // 从左方向下传递
                    {
                        if (myrect[i][j + 1].isDelivery)
                        {

                            center->acc(name);
                            delete this->mine_pix;
                            delete this;
                        } else if (myrect[i][j + 1].isFacilityExist &&
                                   myrect[i][j + 1].getFacility()->getName() == "conveyorbelt")
                        {
                            //下方可以接受的条件是，下方是垂直直立的 或是 上左 上右 弯
                            if ((static_cast<ConveyorBelt *>(myrect[i][j + 1].facility)->turn == "null" &&
                                 static_cast<ConveyorBelt *>(myrect[i][j + 1].facility)->getDoor() % 2 == 0) ||
                                (static_cast<ConveyorBelt *>(myrect[i][j + 1].facility)->turn == "UpL" ||
                                 static_cast<ConveyorBelt *>(myrect[i][j + 1].facility)->turn == "UpR"))
                            {
                                mine_pix->setPos(mine_pix->pos().x(), mine_pix->pos().y() + 2 * belt_speed);
                                j = mine_pix->pos().y() / 50;
                                if (static_cast<ConveyorBelt *>(myrect[i][j].facility)->turn != "DownL")
                                {
                                    sign = 2;
                                }

                            }
                        } else if (name == "copper" && myrect[i][j + 1].isFacilityExist &&
                                   myrect[i][j + 1].getFacility()->getName() == "cutmachine" &&
                                   static_cast<CutMachine *>(myrect[i][j + 1].facility)->l_or_r == "left" &&
                                   static_cast<CutMachine *>(myrect[i][j + 1].facility)->direction == 2)
                        {
                            mine_pix->setPos(mine_pix->pos().x(), mine_pix->pos().y() + 2 * belt_speed);
                            j = mine_pix->pos().y() / 50;
                            if (myrect[i][j].getFacility()->getName() == "cutmachine")
                            {
                                sign = 2;
                            }
                        }
                    }

                } else if (static_cast<ConveyorBelt *>(myrect[i][j].facility)->turn == "DownR") // 该传送带呈现下和右方向弯曲
                {
                    if (sign % 2 == 0) // 从下方向右方传递
                    {
                        if (myrect[i + 1][j].isDelivery)
                        {

                            center->acc(name);
                            delete this->mine_pix;
                            delete this;
                        } else if (myrect[i + 1][j].isFacilityExist &&
                                   myrect[i + 1][j].getFacility()->getName() == "conveyorbelt")
                        {
                            //右方可以接受的条件是，右方是水平直立的 或是 上左 下左 弯
                            if ((static_cast<ConveyorBelt *>(myrect[i + 1][j].facility)->turn == "null" &&
                                 static_cast<ConveyorBelt *>(myrect[i + 1][j].facility)->getDoor() % 2 == 1) ||
                                (static_cast<ConveyorBelt *>(myrect[i + 1][j].facility)->turn == "UpL" ||
                                 static_cast<ConveyorBelt *>(myrect[i + 1][j].facility)->turn == "DownL"))
                            {
                                mine_pix->setPos(mine_pix->pos().x() + 2 * belt_speed, mine_pix->pos().y());
                                i = mine_pix->pos().x() / 50;
                                if (static_cast<ConveyorBelt *>(myrect[i][j].facility)->turn != "DownR")
                                {
                                    sign = 1;
                                }
                            }
                        } else if (name == "copper" && myrect[i + 1][j].isFacilityExist &&
                                   myrect[i + 1][j].getFacility()->getName() == "cutmachine" &&
                                   static_cast<CutMachine *>(myrect[i + 1][j].facility)->l_or_r == "left" &&
                                   static_cast<CutMachine *>(myrect[i + 1][j].facility)->direction == 1)
                        {
                            mine_pix->setPos(mine_pix->pos().x() + 2 * belt_speed, mine_pix->pos().y());
                            i = mine_pix->pos().x() / 50;
                            if (myrect[i][j].getFacility()->getName() == "cutmachine")
                            {
                                sign = 1;
                            }
                        }
                    } else // 从右方向下传递
                    {
                        if (myrect[i][j + 1].isDelivery)
                        {

                            center->acc(name);
                            delete this->mine_pix;
                            delete this;
                        } else if (myrect[i][j + 1].isFacilityExist &&
                                   myrect[i][j + 1].getFacility()->getName() == "conveyorbelt")
                        {
                            //下方可以接受的条件是，下方是垂直直立的 或是 上左 上右 弯
                            if ((static_cast<ConveyorBelt *>(myrect[i][j + 1].facility)->turn == "null" &&
                                 static_cast<ConveyorBelt *>(myrect[i][j + 1].facility)->getDoor() % 2 == 0) ||
                                (static_cast<ConveyorBelt *>(myrect[i][j + 1].facility)->turn == "UpL" ||
                                 static_cast<ConveyorBelt *>(myrect[i][j + 1].facility)->turn == "UpR"))
                            {
                                mine_pix->setPos(mine_pix->pos().x(), mine_pix->pos().y() + 2 * belt_speed);
                                j = mine_pix->pos().y() / 50;
                                if (static_cast<ConveyorBelt *>(myrect[i][j].facility)->turn != "DownR")
                                {
                                    sign = 2;
                                }
                            }
                        } else if (name == "copper" && myrect[i][j + 1].isFacilityExist &&
                                   myrect[i][j + 1].getFacility()->getName() == "cutmachine" &&
                                   static_cast<CutMachine *>(myrect[i][j + 1].facility)->l_or_r == "left" &&
                                   static_cast<CutMachine *>(myrect[i][j + 1].facility)->direction == 2)
                        {
                            mine_pix->setPos(mine_pix->pos().x(), mine_pix->pos().y() + 2 * belt_speed);
                            j = mine_pix->pos().y() / 50;
                            if (myrect[i][j].getFacility()->getName() == "cutmachine")
                            {
                                sign = 2;
                            }
                        }
                    }
                } else if (static_cast<ConveyorBelt *>(myrect[i][j].facility)->turn == "UpL") // 该传送带呈现上和左方向弯曲
                {
                    if (sign % 2 == 0) // 从上方向左传递
                    {
                        if (myrect[i - 1][j].isDelivery)
                        {

                            center->acc(name);
                            delete this->mine_pix;
                            delete this;
                        } else if (myrect[i - 1][j].isFacilityExist &&
                                   myrect[i - 1][j].getFacility()->getName() == "conveyorbelt")
                        {
                            //左方可以接受的条件是，左方是水平直立的 或是 上右 下右 弯
                            if ((static_cast<ConveyorBelt *>(myrect[i - 1][j].facility)->turn == "null" &&
                                 static_cast<ConveyorBelt *>(myrect[i - 1][j].facility)->getDoor() % 2 == 1) ||
                                (static_cast<ConveyorBelt *>(myrect[i - 1][j].facility)->turn == "UpR" ||
                                 static_cast<ConveyorBelt *>(myrect[i - 1][j].facility)->turn == "DownR"))
                            {
                                mine_pix->setPos(mine_pix->pos().x() - 2 * belt_speed, mine_pix->pos().y());
                                i = mine_pix->pos().x() / 50 + 1;
                                if (static_cast<ConveyorBelt *>(myrect[i][j].facility)->turn != "UpL")
                                {
                                    sign = 3;
                                }
                            }
                        } else if (name == "copper" && myrect[i - 1][j].isFacilityExist &&
                                   myrect[i - 1][j].getFacility()->getName() == "cutmachine" &&
                                   static_cast<CutMachine *>(myrect[i - 1][j].facility)->l_or_r == "left" &&
                                   static_cast<CutMachine *>(myrect[i - 1][j].facility)->direction == 3)
                        {
                            mine_pix->setPos(mine_pix->pos().x() - 2 * belt_speed, mine_pix->pos().y());
                            i = mine_pix->pos().x() / 50 + 1;
                            if (myrect[i][j].getFacility()->getName() == "cutmachine")
                            {
                                sign = 3;
                            }
                        }

                    } else // 从左向上传递
                    {
                        if (myrect[i][j - 1].isDelivery)
                        {

                            center->acc(name);
                            delete this->mine_pix;
                            delete this;
                        } else if (myrect[i][j - 1].isFacilityExist &&
                                   myrect[i][j - 1].getFacility()->getName() == "conveyorbelt")
                        {
                            // 上方可以接受的条件是，上方是垂直直立的 或是 下右 下左 弯
                            if ((static_cast<ConveyorBelt *>(myrect[i][j - 1].facility)->turn == "null" &&
                                 static_cast<ConveyorBelt *>(myrect[i][j - 1].facility)->getDoor() % 2 == 0) ||
                                (static_cast<ConveyorBelt *>(myrect[i][j - 1].facility)->turn == "DownR" ||
                                 static_cast<ConveyorBelt *>(myrect[i][j - 1].facility)->turn == "DownL"))
                            {
                                mine_pix->setPos(mine_pix->pos().x(), mine_pix->pos().y() - 2 * belt_speed);
                                j = mine_pix->pos().y() / 50 + 1;
                                if (static_cast<ConveyorBelt *>(myrect[i][j].facility)->turn != "UpL")
                                {
                                    sign = 0;
                                }
                            }
                        } else if (name == "copper" && myrect[i][j - 1].isFacilityExist &&
                                   myrect[i][j - 1].getFacility()->getName() == "cutmachine" &&
                                   static_cast<CutMachine *>(myrect[i][j - 1].facility)->l_or_r == "left" &&
                                   static_cast<CutMachine *>(myrect[i][j - 1].facility)->direction == 0)
                        {
                            mine_pix->setPos(mine_pix->pos().x(), mine_pix->pos().y() - 2 * belt_speed);
                            j = mine_pix->pos().y() / 50 + 1;
                            if (myrect[i][j].getFacility()->getName() == "cutmachine")
                            {
                                sign = 0;
                            }
                        }
                    }
                } else if (static_cast<ConveyorBelt *>(myrect[i][j].facility)->turn == "UpR") // 该传送带呈现上和右方向弯曲
                {
                    if (sign % 2 == 0) // 从上方向右传递
                    {
                        if (myrect[i + 1][j].isDelivery)
                        {

                            center->acc(name);
                            delete this->mine_pix;
                            delete this;
                        } else if (myrect[i + 1][j].isFacilityExist &&
                                   myrect[i + 1][j].getFacility()->getName() == "conveyorbelt")
                        {
                            //右方可以接受的条件是，右方是水平直立的 或是 上左 下左 弯
                            if ((static_cast<ConveyorBelt *>(myrect[i + 1][j].facility)->turn == "null" &&
                                 static_cast<ConveyorBelt *>(myrect[i + 1][j].facility)->getDoor() % 2 == 1) ||
                                (static_cast<ConveyorBelt *>(myrect[i + 1][j].facility)->turn == "UpL" ||
                                 static_cast<ConveyorBelt *>(myrect[i + 1][j].facility)->turn == "DownL"))
                            {
                                mine_pix->setPos(mine_pix->pos().x() + 2 * belt_speed, mine_pix->pos().y());
                                i = mine_pix->pos().x() / 50;
                                if (static_cast<ConveyorBelt *>(myrect[i][j].facility)->turn != "UpR")
                                {
                                    sign = 1;
                                }
                            }
                        } else if (name == "copper" && myrect[i + 1][j].isFacilityExist &&
                                   myrect[i + 1][j].getFacility()->getName() == "cutmachine" &&
                                   static_cast<CutMachine *>(myrect[i + 1][j].facility)->l_or_r == "left" &&
                                   static_cast<CutMachine *>(myrect[i + 1][j].facility)->direction == 1)
                        {
                            mine_pix->setPos(mine_pix->pos().x() + 2 * belt_speed, mine_pix->pos().y());
                            i = mine_pix->pos().x() / 50;
                            if (myrect[i][j].getFacility()->getName() == "cutmachine")
                            {
                                sign = 1;
                            }
                        }
                    } else // 从右向上传递
                    {
                        if (myrect[i][j - 1].isDelivery)
                        {

                            center->acc(name);
                            delete this->mine_pix;
                            delete this;
                        } else if (myrect[i][j - 1].isFacilityExist &&
                                   myrect[i][j - 1].getFacility()->getName() == "conveyorbelt")
                        {
                            // 上方可以接受的条件是，上方是垂直直立的 或是 下右 下左 弯
                            if ((static_cast<ConveyorBelt *>(myrect[i][j - 1].facility)->turn == "null" &&
                                 static_cast<ConveyorBelt *>(myrect[i][j - 1].facility)->getDoor() % 2 == 0) ||
                                (static_cast<ConveyorBelt *>(myrect[i][j - 1].facility)->turn == "DownR" ||
                                 static_cast<ConveyorBelt *>(myrect[i][j - 1].facility)->turn == "DownL"))
                            {
                                mine_pix->setPos(mine_pix->pos().x(), mine_pix->pos().y() - 2 * belt_speed);
                                j = mine_pix->pos().y() / 50 + 1;
                                if (static_cast<ConveyorBelt *>(myrect[i][j].facility)->turn != "UpR")
                                {
                                    sign = 0;
                                }
                            }
                        } else if (name == "copper" && myrect[i][j - 1].isFacilityExist &&
                                   myrect[i][j - 1].getFacility()->getName() == "cutmachine" &&
                                   static_cast<CutMachine *>(myrect[i][j - 1].facility)->l_or_r == "left" &&
                                   static_cast<CutMachine *>(myrect[i][j - 1].facility)->direction == 0)
                        {
                            mine_pix->setPos(mine_pix->pos().x(), mine_pix->pos().y() - 2 * belt_speed);
                            j = mine_pix->pos().y() / 50 + 1;
                            if (myrect[i][j].getFacility()->getName() == "cutmachine")
                            {
                                sign = 0;
                            }
                        }
                    }
                }
            }
        }
    }
}

void Good::state(int ori, int orj, int ii, int jj, int si, std::string na)
{
    oi = ori;
    oj = orj;
    i = ii;
    j = jj;
    sign = si;
    name = na;
};