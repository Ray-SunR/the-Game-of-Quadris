//
//  grapicdisplay.h
//  The Game of Quadris
//
//  Created by Sun Renchen& Chi Zhang on 2013-07-11.
//  Copyright (c) 2013 University of Waterloo. All rights reserved.
//

#ifndef __Project_Graphic___grapicdisplay__
#define __Project_Graphic___grapicdisplay__

#include <iostream>

class GraphicDisplay;
class Xwindow;

class GraphicDisplay
{
    Xwindow* xw;//Xwindow's pointer
    int rowNum;//store the row number of the grid
    int colNum;//store the colnum number of the grid
    int cellSize;//store the cell size
public:
    GraphicDisplay(int rowNum = 15, int colNum = 10, int cellSize = 30);//set the default rowNum to be 15, colnum number to 10, and cell size to be 30.
    void Initialize();//responsible for the initialization
    Xwindow* getWindowPtr() const {return xw;}//return the Xwindow pointer
    void updateScore(int Score);//will update the score in the Graphic window
    void updateHiScore(int hiScore);//will update the high score in the Graphic window
    void updateLevel(int Level);//will update the level in the graphic window
    void drawFace();
    void drawLifeText();
    void updateLife(int num);
    ~GraphicDisplay();//destructor
};
#endif /* defined(__Project_Graphic___grapicdisplay__) */
