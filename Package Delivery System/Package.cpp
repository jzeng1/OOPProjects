
/*****************************************
 ** File:    Package.cpp
 ** Project: Delivery, Spring 2018
 ** Author:  Jason Zeng
 ** Date:    4/23/2018
 ** Section: 22
 ** E-mail:  Jzeng1@umbc.edu
 **
 **  This program is the derived class which inherits from
 **  the Mail class to implement methods how Package would
 **  be a function.
 **
 ***********************************************/

#include "Package.h"

// Default Constructor
// Preconditions: None
// Postconditions: None
Package::Package(){

}

// Overloaded Constructor
// Preconditions: valid inputs
// Postconditions: None
Package::Package(int theCarrier, string theSender, string theRecipient, float theSize, float theBaseCost){
  m_carrier = theCarrier;
  m_sender = theSender;
  m_recipient = theRecipient;
  m_size = theSize;
  m_baseCost = theBaseCost;
}

// Destructor
// Preconditions: Allocated object
// Postconditions: Deallocates object from memory
Package::~Package(){

}

// toString() - Converts the Package object to a string object
// Preconditions: A valid Package object
// Postconditions: returns a string representation of a Package
string Package::toString(){

  return "PACKAGE";
}
