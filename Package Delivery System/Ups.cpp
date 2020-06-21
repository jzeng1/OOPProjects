
/*****************************************
 ** File:    Ups.cpp
 ** Project: Delivery, Spring 2018
 ** Author:  Jason Zeng
 ** Date:    4/23/2018
 ** Section: 22
 ** E-mail:  Jzeng1@umbc.edu
 **
 **  This program is the derived class which inherits from
 **  the Carrier class to implement methods how Ups would
 **  be a function.
 **
 ***********************************************/

#include "Ups.h"

// Constructor
// Preconditions: None
// Postconditions: None
Ups::Ups(){
  

}

// Destructor
// Preconditions: An allocated object in memory
// Postconditions: Deallocates the memory
Ups::~Ups(){
 

}

// deliver() - performs the actions of delivering as a UPS object
// Preconditions: mail present in m_storage
// Postconditions: outputs data and returns a status # (0 - fail, 1 - success)
int Ups::deliver(){
  int checkVector = m_storage.size();
  
  //checks to see if m_storage is not empty so that it can make a delivery
  if(checkVector > 0){
    return 1;
  }

  return 0;
}


ostream& Ups::print(ostream &theOutput) const{
  
  theOutput << "************************" << endl;
  theOutput << "Ups Trucks Contents:" << endl;
  theOutput << endl;
  theOutput << "-----------------------" << endl;
  
  return theOutput;
}
