//
//  score.cpp
//  The Game of Quadris
//
//  Created by Sun Renchen& Chi Zhang on 2013-07-11.
//  Copyright (c) 2013 University of Waterloo. All rights reserved.
//

#include <iostream>
#include <sstream>

#include "score.h"
#include "nextBlock.h"
#include "abstractblock.h"
#include "grid.h"
#include "grapicdisplay.h"
#include "cell.h"

using namespace std;

//constructor
score::score()
{
	scorevalue = 0;
	hiScore = 0;
}

score::~score(){}

//check if a certain cell is belonged to others
bool score::BelongtoOthers(Cell* cell, int pos, std::vector<AbstractBlock*>& vBlock)
{
    for (int i = 0; i < vBlock.size(); i++)
    {
        if (i != pos)
        {
            std::vector<Cell*> vCell = vBlock[i]->getMapCell(vBlock[i]->getCurrentType());
            for (int j = 0; j < 4; j++)
            {
                if (cell == vCell[j])
                    return true;
            }
        }
    }
    return false;
}

//update score
void score::updateScore(Grid* gd, nextBlock *forLevel, int numDele, std::vector<AbstractBlock*>& vBlock, GraphicDisplay* gdisplay)
{
    int numLevel = forLevel->getNumLevel();
    int numDelete = numDele;
    bool flag = false;
    //this loop is for checking if a block is completely removed from the screen
    for (int i = 0; i < vBlock.size(); i++)
    {
        std::vector<Cell*> vCell = vBlock[i]->getMapCell(vBlock[i]->getCurrentType());
        for (int j = 0; j < 4; j++)
        {
            if (!BelongtoOthers(vCell[j], i, vBlock) && vCell[j]->getSymbol() == vBlock[i]->getShape())//If cells of a block do not belong to itself or do not belong to other blocks, then that cell is completely removed. Otherwise it is not.
            {
                flag = true;
                break;
            }
        }
        if (!flag)
        {
            //if this block is completely removed from the screen, then calculate the new score value
            scorevalue += (vBlock[i]->getLevel() + 1) * (vBlock[i]->getLevel() + 1);//each block will have a level, once we determine that a block was completely removed from the screen, add bonus marks based on the level where this block was in.
            vBlock.erase(vBlock.begin() + i);//once completely removed, then remove that block
            i--;
        }
        flag = false;
    }
    //calculate the score value
    scorevalue = scorevalue + (numLevel + numDelete) * (numLevel + numDelete);
	if(scorevalue > hiScore)//update high score
    {
		hiScore = scorevalue;
	}
    //if game was playing on graphic mode, then update scores in the graphic window.
    if (gdisplay)
    {
        gdisplay->updateScore(scorevalue);
        gdisplay->updateHiScore(hiScore);
    }
}
