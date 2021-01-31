/*
 * @Author: Houhao
 * @Date: 2020-08-25 19:08:30
 * @LastEditors: Houhao
 * @LastEditTime: 2020-12-13 20:09:05
 * @FilePath: \cs225git\mp_mazes\main.cpp
 */
#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace std;

int main()
{
    // Write your own main here
    SquareMaze m;
    m.makeMaze(60, 65);

    cs225::PNG* solved = m.drawCreativeMaze();
    solved->writeToFile("creative.png");
    delete solved;
    std::cout << "drawCreative complete" << std::endl;
}
