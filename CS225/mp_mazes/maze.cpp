/*
 * @Author: Houhao
 * @Date: 2020-08-25 19:08:30
 * @LastEditors: Houhao
 * @LastEditTime: 2020-12-13 20:18:35
 * @FilePath: \cs225git\mp_mazes\maze.cpp
 */
#include "maze.h"
#include "dsets.h"
#include<vector>
#include <cmath>
#include <math.h>
#include <queue>
#include <map>

using namespace::std;
using namespace::cs225;

SquareMaze::SquareMaze(){
    //code here
    // nothing here neeeed
}

void SquareMaze::makeMaze(int width, int height){
    //code here
    mazeHeight = height;
    mazeWidth = width;
    DisjointSets dsets;
    dsets.addelements(mazeHeight*mazeWidth);

    for (int i = 0; i < mazeHeight*mazeWidth; i++)
    {
        rightWall.push_back(true);
        downWall.push_back(true);
    }
    
    while (dsets.size(0) != mazeHeight*mazeWidth)
    {
        int randX = rand()%mazeWidth;
        int randY = rand()%mazeHeight;

        int pos = randX + randY*mazeWidth;
        int posRight = pos + 1;
        int posDown = randX + (randY+1)* mazeWidth;
        if (rand() % 2)
        {
            if (randX < mazeWidth-1 && rightWall[pos] && dsets.find(pos) != dsets.find(posRight))
            {
                // merge right wall
                dsets.setunion(pos, posRight);
                rightWall[pos] = false;
            }
            else if (randY < mazeHeight-1 && downWall[pos] && dsets.find(pos)!= dsets.find(posDown))
            {
                // merge down wall
                dsets.setunion(pos, posDown);
                downWall[pos] = false;
            }
        }
    }
}

bool SquareMaze::canTravel(int x, int y, int dir) const {
    //code here
    
    if (dir == 0)
    {
        bool wall = rightWall[x + y*mazeWidth];
        return !wall;
    }
    if (dir == 1)
    {
        bool wall = downWall[x + y*mazeWidth];
        return !wall;
    }
    if (dir == 2) // leftward
    {
        if (x == 0)
        {
            return false;
        }else
        {
            bool wall = rightWall[x + y*mazeWidth - 1];
            return !wall;
        }
    }
    if (dir == 3) // upward
    {
        if (y==0)
        {
            return false;
        }else
        {
            bool wall = downWall[x + (y-1)*mazeWidth];
            return !wall;
        }
    }
    return false;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists){
    //code here
    int pos = x+y*mazeWidth;
    if (dir ==0)
    {
        rightWall[pos] = exists;
    }
    if (dir == 1)
    {
        downWall[pos] = exists;
    }
}

vector<int> SquareMaze::solveMaze(){
    //code here
    vector<bool> visited;
    map<int, int> dirRecord;
    queue<int> search;
    vector<int> bottomRows;

    // BFS search, use queue
    search.push(0);
    for (int i = 0; i < mazeHeight*mazeWidth; i++)
    {
        visited.push_back(false);
    }
    visited[0] = true;

    while (!search.empty())
    {
        int pos = search.front();
        int x = pos % mazeWidth;
        int y = pos / mazeWidth;
        search.pop();

        int rightPos = pos+1;
        int downPos = pos + mazeWidth;
        int leftPos = pos - 1;
        int upPos = pos - mazeWidth;

        // dierections to go
        if (canTravel(x, y, 0) && !visited[rightPos])
        {
            visited[rightPos] = true;
            search.push(rightPos);
            dirRecord[rightPos] = pos;
        }
        if (canTravel(x, y, 1) && !visited[downPos])
        {
            visited[downPos] = true;
            search.push(downPos);
            dirRecord[downPos] = pos;
        }
        if (canTravel(x, y, 2) && !visited[leftPos])
        {
            visited[leftPos] = true;
            search.push(leftPos);
            dirRecord[leftPos] = pos;
        }
        if (canTravel(x, y, 3) && !visited[upPos])
        {
            visited[upPos] = true;
            search.push(upPos);
            dirRecord[upPos] = pos;
        }
        
        // reach bottom row
        if (y == mazeHeight - 1)
        {
            bottomRows.push_back(pos);
        }
    }

    // select square with largest distance
    int bottomIdx = mazeWidth - 1;
    while (bottomRows[bottomIdx] <= bottomRows[bottomIdx-1])
    {
        bottomIdx --;
    }
    // trace back to find path
    vector<int> path;
    int init = bottomRows[bottomIdx];
    while (init != 0)
    {
        int pre = dirRecord[init];
        if (init == pre+1)
        {
            path.push_back(0);
        }
        if (init == pre + mazeWidth)
        {
            path.push_back(1);
        }
        if (init == pre - 1)
        {
            path.push_back(2);
        }
        if (init == pre - mazeWidth)
        {
            path.push_back(3);
        }
        init = pre;
    }
    std::reverse(path.begin(), path.end());
    return path;
      
}

PNG* SquareMaze::drawMaze() const {
    //code here
    int dimW = mazeWidth*10 + 1;
    int dimH = mazeHeight*10 + 1;
    PNG* maze = new PNG(dimW, dimH);

    // blacken topmost row
    for (int i = 0; i < dimH; i++)
    {
        HSLAPixel & pixel = maze->getPixel(0, i);
        pixel.l = 0;
    }
    // blacken leftmost column
    for (int i = 10; i < dimW; i++)
    {
        HSLAPixel & pixel = maze->getPixel(i, 0);
        pixel.l = 0;
    }
    
    for (int x = 0; x < mazeWidth; x++)
    {
        for (int y = 0; y < mazeHeight; y++)
        {
            if (rightWall[x + y*mazeWidth])
            {
                for (int k = 0; k < 11; k++)
                {
                    HSLAPixel & pixel = maze->getPixel((x+1)*10,y*10+k);
                    pixel.l = 0;
                }
            }
            if (downWall[x + y*mazeWidth])
            {
                for (int k = 0; k < 11; k++)
                {
                    HSLAPixel & pixel = maze->getPixel(x*10+k, (y+1)*10);
                    pixel.l = 0;
                }
            }
        }
    }
    return maze;
}

PNG* SquareMaze::drawMazeWithSolution(){
    //code here
    PNG* outMaze = drawMaze();
    vector<int> outPath = solveMaze();
    int x = 5;
    int y = 5;
    for (auto i: outPath)
    {
        if (i == 0)
        {
            for (int k = 0; k < 10; k++)
            {
                HSLAPixel & pixel = outMaze->getPixel(x, y);
                pixel.h = 0;
                pixel.s = 1;
                pixel.l = 0.5;
                pixel.a = 1;
                x++;
            }
        }
        if (i == 1)
        {
            for (int k = 0; k < 10; k++)
            {
                HSLAPixel & pixel = outMaze->getPixel(x, y);
                pixel.h = 0;
                pixel.s = 1;
                pixel.l = 0.5;
                pixel.a = 1;
                y++;
            }
        }
        if (i == 2)
        {
            for (int k = 0; k < 10; k++)
            {
                HSLAPixel & pixel = outMaze->getPixel(x, y);
                pixel.h = 0;
                pixel.s = 1;
                pixel.l = 0.5;
                pixel.a = 1;
                x--;
            }
        }
        if (i == 3)
        {
            for (int k = 0; k < 10; k++)
            {
                HSLAPixel & pixel = outMaze->getPixel(x, y);
                pixel.h = 0;
                pixel.s = 1;
                pixel.l = 0.5;
                pixel.a = 1;
                y--;
            }
        }
    }
    
    // make exit, whiten the space
    x -= 4;
    y += 5;
    for (int k = 0; k < 9; k++)
    {
        HSLAPixel & pixel = outMaze->getPixel(x,y);
        pixel.l = 1;
        x ++;
    }
    
    return outMaze;
}

PNG * SquareMaze::drawCreativeMaze(){
    //code here
    int dimW = mazeWidth*10 + 1;
    int dimH = mazeHeight*10 + 1;
    PNG* maze = new PNG(dimW, dimH);

    // blacken topmost row
    for (int i = 0; i < dimH; i++)
    {
        HSLAPixel & pixel = maze->getPixel(0, i);
        pixel.l = 0;
    }
    // blacken leftmost column
    for (int i = 10; i < dimW; i++)
    {
        HSLAPixel & pixel = maze->getPixel(i, 0);
        pixel.l = 0;
    }
    
    for (int x = 0; x < mazeWidth; x++)
    {
        for (int y = 0; y < mazeHeight; y++)
        {
            if (rightWall[x + y*mazeWidth])
            {
                for (int k = 0; k < 11; k++)
                {
                    HSLAPixel & pixel = maze->getPixel((x+1)*10,y*10+k);
                    pixel.l = 0;
                }
            }
            if (downWall[x + y*mazeWidth])
            {
                for (int k = 0; k < 11; k++)
                {
                    HSLAPixel & pixel = maze->getPixel(x*10+k, (y+1)*10);
                    pixel.l = 0;
                }
            }
        }
    }

    vector<int> outPath = solveMaze();
    int px = 5;
    int py = 5;
    for (auto i: outPath)
    {
        if (i == 0)
        {
            for (int k = 0; k < 10; k++)
            {
                HSLAPixel & pixel = maze->getPixel(px, py);
                pixel.h = 10;
                pixel.s = 20;
                pixel.l = 30;
                pixel.a = 2;
                px++;
            }
        }
        if (i == 1)
        {
            for (int k = 0; k < 10; k++)
            {
                HSLAPixel & pixel = maze->getPixel(px, py);
                pixel.h = 10;
                pixel.s = 20;
                pixel.l = 30;
                pixel.a = 2;
                py++;
            }
        }
        if (i == 2)
        {
            for (int k = 0; k < 10; k++)
            {
                HSLAPixel & pixel = maze->getPixel(px, py);
                pixel.h = 10;
                pixel.s = 20;
                pixel.l = 30;
                pixel.a = 2;
                px--;
            }
        }
        if (i == 3)
        {
            for (int k = 0; k < 10; k++)
            {
                HSLAPixel & pixel = maze->getPixel(px, py);
                pixel.h = 10;
                pixel.s = 20;
                pixel.l = 30;
                pixel.a = 2;
                py--;
            }
        }
    }
    
    // make exit, whiten the space
    px -= 4;
    py += 5;
    for (int k = 0; k < 9; k++)
    {
        HSLAPixel & pixel = maze->getPixel(px,py);
        pixel.l = 4;
        pixel.h = 5;
        px ++;
    }
    return maze;
}
