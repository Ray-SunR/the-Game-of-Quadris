//
//  oblock.cpp
//  The Game of Quadris
//
//  Created by Sun Renchen& Chi Zhang on 2013-07-11.
//  Copyright (c) 2013 University of Waterloo. All rights reserved.
//

#include <iostream>

#include "oblock.h"
#include "grid.h"

using namespace std;
//constructor of the block
OBlock::OBlock(Grid* gd, int level): AbstractBlock(1, level)
{
    shape = 'O';
    refcoord.x = 3;
    refcoord.y = 0;
    currentType = 0;
    update(gd);
    draw(gd, level);
}
//based on the reference coordinate, calculate the coordinates and pointers of four pixels
void OBlock::update(Grid* g)
{
    std::vector<coordinate> vcoor;
    std::vector<Cell*> vcell;
    //first shape
    vcoor.push_back(coordinate(refcoord.x, refcoord.y));
    vcoor.push_back(coordinate(refcoord.x, refcoord.y + 1));
    vcoor.push_back(coordinate(refcoord.x - 1, refcoord.y));
    vcoor.push_back(coordinate(refcoord.x - 1, refcoord.y + 1));
    maCoord[0] = vcoor;//first shape
    vcoor.clear();
    for (int i = 0; i < tolShapeType; i++)
    {
        for (int j = 0; j < 4; j++)
            vcell.push_back(g->getCell(maCoord[i][j]));
        maCell[i] = vcell;
    }
}
//there is no retation for block O
void OBlock::clockwiseRotate(Grid* gd)
{
}

void OBlock::counterClockwiseRotate(Grid* gd)
{
}
//put the coordinate of the block for every type in one vector
void OBlock::calculatePotentialPos(coordinate &fakeRef, vector<coordinate>& potentialVcoor)
{
	//there is one shape for block O
    potentialVcoor.push_back(coordinate(fakeRef.x, fakeRef.y));
    potentialVcoor.push_back(coordinate(fakeRef.x, fakeRef.y + 1));
    potentialVcoor.push_back(coordinate(fakeRef.x - 1, fakeRef.y));
    potentialVcoor.push_back(coordinate(fakeRef.x - 1, fakeRef.y + 1));
}

//get the coordinate of the right corner.
coordinate OBlock::getRightCorner()
{
    rightCorner.x = refcoord.x + 1;
    rightCorner.y = refcoord.y + 1;
    return rightCorner;
}

