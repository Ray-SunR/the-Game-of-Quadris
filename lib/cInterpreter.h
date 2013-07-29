//
//  cInterpreter.h
//  The Game of Quadris
//
//  Created by Sun Renchen& Chi Zhang on 2013-07-11.
//  Copyright (c) 2013 University of Waterloo. All rights reserved.
//

#ifndef __cInterpreter_h__
#define __cInterpreter_h__

#include <iostream>
#include <vector>
#include <string>

class Grid;
class score;
class nextBlock;
class AbstractBlock;
class GraphicDisplay;
class Game;

class cInterpreter{
	std::string fullLeft;
	std::string fullRight;
	std::string fullDown;
	std::string fullClockwise;
	std::string fullCounterClockwise;
	std::string fullDrop;
	std::string fullLevelup;
	std::string fullLeveldown;
	std::string fullRestart;
    std::string fullSkip;
    bool isLeft(std::string command);//Check if the input string means 'left'
	bool isRight(std::string command);//Check if the input string means 'right'
	bool isDown(std::string command);//Check if the input string means 'down'
	bool isClockwise(std::string command);//Check if the input string means 'clockwise'
	bool isCounterClockwise(std::string command);//Check if the input string means 'counterclockwise'
	bool isDrop(std::string command);//Check if the input string means 'drop'
	bool isLevelup(std::string command);//Check if the input string means 'levelup'
	bool isLeveldown(std::string command);//Check if the input string means 'leveldown'
    bool isSkip(std::string command);//Check if the input string means 'skip'
    bool validInput(std::string command);//Check the input is a valid input
    AbstractBlock* generateNextBlock(char c, Grid* gd, nextBlock* updateLevel);//Responsible for generating next block
public:
	cInterpreter();//Constructor
	~cInterpreter();//Destructor
    bool isRestart(std::string command);//Check if the input string means 'restart'
	bool finalcommand(std::string command, AbstractBlock** doblock, AbstractBlock** nextblock, Grid* gd, Grid* subgd, nextBlock * updateLevel, score* scoreboard, std::vector<AbstractBlock*>& vBlock, GraphicDisplay* gdisplay);//Responsible for dealing with the command interpreting, text display, graphic display, update score
	bool multipleCommand(int times, std::string command, AbstractBlock** doblock, AbstractBlock** nextblock, Grid * gd, Grid* subgd, nextBlock * updateLevel, score* scoreboard,std::vector<AbstractBlock*>& vBlock, GraphicDisplay* gdisplay);//Dealing with multiple commands with number prefix.
};

#endif
