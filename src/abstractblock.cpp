//
//  abstractblock.cpp
//  The Game of Quadris
//
//  Created by Sun Renchen& Chi Zhang on 2013-07-11.
//  Copyright (c) 2013 University of Waterloo. All rights reserved.
//

#include <iostream>

#include "abstractblock.h"
#include "grid.h"
#include "cell.h"

using namespace std;

//destructor
AbstractBlock::~AbstractBlock(){}

//shift the block to left by 1 position
void AbstractBlock::shiftLeft(Grid* gd)
{
    undraw(gd);
    if (canBeSLeft(refcoord.y, gd))//check if this block can be shifted left
    {
        refcoord.y--;//x decreases by 1
        update(gd);//update the new coordinate of this block
        draw(gd, level);//draw the block
    }
    else//otherwise it can't be shifted to right, retain the same.
        draw(gd, level);
}

//shift the block to right by 1 position
void AbstractBlock::shiftRight(Grid* gd)
{
    undraw(gd);
    if (canBeSRight(getRightCorner().y, gd))//check if this block can be shifted right
    {
        refcoord.y++;//y increases by 1  
        update(gd);//update the new coordinate of this block   
        draw(gd, level);//draw the block
    }
    else//otherwise it can't be shifted to right, retain the same.   
        draw(gd, level);
}

//shift the block down by 1 position
void AbstractBlock::shiftDown(Grid* gd)
{
    undraw(gd);
    if (canBeSDown(refcoord.x, gd))//check if this block can be shifted downward by 1 position
    {
        refcoord.x++;//x increases by 1
        update(gd);//updadate the coordinates of this block
        draw(gd, level);//draw the block to the new position
    }
    else   
        draw(gd, level);
}

bool AbstractBlock::Fall(Grid* gd)
{
    undraw(gd);
    int dest = gd->canBePlaced(this);//canBePlaced will call canBeDropped to determine whether the specified position can hold the blcok, dest will store the value of the destination of this block.
    if (dest != -1)//if dest's value is not equal to 1, which means the game was not over.
    {
        if (this->shape == 'I' && currentType == 1)//check special case for I, because 'I' block's reference coordinate is a little bit different from others.
            refcoord.x = dest - 1;
        else
            refcoord.x = dest;
        update(gd);//update the coordinates of this block
        draw(gd, level);//draw this block to the new position
        return true;
    }
    else
    {
        //here the game should be over.
        draw(gd, level);
        return false;
    }
}

//draw method will either draw the block in the graphic display, and text display
void AbstractBlock::draw(Grid* gd, int level)
{
    this->level = level;
    //traverse all the cell this block has, and set all the cells to live.
    for (int i = 0; i < 4; i++)
    {
        maCell[currentType][i]->setLiving(shape, level);
        maCell[currentType][i]->notifyDisplay(*gd->getTextDisplay());
    }
}

//erase method will either erase the block in the graphic display, and text display
void AbstractBlock::undraw(Grid* gd)
{
    for (int i = 0; i < 4; i++)
    {
        maCell[currentType][i]->setDead();
        maCell[currentType][i]->notifyDisplay(*gd->getTextDisplay());
    }
}

//check if the block can be dropped to the row r, true means can, false means can't
bool AbstractBlock::canBeDropped(int r, Grid *gd)
{
    coordinate fakeRef;//fake reference coordinate.
    if (this->shape == 'I' && this->currentType == 1)//check for special case where this block is 'I', because the coordinate system was different.
        fakeRef = coordinate(r - 1, getRefCoord().y);
    else
        fakeRef = coordinate(r, getRefCoord().y);//the new potential reference coordinate would be (r, y)
    vector<coordinate> potentialVcoor;//used to store the potential coordinates of this block in the position where the reference coordiante is (r, y).
    calculatePotentialPos(fakeRef, potentialVcoor);//polymorphism happens
    //traverse throught the cells this block has and check either they are out of boundary or is occupied by other blocks. If either case was true, then means it can't be dropped.
    for (int i = 0; i < 4; i++)
    {
        if (potentialVcoor[i].x > gd->getNumRow() - 1 || potentialVcoor[i].x < 0|| potentialVcoor[i].y > gd->getNumCol() - 1|| potentialVcoor[i].y < 0)//boundary checking
            return false;
        if (gd->getCell(potentialVcoor[i])->IsOccupied())
            return false;
    }
    //otherwise, it can be dropped.
    return true;
}

//Check if this block can be shifted to the left by 1 position
bool AbstractBlock::canBeSLeft(int c, Grid* gd)
{
    if (c == 0)//check for special case
        return false;
    //this is the fake reference coordinate.
    coordinate fakeRef = coordinate(getRefCoord().x, c - 1);
    //this is the potential reference coordinates.
    vector<coordinate> potentialVcoor;
    calculatePotentialPos(fakeRef, potentialVcoor);//polymorphism happens
    //Traverase through all the cells it has, if that was ocuppied, then return false
    for (int i = 0; i < 4; i++)
    {
        if (gd->getCell(potentialVcoor[i])->IsOccupied())
            return false;
    }
    //otherwise means this block can be shifted left.
    return true;
}

//check if this block can be shifted to the right by 1 position
bool AbstractBlock::canBeSRight(int c, Grid* gd)
{
    if (c == gd->getNumCol() - 1)//check for special case
        return false;
    //this is the fake reference coordinate.
    coordinate fakeRef = coordinate(getRefCoord().x, getRefCoord().y + 1);
    //this is the potential reference coordinates.
    vector<coordinate> potentialVcoor;
    calculatePotentialPos(fakeRef, potentialVcoor);//polymorphism happens
    //traverse through all the cells it has, if that was occuppied, then return false
    for (int i = 0; i < 4; i++)
    {
        if (gd->getCell(potentialVcoor[i])->IsOccupied())
            return false;
    }
    //otherwise, it is true.
    return true;
}

//check if this block can be shifted downward by 1 position
bool AbstractBlock::canBeSDown(int r, Grid* gd)
{
    if (r == gd->getNumRow() - 1)//check for special case;
        return false;
    //fake reference coordinate
    coordinate fakeRef = coordinate(r + 1, getRefCoord().y);
    vector<coordinate> potentialVcoor;//used to contain the potential coordinates based on the current positions.
    calculatePotentialPos(fakeRef, potentialVcoor);//polymorphism happens
    //traverse through all the cells it has, and check if those cells were occupied.
    for (int i = 0; i < 4; i++)
    {
        if (gd->getCell(potentialVcoor[i])->IsOccupied())
            return false;
    }
    return true;
}

//check if this block can be rotated
bool AbstractBlock::canBeRotate(Grid* gd, string type)
{
    undraw(gd);
    coordinate afterRotate;//used to store the coordinates after rotation
    afterRotate.x = refcoord.x;
    afterRotate.y = refcoord.y;
    vector<coordinate> potentialVcoor;//used to store the potential coordinate 
    int originalType = currentType;//use a vairable to containthe original type of block
    if (tolShapeType == 2)//if the block has only two types of shape
    {
        if (originalType == 0)//if the current type was first type
            currentType = 1;//the next would be 1
        else
            currentType = 0;//otherwise it would be 0
    }
    else//if the block has four types of shape
    {
        //if the rotation was 'clockwise', and current type was the last type of the shape, then the next type would be 0
        if (type == "clockwise" && originalType == 3)
            currentType = 0;
        //otherwise if this rotation was a clockwise rotation
        else if (type == "clockwise")
            //the next type would be just add 1
            currentType++;
        //if the rotation was 'counterclockwise', and current type was the first type of the shape, then the next type would be the last type of shape.
        else if (type == "counterclockwise" && originalType == 0)
            currentType = 3;
        //otherwise, this rotation must be counterclockwise, then the next type would be just decreasing 1.
        else
            currentType--;
    }
    //calculation the potential coordinates of the current type of this block
    calculatePotentialPos(afterRotate, potentialVcoor);//this function will use the currentType to calculate the potential coordinate of this currentType
    //traverse all through the block and check if calculated potential coordinated were occupied.
    for (int i = 0; i < 4; i++)
    {
        //boundary checking.
        if (potentialVcoor[i].x < 0 || potentialVcoor[i].y > gd->getNumCol() - 1 || potentialVcoor[i].y < 0 || potentialVcoor[i].x > gd->getNumRow() - 1)
        {
            //if this rotation is not valid, then restore all the settings to before.
            currentType = originalType;
            draw(gd, level);
            return false;//rotation failed
        }
        //check if this cell is occupied.
        if (gd->getCell(potentialVcoor[i])->IsOccupied())
        {
            currentType = originalType;
            draw(gd, level);
            return false;
        }
    }
    //restore all the settings to the original.
    currentType = originalType;
    draw(gd, level);
    return true;
}

//check whether this block can be drawn on the board.
bool AbstractBlock::canBeDraw(Grid* gd)
{
    for (int i = 0; i < 4; i++)
    {
        if (maCell[currentType][i]->IsOccupied())
            return false;
    }
    return true;
}

//set the reference coordinate and update the other coordinates.
void AbstractBlock::setRefCoord(coordinate& c, Grid* gd)
{
    refcoord.x = c.x;
    refcoord.y = c.y;
    update(gd);
}
