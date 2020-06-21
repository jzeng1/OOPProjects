/*****************************************
 ** File:    Computer.cpp
 ** Project: BattleShip, Fall 2017
 ** Author:  Jason Zeng
 ** Date:    11/6/2017
 ** Section: 10
 ** E-mail:  Jzeng1@umbc.edu
 **
 **   This file contains the header file of the Computer class
 **   this class is a child of Player and  outlines what
 **   a CPU or AI player can do in the game of battleship.
 **
 ***********************************************/

#include <iostream> 
#include <ctime>

#include "Grid.h"
#include "Player.h"
#include "Computer.h"


const static int SIZE = 10;
const static int EMPTY = 0;
const static int OCCUPIED = 1;
const static int HIT = 3;
const static int MISS = 2;

using namespace std;

// Name: Computer (Default Constructor)
// Preconditions - None
// Postconditions - Creates computer player
Computer::Computer(){
  m_xLast = -1;
  m_yLast = -1;
  //Creates a dynamically allocated Grid
  m_grid = new Grid();

}


// Name: Computer (Overloaded Constructor)
// Preconditions - None
// Postconditions - Creates computer player with file name
Computer::Computer(string file){

  //Creates a dynamically allocated Grid
  m_grid = new Grid(file);

}


// Name: makeMove()
// Preconditions - grid is already created
// Postconditions - Makes an educated guess for next place to fire for computer
// **This function should be more thoughtful than just two random numbers**
void Computer::makeMove(Grid* grid){
  
  //this is to allow random to be random every time the program runs.
  srand(time(NULL));
  srand(rand());

  //the rand() has a range between 0-10
  m_xCenter = rand() % SIZE;
  m_yCenter = rand() % SIZE;

  
  //if there's a 3, choose randomly top left right bottom
  int rng = -1;
  
  if (m_xLast != -1 && m_yLast != -1){
  rng = rand() % 4;
  m_xCenter = m_xLast;
  m_yCenter = m_yLast;

    //Checks the top
    if (rng == EMPTY){
      m_yCenter--;
      if (m_yCenter > -1)
	grid->attack(m_xCenter, m_yCenter);
      else {
	m_yCenter += MISS;
	grid->attack(m_xCenter, m_yCenter);
      }
    }

    //Checks the right
    else if (rng == OCCUPIED){
      m_xCenter++;
      if (m_xCenter < SIZE)
	grid->attack(m_xCenter, m_yCenter);
      else {
	m_xCenter -= MISS;
	grid->attack(m_xCenter, m_yCenter);
      }
    }

    //Checks the bottom
    else if (rng == MISS){
      m_yCenter--;
      if (m_yCenter < SIZE)
	grid->attack(m_xCenter, m_yCenter);
      else{
	m_yCenter+= MISS;
	grid->attack(m_xCenter, m_yCenter);
      }
    }

    //Checks the left
    else if (rng == HIT){
      m_xCenter--;
      if (m_xCenter > -1)
	grid->attack(m_xCenter, m_yCenter);
      else{
	m_xCenter += MISS;
	grid->attack(m_xCenter, m_yCenter);
      }
    }
    
  }

  else{
    grid->attack(m_xCenter,m_yCenter);
  }

  if(grid->attack(m_xCenter,m_yCenter) == HIT){
    cout << "User Ship has been Hit!" << endl;
    m_xLast = m_xCenter;
    m_yLast = m_yCenter;
  }else{
    cout << "Computer Missed!" << endl;
  }
}


// Name: printBoard
// Preconditions - Board exists
// Postconditions - Prints the computer's board
void Computer::printBoard(){
  
  //I set the hideShips to false because the computer board is always hidden from the player.
  bool hideShips = false;
  cout << "    *****COMPUTER*****" << endl;
  m_grid->print(hideShips);
}
