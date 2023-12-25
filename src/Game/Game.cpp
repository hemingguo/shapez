//
// Created by hemingguo on 2023-12-14.
//

#include "Game.h"

Game::Game(DeliveryCenter *x) : center(x)
{

}

void Game::check(MyRect myrect[30][30])
{
    for (int i = 22; i < 26; i++)
    {
        for (int j = 22; j < 26; j++)
        {
            dig(myrect, i, j);
        }
    }
    for (int i = 4; i < 8; i++)
    {
        for (int j = 4; j < 8; j++)
        {
            dig(myrect, i, j);
        }
    }
}


void Game::dig(MyRect myrect[30][30], int i, int j)
{

    if (myrect[i][j].isFacilityExist && myrect[i][j].isMineExist && myrect[i][j].getFacility()->getName() == "miner")
    {
        int exit = static_cast<Miner *>(myrect[i][j].facility)->getDirection(); //获取采矿机的出口方向
        if (exit == 0)
        {
            if (j - 1 >= 0 && myrect[i][j - 1].isFacilityExist &&
                myrect[i][j - 1].getFacility()->getName() == "conveyorbelt")
            {
                if (static_cast<ConveyorBelt *>(myrect[i][j - 1].facility)->getDoor() % 2 == 0) //如果是竖着放的
                {

                    pass(myrect, i, j - 1, 0, i, j, myrect[i][j].getMine()->getName(), 0);

                }
            }
        } else if (exit == 1)
        {
            if (i + 1 < 30 && myrect[i + 1][j].isFacilityExist &&
                myrect[i + 1][j].getFacility()->getName() == "conveyorbelt")
            {
                if (static_cast<ConveyorBelt *>(myrect[i + 1][j].facility)->getDoor() % 2 == 1) //如果是横着放的
                {
                    pass(myrect, i + 1, j, 1, i, j, myrect[i][j].getMine()->getName(), 0);
                }
            }
        } else if (exit == 2)
        {
            if (j + 1 < 30 && myrect[i][j + 1].isFacilityExist &&
                myrect[i][j + 1].getFacility()->getName() == "conveyorbelt")
            {
                if (static_cast<ConveyorBelt *>(myrect[i][j + 1].facility)->getDoor() % 2 == 0) //如果是竖着放的
                {
                    pass(myrect, i, j + 1, 2, i, j, myrect[i][j].getMine()->getName(), 0);
                }
            }
        } else
        {
            if (i - 1 >= 0 && myrect[i - 1][j].isFacilityExist &&
                myrect[i - 1][j].getFacility()->getName() == "conveyorbelt")
            {
                if (static_cast<ConveyorBelt *>(myrect[i - 1][j].facility)->getDoor() % 2 == 1) //如果是横着放的
                {
                    pass(myrect, i - 1, j, 3, i, j, myrect[i][j].getMine()->getName(), 0);
                }
            }
        }
    }
}

void Game::pass(MyRect myrect[30][30], int i, int j, int sign, int oi, int oj, string mineName, int distance)
{

    if (static_cast<ConveyorBelt *>(myrect[i][j].facility)->turn == "null")  // 如果该传送带不转弯，即为直的
    {
        if (sign == 0 && j - 1 >= 0)  //从下方 向上 传过来的
        {
            if (myrect[i][j - 1].isDelivery)
            {
                cout << "arrive! start form " << oi << ", " << oj << " to " << i << ", " << j - 1 << " mine: "
                     << mineName << " distance: " << distance + 1 << endl;
                center->arrival(mineName, distance + 1, i, j - 1);
            } else if (myrect[i][j - 1].isFacilityExist &&
                       myrect[i][j - 1].getFacility()->getName() == "conveyorbelt")
            {
                // 上方可以接受的条件是，上方是垂直直立的 或是 下右 下左 弯
                if ((static_cast<ConveyorBelt *>(myrect[i][j - 1].facility)->turn == "null" &&
                     static_cast<ConveyorBelt *>(myrect[i][j - 1].facility)->getDoor() % 2 == 0) ||
                    (static_cast<ConveyorBelt *>(myrect[i][j - 1].facility)->turn == "DownR" ||
                     static_cast<ConveyorBelt *>(myrect[i][j - 1].facility)->turn == "DownL"))
                {
                    pass(myrect, i, j - 1, sign, oi, oj, mineName, distance + 1);
                }
            }

        } else if (sign == 1 && i + 1 < 30)  // 从左边 向右 传过来的
        {
            if (myrect[i + 1][j].isDelivery)
            {
                cout << "arrive! start form " << oi << ", " << oj << " to " << i + 1 << ", " << j << " mine: "
                     << mineName << " distance: " << distance + 1 << endl;
                center->arrival(mineName, distance + 1, i + 1, j);
            } else if (myrect[i + 1][j].isFacilityExist &&
                       myrect[i + 1][j].getFacility()->getName() == "conveyorbelt")
            {
                //右方可以接受的条件是，右方是水平直立的 或是 上左 下左 弯
                if ((static_cast<ConveyorBelt *>(myrect[i + 1][j].facility)->turn == "null" &&
                     static_cast<ConveyorBelt *>(myrect[i + 1][j].facility)->getDoor() % 2 == 1) ||
                    (static_cast<ConveyorBelt *>(myrect[i + 1][j].facility)->turn == "UpL" ||
                     static_cast<ConveyorBelt *>(myrect[i + 1][j].facility)->turn == "DownL"))
                {
                    pass(myrect, i + 1, j, sign, oi, oj, mineName, distance + 1);
                }
            }

        } else if (sign == 2 && j + 1 < 30) // 从上边 向下 传过来的
        {
            if (myrect[i][j + 1].isDelivery)
            {
                cout << "arrive! start form " << oi << ", " << oj << " to " << i << ", " << j + 1 << " mine: "
                     << mineName << " distance: " << distance + 1 << endl;
                center->arrival(mineName, distance + 1, i, j + 1);
            } else if (myrect[i][j + 1].isFacilityExist &&
                       myrect[i][j + 1].getFacility()->getName() == "conveyorbelt")
            {
                //下方可以接受的条件是，下方是垂直直立的 或是 上左 上右 弯
                if ((static_cast<ConveyorBelt *>(myrect[i][j + 1].facility)->turn == "null" &&
                     static_cast<ConveyorBelt *>(myrect[i][j + 1].facility)->getDoor() % 2 == 0) ||
                    (static_cast<ConveyorBelt *>(myrect[i][j + 1].facility)->turn == "UpL" ||
                     static_cast<ConveyorBelt *>(myrect[i][j + 1].facility)->turn == "UpR"))
                {
                    pass(myrect, i, j + 1, sign, oi, oj, mineName, distance + 1);
                }
            }
        } else if (sign == 3 && i - 1 >= 0)// 从右边 向左 传过来的
        {
            if (myrect[i - 1][j].isDelivery)
            {
                cout << "arrive! start form " << oi << ", " << oj << " to " << i - 1 << ", " << j << " mine: "
                     << mineName << " distance: " << distance + 1 << endl;
                center->arrival(mineName, distance + 1, i - 1, j);
            } else if (myrect[i - 1][j].isFacilityExist &&
                       myrect[i - 1][j].getFacility()->getName() == "conveyorbelt")
            {
                //左方可以接受的条件是，左方是水平直立的 或是 上右 下右 弯
                if ((static_cast<ConveyorBelt *>(myrect[i - 1][j].facility)->turn == "null" &&
                     static_cast<ConveyorBelt *>(myrect[i - 1][j].facility)->getDoor() % 2 == 1) ||
                    (static_cast<ConveyorBelt *>(myrect[i - 1][j].facility)->turn == "UpR" ||
                     static_cast<ConveyorBelt *>(myrect[i - 1][j].facility)->turn == "DownR"))
                {
                    pass(myrect, i - 1, j, sign, oi, oj, mineName, distance + 1);
                }
            }
        }
    } else if (static_cast<ConveyorBelt *>(myrect[i][j].facility)->turn == "DownL") // 该传送带呈现下和左方向弯曲
    {
        if (sign % 2 == 0) // 从下方向左方传递
        {
            if (myrect[i - 1][j].isDelivery)
            {
                cout << "arrive! start form " << oi << ", " << oj << " to " << i - 1 << ", " << j << " mine: "
                     << mineName << " distance: " << distance + 1 << endl;
                center->arrival(mineName, distance + 1, i - 1, j);
            } else if (myrect[i - 1][j].isFacilityExist &&
                       myrect[i - 1][j].getFacility()->getName() == "conveyorbelt")
            {
                //左方可以接受的条件是，左方是水平直立的 或是 上右 下右 弯
                if ((static_cast<ConveyorBelt *>(myrect[i - 1][j].facility)->turn == "null" &&
                     static_cast<ConveyorBelt *>(myrect[i - 1][j].facility)->getDoor() % 2 == 1) ||
                    (static_cast<ConveyorBelt *>(myrect[i - 1][j].facility)->turn == "UpR" ||
                     static_cast<ConveyorBelt *>(myrect[i - 1][j].facility)->turn == "DownR"))
                {
                    pass(myrect, i - 1, j, 3, oi, oj, mineName, distance + 1);
                }
            }
        } else // 从左方向下传递
        {
            if (myrect[i][j + 1].isDelivery)
            {
                cout << "arrive! start form " << oi << ", " << oj << " to " << i << ", " << j + 1 << " mine: "
                     << mineName << " distance: " << distance + 1 << endl;
                center->arrival(mineName, distance + 1, i, j + 1);
            } else if (myrect[i][j + 1].isFacilityExist &&
                       myrect[i][j + 1].getFacility()->getName() == "conveyorbelt")
            {
                //下方可以接受的条件是，下方是垂直直立的 或是 上左 上右 弯
                if ((static_cast<ConveyorBelt *>(myrect[i][j + 1].facility)->turn == "null" &&
                     static_cast<ConveyorBelt *>(myrect[i][j + 1].facility)->getDoor() % 2 == 0) ||
                    (static_cast<ConveyorBelt *>(myrect[i][j + 1].facility)->turn == "UpL" ||
                     static_cast<ConveyorBelt *>(myrect[i][j + 1].facility)->turn == "UpR"))
                {
                    pass(myrect, i, j + 1, 2, oi, oj, mineName, distance + 1);
                }
            }
        }

    } else if (static_cast<ConveyorBelt *>(myrect[i][j].facility)->turn == "DownR") // 该传送带呈现下和右方向弯曲
    {
        if (sign % 2 == 0) // 从下方向右方传递
        {
            if (myrect[i + 1][j].isDelivery)
            {
                cout << "arrive! start form " << oi << ", " << oj << " to " << i + 1 << ", " << j << " mine: "
                     << mineName << " distance: " << distance + 1 << endl;
                center->arrival(mineName, distance + 1, i + 1, j);
            } else if (myrect[i + 1][j].isFacilityExist &&
                       myrect[i + 1][j].getFacility()->getName() == "conveyorbelt")
            {
                //右方可以接受的条件是，右方是水平直立的 或是 上左 下左 弯
                if ((static_cast<ConveyorBelt *>(myrect[i + 1][j].facility)->turn == "null" &&
                     static_cast<ConveyorBelt *>(myrect[i + 1][j].facility)->getDoor() % 2 == 1) ||
                    (static_cast<ConveyorBelt *>(myrect[i + 1][j].facility)->turn == "UpL" ||
                     static_cast<ConveyorBelt *>(myrect[i + 1][j].facility)->turn == "DownL"))
                {
                    pass(myrect, i + 1, j, 1, oi, oj, mineName, distance + 1);
                }
            }
        } else // 从右方向下传递
        {
            if (myrect[i][j + 1].isDelivery)
            {
                cout << "arrive! start form " << oi << ", " << oj << " to " << i << ", " << j + 1 << " mine: "
                     << mineName << " distance: " << distance + 1 << endl;
                center->arrival(mineName, distance + 1, i, j + 1);
            } else if (myrect[i][j + 1].isFacilityExist &&
                       myrect[i][j + 1].getFacility()->getName() == "conveyorbelt")
            {
                //下方可以接受的条件是，下方是垂直直立的 或是 上左 上右 弯
                if ((static_cast<ConveyorBelt *>(myrect[i][j + 1].facility)->turn == "null" &&
                     static_cast<ConveyorBelt *>(myrect[i][j + 1].facility)->getDoor() % 2 == 0) ||
                    (static_cast<ConveyorBelt *>(myrect[i][j + 1].facility)->turn == "UpL" ||
                     static_cast<ConveyorBelt *>(myrect[i][j + 1].facility)->turn == "UpR"))
                {
                    pass(myrect, i, j + 1, 2, oi, oj, mineName, distance + 1);
                }
            }
        }
    } else if (static_cast<ConveyorBelt *>(myrect[i][j].facility)->turn == "UpL") // 该传送带呈现上和左方向弯曲
    {
        if (sign % 2 == 0) // 从上方向左传递
        {
            if (myrect[i - 1][j].isDelivery)
            {
                cout << "arrive! start form " << oi << ", " << oj << " to " << i - 1 << ", " << j << " mine: "
                     << mineName << " distance: " << distance + 1 << endl;
                center->arrival(mineName, distance + 1, i - 1, j);
            } else if (myrect[i - 1][j].isFacilityExist &&
                       myrect[i - 1][j].getFacility()->getName() == "conveyorbelt")
            {
                //左方可以接受的条件是，左方是水平直立的 或是 上右 下右 弯
                if ((static_cast<ConveyorBelt *>(myrect[i - 1][j].facility)->turn == "null" &&
                     static_cast<ConveyorBelt *>(myrect[i - 1][j].facility)->getDoor() % 2 == 1) ||
                    (static_cast<ConveyorBelt *>(myrect[i - 1][j].facility)->turn == "UpR" ||
                     static_cast<ConveyorBelt *>(myrect[i - 1][j].facility)->turn == "DownR"))
                {
                    pass(myrect, i - 1, j, 3, oi, oj, mineName, distance + 1);
                }
            }
        } else // 从左向上传递
        {
            if (myrect[i][j - 1].isDelivery)
            {
                cout << "arrive! start form " << oi << ", " << oj << " to " << i << ", " << j - 1 << " mine: "
                     << mineName << " distance: " << distance + 1 << endl;
                center->arrival(mineName, distance + 1, i, j - 1);
            } else if (myrect[i][j - 1].isFacilityExist &&
                       myrect[i][j - 1].getFacility()->getName() == "conveyorbelt")
            {
                // 上方可以接受的条件是，上方是垂直直立的 或是 下右 下左 弯
                if ((static_cast<ConveyorBelt *>(myrect[i][j - 1].facility)->turn == "null" &&
                     static_cast<ConveyorBelt *>(myrect[i][j - 1].facility)->getDoor() % 2 == 0) ||
                    (static_cast<ConveyorBelt *>(myrect[i][j - 1].facility)->turn == "DownR" ||
                     static_cast<ConveyorBelt *>(myrect[i][j - 1].facility)->turn == "DownL"))
                {
                    pass(myrect, i, j - 1, 0, oi, oj, mineName, distance + 1);
                }
            }
        }
    } else if (static_cast<ConveyorBelt *>(myrect[i][j].facility)->turn == "UpR") // 该传送带呈现上和右方向弯曲
    {
        if (sign % 2 == 0) // 从上方向右传递
        {
            if (myrect[i + 1][j].isDelivery)
            {
                cout << "arrive! start form " << oi << ", " << oj << " to " << i + 1 << ", " << j << " mine: "
                     << mineName << " distance: " << distance + 1 << endl;
                center->arrival(mineName, distance + 1, i + 1, j);
            } else if (myrect[i + 1][j].isFacilityExist &&
                       myrect[i + 1][j].getFacility()->getName() == "conveyorbelt")
            {
                //右方可以接受的条件是，右方是水平直立的 或是 上左 下左 弯
                if ((static_cast<ConveyorBelt *>(myrect[i + 1][j].facility)->turn == "null" &&
                     static_cast<ConveyorBelt *>(myrect[i + 1][j].facility)->getDoor() % 2 == 1) ||
                    (static_cast<ConveyorBelt *>(myrect[i + 1][j].facility)->turn == "UpL" ||
                     static_cast<ConveyorBelt *>(myrect[i + 1][j].facility)->turn == "DownL"))
                {
                    pass(myrect, i + 1, j, 1, oi, oj, mineName, distance + 1);
                }
            }
        } else // 从右向上传递
        {
            if (myrect[i][j - 1].isDelivery)
            {
                cout << "arrive! start form " << oi << ", " << oj << " to " << i << ", " << j - 1 << " mine: "
                     << mineName << " distance: " << distance + 1 << endl;
                center->arrival(mineName, distance + 1, i, j - 1);
            } else if (myrect[i][j - 1].isFacilityExist &&
                       myrect[i][j - 1].getFacility()->getName() == "conveyorbelt")
            {
                // 上方可以接受的条件是，上方是垂直直立的 或是 下右 下左 弯
                if ((static_cast<ConveyorBelt *>(myrect[i][j - 1].facility)->turn == "null" &&
                     static_cast<ConveyorBelt *>(myrect[i][j - 1].facility)->getDoor() % 2 == 0) ||
                    (static_cast<ConveyorBelt *>(myrect[i][j - 1].facility)->turn == "DownR" ||
                     static_cast<ConveyorBelt *>(myrect[i][j - 1].facility)->turn == "DownL"))
                {
                    pass(myrect, i, j - 1, 0, oi, oj, mineName, distance + 1);
                }
            }
        }
    }
}