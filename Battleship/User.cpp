/*****************************************
 ** File:    User.cpp
 ** Project: BattleShip, Fall 2017
 ** Author:  Jason Zeng
 ** Date:    11/06/2017
 ** Section: 10
 ** E-mail:  jzeng1@umbc.edu
 **
 **   This file contains the header file of the User class
 **   this class is a child of Player and  outlines what
 **   a human user can do in the game of battleship.
 **
 ***********************************************/

#include <iostream>

#include "Grid.h"
#include "Player.h"
#include "User.h"

//This is for the makeMove function 
const static int HIT = 3;

using namespace std;

// Name: User (Default Constructor)
// Preconditions - None
// Postconditions - None
User::User(){

  //Creates a dynamically allocated Grid
  m_grid = new Grid();

}



// Name: User (Overloaded Constructor)
// Preconditions - None
// Postconditions - None
User::User(string file){

  //Creates a dynamically allocated Grid
  m_grid = new Grid(file);

}


// Name: makeMove(grid)
// Preconditions - None
// Postconditions - Checks if move (x,y) hits or misses (or if already checked)
void User::makeMove(Grid* grid){
  
  int theRow,theCol = 0;
  
  //This ask the user input of column and row they want to attack
  cout << endl;
  cout << "Enter square to attack:" << endl;

  cout << "Enter x (column): ";
  cin >> theCol;
  cout << "Enter y (row): ";
  cin >> theRow;

  grid->attack(theRow,theCol);

  //if the attack in grid equal to 3 which is HIT then it cout the IT has been hit prompt.
  if(grid->attack(theRow,theCol) == HIT){
    cout << "Computer Ship has been HIT!" << endl;
  }else{
    cout << "You Missed!" << endl;
  }   
}



// Name: printBoard
// Preconditions - User's grid exists
// Postconditions - Displays the users grid
void User::printBoard(){
  
  //This is set to true beacuse the user board is always displayed.
  bool hideShips = true;
  cout << "    *******USER*******" << endl;
  m_grid->print(hideShips);
}

