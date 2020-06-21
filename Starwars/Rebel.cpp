/*****************************************
 ** File:    Rebel.cpp
 ** Project: StarWars
 ** Author:  Jason Zeng
 ** Date:    5/08/2018
 ** Section: 22
 ** E-mail:  Jzeng1@umbc.edu
 **
 **   This is the subclasses to ships which manages
 **   the attack and display if the object is either a
 **   rebel or imperial.
 **
 ***********************************************/

#include "Rebel.h"

// Name: Attack (inherited from Ship)
// Preconditions: Requires valid enemy ship
// Postconditions: Compares Rebel attack to Imperial defense
// Returns 1 if destroyed or 0 if damaged
bool Rebel::attack(Ship* enemy){

  int theTotalDefense = 0;

  theTotalDefense = enemy->getDefense() - getAttack();
  enemy->setDefense(theTotalDefense);

  if(getAttack() < enemy->getDefense()){
    return 0;
  }

  if(enemy->getDefense() <= 0){
    return 1;
  }

  return 0;
}

// Name: toString() - method to format a rebel
// Preconditions: A rebel object
// Postconditions: returns the rebel object as a ostream object
ostream& Rebel::toString(ostream& os){

  os << " Rebel ";

  return os;
}


