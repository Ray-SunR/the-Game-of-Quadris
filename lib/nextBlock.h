//
//  nextBlock.h
//  The Game of Quadris
//
//  Created by Sun Renchen& Chi Zhang on 2013-07-11.
//  Copyright (c) 2013 University of Waterloo. All rights reserved.
//

#ifndef __NEXTBLOCK_H__
#define __NEXTBLOCK_H__

#include <iostream>
#include <string>
#include <fstream>

class nextBlock
{
   std::string filename;//script file name
	int numLevel;//indicate the game level
    std::ifstream seq;//input file source.
public:
	nextBlock(std::string filename, int level);//constructor
	~nextBlock();//destructor
	int getNumLevel() const;//get the number of level
	void addLevel();//level up
	void subLevel();//level down
	char startRun();//used to indicate what kind of block the next is
};

#endif
