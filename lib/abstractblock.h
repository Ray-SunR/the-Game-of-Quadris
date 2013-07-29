//
//  abstractblock.h
//  The Game of Quadris
//
//  Created by Sun Renchen& Chi Zhang on 2013-07-11.
//  Copyright (c) 2013 University of Waterloo. All rights reserved.
//

#ifndef __Project__abstractblock__
#define __Project__abstractblock__

#include <iostream>
#include <vector>
#include <map>

#include "coordinate.h"

class Grid;
class Cell;

class AbstractBlock
{
protected:
    int level;
    char shape;
    coordinate refcoord;//used as a reference coordinate in the left corner as x& y.
    coordinate rightCorner;//Used to contain the right corner of the block
    const int tolShapeType;//how many shapes it has
    std::map < int, std::vector<coordinate> > maCoord;//map int to coordinate, 'int' means which status the block is, originally it is 0, max is tolShapeType; e.g:
    std::map < int, std::vector<Cell*> > maCell;//map int to array of cell pointers. Used to store each kind of shape's pointer condition
    int currentType;//current type of shape
    virtual void update(Grid* gd) = 0;
    
    bool canBeSLeft(int c, Grid* gd);//This function is used to determine whether column c can contain the current type of this block, true can, false not
    bool canBeSRight(int c, Grid* gd);//check if this block can be shifted to right by 1 position
    bool canBeSDown(int r, Grid* gd);//check if this block can be shifted down by 1 position
    bool canBeRotate(Grid* gd, std::string c);//check whether the block can be rotate, string is used to indicate what kind of rotate it is
    virtual void calculatePotentialPos(coordinate& ref, std::vector<coordinate>& vcoor) = 0;//by given a reference coordinate, calculate the potential position of a specific block
    
public:
    AbstractBlock(int num, int level):tolShapeType(num), level(level){};//base class's constructor. 
    virtual ~AbstractBlock();//destructor
    virtual void draw(Grid* gd, int level);//Once call draw block, then it will use gd to call the specific cell to be alive
    virtual void undraw(Grid* gd);//Once call undraw blcok, then it will use gd to call the specific cell to be dead.
    virtual void clockwiseRotate(Grid* gd) = 0;//clockwise rotate
    virtual void counterClockwiseRotate(Grid* gd) = 0;//counter clockwise rotate
    bool canBeDropped(int r, Grid* gd); //This function is used to determine whether row r can contain the current type of this block, true can, false not.
    virtual coordinate getRefCoord() const {return refcoord;}//get the reference coordinate
    int getCurrentType() const {return currentType;}//return the current type of this block
    std::vector<coordinate> getMapCoordinate(int Type) {return maCoord[Type];}//return the coordinate of this block based on the current type of it.
    std::vector<Cell*> getMapCell(int Type) {return maCell[Type];}//return the pointers to the cells based on the current type of it.
    virtual coordinate getRightCorner() = 0;//will return the right corner of this block
    int getLevel() const {return level;}//used to store which level is this block in.
    void setRefCoord(coordinate& c, Grid* gd);//set the reference coordinate to c
    void shiftLeft(Grid* gd);//shift left
    void shiftRight(Grid* gd);//shift right
    void shiftDown(Grid* gd);//shift down
    bool Fall(Grid* gd);//drop a block
    bool canBeDraw(Grid* gd);//check whether the this block can be drawn on the grid.
    char getShape() const {return shape;}//answer which type of block it is.
};
#endif /* defined(__Project__abstractblock__) */
