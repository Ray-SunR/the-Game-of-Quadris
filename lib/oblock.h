//
//  oblock.h
//  The Game of Quadris
//
//  Created by Sun Renchen& Chi Zhang on 2013-07-11.
//  Copyright (c) 2013 University of Waterloo. All rights reserved.
//

#ifndef __Project__oblock__
#define __Project__oblock__

#include <iostream>

#include "abstractblock.h"

class OBlock: public AbstractBlock
{
    void update(Grid* gd);//based on the reference coordinate, calculate the coordinates and pointers of four pixels
public:
    OBlock(Grid* gd, int level);//constructor for the class
    void clockwiseRotate(Grid* gd);//do clockwise rotate
    void counterClockwiseRotate(Grid* gd);//do counter clockwise rotate
	//put the coordinate of the block for every type in one vector
    void calculatePotentialPos(coordinate& ref, std::vector<coordinate>& vcoor);
	//get the coordinate of the right corner
    coordinate getRightCorner();
};
#endif /* defined(__Project__oblock__) */
