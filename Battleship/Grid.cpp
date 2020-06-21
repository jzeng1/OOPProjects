/*****************************************
 ** File:    Grid.cpp
 ** Project: BattleShip, Fall 2017
 ** Author:  Jason Zeng
 ** Date:    11/6/2017
 ** Section: 10
 ** E-mail:  jzeng1@umbc.edu
 **
 **   This file contains the class header of the Grid class
 **   this class is resposible for keeping track of all
 **   spaces on the board and their current state
 **
 ***********************************************/

#include <string>
#include <fstream>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>

#include "Grid.h"

using namespace std;

const static char EMPTY_SPACE = '.';
const static char OCCUPIED_SPACE = '#';
const static char THE_MISS = 'O';
const static char THE_HIT = 'X';


// Name: Grid() Default Constructor
// Preconditions -
// Postconditions - Constructor for the grid
Grid::Grid(){
  //This creates an empty Grid just in case for some reason the default constructor gets called.
  for(int i = 0; i < SIZE; i++){
    for(int j = 0; j < SIZE; j++){
      m_grid[i][j] = EMPTY;
    }
  }
}

// Name: Grid (file name) - Overloaded Constructor
// Preconditions - Have file name with valid input
// Postconditions - Constructor to build grid with ship locations from file
Grid::Grid(string file){
  
  int lengthShip,startingCol,startingRow = 0;
  char thePosition;

  //Opens the txt file
  ifstream myFile (file.c_str());

  //Iterate through the array and set all values to Zero.
  for(int i = 0; i < SIZE; i++){
    for(int j = 0; j < SIZE; j++){
      m_grid[i][j] = EMPTY;
    }
  }

  //Open the txt file set the values for each the lengthShip, startingCol etc.
  while (myFile >> lengthShip){

    myFile >> startingCol >> startingRow >> thePosition;

    //Sets the value of the starting row and starting col to 1 because there
    //is a ship occupied in that location.
    m_grid[startingRow][startingCol] = OCCUPIED;
    
    //Checks the position of the ship
    if (thePosition == HORIZONTAL){

      //Goes Horizontal
      for(int i = 0; i < lengthShip; i++){
	m_grid[startingRow][startingCol + i] = OCCUPIED;
      }

    }else if(thePosition == VERTICAL){

      //Goes Vertical
      for(int i = 0; i < lengthShip; i++){
        m_grid[startingRow + i][startingCol] = OCCUPIED;
      }
    }
  }

  //closes the file
  myFile.close();
}


// Name: alreadyTried(int, int)
// Preconditions - Have a grid with data
// Postconditions - Returns true if location has already been checked (returned MISS)
bool Grid::alreadyTried(int x, int y){
  if ((m_grid[x][y] == HIT || m_grid[x][y] == MISS)){
    return true;
  }else{
    return false;
  } 
}



// Name: isMiss(int, int)
// Preconditions - Have a grid with data
// Postconditions - Returns true if a location is not occupied
bool Grid::isMiss(int x, int y){
  m_grid[x][y] = MISS;
  return true;
}


// Name: attack(int, int)
// Preconditions - Have a grid with data
// Postconditions - Returns integer based on result also checks if occupied
int Grid::attack(int x, int y){

  //checks if that spot has already been changed if it is it does nothing if not then it changes the position to HIT.
  //for the else if it pretty much the same concept.
  if (m_grid[x][y] == OCCUPIED){
    if(alreadyTried(x,y) == false){
      m_grid[x][y] = HIT;
      noOccupiedLeft();
      return HIT;
    }else{
      noOccupiedLeft();
      return HIT;
    }
    
  }else if(m_grid[x][y] == EMPTY){
    if(alreadyTried(x,y) == false){
      isMiss(x,y);
      noOccupiedLeft();
      return EMPTY;
    }else{
      noOccupiedLeft();
      return EMPTY;
    }
  }
}

// Name: noOccupiedLeft()
// Preconditions - Have a grid with data
// Postconditions - Returns true if no cells in grid have a value of 1 (checks win)
bool Grid::noOccupiedLeft(){
  for(int i = 0; i < SIZE; i++){
    for(int j = 0; j < SIZE; j++){
      if(m_grid[i][j] == 1){
	return false;
      }
    }
  }
  return true;
}

  


// Name: print(bool)
// Preconditions - Have a grid with data
// Postconditions - Prints the grid - parameter toggles if ships are hidden or not
string Grid::print(bool hideShips){
  
  stringstream theCout;
  
  //Board that is hidden
  if(hideShips == false){
    
    cout << "    0 1 2 3 4 5 6 7 8 9" << endl;
    
    for(int i = 0; i < SIZE; i++){
      cout << "  " << i << setw(2);
      
      for(int j = 0; j < SIZE; j++){

	if(m_grid[i][j] == EMPTY){
	  cout << EMPTY_SPACE << " ";

	}else if(m_grid[i][j] == OCCUPIED){
	  cout << EMPTY_SPACE << " ";
	
	}else if(m_grid[i][j] == MISS){
          cout << THE_MISS << " ";

        }else if(m_grid[i][j] == HIT){
          cout << THE_HIT << " ";
        }
	
	//Spacing of the board so it more presentable.
	if ((j + 1) % SIZE == EMPTY){
	  cout << endl;
	}
      }
    }
    
    //Board that is revealed
  }else if(hideShips == true){
    
    //Printing the board
    cout << "    0 1 2 3 4 5 6 7 8 9" << endl;
    
    for(int i = 0; i < SIZE; i++){
      cout << "  " << i << setw(2);
      
      for(int j = 0; j < SIZE; j++){
	
	if (m_grid[i][j] == EMPTY){
          cout << EMPTY_SPACE << " ";
	  
        }else if(m_grid[i][j] == OCCUPIED){
          cout << OCCUPIED_SPACE << " ";
	  
        }else if(m_grid[i][j] == MISS){
	  cout << THE_MISS << " ";
	  
	}else if(m_grid[i][j] == HIT){
	  cout << THE_HIT << " ";
	}
		
	//Spacing of the board so it more presentable.
	if ((j + 1) % SIZE == EMPTY){
	  cout << endl;
	}
      } 
    }
  }

  return theCout.str();
}


