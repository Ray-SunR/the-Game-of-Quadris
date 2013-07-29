//
//  textdisplay.h
//  The Game of Quadris
//
//  Created by Sun Renchen& Chi Zhang on 2013-07-11.
//  Copyright (c) 2013 University of Waterloo. All rights reserved.
//

#ifndef __Project__TextDisplay__
#define __Project__TextDisplay__

#include <iostream>

class TextDisplay
{
    char** theDisplay;//two dimentional char array
    const int gridSize_Width;//column number
    const int gridSize_Height;//row number
public:
    TextDisplay(int gridSize_Height = 15, int gridSize_Width = 10);//default game size is 15 x 10
    ~TextDisplay();//destructor
    void notify(int r, int c, char ch);//register a character in the game board.
    friend std::ostream& operator<< (std::ostream& out, TextDisplay& td);//out stream
};
#endif /* defined(__Project__TextDisplay__) */
