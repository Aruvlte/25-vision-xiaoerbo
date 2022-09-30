/**
 * @file server.cpp
 * @author 赵曦 (535394140@qq.com)
 * @brief
 * @version 1.0
 * @date 2022-08-29
 *
 * @copyright Copyright SCUT RobotLab(c) 2022
 *
 */

#include <thread>

#include <opencv2/core/types.hpp>

#include "robotlab/module1.hpp"
#include "robotlab/rmath.h"
#include "robotlab/opcua_cs.hpp"

using namespace std;
using namespace cv;
using namespace ua;

#ifdef WITH_A
void print()
{
    module1a m;
    m.print1(), m.print2(), m.print3(), m.print4();
}
#endif // WITH_A

#ifdef WITH_B
void print()
{
    module1b m;
    m.print();
}
#endif // WITH_B

int main(int argc, char *argv[])
{
    print();
    this_thread::sleep_for(chrono::seconds(2));

    Server server;
    UA_Float dis = getDistances(Point(11, 22), Point(33, 44));

    server.addVariableNode("distance", dis);

    server.run();
    return 0;
}
