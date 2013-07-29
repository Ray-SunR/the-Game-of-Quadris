//
//  cInterpreter.cpp
//  The Game of Quadris
//
//  Created by Sun Renchen& Chi Zhang on 2013-07-11.
//  Copyright (c) 2013 University of Waterloo. All rights reserved.
//

#include <string>
#include <sstream>
#include <iostream>

#include "cInterpreter.h"
#include "abstractblock.h"
#include "nextBlock.h"
#include "score.h"
#include "iblock.h"
#include "jblock.h"
#include "lblock.h"
#include "oblock.h"
#include "sblock.h"
#include "zblock.h"
#include "tblock.h"
#include "grid.h"
#include "grapicdisplay.h"

using namespace std;

//Constructor
cInterpreter::cInterpreter()
{
	fullLeft = "left";
	fullRight = "right";
	fullDown = "down";
	fullClockwise = "clockwise";
	fullCounterClockwise = "counterclockwise";
	fullDrop = "drop";
	fullLevelup = "levelup";
	fullLeveldown = "leveldown";
	fullRestart = "restart";
    fullSkip = "skip";
}

//Destructor
cInterpreter::~cInterpreter(){}

//Check if the input string means 'left'
bool cInterpreter::isLeft(std::string command)
{
	int len = (int)command.length();
	if(len == 4)
		return command == "left";
	else if(len > 4 || len < 2)
		return false;
	else
    {
		for(int i = 0; i < len;i = i + 1)
			if (command[i] != fullLeft[i])
				return false;
		if(len <= 2)
			return false;
		return true;
	}
}

//Check if the input string means 'right'
bool cInterpreter::isRight(std::string command)
{
	int len = (int)command.length();
	if(len == 5)
		return command == fullRight;
	else if(len > 5 || len < 2)
		return false;
	else
    {
		for(int i = 0; i < len;i = i + 1)
        {
			if (command[i] != fullRight[i])
				return false;
		}
		return true;
	}
}

//Check if the input string means 'down'
bool cInterpreter::isDown(std::string command){
	int len = (int)command.length();
	if(len == 4)
		return command == "down";
	else if(len > 4 || len < 2)
		return false;
	else
    {
		for(int i = 0; i < len; i = i + 1)
        {
			if (command[i] != fullDown[i])
				return false;
		}
		return true;
	}
}

//Check if the input string means 'clockwise'
bool cInterpreter::isClockwise(std::string command)
{
	int len = (int)command.length();
	if(len == 9)
		return command == "clockwise";
	else if(len > 9 || len < 2)
		return false;
	else
    {
		for(int i = 0; i < len; i = i + 1)
			if (command[i] != fullClockwise[i])
				return false;
		return true;
	}
}

//Check if the input string means 'counterclockwise'
bool cInterpreter::isCounterClockwise(std::string command)
{
	int len = (int)command.length();
	if(len == 16)
		return command == "counterclockwise";
	else if(len > 16 || len < 2)
		return false;
	else
    {
		for(int i = 0; i < len; i = i + 1)
        {
			if (command[i] != fullCounterClockwise[i])
				return false;
		}
		return true;
	}
}

//Check if the input string means 'drop'
bool cInterpreter::isDrop(std::string command)
{
	int len = (int)command.length();
	if(len == 4)
		return command == "drop";
	else if(len > 4 || len < 2)
		return false;
	else
    {
		for(int i = 0; i < len; i = i + 1)
			if (command[i] != fullDrop[i])
				return false;
		return true;
	}
}

//Check if the input string means 'levelup'
bool cInterpreter::isLevelup(std::string command)
{
	int len = (int)command.length();
	if(len == 7)
		return command == "levelup";
	else if(len > 7 || len < 2)
		return false;
	else
    {
		for(int i = 0; i < len;i = i + 1)
			if (command[i] != fullLevelup[i])
				return false;
		if(len <= 5)
			return false;
		return true;
	}
}

//Check if the input string means 'leveldown'
bool cInterpreter::isLeveldown(std::string command)
{
	int len = (int)command.length();
	if(len == 9)
		return command == "leveldown";
	else if(len > 9 || len < 2)
		return false;
	else
    {
		for(int i = 0; i < len;i = i + 1)
			if (command[i] != fullLeveldown[i])
				return false;
		if(len <= 5)
			return false;
		return true;
	}
}

//Check if the input string means 'restart'
bool cInterpreter::isRestart(string command)
{
	int len = (int)command.length();
	if(len == 7)
		return command == "restart";
	else if(len > 7 || len < 2)
		return false;
	else
    {
		for(int i = 0; i < len; i = i + 1)
			if (command[i] != fullRestart[i])
				return false;
		return true;
	}
}

//Check if the input string means 'skip'
bool cInterpreter::isSkip(string command)
{
    int len = (int)command.length();
    if (len == 4)
        return command == "skip";
    else if (len > 4 || len < 1)
        return false;
    else
    {
        for (int i = 0; i < len; i++)
        {
            if (command[i] != fullSkip[i])
                return false;
        }
        return true;
    }
}

//Responsible for generating next block
AbstractBlock* cInterpreter::generateNextBlock(char c, Grid* gd, nextBlock* updateLevel)
{
    AbstractBlock* ab = NULL;
    switch (c) {
        case 'I':
            ab = new IBlock(gd, updateLevel->getNumLevel());
            break;
        case 'J':
            ab = new JBlock(gd, updateLevel->getNumLevel());
            break;
        case 'L':
            ab = new LBlock(gd, updateLevel->getNumLevel());
            break;
        case 'O':
            ab = new OBlock(gd, updateLevel->getNumLevel());
            break;
        case 'S':
            ab = new SBlock(gd, updateLevel->getNumLevel());
            break;
        case 'Z':
            ab = new ZBlock(gd, updateLevel->getNumLevel());
            break;
        case 'T':
            ab = new TBlock(gd, updateLevel->getNumLevel());
            break;
        default:
            ab = NULL;
            break;
    }
    return ab;
}

//Responsible for dealing with the command interpreting, text display, graphic display, update score
bool cInterpreter::finalcommand(string command, AbstractBlock** doblock, AbstractBlock** nextblock, Grid * gd, Grid* subgd, nextBlock * updateLevel, score* scoreboard, std::vector<AbstractBlock*>& vBlock, GraphicDisplay* gdisplay){
	if(isLeft(command))
		(*doblock)->shiftLeft(gd);
	else if(isRight(command))
		(*doblock)->shiftRight(gd);
	else if(isDown(command))
		(*doblock)->shiftDown(gd);
	else if(isClockwise(command))
		(*doblock)->clockwiseRotate(gd);
	else if(isCounterClockwise(command))
		(*doblock)->counterClockwiseRotate(gd);
    //if the block is skipped
    else if (isSkip(command))
    {
        //erase the previous block
        vBlock.erase(vBlock.end() - 2);
        //undraw this block from either the command line game board or graphic game board.
        (*doblock)->undraw(gd);
        delete *doblock;
        //The next block becomes the current block.
        *doblock = *nextblock;
        //Fetch the next block.
        char next = updateLevel->startRun();
        //'e' block does not exists, thus, once get this block means the input source file was exausted, the game was over.
        if (next == 'e')
            return false;
        coordinate temp;
        temp.x = 3;
        temp.y = 0;
        //undraw the previous next-block from the sub-board.
        (*nextblock)->undraw(subgd);
        //Should reset the current block to have the correct reference coordinate.
        (*doblock)->setRefCoord(temp, gd);
        //Check if game was over
        if ((*doblock)->canBeDraw(gd))
            //if the game was not over, then draw the block in the game board
            (*doblock)->draw(gd, updateLevel->getNumLevel());
        //Otherwise, display game over, and return false to tell game class that the game was over.
        else
            return false;
        //should generate the next block.
        *nextblock = generateNextBlock(next, subgd, updateLevel);//will generate a next block in the sub-board.
        //once created, then add the block into a container.
        vBlock.push_back(*nextblock);
    }
    //Check if the input means 'drop'
    else if(isDrop(command))//triggers to create a new block
    {
        if (!(*doblock)->Fall(gd))//if the return type is false, then the game was over
            return false;
        int numDele = gd->check();
        if (numDele)//check whether we should delete rows
            scoreboard->updateScore(gd, updateLevel, numDele, vBlock, gdisplay);
        char next = updateLevel->startRun();//get next block
        *doblock = *nextblock;//assign the previous next-block to the current block
        if (next == 'e')//means the input was exausted
            return false;
        coordinate temp;
        temp.x = 3;
        temp.y = 0;
        (*nextblock)->undraw(subgd);//undraw from the sub-board
        (*doblock)->setRefCoord(temp, gd);//should set the new reference coordinate, the board will be updated automatically
        if ((*doblock)->canBeDraw(gd))
            (*doblock)->draw(gd, updateLevel->getNumLevel());//draw on the main-board
        //if can't be placed, then the game was over
        else
            return false;
        *nextblock = generateNextBlock(next, subgd, updateLevel);//will generate a next block in the sub-board.
        vBlock.push_back(*nextblock);
    }
    //Check if the command means 'levelup'
	else if(isLevelup(command))
    {
		//add level
		updateLevel->addLevel();
        //if it is only the text display mode, then update the level in the game board.
        if (gdisplay)
            gdisplay->updateLevel(updateLevel->getNumLevel());
        
	}
    //Check if the command means 'leveldown'
	else if(isLeveldown(command))
    {
        //decrease level
		updateLevel->subLevel();
        //if it is only the text display mode, then update the level in the game board.
        if (gdisplay)
            gdisplay->updateLevel(updateLevel->getNumLevel());
	}
    return true;
}

//Check the input is a valid input
bool cInterpreter::validInput(string command)
{
    return (isLeft(command) || isRight(command) || isDown(command) || isClockwise(command) || isCounterClockwise(command) || isDrop(command) || isLevelup(command) || isLeveldown(command) || isSkip(command));
}

//Dealing with multiple commands with number prefix.
bool cInterpreter::multipleCommand(int times, string command, AbstractBlock** doblock, AbstractBlock** nextblock, Grid * gd, Grid* subgd, nextBlock * updateLevel, score* scoreboard, std::vector<AbstractBlock*>& vBlock, GraphicDisplay* gdisplay)
{
    //if the time was 0, then do nothing.
	if (times == 0) return true;
    //if the command restart, then restart.
	else if(isRestart(command))
        gd->restart();
    //if the time is grater than 0 and it is a valid command
	else if (times > 0 && validInput(command))
    {
		for(int i = 0; i < times; i = i + 1)
			if (!finalcommand(command,doblock, nextblock, gd, subgd, updateLevel, scoreboard, vBlock, gdisplay))
                return false;
    }
    return true;
}

