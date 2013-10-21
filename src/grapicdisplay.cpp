//
//  grapicdisplay.cpp
//  The Game of Quadris
//
//  Created by Sun Renchen& Chi Zhang on 2013-07-11.
//  Copyright (c) 2013 University of Waterloo. All rights reserved.
//

#include <sstream>

#include "grapicdisplay.h"
#include "window.h"

using namespace std;

//constructor
GraphicDisplay::GraphicDisplay(int RowNum, int ColNum, int CellSize)
{
    rowNum = RowNum;
    colNum = ColNum;
    cellSize = CellSize;
}

//destructor
GraphicDisplay::~GraphicDisplay()
{
    delete xw;
}

//Initialize the window
void GraphicDisplay::Initialize()
{
    //Initialize the main grid
    if (rowNum == 15)
        xw  = new Xwindow((colNum + 5) * cellSize, rowNum * cellSize);
    //initialize the sub grid
    else
        xw = new Xwindow(colNum * cellSize, rowNum * cellSize);
    //Background colour is white,
    xw->fillRectangle(0, 0, cellSize * rowNum, 30 * colNum, Xwindow::White);
    //Set the boundary for the game board. Beacuse we reserve 5 columns on the right hand side of the window for updating score, level, and high scores.
    if (rowNum == 15)
    {
        for (int i = 0; i < 15; i++)
        {
            xw->fillRectangle(10 * cellSize, i * cellSize, 2, cellSize, Xwindow::Black);
        }
    }
    //Draw the information of the game
    if (rowNum == 15)
    {
        xw->drawString(10 * cellSize + 15, 1 * cellSize, "Game of Quadris", Xwindow::Red);
        xw->drawString(10 * cellSize + 3, 2 * cellSize, "Designed By: Chi Zhang", Xwindow::Blue);
        xw->drawString(12 * cellSize + 10, 3 * cellSize, "& Renchen Sun", Xwindow::Red);
        xw->drawString(10 * cellSize + 3, 4 * cellSize, "Level: ", Xwindow::Black);
        xw->drawString(10 * cellSize + 3, 5 * cellSize, "Score: ", Xwindow::Black);
        xw->drawString(10 * cellSize + 3, 6 * cellSize, "High Score: ", Xwindow::Black);
        xw->drawString(14 * cellSize, 4 * cellSize, "0", Xwindow::Black);
        xw->drawString(14 * cellSize, 5 * cellSize, "0", Xwindow::Black);
        xw->drawString(14 * cellSize, 6 * cellSize, "0", Xwindow::Black);
    }
    //This is for sub board.
    if (rowNum == 4)
    {
        xw->drawString(1, cellSize, "Next:", Xwindow::Black);
    }
}

void GraphicDisplay::updateScore(int Score)
{
    //convert the integer to string
    stringstream ss;
    ss << Score;
    string score;
    ss >> score;
    //erase the original score
    xw->fillRectangle(14 * cellSize - 15, 4 * cellSize + 10, cellSize + 20, cellSize, Xwindow::White);
    //update the new score.
    xw->drawString(14 * cellSize, 5 * cellSize, score, Xwindow::Black);
}

void GraphicDisplay::updateHiScore(int hiScore)
{
    //convert the integer to string
    stringstream ss;
    ss << hiScore;
    string hiscore;
    ss >> hiscore;
    //erase the original score
    xw->fillRectangle(14 * cellSize - 15, 5 * cellSize + 15, cellSize + 20, cellSize, Xwindow::White);
    //update the new score.
    xw->drawString(14 * cellSize, 6 * cellSize, hiscore, Xwindow::Black);
}

void GraphicDisplay::updateLevel(int Level)
{
    //convert the integer to string
    stringstream ss;
    ss << Level;
    string level;
    ss >> level;  
    //erase the original level
    xw->fillRectangle(14 * cellSize - rowNum, 3 * cellSize, cellSize, cellSize, Xwindow::White);
    //update the new level.
    xw->drawString(14 * cellSize, 4 * cellSize, level, Xwindow::Black);
}

void GraphicDisplay::updateLife(int Life)
{
    //convert the integer to string
    stringstream ss;  
    ss << Life;
    string life;
    ss >> life;  
    //erase the original score
    xw->fillRectangle(13 * cellSize - 15, 6 * cellSize + 15, 4 * cellSize , cellSize, Xwindow::White);
    for (int i = 0; i < Life; i++)
	xw->fillRectangle(13 * cellSize - 20 + i * cellSize + 3, 6 * cellSize + 15, cellSize / 2, cellSize / 2, Xwindow::Red);
}

void GraphicDisplay::drawLifeText()
{   
    xw->drawString(10 * cellSize + 3, 7 * cellSize, "Life: ", Xwindow::Black);
}

void GraphicDisplay::drawFace()
{  
    int refx = 11 * cellSize;
    int refy = 12 * cellSize - 20;
    int scellSize = cellSize / 2; 
    int scellSize2 = cellSize / 4;
    xw->fillRectangle(refy, refx, scellSize2, scellSize, Xwindow::Black);
    xw->fillRectangle(refy + scellSize2, refx - scellSize, scellSize2, scellSize, Xwindow::Black);
    xw->fillRectangle(refy + 2 * scellSize2, refx - 2 * scellSize, scellSize2, scellSize, Xwindow::Black);
    xw->fillRectangle(refy + 3 * scellSize2, refx - 3 * scellSize, scellSize2, scellSize, Xwindow::Black);
    xw->fillRectangle(refy + 4 * scellSize2, refx - 3 * scellSize, scellSize2, scellSize, Xwindow::Black);
    xw->fillRectangle(refy + 5 * scellSize2, refx - 3 * scellSize, scellSize2, scellSize, Xwindow::Black);
    xw->fillRectangle(refy + 6 * scellSize2, refx - 3 * scellSize, scellSize2, scellSize, Xwindow::Black);
    xw->fillRectangle(refy + 7 * scellSize2, refx - 2 * scellSize, scellSize2, scellSize, Xwindow::Black);
    xw->fillRectangle(refy + 8 * scellSize2, refx - scellSize, scellSize2, scellSize, Xwindow::Black);
    xw->fillRectangle(refy + 9 * scellSize2, refx, scellSize2, scellSize, Xwindow::Black); 
    //the rest part
    xw->fillRectangle(refy + scellSize2, refx + scellSize, scellSize2, scellSize, Xwindow::Black);
    xw->fillRectangle(refy + 2 * scellSize2, refx + 2 * scellSize, scellSize2, scellSize, Xwindow::Black);
    xw->fillRectangle(refy + 3 * scellSize2, refx + 3 * scellSize, scellSize2, scellSize, Xwindow::Black);
    xw->fillRectangle(refy + 4 * scellSize2, refx + 3 * scellSize, scellSize2, scellSize, Xwindow::Black);
    xw->fillRectangle(refy + 5 * scellSize2, refx + 3 * scellSize, scellSize2, scellSize, Xwindow::Black);
    xw->fillRectangle(refy + 6 * scellSize2, refx + 3 * scellSize, scellSize2, scellSize, Xwindow::Black);
    xw->fillRectangle(refy + 7 * scellSize2, refx + 2 * scellSize, scellSize2, scellSize, Xwindow::Black);
    xw->fillRectangle(refy + 8 * scellSize2, refx + scellSize, scellSize2, scellSize, Xwindow::Black);
    //draw eyes
    xw->fillRectangle(refy + 3 * scellSize2, refx - scellSize, scellSize2, scellSize2, Xwindow::Red);
    xw->fillRectangle(refy + 6 * scellSize2, refx - scellSize, scellSize2, scellSize2, Xwindow::Red);
    xw->fillRectangle(refy + 3 * scellSize2 + scellSize2 / 2, refx - scellSize + scellSize2 / 2, scellSize2 / 3 + 2, scellSize2 / 3 + 2, Xwindow::Black);   
    xw->fillRectangle(refy + 6 * scellSize2 + scellSize2 / 2, refx - scellSize + scellSize2 / 2, scellSize2 / 3 + 2, scellSize2 / 3 + 2, Xwindow::Black);
    xw->fillRectangle(refy + 6 * scellSize2 + scellSize2 / 2, refx - scellSize + scellSize2 / 2, scellSize2 / 3 + 2, scellSize2 / 3 + 2, Xwindow::Black);
    //draw mouth
    xw->fillRectangle(refy + 3 * scellSize2, refx + scellSize, scellSize2, scellSize2, Xwindow::Red);
    xw->fillRectangle(refy + 4 * scellSize2, refx + 2 * scellSize, scellSize2, scellSize2, Xwindow::Red);
    xw->fillRectangle(refy + 5 * scellSize2, refx + 2 * scellSize, scellSize2, scellSize2, Xwindow::Red);
    xw->fillRectangle(refy + 6 * scellSize2, refx + scellSize, scellSize2, scellSize2, Xwindow::Red);
    xw->fillRectangle(refy + 3.5 * scellSize2, refx + scellSize + scellSize2, scellSize2, scellSize - scellSize2, Xwindow::Red);
    xw->fillRectangle(refy + 5.5 * scellSize2, refx + scellSize + scellSize2, scellSize2, scellSize - scellSize2, Xwindow::Red);
    xw->fillRectangle(refy + 4 * scellSize2, refx + scellSize, scellSize2, 2, Xwindow::Red);
    xw->fillRectangle(refy + 5 * scellSize2, refx + scellSize, scellSize2, 2, Xwindow::Red);
    //draw nose
    xw->fillRectangle(refy + 4.5 * scellSize2, refx, scellSize2, scellSize2, Xwindow::Red);
}
