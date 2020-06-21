
/*****************************************
 ** File:    FedEx.cpp
 ** Project: Delivery, Spring 2018
 ** Author:  Jason Zeng
 ** Date:    4/23/2018
 ** Section: 22
 ** E-mail:  Jzeng1@umbc.edu
 **
 **  This program is the derived class which inherits from
 **  the Carrier class to implement methods how FedEx would 
 **  be a function.
 **
 ***********************************************/

#include "FedEx.h"

// Constructor
// Preconditions: None
// Postconditions: None
FedEx::FedEx(){

}

// Destructor
// Preconditions: An allocated object in memory
// Postconditions: Deallocates the memory
FedEx::~FedEx(){
 
}

// deliver() - performs the actions of delivering as a FedEx object
// Preconditions: mail present in m_storage
// Postconditions: outputs data and returns a status # (0 - fail, 1 - success)
int FedEx::deliver(){
  int checkVector = m_storage.size();

  //checks to see if m_storage is not empty so that it can make a delivery
  if(checkVector > 0){
    return 1;
  }

  return 0;
}

ostream& FedEx::print(ostream &theOutput) const{

  theOutput << "************************" << endl;
  theOutput << "FEDEX Trucks Contents:" << endl;
  theOutput << endl;
  theOutput << "-----------------------" << endl;

  return theOutput;
}
