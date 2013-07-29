//
//  iblock.cpp
//  The Game of Quadris
//
//  Created by Sun Renchen& Chi Zhang on 2013-07-11.
//  Copyright (c) 2013 University of Waterloo. All rights reserved.
//

#include <iostream>

#include "iblock.h"

using namespace std;
//constructor of the block
IBlock::IBlock(Grid* gd, int level):AbstractBlock(2, level)
{
    shape = 'I';
    refcoord.x = 3;
    refcoord.y = 0;
    currentType = 0;
    update(gd);
    draw(gd, level);
}

void IBlock::clockwiseRotate(Grid* gd)
{
    if (!canBeRotate(gd, "clockwise"))//at extreme right-hand-side of the board, so that it can't be rotate
        return;
    undraw(gd);
    currentType == 0? currentType = 1: currentType = 0;
    draw(gd, level);
}

void IBlock::counterClockwiseRotate(Grid* gd)
{
    clockwiseRotate(gd);
}
//based on the reference coordinate, calculate the coordinates and pointers of four pixels
void IBlock::update(Grid* gd)
{
    vector<coordinate> vcoor;
    vector<Cell*> vcell;
	//put these four coordinates in one vector
    vcoor.push_back(coordinate(refcoord.x, refcoord.y));
    vcoor.push_back(coordinate(refcoord.x, refcoord.y + 1));
    vcoor.push_back(coordinate(refcoord.x, refcoord.y + 2));
    vcoor.push_back(coordinate(refcoord.x, refcoord.y + 3));
    for (int j = 0; j < 4; j++)
        vcell.push_back(gd->getCell(vcoor[j]));
    maCoord[0] = vcoor;
    maCell[0] = vcell;
    vcoor.clear();
    vcell.clear();
    vcoor.push_back(coordinate(refcoord.x + 1, refcoord.y));
    vcoor.push_back(coordinate(refcoord.x, refcoord.y));
    vcoor.push_back(coordinate(refcoord.x - 1, refcoord.y));
    vcoor.push_back(coordinate(refcoord.x - 2, refcoord.y));
    for (int i = 0; i < 4; i++)
        vcell.push_back(gd->getCell(vcoor[i]));
    maCoord[1] = vcoor;
    maCell[1] = vcell;
}

//put the coordinate of the block for every type in one vector
void IBlock::calculatePotentialPos(coordinate& fakeRef, vector<coordinate>& potentialVcoor)
{
	//there are two types for block I
    if (currentType == 0)
    {
        potentialVcoor.push_back(coordinate(fakeRef.x, fakeRef.y));
        potentialVcoor.push_back(coordinate(fakeRef.x, fakeRef.y + 1));
        potentialVcoor.push_back(coordinate(fakeRef.x, fakeRef.y + 2));
        potentialVcoor.push_back(coordinate(fakeRef.x, fakeRef.y + 3));
    }
    else
    {
        potentialVcoor.push_back(coordinate(fakeRef.x, fakeRef.y));
        potentialVcoor.push_back(coordinate(fakeRef.x + 1, fakeRef.y ));
        potentialVcoor.push_back(coordinate(fakeRef.x - 1, fakeRef.y));
        potentialVcoor.push_back(coordinate(fakeRef.x - 2, fakeRef.y));
    }

}

//get the coordinate of the right corner.
coordinate IBlock::getRightCorner()
{
    coordinate temp;
    temp.x = refcoord.x;
    temp.y = refcoord.y;
    if (currentType == 0)
    {
        rightCorner.x = temp.x;
        rightCorner.y = temp.y + 3;
    }
    else
    {
        rightCorner.x = temp.x - 3;
        rightCorner.y = temp.y;
    }
    return rightCorner;
}
