//
//  grid.h
//  The Game of Quadris
//
//  Created by Sun Renchen& Chi Zhang on 2013-07-11.
//  Copyright (c) 2013 University of Waterloo. All rights reserved.
//

#ifndef __Project__Grid__
#define __Project__Grid__

#include <iostream>

#include "cell.h"
#include "coordinate.h"

class AbstractBlock;
class score;
class Xwindow;
class GraphicDisplay;

class Grid
{
    Cell** cell;//Two-dimentional array
    TextDisplay* td;//Pointer to text-display
    int cellSize_Width, cellSize_Height, numRow, numCol;//cell width, cell height, number of rows, number of columns
    int numDelete;//determine how many rows have been deleted.
    bool isRowFull(int r);//return whether row r is full
public:
    Grid(GraphicDisplay* gd = NULL, int rownum = 15, int colnum = 10);//Constructor, the defualt size of the game is 15 x 10.
    ~Grid();//destructor
    Cell* getCell(coordinate& c){return &cell[c.x][c.y];}//get a cell according to a given coordinate.
    int check();//check whether we should delete a row, called by block when a block is dropped down.
    void deleteRow(int r);//shift all alive cells down 1
    void initialize(GraphicDisplay* gd = NULL, int rownum = 15, int colnum = 10);//initialize the grid
    int canBePlaced(AbstractBlock* ab);//when a fall operation of a block is called, this function will determine which row should this block placed
    TextDisplay* getTextDisplay() const {return td;}
    void restart();//used for restart the game
    friend std::ostream& operator<< (std::ostream& out, Grid& g);//outstream
    int getNumRow() const {return numRow;}//return row number
    int getNumCol() const {return numCol;}//return column number
};
#endif /* defined(__Project__Grid__) */
