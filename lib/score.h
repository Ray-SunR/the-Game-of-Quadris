//
//  score.h
//  The Game of Quadris
//
//  Created by Sun Renchen& Chi Zhang on 2013-07-11.
//  Copyright (c) 2013 University of Waterloo. All rights reserved.
//

#ifndef __score_h__
#define __score_h__

#include <iostream>
#include <vector>

class AbstractBlock;
class Cell;
class Grid;
class nextBlock;
class GraphicDisplay;

class score
{
	int scorevalue;//current score
	int hiScore;//highest score
    bool BelongtoOthers(Cell* cell, int pos, std::vector<AbstractBlock*>& vBlock);//check if a certain cell of a block is belonged to other blocks
	public:
	score();//constructor
	~score();//distructor
	void updateScore(Grid* gd, nextBlock *forLevel, int numDelete, std::vector<AbstractBlock*>& vBlock, GraphicDisplay* gdisplay);//update the score
	int getScore() const {return scorevalue;}//return score for display later
	int getHi() const {return hiScore;}//return highest score for display later
    void resetScore() {scorevalue = 0;}//reset the score if restart.
};

#endif
