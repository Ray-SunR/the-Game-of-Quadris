//
//  sblock.cpp
//  The Game of Quadris
//
//  Created by Sun Renchen& Chi Zhang on 2013-07-11.
//  Copyright (c) 2013 University of Waterloo. All rights reserved.
//

#include <iostream>

#include "sblock.h"
#include "grid.h"

using namespace std;
//constructor of the block
SBlock::SBlock(Grid* gd, int level): AbstractBlock(2, level)
{
    shape = 'S';
    refcoord.x = 3;
    refcoord.y = 0;
    currentType = 0;
    update(gd);
    draw(gd,level);
}
//based on the reference coordinate, calculate the coordinates and pointers of four pixels
void SBlock::update(Grid* g)
{
    std::vector<coordinate> vcoor;
    std::vector<Cell* > vcell;
    //first shape
    vcoor.push_back(coordinate(refcoord.x, refcoord.y));
    vcoor.push_back(coordinate(refcoord.x, refcoord.y + 1));
    vcoor.push_back(coordinate(refcoord.x - 1, refcoord.y + 1));
    vcoor.push_back(coordinate(refcoord.x - 1, refcoord.y + 2));
    maCoord[0] = vcoor;//first shape
    vcoor.clear();
    //second shape
    vcoor.push_back(coordinate(refcoord.x, refcoord.y + 1));
    vcoor.push_back(coordinate(refcoord.x - 1, refcoord.y));
    vcoor.push_back(coordinate(refcoord.x - 1, refcoord.y + 1));
    vcoor.push_back(coordinate(refcoord.x - 2, refcoord.y));
    maCoord[1] = vcoor;
    vcoor.clear();
    for (int i = 0; i < tolShapeType; i++)
    {
        for (int j = 0; j < 4; j++)
            vcell.push_back(g->getCell(maCoord[i][j]));
        maCell[i] = vcell;
        vcell.clear();
    }
}

void SBlock::clockwiseRotate(Grid* gd)
{
    if (!canBeRotate(gd, "clockwise"))//at extreme right-hand-side of the board, so that it can't be rotate
        return;
    undraw(gd);
    if (currentType == 0)
        currentType = 1;
    else
        currentType = 0;
    draw(gd, level);
}

void SBlock::counterClockwiseRotate(Grid* gd)
{
    clockwiseRotate(gd);
}
//put the coordinate of the block for every type in one vector
void SBlock::calculatePotentialPos(coordinate& fakeRef, vector<coordinate>& potentialVcoor)
{
	//there are two types for block s
    if (currentType == 0)
    {
		//first shape
        potentialVcoor.push_back(coordinate(fakeRef.x, fakeRef.y));
        potentialVcoor.push_back(coordinate(fakeRef.x, fakeRef.y + 1));
        potentialVcoor.push_back(coordinate(fakeRef.x - 1, fakeRef.y + 1));
        potentialVcoor.push_back(coordinate(fakeRef.x - 1, fakeRef.y + 2));
    }
    else
    {
		//second shape
        potentialVcoor.push_back(coordinate(fakeRef.x, fakeRef.y + 1));
        potentialVcoor.push_back(coordinate(fakeRef.x - 1, fakeRef.y));
        potentialVcoor.push_back(coordinate(fakeRef.x - 1, fakeRef.y + 1));
        potentialVcoor.push_back(coordinate(fakeRef.x - 2, fakeRef.y));
    }
}
//get the coordinate of the right corner.
coordinate SBlock::getRightCorner()
{
    coordinate temp;
    temp.x = refcoord.x;
    temp.y = refcoord.y;
    if (currentType == 0)
    {
        rightCorner.x = temp.x - 1;
        rightCorner.y = temp.y + 2;
    }
    else
    {
        rightCorner.x = temp.x - 2;
        rightCorner.y = temp.y + 1;
    }
    return rightCorner;
}
