/*
 * @Author: Houhao
 * @Date: 2020-08-25 19:08:30
 * @LastEditors: Houhao
 * @LastEditTime: 2020-12-13 12:28:36
 * @FilePath: \cs225git\mp_mazes\dsets.cpp
 */
#include "dsets.h"
#include<vector>
#include <cmath>

using namespace std;


void DisjointSets::addelements(int num){
    // code here
    for (int i = 0; i < num; i++)
    {
        // a negative number in a root node is the negative of the set size.
        elems.push_back(-1);
    }
}

int DisjointSets::find(int elem){
    // code here
    if (elems[elem] < 0)
    {
        return elem;
    }
    else
    {
        int root = find(elems[elem]);
        elems[elem] = root;
        return root;
    }
}

void DisjointSets::setunion(int a, int b){
    // code here
    int rootFirst = find(a);
    int rootSecond = find(b);
    int newRootSize = elems[rootFirst] + elems[rootSecond];

    // smaller -> larget, note: negative num
    if (abs(elems[a]) < abs(elems[b]))
    {
        elems[rootFirst] = rootSecond;
        elems[rootSecond] = newRootSize;
    }
    else
    {
        elems[rootSecond] = rootFirst;
        elems[rootFirst] = newRootSize;
    }
}

int DisjointSets::size(int elem){
    // code here
    int size = find(elem);
    return -1*elems[size];
}
