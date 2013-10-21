//
//  nextBlock.cpp
//  The Game of Quadris
//
//  Created by Sun Renchen& Chi Zhang on 2013-07-11.
//  Copyright (c) 2013 University of Waterloo. All rights reserved.
//

#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<cstdlib>

#include"nextBlock.h"

using namespace std;

//constructor
nextBlock::nextBlock(std::string filename, int level):filename(filename), numLevel(level)
{
    //open the input source
    seq.open(filename.c_str());
}

//destructor
nextBlock::~nextBlock()
{
	seq.close();
}

//get level
int nextBlock::getNumLevel() const
{
	return numLevel;
}

//level up
void nextBlock::addLevel()
{
    //boundary checking
    if (numLevel < 3)
        numLevel = numLevel + 1;
}

//level down
void nextBlock::subLevel()
{
    //boundray checking
    if (numLevel > 0)
        numLevel = numLevel - 1;  
}

//will determine which block comes next based on whcih level it is.
char nextBlock:: startRun()
{
    //if the current level is 0, then the blocks come from the script file
    if(numLevel == 0)
    {
		string blockname;
		string row;
		if(seq >> blockname)
        {
            //I block
            if(blockname == "I")
                return 'I';
            //J block
            else if (blockname == "J")
                return 'J';
            //L block
            else if (blockname == "L")
                return 'L';
            //O block
            else if(blockname == "O")
                return 'O';
            //S block
            else if(blockname == "S")
                return 'S';
            //Z block
            else if(blockname == "Z")
                return 'Z';
            //T block
            else
                return 'T';
        }
        //if the input was exhausted, then close the file
        else
        {
            seq.close();
            //e represents the input was exhausted
            return 'e';
        }
	}
    //if the current level is 1, then apply some probality to certain blocks.
	else if(numLevel == 1)
    {
		int lotto = rand() % 12;
		if (lotto == 0 || lotto == 1)
            return 'I';
		else if(lotto == 2 || lotto == 3)
            return 'J';
        else if(lotto == 4 || lotto == 5)
            return 'L';
		else if(lotto == 6 || lotto == 7)
            return 'O';
		else if(lotto == 8)//the possibility of S is 1/12
			return 'S';
		else if(lotto == 9)//the possibility of Z is 1/12
			return 'Z';
		else
            return 'T';
	}
	else if(numLevel == 2)
    {
		int lotto = rand() % 7;
		if (lotto == 0)
            return 'I';
		else if(lotto == 1)
            return 'J';
		else if(lotto == 2)
            return 'L';
		else if(lotto == 3)
            return 'O';
		else if(lotto == 4)
            return 'S';
		else if(lotto == 5)
            return 'Z';
		else
            return 'T';
	}
	else
    {
		int lotto = rand() % 9;
		if (lotto == 0)
            return 'I';
		else if(lotto == 1)
            return 'J';
		else if(lotto == 2)
            return 'L';  
		else if(lotto == 3)
            return 'O';
		else if(lotto == 4 || lotto == 5)
            return 'S';
		else if(lotto == 6 || lotto == 7)
            return 'Z';
		else
            return 'T';
	}
}
