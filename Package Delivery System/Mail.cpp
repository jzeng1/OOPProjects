
/*****************************************
 ** File:    Mail.cpp
 ** Project: Delivery, Spring 2018
 ** Author:  Jason Zeng
 ** Date:    4/23/2018
 ** Section: 22
 ** E-mail:  Jzeng1@umbc.edu
 **
 **   This program is the base class cotaining
 **   the methods and member variable that the Mail type
 **   are able to use.
 **
 ***********************************************/

#include "Mail.h"

// Default Constructor
// Preconditions: None
// Postconditions: None
Mail::Mail(){

}

// Overloaded Constructor
// Preconditions: Valid inputs
// Postconditions: None
Mail::Mail(int theCarrier, string theSender, string theRecipient, float theSize, float theBaseCost){
  m_carrier = theCarrier;
  m_sender = theSender;
  m_recipient = theRecipient;
  m_size = theSize;
  m_baseCost = theBaseCost;
}

// getCarrier() - returns the type of the carrier
// Preconditions: m_carrier is set
// Postconditions: returns an int reffering to which carrier
int Mail::getCarrier(){
  return m_carrier;
}

// getSender() - returns the sender of the mail
// Preconditions: m_sender is set
// Postconditions: returns a string of the sender
string Mail::getSender(){
  return m_sender;
}

// getRecipient() - returns the recipient of the mail
// Preconditions: m_recipient is set
// Postconditions: returns a string of the recipient
string Mail::getRecipient(){
  return m_recipient;
}

// getSize() - returns the size of the Mail
// Preconditions: m_size is set
// Postconditions: returns a float
float Mail::getSize(){
  return m_size;
}

// getBaseCost() - returns the base cost of the mail
// Preconditions: m_baseCost is set
// Postconditions: returns a float
float Mail::getBaseCost(){
  return m_baseCost;
}

// operator<<(ostream&, Mail&) - overload the << operator to handle a Mail object
// Preconditions: a valid ostream and Mail operator
// Postconditions: returns an ostream object
ostream& operator<<(ostream &theOutput, Mail &mailObj){

  theOutput << mailObj.toString() << endl;

  theOutput << "To: " << mailObj.getRecipient() << endl;
  theOutput << "From: " << mailObj.getSender() << endl;

  if(mailObj.toString() == "PACKAGE"){
    theOutput << "Weight: " << mailObj.getSize() << " lbs" << endl;
  }

  if(mailObj.toString() == "LETTER"){
    theOutput << "Weight: " << mailObj.getSize() << " square inches" << endl;
  }

  theOutput << "---------------------------" << endl;
  theOutput << "---------------------------" << endl;
  
  return theOutput;
}
