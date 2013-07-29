//
//  game.h
//  The Game of Quadris
//
//  Created by Sun Renchen& Chi Zhang on 2013-07-11.
//  Copyright (c) 2013 University of Waterloo. All rights reserved.
//

#ifndef __Project__game__
#define __Project__game__

#include <iostream>
#include <vector>

class Cell;
class Grid;
class score;
class AbstractBlock;
class cInterpreter;
class nextBlock;
class GraphicDisplay;
class TextDisplay;

class Game
{
    Grid* gd;//game board
    Grid* subgd;//sub-board for displaying next-block
    score* scoreboard;//scoreboard pointer
    AbstractBlock* ab;//pointer to block
    nextBlock* next;//next block
    cInterpreter* interpreter;//command line interpreter pointer
    AbstractBlock* generateNextBlock(char c, Grid* gd, nextBlock* next);//will generate the next block according to the chararacter 'c'
    std::vector<AbstractBlock*> vBlock;//a container responsible for containing blocks.
    GraphicDisplay* gdisplay;//Graphic Display pointer
    GraphicDisplay* subGdisplay;//Sub-Graphic Display pointer
    std::string scriptfile;//script file name
    int seed;//seed for the game
    int startLevel;//startLevel
    int life;
    bool textOnly;//indicate if the game was played in text mode.
    bool playing;//check if the game is playing.
    bool lifeMode;
    void restart();//restart method
    void Display(Grid* gd, Grid* subgd, nextBlock* level, score* scoreboard);//responsible for displaying some information on board.
public:
    Game():scoreboard(NULL), playing(true),gd(NULL),subgd(NULL), ab(NULL),next(NULL),interpreter(NULL), gdisplay(NULL), subGdisplay(NULL), textOnly(false), seed(0), scriptfile("sequence.txt"), startLevel(0), lifeMode(false), life(3){}//constructor
    ~Game();//destructor
    void setSeed(int seed) {this->seed = seed;}//set seed
    void setScriptFile(std::string filename) {scriptfile = filename;}//set scriptfile
    void setTextOnly() {textOnly = true;}//set text only
    void setStartLevel(int Level) {if (Level > 3) startLevel = 3; else if (Level < 0) startLevel = 0; else startLevel = Level;}//set start level
    void setLifeMode() { lifeMode = true;}
    void setGameLife(int num) {if (!lifeMode) return; if (num > 3) life = 3; else if (num < 0) life =0; else life = num;}
    void start();//start the game
    void end();//end the game
};

#endif /* defined(__Project__game__) */
