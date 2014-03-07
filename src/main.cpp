//
//  main.cpp
//  The Game of Quadris
//
//  Created by Sun Renchen& Chi Zhang on 2013-07-11.
//  Copyright (c) 2013 University of Waterloo. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <cstdlib>

#include "game.h"

using namespace std;

int main(int argc, const char * argv[])
{
    Game* g = new Game();
    for (int i = 0; i < argc; i++)
    {
         string ar = argv[i];
         if (ar == "-text")
         {
            g->setTextOnly();
         }
         if (ar == "-scriptfile")
         {
            g->setScriptFile(argv[i + 1]);
         }
         if (ar == "-startlevel")
         {
            int num;
            stringstream ss(argv[i + 1]);
            ss >> num;
            g->setStartLevel(num);
         }
         if (ar == "-seed")
         {
            int num;
            stringstream ss(argv[i + 1]);
            ss >> num;
            srand(num);
         }
         if (ar == "-lifemode")
	 {
	    g->setLifeMode();
	 }
         if (ar == "-setlife")
         {
	    int num;
            stringstream ss(argv[i + 1]);
            ss >> num;
	    g->setGameLife(num);
         }
    }
    g->start();
    g->end();
    delete g;
}

