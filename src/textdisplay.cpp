//
//  textdisplay.cpp
//  The Game of Quadris
//
//  Created by Sun Renchen& Chi Zhang on 2013-07-11.
//  Copyright (c) 2013 University of Waterloo. All rights reserved.
//

#include <iostream>

#include "textdisplay.h"

using namespace std;

//constructor, create a two-dimentional array
TextDisplay::TextDisplay(int gridSize_Height, int gridSize_Width):gridSize_Height(gridSize_Height), gridSize_Width(gridSize_Width)
{
    theDisplay = new char* [gridSize_Height];
    for (int i = 0; i < gridSize_Height; i++)
        theDisplay[i] = new char [gridSize_Width];
    for (int i = 0; i < gridSize_Height; i++)
        for (int j = 0; j < gridSize_Width; j++)
            theDisplay[i][j] = ' ';
}

//destructor, free the memeory
TextDisplay::~TextDisplay()
{
    for (int i = 0; i < gridSize_Height; i++)
        delete theDisplay[i];
    delete [] theDisplay;
}

//register a character in a certain position
void TextDisplay::notify(int r, int c, char ch)
{
    theDisplay[r][c] = ch;
}

//output stream
ostream& operator<< (ostream& out, TextDisplay& td)
{
    out << " ";
    for (int i = 0; i < td.gridSize_Width; i++)
        out << "-";
    out << endl;
    for (int i = 0; i < td.gridSize_Height; i++)
    {
        out << "|";
        for (int j = 0; j < td.gridSize_Width; j++)
            out << td.theDisplay[i][j];
        out << "|";
        out << endl;
    }
    out << " ";
    for (int i = 0; i < td.gridSize_Width; i++)
        out << "-";
    out << endl;
    if (td.gridSize_Width == 4)
        out << "Designed By: Chi Zhang& Renchen Sun";
    return out;
}
