
/*****************************************
 ** File:    Letter.cpp
 ** Project: Delivery, Spring 2018
 ** Author:  Jason Zeng
 ** Date:    4/23/2018
 ** Section: 22
 ** E-mail:  Jzeng1@umbc.edu
 **
 **  This program is the derived class which inherits from
 **  the Mail class to implement methods how Letter would
 **  be a function.
 **
 ***********************************************/

#include "Letter.h"

// Default Constructor
// Preconditions: None
// Postconditions: None
Letter::Letter(){


}

// Overloaded Constructor
// Preconditions: Valid inputs
// Postconditions: None
Letter::Letter(int theCarrier, string theSender, string theRecipient, float theSize, float theBaseCost){
  m_carrier = theCarrier;
  m_sender = theSender;
  m_recipient = theRecipient;
  m_size = theSize;
  m_baseCost = theBaseCost;
}
  

// Destructor
// Preconditions: A letter object allocated in memory
// Postconditions: Deallocates the object in memory
Letter::~Letter(){
  

}

// toString() - method to format the Letter object as a string
// Preconditions: A Letter object
// Postconditions: returns the letter object as a string
string Letter::toString(){
  
  return "LETTER";
}
