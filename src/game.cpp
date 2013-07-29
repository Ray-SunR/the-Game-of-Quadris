//
//  game.cpp
//  The Game of Quadris
//
//  Created by Sun Renchen& Chi Zhang on 2013-07-11.
//  Copyright (c) 2013 University of Waterloo. All rights reserved.
//

#include <iostream>
#include <sstream>

#include "game.h"
#include "grid.h"
#include "abstractblock.h"
#include "cInterpreter.h"
#include "nextBlock.h"
#include "grapicdisplay.h"
#include "iblock.h"
#include "jblock.h"
#include "lblock.h"
#include "oblock.h"
#include "sblock.h"
#include "zblock.h"
#include "tblock.h"
#include "score.h"

using namespace std;

//responsible for display information on the game board.
void Game::Display(Grid* gd, Grid* subgd, nextBlock* level, score* scoreboard)
{
    if (lifeMode)
        cout << "Life: " << life << endl;
    cout << "Level: " << level->getNumLevel() << endl;
    cout << "Score: " << scoreboard->getScore() << endl;
    cout << "Hi Score: " << scoreboard->getHi() << endl;
    cout << *gd << endl;
    cout << "Next:" << endl;
    cout << *subgd << endl;
}

//destructor
Game::~Game()
{
    for (int i = 0; i < vBlock.size(); i++)//free blocks
        delete vBlock[i];
    delete gd;//free grid;
    delete subgd;//free sub grid
    if (!textOnly)//if it is a graphic display
    {
        delete gdisplay;//free graphic display
        delete subGdisplay;//free sub-graphic display
    }
    //    delete ab;
    delete next;//free level
    delete interpreter;//free command-line interpreter
    delete scoreboard;//free scoreboard.
}

//restart
void Game::restart()
{
    delete gd;//free grid;
    delete subgd;//free sub-grid
    delete interpreter;//free command-line interpreter
    delete next;//free level
    //    delete ab;
    if (!textOnly)//if it is a graphic display
    {
        delete gdisplay;//free graphic display
        delete subGdisplay;//free sub-graphic display
    }
    gdisplay = NULL;
    subGdisplay = NULL;
    for (int i = 0; i < vBlock.size(); i++)//free blocks
        delete vBlock[i];
    //Should clear the vector
    vBlock.clear();
    //Should reset the game board.
    scoreboard->resetScore();
    //start again
    start();
}

//generate the next block
AbstractBlock* Game::generateNextBlock(char c, Grid* gd, nextBlock* updateLevel)
{
    AbstractBlock* ab = NULL;
    switch (c) {
        case 'I':
            //I block
            ab = new IBlock(gd, updateLevel->getNumLevel());
            break;
        case 'J':
            //J block
            ab = new JBlock(gd, updateLevel->getNumLevel());
            break;
        case 'L':
            //L block
            ab = new LBlock(gd, updateLevel->getNumLevel());
            break;
        case 'O':
            //O block
            ab = new OBlock(gd, updateLevel->getNumLevel());
            break;
        case 'S':
            //S block
            ab = new SBlock(gd, updateLevel->getNumLevel());
            break;
        case 'Z':
            //Z block
            ab = new ZBlock(gd, updateLevel->getNumLevel());
            break;
        case 'T':
            //T block
            ab = new TBlock(gd, updateLevel->getNumLevel());
            break;
        default:
            break;
    }
    return ab;
}

//start the game
void Game::start()
{
    //if it is not text-only
    if (!textOnly)
    {
        //graphic display main board.
        gdisplay = new GraphicDisplay();
        //sub-board for displaying next block
        subGdisplay = new GraphicDisplay(4, 4);
    }
    //otherwise, no graphic window is displayed.
    else
    {
        gdisplay = NULL;
        subGdisplay = NULL;
    }
    //Create a new grid.
    gd = new Grid(gdisplay);
    //create a new command line interpreter
    interpreter = new cInterpreter();
    //next block
    next = new nextBlock(scriptfile, startLevel);
    //sub grid for displaying
    subgd = new Grid(subGdisplay, 4, 4);
    if (gdisplay)
        gdisplay->drawFace();
    //if it is graphic display
    if (gdisplay)
        //update the level in the window
        gdisplay->updateLevel(next->getNumLevel());
    //if the scoreboard has already existed, then don't create a new scoreboard, otherwise, should create a new scoreboard.
    if (!scoreboard)
        scoreboard = new score();
    //reset the current score in the scoreboard to 0
    scoreboard->resetScore();
    //hi score should be retained even if restart
    if (gdisplay)
        gdisplay->updateHiScore(scoreboard->getHi());
    if (gdisplay && lifeMode)
    {
        gdisplay->drawLifeText();
        gdisplay->updateLife(life);
    }
    string command;
    char c = next->startRun();//determine which block is the first block
    char cnext = next->startRun();//determine which block is the next
    //create the first block
    ab = generateNextBlock(c, gd, next);
    //put that block into the container
    vBlock.push_back(ab);
    AbstractBlock* abnext = NULL;
    //create the next block
    abnext = generateNextBlock(cnext, subgd, next);
    //put the next block into the container
    vBlock.push_back(abnext);
    //display the information on board.
    Display(gd, subgd, next, scoreboard);
    while (cin >> command)
    {
        //check if the command was restart.
        if (interpreter->isRestart(command))
        {
            //if so, then restart
            restart();
            return;
        }
        int t;//used to store how many times a command runs
        int pos = -1;
        while (command[pos + 1] <= 57 && command[pos + 1] >= 48)//check whether it is a multiple command
            pos++;
        //determine if the command was a multiple command
        if (pos != -1)
        {
            //if so, then call the multiple command method
            string subCommand;
            string time = command.substr(0, pos + 1);
            subCommand = command.substr(pos + 1, command.length() - time.length());
            stringstream ss(time);
            ss >> t;
            playing = interpreter->multipleCommand(t, subCommand, &ab, &abnext, gd, subgd, next, scoreboard, vBlock, gdisplay);
        }
        //otherwise, it is a single command
        else
        {
            playing = interpreter->finalcommand(command, &ab, &abnext, gd, subgd, next, scoreboard, vBlock, gdisplay);
        }
        Display(gd, subgd, next, scoreboard);
        //if the game was over, then end the game.
        if (!playing)//if not playing, either game over or input is exausted, then terminate the game
        {
            if (!lifeMode)//if it is not a life Mode, then exit the game.
            {
                cout << "game over!" << endl;
                return;
            }
            if (--life == 0)//if ti is a life mode, then if life is equal to 0, then end the game
            {
                cout << "game over!" << endl;
                return;
            }
            //otherwise, still have life, continue the game.
            restart();
            return;
        }
    }
}

void Game::end()
{
    delete this;
}

