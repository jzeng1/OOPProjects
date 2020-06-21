
/*****************************************
 ** File:    driver.cpp
 ** Project: Shipping
 ** Author:  Jason Zeng
 ** Date:    4/12/2018
 ** Section: 22
 ** E-mail:  jzeng1@umbc.edu
 **
 **  This is the main control of the program of how
 **  it runs.
 **
 ***********************************************/

#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

#include "MailHouse.h"
#include "Carrier.h"
#include "Mail.h"
#include "Ups.h"
#include "FedEx.h"
#include "Letter.h"
#include "Package.h"


int failed(){
    cout << "Failed. Exitting..." << endl << endl;
    return 0;
}

int main(int argv, char* argc[]){
    if(argv != 2){
      cout << "Invalid number of parameters..." << endl;
      return -1;
    }
    
    MailHouse m;
    cout << "Loading file: " << argc[1] << endl << endl;
    if(!m.loadMail(argc[1])){
      m.cleanUp();
      return failed();
    }
    cout << "SUCCESS" << endl << endl;
    
    cout << "Filling carriers...." << endl << endl;
    if(!m.fillCarriers()){
      m.cleanUp();
      return failed();
    }
    cout << "SUCCESS" << endl << endl;
    
    cout << "Delivering...." << endl << endl;
    if(!m.deliverMail()){
      m.cleanUp();
      return failed();
    }
    cout << "SUCCESS" << endl << endl;

    cout << "Cleaning up the carriers....." << endl << endl;
    m.cleanUp();

    cout << "Simulation success. Have a nice day!" << endl;
    return 0;
}
