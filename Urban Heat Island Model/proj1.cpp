/****************************************************
 **File: proj1.cpp
 **Author: Jason Zeng
 **Date: 2/10/2018
 **Section: 22
 **E-mail: jzeng1@umbc.edu
 **
 **This program develop a grid system to model how much
 **an urban heat island might affect the temperature of
 **a city. We will use two-dimensional arrays to store 
 **the information.
 **
 ******************************************************/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>

using namespace std;

//Constants
const int MAX_ROW = 5;
const int MAX_COL = 6;
const double RURAL_LAND = 1.01;
const double SUB_RESIDENTIAL = 1.03;
const double COMMERCIAL_LAND = 1.05;
const double URBAN_RESIDENTIAL = 1.04;
const double DOWN_TOWN = 1.09;
const double THE_PARK = 1.02;
const double RURAL_FARMLAND = 1;
const int MAX_TEMP = 134;
const int MIN_TEMP = -130;

//Function Prototype
int userChoice();

int displayTemp(string letterTemp[MAX_COL][MAX_ROW]);

int displayLand(string letterArrays[MAX_COL][MAX_ROW]);

void modelTemp(string letterArray[MAX_COL][MAX_ROW]);

int main(){

  int userNumber = 0;

  string fileName;
  string letterArray[MAX_COL][MAX_ROW];

  //set variable for every columns from the txt file
  string firstCol;
  string secondCol;
  string thirdCol;
  string fourCol;
  string fifthCol;

  //this is used as a counter to go through the 2d array.
  int countRow = 0;
  int countCol = 0;

  //Greatings
  cout << "Welcome to the Urban Heat Island Model" << endl;
  
  do{
    userChoice();
    cin >> userNumber;
    
    //Check validation from the userChoice 
    while ((userNumber < 1) || (userNumber > 3)){
      cout << "That is not a valid option" << endl;
      cout << "Which option would you like to choice? ";
      cin >> userNumber;
    }
    
    switch(userNumber){
    case 1:

      if(true){

	cout << "What is the name of the file to import?" << endl;
	cin >> fileName;
	
	ifstream myFile (fileName.c_str());
	
	if(myFile.is_open()){
	  
	  cout << "File Successfully Loaded!" << endl;
	  cout << endl;
	
	  //This stores the data inside the txt file to a 2d Array
	  while(myFile >> firstCol && countCol < MAX_COL){
	    
	    myFile >> secondCol >> thirdCol >> fourCol >> fifthCol;
	    
	    letterArray[countCol][0] = firstCol;
	    letterArray[countCol][1] = secondCol;
	    letterArray[countCol][2] = thirdCol;
	    letterArray[countCol][3] = fourCol;
	    letterArray[countCol][4] = fifthCol;
	    
	    countCol++;
	  }
	  
	}else{
	  cout << "The file " << fileName << " was not opened!" << endl;
	}
	
	myFile.close();
	displayLand(letterArray);
      }
      break;

    case 2:
      modelTemp(letterArray);
      break;
      
    case 3:
      cout << "Thank You for Using the Uran Heat Island Model!" << endl;
      break;
    }

    //program ends when the user enter 3 to exit
  }while(userNumber != 3); 

  
  
}   

//This functoin displays the user choices from the menu, it doesnt take in anything.
int userChoice(){
  
  cout << "What would you like to do?" << endl;
  cout << "1. Load Land Cover File" << endl;
  cout << "2. Model Temperatures Based on Land Cover" << endl;
  cout << "3. Exit" << endl;

}

//This function takes in a double 2d array and cout the content in the array displaying the temperature.
int displayTemp(double tempArray[MAX_COL][MAX_ROW]){
  
  //iterating throught the array and printing out it contents with the proper formating using the setw(0 function with the setprecision().
  for(int i = 0; i < MAX_COL; i++){
    cout << setw(10) << fixed << setprecision(1) << tempArray[i][0] << setw(8) << fixed << setprecision(1) << tempArray[i][1] << setw(8) << fixed << setprecision(1) << tempArray[i][2] << setw(8) << fixed << setprecision(1) << tempArray[i][3] << setw(8) << fixed << setprecision(1) << tempArray[i][4] << endl;
  }
  cout << endl;
  
}


//This function takes in a string 2d array and cout the content in the array displaying the landscape.
int displayLand(string letterArrays[MAX_COL][MAX_ROW]){

  //iterating through the array and printing out it contents with the proper formating using the setw() function.
  for(int i = 0; i < MAX_COL;i++){
    cout << setw(10) << letterArrays[i][0] << setw(2) << letterArrays[i][1] << setw(2) << letterArrays[i][2] << setw(2) << letterArrays[i][3] << setw(2) << letterArrays[i][4] << endl;
  }

  cout << endl;

}
  
//This function takes in a string 2d array does the calulation that correspond to the correct landscape.
void modelTemp(string letterArray[MAX_COL][MAX_ROW]){
  
  int baseTemp = 0;
  double baseTotal = 0;
  double tempArray[MAX_COL][MAX_ROW];
  
  cout << "What is the base temperature?" << endl;
  cin >> baseTemp;
  
  //Check validation the temp that the user input cant be under -130 or greater than 134.
  while(baseTemp < MIN_TEMP || baseTemp > MAX_TEMP){
    cout <<"The valid you enter is invalid must be between -130 to 134!" << endl;
    cout << "What is the base temperature?" << endl;
    cin >> baseTemp;
    }

  //iterate throught the tempArray seting values corresponding to the type of landscape.
  for(int i = 0; i < MAX_COL; i++){
    for(int j = 0; j < MAX_ROW; j++){

      //the basetemp is user input multiplied by set value of the landscape.
      //it goes for the same for the code in the bottom.
      if(letterArray[i][j] == "R"){
	baseTotal = baseTemp * RURAL_LAND;
	tempArray[i][j] = baseTotal;

      }else if(letterArray[i][j] == "S"){
	baseTotal = baseTemp * SUB_RESIDENTIAL;
        tempArray[i][j] = baseTotal;
	
      }else if(letterArray[i][j] == "C"){
	baseTotal = baseTemp * COMMERCIAL_LAND;
        tempArray[i][j] = baseTotal;

      }else if(letterArray[i][j] == "U"){
	baseTotal = baseTemp * URBAN_RESIDENTIAL;
        tempArray[i][j] = baseTotal;

      }else if(letterArray[i][j] == "D"){
        baseTotal = baseTemp * DOWN_TOWN;
        tempArray[i][j] = baseTotal;

      }else if(letterArray[i][j] == "P"){
        baseTotal = baseTemp * THE_PARK;
        tempArray[i][j] = baseTotal;
	
      }else if(letterArray[i][j] == "F"){
        baseTotal = baseTemp * RURAL_FARMLAND;
        tempArray[i][j] = baseTotal;
      }
    }
  }
  
  //function call to display the tempArray.
  displayTemp(tempArray);
}  


