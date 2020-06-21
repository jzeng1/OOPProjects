/*****************************************
 ** File:    Ship.cpp
 ** Project: StarWars
 ** Author:  Jason Zeng
 ** Date:    5/08/2018
 ** Section: 22
 ** E-mail:  Jzeng1@umbc.edu
 **
 **   This is a parent calss with simple constructor
 **   setters, getters , and a purely virtual attack 
 **   function. 
 **
 ***********************************************/

#include "Ship.h"
 
Ship::Ship(string name,string type,int attack, int defense){
  m_name = name;
  m_type = type;
  m_attack = attack;
  m_defense = defense;
}

// Name: Getters and Setters
// Preconditions: Must have a ship
// Postconditions: Either sets or gets part of class
string Ship::getName(){
  return m_name;
}
void Ship::setName(string name){
  m_name = name;
}
string Ship::getType(){
  return m_type;
}
void Ship::setType(string type){
  m_type = type;
}
int Ship::getAttack(){
  return m_attack;
}
void Ship::setAttack(int attack){
  m_attack = attack;
}
int Ship::getDefense(){
  return m_defense;
}
void Ship::setDefense(int defense){
  m_defense = defense;
}

// operator<<(ostream&, Ship&) - overload the << operator to handle a Ship object
// Preconditions: a valid ostream and Ship operator (calls toString)
// Postconditions: returns an ostream object
ostream& operator<<(ostream& os, Ship& b){

  b.toString(os);

  return os;
}
