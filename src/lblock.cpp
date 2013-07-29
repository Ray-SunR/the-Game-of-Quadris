//
//  lblock.cpp
//  The Game of Quadris
//
//  Created by Sun Renchen& Chi Zhang on 2013-07-11.
//  Copyright (c) 2013 University of Waterloo. All rights reserved.
//

#include <iostream>

#include "lblock.h"
#include "grid.h"

using namespace std;
//constructor of the block
LBlock::LBlock(Grid* gd, int level):AbstractBlock(4, level)
{
    shape = 'L';
    refcoord.x = 3;
    refcoord.y = 0;
    currentType = 0;
    update(gd);
    draw(gd, level);
}
//based on the reference coordinate, calculate the coordinates and pointers of four pixels
void LBlock::update(Grid* gd)
{
    std::vector<coordinate> vcoor;
    std::vector<Cell*> vcell;
    vcoor.push_back(coordinate(refcoord.x, refcoord.y));
    vcoor.push_back(coordinate(refcoord.x, refcoord.y + 1));
    vcoor.push_back(coordinate(refcoord.x, refcoord.y + 2));
    vcoor.push_back(coordinate(refcoord.x - 1, refcoord.y + 2));
    maCoord[0] = vcoor;//first shape
    vcoor.clear();
    //second shape
    vcoor.push_back(coordinate(refcoord.x, refcoord.y));
    vcoor.push_back(coordinate(refcoord.x, refcoord.y + 1));
    vcoor.push_back(coordinate(refcoord.x - 1, refcoord.y));
    vcoor.push_back(coordinate(refcoord.x - 2, refcoord.y));
    maCoord[1] = vcoor;//second shape
    vcoor.clear();
    //third shape
    vcoor.push_back(coordinate(refcoord.x, refcoord.y));
    vcoor.push_back(coordinate(refcoord.x - 1, refcoord.y));
    vcoor.push_back(coordinate(refcoord.x - 1, refcoord.y + 1));
    vcoor.push_back(coordinate(refcoord.x - 1, refcoord.y + 2));
    maCoord[2] = vcoor;//third shape
    vcoor.clear();
    //fourth shape
    vcoor.push_back(coordinate(refcoord.x - 2, refcoord.y));
    vcoor.push_back(coordinate(refcoord.x - 2, refcoord.y + 1));
    vcoor.push_back(coordinate(refcoord.x - 1, refcoord.y + 1));
    vcoor.push_back(coordinate(refcoord.x, refcoord.y + 1));
    maCoord[3] = vcoor;//fourth shape
    
    vcoor.clear();
    for (int i = 0; i < tolShapeType; i++)
    {
        for (int j = 0; j < 4; j++)
            vcell.push_back(gd->getCell(maCoord[i][j]));
        maCell[i] = vcell;
        vcell.clear();
    }
}


void LBlock::clockwiseRotate(Grid* gd)
{
    if (!canBeRotate(gd, "clockwise"))
        return;
    undraw(gd);
    if (currentType == 3)
        currentType = 0;
    else
        currentType++;
    draw(gd, level);
}

void LBlock::counterClockwiseRotate(Grid* gd)
{
    if (!canBeRotate(gd, "counterclockwise"))
        return;
    undraw(gd);
    if (currentType == 0)
        currentType = 3;
    else
        currentType--;
    draw(gd, level);
}
//put the coordinate of the block for every type in one vector
void LBlock::calculatePotentialPos(coordinate& fakeRef, vector<coordinate>& potentialVcoor)
{
	//there are four types for block l
    if (currentType == 0)
    {
        //first shape
        potentialVcoor.push_back(coordinate(fakeRef.x, fakeRef.y));
        potentialVcoor.push_back(coordinate(fakeRef.x, fakeRef.y + 1));
        potentialVcoor.push_back(coordinate(fakeRef.x, fakeRef.y + 2));
        potentialVcoor.push_back(coordinate(fakeRef.x - 1, fakeRef.y + 2));
    }
    else if(currentType == 1)
    {
        //second shape
        potentialVcoor.push_back(coordinate(fakeRef.x, fakeRef.y));
        potentialVcoor.push_back(coordinate(fakeRef.x, fakeRef.y + 1));
        potentialVcoor.push_back(coordinate(fakeRef.x - 1, fakeRef.y));
        potentialVcoor.push_back(coordinate(fakeRef.x - 2, fakeRef.y));
    }
    else if(currentType == 2)
    {
        //third shape
        potentialVcoor.push_back(coordinate(fakeRef.x, fakeRef.y));
        potentialVcoor.push_back(coordinate(fakeRef.x - 1, fakeRef.y ));
        potentialVcoor.push_back(coordinate(fakeRef.x - 1, fakeRef.y + 1));
        potentialVcoor.push_back(coordinate(fakeRef.x - 1, fakeRef.y + 2));
    }
    else
    {
        //fourth shape
        potentialVcoor.push_back(coordinate(fakeRef.x - 2, fakeRef.y));
        potentialVcoor.push_back(coordinate(fakeRef.x - 2, fakeRef.y + 1));
        potentialVcoor.push_back(coordinate(fakeRef.x - 1, fakeRef.y + 1));
        potentialVcoor.push_back(coordinate(fakeRef.x, fakeRef.y + 1));
    }
}
//get the coordinate of the right corner.
coordinate LBlock::getRightCorner()
{
    if (currentType == 0)
    {
        rightCorner.x = refcoord.x - 1;
        rightCorner.y = refcoord.y + 2;
    }
    else if (currentType == 1)
    {
        rightCorner.x = refcoord.x - 2;
        rightCorner.y = refcoord.y + 1;
    }
    else if (currentType == 2)
    {
        rightCorner.x = refcoord.x - 1;
        rightCorner.y = refcoord.y + 2;
    }
    else
    {
        rightCorner.x = refcoord.x - 2;
        rightCorner.y = refcoord.y + 1;
    }
    return rightCorner;
}
