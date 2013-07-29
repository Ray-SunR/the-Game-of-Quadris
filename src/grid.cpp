//
//  grid.cpp
//  The Game of Quadris
//
//  Created by Sun Renchen& Chi Zhang on 2013-07-11.
//  Copyright (c) 2013 University of Waterloo. All rights reserved.
//

#include <iostream>

#include "textdisplay.h"
#include "abstractblock.h"
#include "score.h"
#include "window.h"
#include "grapicdisplay.h"
#include "grid.h"

using namespace std;

//constructor
Grid::Grid(GraphicDisplay* gdisplay, int rownum, int colnum)
{
    initialize(gdisplay, rownum, colnum);
}

//destructor
Grid::~Grid()
{
    delete td;
    td= NULL;
    for (int i = 0; i < numRow; i++)
        delete cell[i];
    delete [] cell;
}

//initialize fields and create a two-dimentional array
void Grid::initialize(GraphicDisplay* gd, int rownum, int colnum)
{
    if (gd)
        gd->Initialize();//initialize a window
    cellSize_Width = 30;
    cellSize_Height = 30;
    numRow = rownum;
    numCol = colnum;
    numDelete = 0;
    cell = new Cell* [numRow];
    for (int i = 0; i < numRow; i++)
        cell[i] = new Cell [numCol];
    //initialize those cells
    for (int i = 0; i < numRow; i++)
        for (int j = 0; j < numCol; j++)
        {
            //if it is in graphic mode
            if (!gd)
               cell[i][j].Initialize(coordinate(i , j), coordinate(i * cellSize_Width, j * cellSize_Height), i, j, cellSize_Width, cellSize_Height, NULL);
            else
               cell[i][j].Initialize(coordinate(i , j), coordinate(i * cellSize_Width, j * cellSize_Height), i, j, cellSize_Width, cellSize_Height, gd->getWindowPtr());
        }
    td = new TextDisplay(numRow, numCol);
}

//check if row 'r' is full
bool Grid::isRowFull(int r)
{
    for (int j = 0; j < numCol; j++)
        if (!cell[r][j].IsOccupied())
            return false;
    return true;
}

//delete row 'r'
void Grid::deleteRow(int r)
{
    int dest = r;
    for (int src = dest - 1; src > 0; src--)//shift all the blocks above to the destination, also should have check the condition where the shifted blocks float in the air. 
    {
        for (int j = 0; j < numCol; j++)
        {
            //onced assigned, then draw the specific cell.
            cell[dest][j] = cell[src][j];
            cell[dest][j].notifyDisplay(*td);
            cell[dest][j].draw();
        }
        dest--;
    }
    numDelete++;
}

//restart the game
void Grid::restart()
{
    delete td;
    td= NULL;
    for (int i = 0; i < numRow; i++)
        delete cell[i];
    delete [] cell;
    initialize();
}

//check if a specific block can be placed, if so, then return the destination, otherwise return -1.
int Grid::canBePlaced(AbstractBlock* ab)
{
    vector<coordinate> vcoor = ab->getMapCoordinate(ab->getCurrentType());//get the coordinates of this block
    vector<Cell*> vcell = ab->getMapCell(ab->getCurrentType());//get the cell pointers of this block
    int r;
    bool flag = false;//used to check if this block can be placed at r.
    for (r = ab->getRefCoord().x; r < numRow + 1;r++)
    {
        if (!ab->canBeDropped(r, this))
        {
            flag = true;
            break;
        }
    }
    //if it can, then return the destination which is r - 1
    if (flag)
        return r - 1;
    //check if the block can be placed at the top of the grid, if so, then check if the top row is full. 
    else
    {
        ab->draw(this, ab->getLevel());
        if (!isRowFull(ab->getRefCoord().x))//if previously determined that the game was over, then we have to determine wehther after placing this block will result in the full row
        {
            ab->undraw(this);//if not full, then absolutely game over
            return -1;//if it is -1, means the game is over
        }
        else
        {
            ab->undraw(this);//otherwise, this block still can be placed, for it will cause some rows to be deleted
            return ab->getRefCoord().x;
        }
    }
}

//check method is responsible for checking if some rows are meant to be deleted.
int Grid::check()
{
    numDelete = 0;
    for (int i = numRow - 1; i >= 0; i--)
    {
        while(isRowFull(i))
        {
            deleteRow(i);
        }
    }
    return numDelete;
}

//output operator
std::ostream& operator<< (std::ostream& out, Grid& g)
{
    if (g.td)
        return out << *g.td << endl;
    else
        return out;
}
