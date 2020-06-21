
/*****************************************
 ** File:    MailHouse.cpp
 ** Project: Delivery, Spring 2018
 ** Author:  Jason Zeng
 ** Date:    4/23/2018
 ** Section: 22
 ** E-mail:  Jzeng1@umbc.edu
 **
 **   This programs manages the loading, sorting,
 **   calling for deliveries and cleaning here. 
 **   by checking validation if it is sucessful or not.
 **
 ***********************************************/

#include "MailHouse.h"
#include <sstream>
#include <cstdlib>
#include <iomanip>

// Constructor
// Preconditions: None
// Postconditions: None
MailHouse::MailHouse(){

  //creating object pointers for both ups and fedex pushing back the object
  Carrier *upsObj = new Ups();
  m_carriers.push_back(upsObj);

  Carrier *fedExObj = new FedEx();
  m_carriers.push_back(fedExObj);
  
}

// loadMail(char*) - loads the file and sets any data from the file
// Preconditions: a valid filepath
// Postconditions: Loads m_mail. Returns int for status (1 - success, 0 - fail)
int MailHouse::loadMail(char* loadMail){
 
  string loadMails = loadMail;
  
  string upsCapacity,fedExCap,upsSpeed,fedSpeed,letterBase,packageBase;

  string firstLine,theLine,upsOrFedEx,letterOrPackage,theSender,theReceiver,theWeight;

  int theUpsOrFedEx,theLetterOrPackage,theUpsCap,theFedExCap;

  float theWeights,theUpsSpeed,theFedSpeed,theLetterBase,thePackageBase;

  //opens the file 
  fstream myFile (loadMails.c_str());
    
  //Checks if the file has been open
  if(myFile.is_open()){

    //taking the first line of the txt file and spliting them to individual variables
    myFile >> upsCapacity >> fedExCap >> upsSpeed >> fedSpeed >> letterBase >> packageBase;
    
    theUpsCap = atoi(upsCapacity.c_str());
    theFedExCap = atoi(fedExCap.c_str());
    theUpsSpeed = atof(upsSpeed.c_str());
    theFedSpeed = atof(fedSpeed.c_str());
    theLetterBase = atof(letterBase.c_str());
    thePackageBase = atof(packageBase.c_str());

    //Skip the first line goes to the next line
    getline(myFile,firstLine);

    //set variables of the next line by the delimiter.
    while(getline(myFile, theLine)){
     
      stringstream linestream(theLine);
      
      getline(linestream, upsOrFedEx, ',');
      getline(linestream, letterOrPackage, ',');
      getline(linestream, theSender, ',');
      getline(linestream, theReceiver, ',');
      getline(linestream, theWeight, ',');
   
      theUpsOrFedEx = atoi(upsOrFedEx.c_str());
      theLetterOrPackage = atoi(letterOrPackage.c_str());
      theWeights = atof(theWeight.c_str());
      
      //Create an dynamically alocated object Letter pushing the elements to m_mail.
      if(theLetterOrPackage == 0){
	Letter *infoMail = new Letter(theUpsOrFedEx,theSender,theReceiver,theWeights,theLetterBase);
	m_mail.push_back(infoMail);
      }

      //Create an dynamically alocated object Package pushing the elements to m_mail.
      if(theLetterOrPackage == 1){
	Package *infoMail = new Package(theUpsOrFedEx,theSender,theReceiver,theWeights,thePackageBase);
        m_mail.push_back(infoMail);
      }
      
    }

    //set the rate and the MaxCapacity of the carriers
    m_carriers.at(0)->setMaxCapacity(theUpsCap);
    m_carriers.at(1)->setMaxCapacity(theFedExCap);
    m_carriers.at(0)->setRate(theUpsSpeed);
    m_carriers.at(1)->setRate(theFedSpeed);

    return 1;

  }else{

    //close the file
    myFile.close();
    cout << "The File was not opened properly!" << endl;
    return 0;
  }
      
  return 0;
}

// fillCarriers() - Loads the carrier vectors from the m_mail vectors
// Preconditions: m_mail is populated. m_carriers is populated
// Postconditions: m_carriers have mail in their respective vectors.
// Returns int for status (1 - success, 0 - fail)
int MailHouse::fillCarriers(){

  int itemsUps = 0;
  int itemsFedEx = 0;
  int maxCapacityUps = 0;
  int maxCapacityFedEx = 0;
    
  //inserting elements by iterating through the size of m_mail checking 
  //to see if it ups or fedex then keeping track of how many things 
  //the carrier is holding with itemUps += 1 and itemFedEx += 1.
  for(unsigned int i = 0; i < m_mail.size(); i++){
    if(m_mail.at(i)->getCarrier() == UPS){
      maxCapacityUps = m_carriers.at(0)->insert(m_mail.at(i));
      itemsUps += 1;
    } 
  }
  
  for(unsigned int i = 0; i < m_mail.size(); i++){
    if(m_mail.at(i)->getCarrier() == FEDEX){
      maxCapacityFedEx = m_carriers.at(1)->insert(m_mail.at(i));
      itemsFedEx += 1;
    }
  }

  //Checks validation if either FedEx or Ups carriers are empty then return false
  if(itemsUps == 0 || itemsFedEx == 0){
    return 0;
  }
  
  //if the carriers reach it max capacity then it will fail aswell.
  if(itemsUps > maxCapacityUps || itemsFedEx > maxCapacityFedEx){
    cout << "It has reach Max Capacity for either the Ups or FedEx carriers" << endl;
    cout << "The Program will exit" << endl;
    return 0;
  }

  //Here is to display the letter/packages assigned to the carrier type which is 
  //fedEx or Ups.
  cout << *m_carriers.at(0) << endl;

  for(unsigned int i = 0; i < m_mail.size(); i++){
    if(m_mail.at(i)->getCarrier() == UPS){
      cout << *m_mail.at(i) << endl;
    }
  }

  cout << *m_carriers.at(1) << endl;

  for(unsigned int i = 0; i < m_mail.size(); i++){
    if(m_mail.at(i)->getCarrier() == FEDEX){
      cout << *m_mail.at(i) << endl;
    }
  }

  return 1;
}

// deliverMail() - Send carriers out for delivery
// Preconditions: m_carriers are populated
// Postconditions: m_carriers have cleared their vectors.
// Returns int for status (1 - success, 0 - fail)
int MailHouse::deliverMail(){

  int sizeOfmail = m_mail.size();
  float upsTotals = 0;
  float upsTotal = 0;
  float fedExTotals = 0;
  float fedExTotal = 0;

  //Checks to see if m_storage has been populated and ready for delivery.
  if(m_carriers.at(0)->deliver() == 1){
    
    //iterating the vector backwards so that m_carriers would be clear from
    //the back to the front.
    for(int i = sizeOfmail - 1; i >= 0; i--){
      if(m_mail.at(i)->getCarrier() == UPS){
	cout << "Delivered: " << endl;
	cout << "----------------" << endl;
	cout << *m_mail.at(i) << endl;
	
	//calculation of the delivery are done here. it goes the same from the code in the bottom.
	upsTotals = m_mail.at(i)->getBaseCost() * m_mail.at(i)->getSize() * m_carriers.at(0)->getRate();
	upsTotal += upsTotals;
      }
    }
    
    cout << "Deliveries Completed! UPS total earned: $" << fixed << setprecision(2) << upsTotal << endl;
    cout << endl;
    
    for(int i = sizeOfmail - 1; i >= 0; i--){
      if(m_mail.at(i)->getCarrier() == FEDEX){
	cout << "Delivered: " << endl;
	cout << "----------------" << endl;
	cout << *m_mail.at(i) << endl;
	fedExTotals = m_mail.at(i)->getBaseCost() * m_mail.at(i)->getSize() * m_carriers.at(1)->getRate();
	fedExTotal += fedExTotals;
      }
    }
    
    cout << "Deliveries Completed! FEDEX total earned: $" << fixed << setprecision(2) << fedExTotal << endl;
    cout << endl;
 
    return 1;

  }else{
    return 0;
  }
}

// cleanUp() - Any additional clean up is done here
// Preconditions: Allocated memory
// Postconditions: Deallocates any remaining allocations
int MailHouse::cleanUp(){
  
  //iterating through the vector of both m_mail and m_carriers and deleting every single element 
  //inside the array.
  for(unsigned int i = 0; i < m_mail.size(); i++){
    delete m_mail[i];
  }

  for(unsigned int i = 0; i < m_carriers.size(); i++){
    delete m_carriers[i];
  }
    
  return 1;
}
