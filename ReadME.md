#The Game of Quadris
Contributor: Renchen Sun(Ray), Chi Zhang(Ace)   

##Compilation
The program can be compiled by using the following command:
make (make -f Makefile)

An executable called "quadris" will be produced.
 
####Note: that the proper XLib is necessary for compilation. Please refer to the makefile for more information.####

##Commands:

1. left
Moves the current block one cell to the left. If this is not possible (left edge of the board, or block in the way), the command has no effect.
2. right
As above, but to the right.
3. down
As above, but one cell downward.
4.  clockwise
Rotates the block 90 degrees clockwise, as described earlier. If the rotation cannot be accomplished without coming into contact with existing blocks, the command has no effect
5. counterclockwise
As above, but counterclockwise.
6. drop
Drops the current block. It is (in one step) moved downward as far as possible until it comes into contact with either the bottom of the board or a block. This command also triggers the next block to appear. Even if a block is already as far down as it can go (as a result of executing the down command), it still needs to be dropped in order to get the next block.
7. levelup
Increases the difficulty level of the game by one. The block showing as next still comes next, but subsequent blocks are generated using the new level. If there is no higher level, this command has no effect.
8. leveldown
Decreases the difficulty level of the game by one. The block showing as next still comes next, but subsequent blocks are generated using the new level. If there is no lower level, this command has no effect.
9. restart
Clears the board and starts a new game.

##Command-line Interface:
Your program should support the following options on the command line:   
 * -text
runs the program in text-only mode. No graphics are displayed. The default behaviour (no -text) is to show both text and graphics.
 * -seed xxx
sets the random number generator�s seed to xxx. If you don�t set the seed, you always get the same random sequence every time you run the program. It it good for testing, but not much fun.
 * -scriptfile xxx   
Uses xxx instead of sequence.txt as a source of blocks for level 0.
 * -startlevel n
Starts the game in level n. The game starts in level 0 if this option is no supplied.
 * -lifemode
plays the game in life mode
 * -setlife x
set the lives in the game to be x. If x is greater than 3, the number of lives is 3, if x is less than 0, the number of lives is 1 instead; this command is not effective when the game was not played in life-mode

##Extra Feature:

 * Skip block
Once a block has appeared, you can either decide use that block or skip that block. If you want to skip it, just type 'skip' in the command line.
 * Life-mode
The game can be played in Life-mode which gives the player maximum 3 lives per game.
