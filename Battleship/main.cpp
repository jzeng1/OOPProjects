/*****************************************
 ** File:    main.cpp
 ** Project: BattleShip, Fall 2017
 ** Author:  Jason Zeng
 ** Date:    11/6/2017
 ** Section: 10
 ** E-mail:  jzeng1@umbc.edu
 **
 **  This is the main control of the program of how 
 **  it runs.
 **
 ***********************************************/

#include <iostream>
#include <string>

#include "Grid.h"
#include "User.h"
#include "Player.h"
#include "Computer.h"
 
using namespace std;

int main(int argc, char* argv[]){
  
  cout << "Welcome to UMBC Battleship" << endl;

  if((argv[1] > 0) || (argv[2] > 0)){
    cout << "Ships Loaded" << endl;
  }else{
    cout << "Both of the txt file Was not loaded. Please Try again!" << endl;
  }
  
  //Creates the object for both Computer and User.
  Computer theComputer(argv[1]);
  User theUser(argv[2]);
  
  //Creating the Player object 
  Player* play1 = &theComputer;
  Player* play2 = &theUser;

  //These print the board both computer and user.
  theComputer.printBoard();
  cout << endl;
  theUser.printBoard();
  cout << endl;
  
  //the while loop will end if all the ships are hit 
  while((play1->Player::hasLost() != true) && (play2->Player::hasLost() != true)){
					       
    //Passing the user board to the computer
    theComputer.makeMove(play2->getGrid());
    theUser.printBoard();

    //Passing the computer board to the user
    theUser.makeMove(play1->getGrid());
    theComputer.printBoard();

    //who ever destroy the all the ship first wins.
    if (play1->Player::hasLost() == true){
      cout <<"You Won!" << endl;

    }else if (play2->Player::hasLost() == true){
      cout <<"You Lost!" << endl;
    }

  }
}
