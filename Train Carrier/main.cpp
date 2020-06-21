/*  Name :    main.cpp
    Project: CMSC 202 Project 3, Spring 2018
    Project Design: Jason Zeng
    Desc: This file manages the train. Passing the infomation in the txt file to a vector
          then a train object is dynamically allocated passing it information to a linked
	  list.
*/

#include "Car.h"
#include "Train.h"

#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

//Constants
const string THE_BIOLOGICAL = "BIOLOGICAL";
const string THE_POISONOUS = "POISONOUS";
const string THE_COMBUSTIBLE = "COMBUSTIBLE";
const string THE_OXIDIZER = "OXIDIZER";
const string THE_RADIOACTIVE = "RADIOACTIVE";
const string THE_LOCOMOTIVE = "LOCOMOTIVE";
const string THE_CABOOSE = "CABOOSE";
const string THE_ADD = "add";
const string THE_REMOVE = "remove";

//Temp variable that keep tracks of the index of the node that being added.
int theIndexTrain = 0;

//This class is created to storage the infomation to a vector<train> infoTrain.
class Trains{
  int m_trainNumber;
  string m_addRemove, m_cargoType;

public:
  Trains(int train, string addOrRemoves, string cargo){m_trainNumber = train; m_addRemove = addOrRemoves; m_cargoType = cargo;}
  int getTrain(){return m_trainNumber;}
  string getAdd(){return m_addRemove;}
  string getCargo(){return m_cargoType;}
};

int main(int argc, char* argv[]){

  string trainNumber,addOrRemove,theCargoType,theLine;
  int theTrainNumber = 0;

  vector<Trains> infoTrain;

  if(argv[1] > 0){
    cout << "Message Loaded" << endl;
  }else{
    cout << "No text file loaded = try make run1" << endl;
    return 0;
  }

  //open the txt file and reads in.
  ifstream myFile (argv[1]);
  
  if(myFile.is_open()){

    //sperate the delimiter comma from the txt file.
    while(getline(myFile,theLine)){

      stringstream linestream(theLine);

      getline(linestream, trainNumber, ',');
      getline(linestream, addOrRemove, ',');
      getline(linestream, theCargoType, ',');

      //convert the string to an int
      theTrainNumber = atoi(trainNumber.c_str());

      //call the overloaded constructor in the Trains class storage infomation into the vector.
      Trains theinfo(theTrainNumber,addOrRemove,theCargoType);
      infoTrain.push_back(theinfo);

    }

  }else{
    
    //close the file
    myFile.close();
    cout << "The File was not opened properly!" << endl;
  }

  //creating a Train pointer
  Train *theTrain;

  //iterating through the vector 
  for(unsigned int i = 0; i < infoTrain.size(); i++){
    
    //if locomotive create a dynamically allocated Train and if add then it add's to the linked
    //list if remove, then it remove the cargo from the linked list.
    if(infoTrain.at(i).getCargo() == THE_LOCOMOTIVE && infoTrain.at(i).getAdd() == THE_ADD){	
      theTrain = new Train(infoTrain.at(i).getTrain());
      theIndexTrain += 1;
      theTrain->addCar(LOCOMOTIVE,theIndexTrain);
    }
    
    if(infoTrain.at(i).getCargo() == THE_LOCOMOTIVE && infoTrain.at(i).getAdd() == THE_REMOVE){
      theTrain->removeCar(LOCOMOTIVE);
      cout << *theTrain << endl;
    }
      
    //if BIOLOGICAL and add then it add to the linked list of BIOLOGICAL. if remove then it remove 
    //the cargo BIOLOGICAL from the linked list. it goes the same for every cargo to CABOOSE
    //What CABOOSE is doing is when it hit CABOOSE it has reach to the end of the train
    //so what happens is it creates a new train again.
    if(infoTrain.at(i).getCargo() == THE_BIOLOGICAL && infoTrain.at(i).getAdd() == THE_ADD){
      theIndexTrain += 1;
      theTrain->addCar(BIOLOGICAL,theIndexTrain);
    }

    if(infoTrain.at(i).getCargo() == THE_BIOLOGICAL && infoTrain.at(i).getAdd() == THE_REMOVE){
      theTrain->removeCar(BIOLOGICAL);
      cout << *theTrain << endl;
    }
  
    if(infoTrain.at(i).getCargo() == THE_POISONOUS && infoTrain.at(i).getAdd() == THE_ADD){
      theIndexTrain += 1;
      theTrain->addCar(POISONOUS,theIndexTrain);
    }
    
    if(infoTrain.at(i).getCargo() == THE_POISONOUS && infoTrain.at(i).getAdd() == THE_REMOVE){
      theTrain->removeCar(POISONOUS);
      cout << *theTrain << endl;
    }
    
    if(infoTrain.at(i).getCargo() == THE_COMBUSTIBLE && infoTrain.at(i).getAdd() == THE_ADD){
      theIndexTrain += 1;
      theTrain->addCar(COMBUSTIBLE,theIndexTrain);
    }
    
    if(infoTrain.at(i).getCargo() == THE_COMBUSTIBLE && infoTrain.at(i).getAdd() == THE_REMOVE){
      theTrain->removeCar(COMBUSTIBLE);
      cout << *theTrain << endl;
    }    
    
    if(infoTrain.at(i).getCargo() == THE_OXIDIZER && infoTrain.at(i).getAdd() == THE_ADD){
      theIndexTrain += 1;
      theTrain->addCar(OXIDIZER,theIndexTrain);
    }

    if(infoTrain.at(i).getCargo() == THE_OXIDIZER && infoTrain.at(i).getAdd() == THE_REMOVE){
      theTrain->removeCar(OXIDIZER);
      cout << *theTrain << endl;
    }
    
    if(infoTrain.at(i).getCargo() == THE_RADIOACTIVE && infoTrain.at(i).getAdd() == THE_ADD){
      theIndexTrain += 1;
      theTrain->addCar(RADIOACTIVE,theIndexTrain);
    }
    
    if(infoTrain.at(i).getCargo() == THE_RADIOACTIVE && infoTrain.at(i).getAdd() == THE_REMOVE){
      theTrain->removeCar(RADIOACTIVE);
      cout << *theTrain << endl;
    }
    
    if(infoTrain.at(i).getCargo() == THE_CABOOSE && infoTrain.at(i).getAdd() == THE_ADD){
      theIndexTrain += 1;
      theTrain->addCar(CABOOSE,theIndexTrain);

      if(infoTrain.at(i).getTrain() != 3333){
	cout << *theTrain << endl;
      }
    }
    
    if(infoTrain.at(i).getCargo() == THE_CABOOSE && infoTrain.at(i).getAdd() == THE_REMOVE){
      theTrain->removeCar(CABOOSE);
      cout << *theTrain << endl;
    }
  }
  
  theTrain = NULL;
}
