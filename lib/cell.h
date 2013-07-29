//
//  cell.h
//  The Game of Quadris
//
//  Created by Sun Renchen& Chi Zhang on 2013-07-11.
//  Copyright (c) 2013 University of Waterloo. All rights reserved.
//

#ifndef __Project__Cell__
#define __Project__Cell__

#include <iostream>

#include "coordinate.h"

class Xwindow;
class TextDisplay;

class Cell
{
    coordinate xy;//coordinate in the two-dimentional array
    coordinate graxy;//graphical coordinate
    int r,c,width, height;//row, column, cell width, cell height
    char symbol;//used to indicate which kind of block it is
    bool isOccupied;//if it is ocuppied
    int level;//which level this cell is in
    Xwindow* xw;//Xwindow's pointer
public:
    Cell();
    void draw();//draw a cell in either command line game board or window game board.
    void undraw();//erase a cell in either command line game board or window game board.
    bool IsOccupied() const {return isOccupied;}//Initialize fields
    void Initialize(coordinate xy, coordinate graxy, int r, int c, int width, int height, Xwindow* xw);//initialize fields
    void setLiving(char sym, int level);//set a cell to alive
    void setDead();//set a cell to dead
    void notifyDisplay(TextDisplay& t);//register a cell in the command line game board.
    char getSymbol() const {return symbol;}//return the which kind of cell it is.
    Cell& operator= (Cell& other);//Useful when delete a row
};
#endif /* defined(__Project__Cell__) */
