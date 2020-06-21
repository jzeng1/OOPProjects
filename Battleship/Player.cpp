/*****************************************
 ** File:    Player.cpp
 ** Project: BattleShip, Fall 2018
 ** Author:  Jason Zeng
 ** Date:    11/06/2017
 ** Section: 10
 ** E-mail:  jzeng1@umbc.edu
 **
 **   This file contains the header file of the Player class
 **   this class outlines the basics of what a player in
 **   a game of battleship can do.
 **
 ***********************************************/

#include <iostream> 
#include "Grid.h"
#include "Player.h"

using namespace std;

// Name: Player (Default Constructor)
// Preconditions - None
// Postconditions - Constructor that builds a new grid

// This is an abstract class there is no need for me to create a new grid
// this will create more memory leaks and also the new grid is being called 
// in the child class.
Player::Player(){
}


// Name: Player (Overloaded Constructor)
// Preconditions - File exists
// Postconditions - Constructor that builds a new grid based on a file

// This is an abstract class there is no need for me to create a new grid 
// this will create more memory leaks and also thr new grid is being called
// in the child class.
Player::Player(string file){ 
}



// Name: ~Player (Destructor)
// Preconditions - Player was dynamically allocated
// Postconditions - Deletes dynamically allocated player
Player::~Player(){
  //deleting m_grid to prevent memory leaks
  delete m_grid;
  m_grid = NULL;
}


// Name: hasLost()
// Preconditions - Grid is populated
// Postconditions - Checks to see if there are any "occupied" spaces left in grid
bool Player::hasLost(){
  return m_grid->noOccupiedLeft();
}


// Name: getGrid()
// Preconditions - Grid exists
// Postconditions - Returns a Grid pointer
Grid* Player::getGrid(){
  return m_grid;
}



// Name: printBoard()
// Preconditions - Grid exists
// Postconditions - Prints current grid with ships not hidden
void Player::printBoard(){
  m_grid->print(true);
}

