/****************************************************
**File: proj1.cpp
**Author: Jason Zeng
**Date: 9/17/2017
**Section: 10
**E-mail: jzeng1@umbc.edu
**
** This program is a self- service snack bar that reads in the list
** of products available from the text file. The user then can 
** select an item and decide the quantity amount of the time it 
** was purchase. The total amount is then calculated with the tax 
** of 6%. The entire order is then given a sequential order number
** and stored in one text file per order.
**
**
******************************************************/

#include <iostream>
#include <fstream> //Note: This is used to open/close and read a file
#include <string> //Note: This is to allow me to use string
#include <iomanip> //Note: This is for the formating of the menu
#include <cstdlib> //Note: This is to convert string to a double

using namespace std;

//Constants
const int NUM_ITEMSROWS = 10;
const int NUM_ITEMSCOL = 2;
const int SIZE_RECEIPTARRAY = 3; 
const double TAX_RATE = 0.06;

//Prototype of a function

//--------------------------------------------------------------------------//
//Name: userChoice()
//PreCondition: display the menu option.
//PostCondition: return an integer of userChoiceNum from the user.
//--------------------------------------------------------------------------//
int userChoice();

//----------------------------------------------------------------------------//
//Name: displayMenu()
//PreCondition: display the vending machine menu
//PostCondition: pass two array that are string into the function manageOrder()
//----------------------------------------------------------------------------/z/
void displayMenu();


//----------------------------------------------------------------------------//
//Name: displayChoice()
//PreCondition: takes in a integer of the user choice in userChoice()
//PostCondition: display menu and user input of what items they want to buy
//----------------------------------------------------------------------------//
void displayChoice(int);

//----------------------------------------------------------------------------//
//Name: manageOrder()
//PreCondition: takes in two arrays that are strings
//PostCondition: calculate total price for the items, writing into a txt file,
//               converting the arrays with the price to double.
//----------------------------------------------------------------------------//
void manageOrder(string foodPriceArray[],string foodNameArray[]);

//----------------------------------------------------------------------------//
//Name: writeReceipt()
//PreCondition: takes in values that are storage in save txt file receipt
//PostCondition: opens the value inside the recipt.txt calculate the total of 
//               all the items bought from the user.
//----------------------------------------------------------------------------//
void writeReceipt();

int main(){

  int userChoiceNum = 0;

  //writeReceipt();

  //Greetings
  cout << "The item list was successfully loaded" << endl;
  cout << "Welcome to the True Grit Snack Bar" << endl;
  
  userChoiceNum = userChoice();

  // if the user enter 3 then the while loop will stop and it will end the program
  //try a do while for here cuz it requires that you use one
  while (userChoiceNum != 3){
    switch(userChoiceNum){
    case 1:
      displayChoice(1);
      break;
      
    case 2:
      displayChoice(2);
      break;      
    }
    userChoiceNum = userChoice();
  }
  
  //if the integer 3 is press it will go to this cout statment
  if (userChoiceNum == 3){
    cout << "Thank you for using True Grit Snack Bar" << endl;
  }
}

//--------------------------------------------------------------------------//
//Name: userChoice()
//PreCondition: display the menu option. 
//PostCondition: return an integer of userChoiceNum from the user.
//--------------------------------------------------------------------------//
int userChoice(){

  int userChoiceNum = 0;

  //display menu option
  cout << "What would you like to do?: " << endl;
  cout << "1. New Order" << endl;
  cout << "2. View Receipts" << endl;
  cout << "3. Exit" << endl;

  cin >> userChoiceNum;
  return userChoiceNum;

}

//----------------------------------------------------------------------------//
//Name: displayMenu()
//PreCondition: display the vending machine menu
//PostCondition: pass two array that are string into the function manageOrder()
//----------------------------------------------------------------------------//
void displayMenu(){

  ifstream myFile ("proj1_items.txt");
  
  string foodArray[NUM_ITEMSROWS][NUM_ITEMSCOL];
  string foodPriceArray[NUM_ITEMSROWS];
  string foodNameArray[NUM_ITEMSROWS];
  double foodPriceArrayMenu[NUM_ITEMSROWS];
  string foodName;
  string foodPrice;
  
  int count = 0;
  
  //This is a while loop that allows me to set a delimiter adding data to an array
  while (getline(myFile,foodName,',') && getline(myFile,foodPrice) && count < 20) {
    
    foodArray[count][0] = foodName;
    foodArray[count][1] = foodPrice;

    foodPriceArray[count] = foodPrice;
    foodNameArray[count] = foodName;
    
    //changing a string of array to a double of arrays
    foodPriceArrayMenu[count] = atof(foodPriceArray[count].c_str());

    count++;
  }

  //This is the formating for the menu using the setw() function.
  cout << setw(10) << "Number" << setw(35) << "Item" << setw(25) << "Price" << endl;

  //This iterates through the 2d array which is foodArray in this case.
  for (int i = 0; i < NUM_ITEMSROWS; ++i){
    cout << right << setw(10) << i + 1 << '.'<< right << setw(35) << foodArray[i][0] << right << setw(20) << '$' << fixed << setprecision(2) << foodPriceArrayMenu[i] << endl; 
    
  }
  
  //A function call of manageOrder passing two array that are strings.
  manageOrder(foodPriceArray,foodNameArray);
  myFile.close();
}

//----------------------------------------------------------------------------//
//Name: displayChoice()
//PreCondition: takes in a integer of the user choice in userChoice()
//PostCondition: display menu and user input of what items they want to buy
//----------------------------------------------------------------------------//
void displayChoice(int choiceNum){
  
  //if user choiceNum is 1 then it will display all content related to option 1 in
  //the menu if 2 is press then it will display the receipt.
  if (choiceNum == 1){
    displayMenu();

  } else if(choiceNum == 2){
    writeReceipt();
  }
}

//----------------------------------------------------------------------------//
//Name: manageOrder()
//PreCondition: takes in two arrays that are strings
//PostCondition: calculate total price for the items, writing into a txt file, 
//               converting the arrays with the price to double.
//----------------------------------------------------------------------------//
void manageOrder(string foodPriceArray[],string foodNameArray[]){

  string convertArray[NUM_ITEMSROWS];
  int menuNumber = 0;
  int quantityNum = 0;
  double priceInDouble;
  double subTotal = 0;
  double overallTax = 0;
  double overallTotal = 0;
  char addItems;

  cout << "What would you like to buy?" << endl;
  cin >> menuNumber;

  //if the user picks a number that isn't on the list it will reprompt the menu
  if ((menuNumber <= 0)|| (menuNumber > 10)){
    displayMenu();
  }
  
  cout << "How many would you like to buy?" << endl;
  cin >> quantityNum;
  
  //convert string to double 
  priceInDouble = atof(foodPriceArray[menuNumber - 1].c_str());

  //Calculates overall subtotal
  subTotal = (priceInDouble * quantityNum);

  //Tax is a constant of 6%
  overallTax = (subTotal * TAX_RATE);

  //Calculates overall Total
  overallTotal = (subTotal + overallTax);
    
  cout << "Do you want to add more items? (y/n):" << endl;
  cin >> addItems;
  
  if (addItems == 'y'){
    
    //This writes in the recepit.txt and saves the values 
    ofstream receiptFile;
    receiptFile.open("receipt.txt", fstream::app);
   
    receiptFile << ',' << foodNameArray[menuNumber - 1] << ',' << foodPriceArray[menuNumber - 1] << ','<< quantityNum << ',' << subTotal;
  
    receiptFile.close();
    cin.get();
    
    //function call displayMenu() goes back and ask for a second item.
    displayMenu();

  } else if (addItems == 'n'){
    
    ofstream receiptFile;
    receiptFile.open("receipt.txt", fstream::app);

    receiptFile << ',' << foodNameArray[menuNumber - 1] << ',' << foodPriceArray[menuNumber - 1] << ','<< quantityNum << ',' << subTotal;

    receiptFile.close();
    cin.get();
    
    //function call writeReceipt() display the receipt
    writeReceipt();

  }
}
  
//----------------------------------------------------------------------------//
//Name: writeReceipt()
//PreCondition: takes in values that are storage in save txt file receipt
//PostCondition: opens the value inside the recipt.txt calculate the total of
//               all the items bought from the user.
//----------------------------------------------------------------------------//
void writeReceipt(){

  ifstream myFile("receipt.txt");
  string doubleArray[20];
  string elementsReceipt;
  double priceInDouble[20];
  double subTotal = 0;
  double overallTax;
  double overallTotal; 


  int count = 0;

  while (getline(myFile,elementsReceipt,',') && count < 18){
    
    doubleArray[count] = elementsReceipt;
    count ++;

  }
  
  //formatting with the function setw() for the save items in Qnty, Item and Price.
  cout << right << setw(10) << "Qnty" << right << setw(35) << "Item" << right << setw(23) << "Price" << endl;
  cout << right << setw(10) << doubleArray[3] << right << setw(35) << doubleArray[1] << right << setw(20) << '$' << fixed << setprecision(2) << atof(doubleArray[2].c_str()) << endl;

  cout << right << setw(10) << doubleArray[7] << right << setw(35) << doubleArray[5] << right << setw(20) << '$' << fixed << setprecision(2) << atof(doubleArray[6].c_str()) << endl;

     cout << right << setw(10) << doubleArray[11] << right << setw(35) << doubleArray[9] << right << setw(20) << '$' << fixed << setprecision(2) << atof(doubleArray[10].c_str()) << endl;



  //convert string to double
  priceInDouble[0] = atof(doubleArray[4].c_str());
  priceInDouble[1] = atof(doubleArray[8].c_str());
  priceInDouble[2] = atof(doubleArray[12].c_str());

  //add all the elements in the priceInDouble Array
  for (int i = 0; i < SIZE_RECEIPTARRAY; i++){
    subTotal = subTotal + priceInDouble[i]; 
  }

  //Tax is a constant of 6%
  overallTax = (subTotal * TAX_RATE);

  //Calculates overall Total
  overallTotal = (subTotal + overallTax);

  //cout the given data
  cout << "Subtotal: " << fixed << setprecision(2) << subTotal << endl;
  cout << "Tax: " << overallTax << endl;
  cout << "Total: " << overallTotal << endl;
  cout << "Receipt Written" << endl;

}
