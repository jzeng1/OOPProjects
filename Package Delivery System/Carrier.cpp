
/*****************************************
 ** File:    Carrier.cpp
 ** Project: Delivery, Spring 2018
 ** Author:  Jason Zeng
 ** Date:    4/23/2018
 ** Section: 22
 ** E-mail:  Jzeng1@umbc.edu
 **
 **   This program is the base class cotaining
 **   the methods and member variable that the carriers
 **   are able to use. 
 **
 ***********************************************/


#include "Carrier.h"

// Constructor
// Preconditions: None
// Postconditions: None
Carrier::Carrier(){
  
}

// insert(Mail*) - Inserts mail into the vector of Mail*
// Preconditions: A valid Mail pointer. Not at max capacity
// Postconditions: Adds the mail pointer to m_storage
int Carrier::insert(Mail *theInfo){
  m_storage.push_back(theInfo);
  return m_max_capacity;
}

// setMaxCapacity(int) - Sets the max capacity of the Carrier
// Preconditions: a positive int
// Postconditions: m_max_capacity is set
void Carrier::setMaxCapacity(int theMax){
  m_max_capacity = theMax;
}

// setRate(float) - Sets the delivery cost rate of the Carrier
// Preconditions: a positve float
// Postconditions: m_delivery_rate is set
void Carrier::setRate(float theRate){
  m_delivery_rate = theRate;
}

// getCarrier() - returns the type of the delivery rate
// Preconditions: m_delivery_rate is set
// Postconditions: returns an flaot reffering to which carrier
float Carrier::getRate(){
  return m_delivery_rate;
}

// operator<<(ostream&, const Carrier&) - Allows the << operator to be
// used on a Carrier object
// Preconditions: valid ostream and Carrier objects
// Postconditions: returns ostream
ostream &operator<<(ostream &theOutput, const Carrier &carrierObj){
  
  //Called the print object in the derived class.
  carrierObj.print(theOutput);

  return theOutput;
}
