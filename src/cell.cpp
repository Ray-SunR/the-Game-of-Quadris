//
//  cell.cpp
//  The Game of Quadris
//
//  Created by Sun Renchen& Chi Zhang on 2013-07-11.
//  Copyright (c) 2013 University of Waterloo. All rights reserved.
//

#include "cell.h"
#include "window.h"
#include "textdisplay.h"

//Constructor
Cell::Cell()
{
    xy.x = 0;
    xy.y = 0;
    r = 0;
    c = 0;
    width = 0;
    height = 0;
    level = 0;
    isOccupied = false;
}

//Initialize fields
void Cell::Initialize(coordinate xy, coordinate graxy, int r, int c, int width, int height, Xwindow* x)
{
    this->xw = x;//Xwindow's pointer
    this->xy = xy;//coordinate in the two-dimentional array
    this->graxy = graxy;//coodinate in the graphic window
    this->r = r;//row
    this->c = c;//column
    this->width = width;//width of the cell
    this->height = height;//height of the cell
}

//draw method 
void Cell::draw()
{
    if (!xw)//if the game was played in the command line mode, then a cell can't be drawn.
        return;
    //According to different kinds of blocks, draw them by using different colors.
    if (isOccupied && this->symbol == 'I')
        xw->fillRectangle(graxy.y, graxy.x, width, height, Xwindow::Black);
    else if (isOccupied && this->symbol == 'J')
        xw->fillRectangle(graxy.y, graxy.x, width, height, Xwindow::Red);
    else if (isOccupied && this->symbol == 'L')
        xw->fillRectangle(graxy.y, graxy.x, width, height, Xwindow::Blue);
    else if (isOccupied && this->symbol == 'O')
        xw->fillRectangle(graxy.y, graxy.x, width, height, Xwindow::Brown);
    else if (isOccupied && this->symbol == 'S')
        xw->fillRectangle(graxy.y, graxy.x, width, height, Xwindow::Cyan);
    else if (isOccupied && this->symbol == 'Z')
        xw->fillRectangle(graxy.y, graxy.x, width, height, Xwindow::Green);
    else if (isOccupied && this->symbol == 'T')
        xw->fillRectangle(graxy.y, graxy.x, width, height, Xwindow::Yellow);
    else
	xw->fillRectangle(graxy.y, graxy.x, width, height, Xwindow::White);
}

//undraw method
void Cell::undraw()
{
    //undraw them by filling the block with white color.
    if (xw)
        xw->fillRectangle(graxy.y, graxy.x, width, height, Xwindow::White);
}

//set a cell to alive
void Cell::setLiving(char sym, int level)
{
    this->level = level;
    isOccupied = true;
    symbol = sym;
    //if the game was played in the command-line mode, then do not have to draw the block in the window.
    if (xw)
        draw();
}

//set a cell to dead
void Cell::setDead()
{
    this->level = 0;
    isOccupied = false;
    //if the game was played in the command-line mode, then do not have to draw the block in the window.
    if (xw)
        undraw();
}

//register a cell in the command line mode
void Cell::notifyDisplay(TextDisplay& t)
{
    char ch = ' ';
    if (isOccupied)
        t.notify(r, c, symbol);
    else
        t.notify(r, c, ch);
}

//assignment operator, useful when deleting a row
Cell& Cell::operator=(Cell& other)
{
    //selft checking
    if (this == &other)
        return *this;
    //downward by 1 position
    xy.x = other.xy.x + 1;
    xy.y = other.xy.y;
    r = other.r + 1;
    c = other.c;
    width = other.width;
    height = other.height;
    symbol = other.symbol;
    isOccupied = other.isOccupied;
    return *this;
}
