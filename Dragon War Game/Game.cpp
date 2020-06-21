/****************************************************
 **File: Game.cpp
 **Author: Jason Zeng
 **Date: 3/8/2018
 **Section: 22
 **E-mail: jzeng1@umbc.edu
 **In this game, we will load in a large file of dragons (and their respective characteristics) 
 **and work to hatch eggs so that they become dragons. Once dragons have been hatched, they will 
 **fight in order to grow bigger and bigger to show dominance on the battlefield!
 ******************************************************/

#include "Game.h"
#include "Dragon.h"
#include <sstream>
#include <ctime>

const int FIRST_CHOICE = 1;
const int SECOND_CHOICE = 2;
const int THIRD_CHOICE = 3;
const int FOURTH_CHOICE = 4;
const int FIFTH_CHOICE = 5;
const int MIN_RANGE = 1;
const int MAX_RANGE = 10;
const double ITS_NINEPERCENT = 0.09;
const int ITS_HUNDRED = 100;
const int ITS_FIFTYPERCENT = 50;
const int SIZE_SET = 30;

/* Name: Game() Default Constructor
  // Desc - Builds a new game by:
  // 1. Asking user for their name,
  // 2. Loading all dragons from file (function call)
  // Preconditions - None
  // Postconditions - m_dragons is populated
  */

//Default Constructor
Game::Game(){
  cout << "Welcome to Dragon Wars" << endl;
  cout << "What is your name? " << endl;
  getline(cin,m_name,'\n');

  //I include this here is so that when the game runs again the randomizer will be diffrent 
  srand(time(NULL));
  srand(rand());

  //call LoadDragons to input txt file to the vector
  LoadDragons();

}

// Name: LoadDragons
// Desc - Loads each dragon into m_dragon from file
// Preconditions - Requires file with valid dragon data
// Postconditions - m_dragons is populated with Dragon objects

void Game::LoadDragons(){

  string theName,theType,theRarity,maxSize,theLine;
  int theMaxSize,theRarityInt;
  
  bool isHatched = false;
  int curSize = 1;

  //Open the txt file 
  ifstream myFile (PROJ2_DRAGONS.c_str());

  //Checks if the txt file is open
  if(myFile.is_open()){

    //seperate the delimiter commma from the txt file
    while(getline(myFile,theLine)){
      
      stringstream linestream(theLine);
      
      getline(linestream, theName, ',');
      getline(linestream, theType, ',');
      getline(linestream, maxSize, ',');
      getline(linestream, theRarity, ',');
      
      //convert the string to an integer
      theMaxSize = atof(maxSize.c_str());
      theRarityInt = atof(theRarity.c_str());
      
      //pass the information to an overoladed constructor 
      Dragon theInfo(theName,theType,isHatched,dragonSize(curSize),dragonSize(theMaxSize),theRarityInt);
      m_dragons.push_back(theInfo);

    }
    
  }else{
    //close the txt file
    myFile.close();
    cout << "The File was not opened properly!" << endl;
  }
  
  myFile.close();
  
}

// Name: SearchEgg
// Desc - Randomly chooses an egg and adds to players dragon vector
// Preconditions - m_dragons is populated
// Postconditions - m_myDragons is populated

void Game::SearchEgg(){

  int inputRarity,totalLikelihood,sizeOfDragons,sizeOfRan,randomNum;
  double theLikelihood;  

  //I included a vector because it need to storage the rarity that the user has chosen
  //so that it will pick at random of that rairty.
  vector <Dragon> randomizeRarity;

  //This is to validate user input
  cout << "What rarity egg would you like to search for?" << endl;
  cout << "Enter a rarity (1 = very common and 10 = very rare): " << endl;
  cin >> inputRarity;

  while(inputRarity < MIN_RANGE || inputRarity > MAX_RANGE){
    cout <<"The rarity needs to be in the range from 1 to 10 " << endl;
    cin >> inputRarity;
  }
  
  //This is to calculate % chance of it sucesseding or failing
  theLikelihood = 1 - (inputRarity * ITS_NINEPERCENT);
  totalLikelihood = (theLikelihood * ITS_HUNDRED);
  

  //find the size of m_dragons which is 167 elements.
  sizeOfDragons =  m_dragons.size(); 

  //the % chance for the likelihood that it will fail or be sucessful.
  if (rand() % ITS_HUNDRED < totalLikelihood){

    //Store the rarity into a vector so that it will choose at random of that rarity.
    for(int i = 0; i < sizeOfDragons; i++){
      if(m_dragons.at(i).GetRarity() == inputRarity){
	
	//information of rarity is pass to an overloaded function 
	Dragon infoOfRarity(m_dragons.at(i).GetName(),m_dragons.at(i).GetType(),m_dragons.at(i).GetIsHatched()\
			    ,dragonSize(m_dragons.at(i).GetCurSize()),dragonSize(m_dragons.at(i).GetMaxSize()),
			    m_dragons.at(i).GetRarity());
	
	//it is then stored into the vector randomizeRariry.
	randomizeRarity.push_back(infoOfRarity);
	
      }
    }
    
    //check the size of the vector
    sizeOfRan = randomizeRarity.size();

    //have another random number generator from it given range
    randomNum = rand() % (sizeOfRan);
    
    //information of the dragon is passed to the overloaded function of the player dragon.
    Dragon playerInfo(randomizeRarity.at(randomNum).GetName(),randomizeRarity.at(randomNum).GetType(),randomizeRarity.at(randomNum).GetIsHatched()\
		      ,dragonSize(randomizeRarity.at(randomNum).GetCurSize()),dragonSize(randomizeRarity.at(randomNum).GetMaxSize()),randomizeRarity.at(randomNum).GetRarity());
    
    //it is then stored into the vector m_myDragons which is the player dragon.
    m_myDragons.push_back(playerInfo);

    cout << "You have found " << randomizeRarity.at(randomNum).GetName() << " egg!" << endl;
		      
  }else{
    cout << "Sorry, you did not find a dragon of that rarity." << endl;
  }  
}

// Name: HatchEgg
// Desc - Tries to change from egg to small dragon
// Preconditions - m_dragons is populated
// Postconditions - m_myDragons is populated

void Game::HatchEgg(){

  int userChoiceHatch;
  int sizeOfmyDragons;
  bool checkHatch;

  //Display the Dragons
  DisplayMyDragons();

  sizeOfmyDragons = m_myDragons.size();
  
  //checks the size of the vector m_myDragons to see if the roster is empty or not
  if(sizeOfmyDragons == 0){
    cout << "There are no dragons on your roster!" << endl;

  }else{
  
    //Check vaildation between it given range.
    cout << "Which dragon would you like to try and hatch?" << endl;
    cin >> userChoiceHatch;
  
    while(userChoiceHatch < MIN_RANGE  || userChoiceHatch > sizeOfmyDragons ){
      cout <<"That is not a valid choice!!!" << endl;
      cout << "Which dragon would you like to try and hatch?" << endl;

      cin >> userChoiceHatch;
    }
    
    checkHatch = m_myDragons.at(userChoiceHatch - 1).GetIsHatched();
    
    //There is a 50% chance that the egg will hatch with this if statement below which also checks if the egg is hatch or not
    if (rand() % ITS_HUNDRED < ITS_FIFTYPERCENT && checkHatch == false){
      cout << "Your " << m_myDragons.at(userChoiceHatch - 1).GetName() << " egg hatches into a dragon!" << endl;
      m_myDragons.at(userChoiceHatch - 1).HatchDragon();
      
    }else{
      cout << "The dragon did not hatch or is already hatched." << endl;
    }
  } 
}

// Name: StartGame()
// Desc - Manages the game itself including win conditions continually
//         calling the main menu
// Preconditions - Player has an egg or a dragon
// Postconditions - Continually checks to see if player has an egg or a dragon

void Game::StartGame(){
  
  //A simple do while loop so that if the user hit 5 to quit the while loop will stop
  int userChoice;
  
  do{
    userChoice = MainMenu();
    
    if (userChoice == FIRST_CHOICE){
      SearchEgg();

    }else if (userChoice == SECOND_CHOICE){
      HatchEgg();
      
    }else if (userChoice == THIRD_CHOICE){
      DisplayMyDragons();

    }else if (userChoice == FOURTH_CHOICE){
      Attack();

    }else if (userChoice == FIFTH_CHOICE){
      cout << "Thanks for playing Dragon Wars!" << endl;
    }
     
  }while(userChoice != FIFTH_CHOICE);
  
}

// Name: DisplayMyDragons()
// Desc - Displays the current dragons (both hatched and unhatched)
// Preconditions - Player has dragons (either hatched or unhatched)
// Postconditions - Displays a numbered list of dragons

void Game::DisplayMyDragons(){
  
  //This is all formating the display of the dragons using setw() function
  cout << "********************" << endl;
  cout << endl;

  cout << m_name << "'s" << " Dragons" << endl;
  cout << endl;

  cout << setw(33) << "Name" << setw(SIZE_SET) << "Type" << setw(SIZE_SET) << "Egg/Dragon" << setw(SIZE_SET) << "Current Size" << setw(SIZE_SET) << "Max Size" << endl;
  
  int sizeOfmyDragons;
  string eggOrDragon;
  
  sizeOfmyDragons = m_myDragons.size();
  for(int i = 0; i < sizeOfmyDragons; i++){

    //checks to see if the dragon is hatched or not if it is then the value changes to dragon if not 
    //then it stays an egg.
    if (m_myDragons.at(i).GetIsHatched() == true){
      eggOrDragon = "Dragon";

      //store the number of hatched dragon eggs 
      m_countHatchedDragons += 1;

    }else{
      eggOrDragon = "Egg"; 
    }


    cout << setw(2) << i + 1 << "." << right << setw(SIZE_SET) << m_myDragons.at(i).GetName() << right << setw(SIZE_SET) << m_myDragons.at(i).GetType() << right << setw(SIZE_SET) << eggOrDragon << right << setw(SIZE_SET) << m_myDragons.at(i).GetCurSize() << right << setw(SIZE_SET) << m_myDragons.at(i).GetMaxSize() << endl; 
  }

  cout << endl;
  
}

// Name: MainMenu()
// Desc - Displays and manages menu
// Preconditions - Player has a dragon (either hatched or unhatched)
// Postconditions - Returns number indicating exit
int Game::MainMenu(){
  
  int userChoiceNum = 0;

  cout << "What would you like to do? " << endl;
  cout << "1. Search for an egg " << endl;
  cout << "2. Try to hatch egg " << endl;
  cout << "3. Display all dragon and eggs " << endl;
  cout << "4. Attack! " << endl;
  cout << "5. Quit " << endl;
  
  //taking in user input and returning the integer to the function 
  cin >> userChoiceNum;
  
  //check for validation of numbers between 1 - 5
  while(userChoiceNum < MIN_RANGE || userChoiceNum > FIFTH_CHOICE){
    cout <<"Not a valid choice needs to be in the range from 1 to 5 " << endl;
    cin >> userChoiceNum;
  }

  return (userChoiceNum);
  
}

// Name: Attack()
// Desc - Manages the dragons attacking each other
// FYI: remove element at front of a vector is m_vectorName.erase(m_vectorName.begin());
// Preconditions - Player has hatched dragons
// Postconditions - Player attacks a random dragon of random size

void Game::Attack(){
  
  int enemyRandom,sizeOfDragons,sizeOfmyDragons,userChoiceFight;
  string yesOrNo;
  bool checkDragonStats;

  sizeOfDragons = m_dragons.size();
  sizeOfmyDragons = m_myDragons.size();
  
  cout << "Attack!" << endl;

  //I have this here to check if the roster for the player dragon is empty or not also if it has a hatched egg or not
  if(sizeOfmyDragons == 0){
    cout << "There are no dragons on your roster that is Hatched!"  << endl;

  }else if(m_countHatchedDragons == 0){
    cout << "There are no dragons on your roster that is Hatched!"  << endl;
  
  }else{
    
    //I have this here to create a random for the enemy so that i have data for the dragon that it up against.
    enemyRandom = rand() % (sizeOfDragons);
    cout << "You have found a " << m_dragons.at(enemyRandom).GetName() << " to fight!" << endl;
    
    cout << "Do you want to fight it? (y/n)" << endl;
    cin >> yesOrNo;

    if (yesOrNo == "y"){
      
      DisplayMyDragons();
      
      cout << "Which Dragon would you like to fight with?" << endl;
      cin >> userChoiceFight;

      //Checks user input the correct range and if the dragon is hatched or not
      while(userChoiceFight < MIN_RANGE  || userChoiceFight > sizeOfmyDragons || m_myDragons.at(userChoiceFight - 1).GetIsHatched() == false){
	
	cout <<  "That is not a valid choice!!!" << endl;
	cout << "Which dragon would you like to fight with?" << endl;
	cin >> userChoiceFight;
      }

      //Checks if the dragon is alive or dead
      checkDragonStats = m_myDragons.at(userChoiceFight - 1).AttackDragon(m_dragons.at(enemyRandom));
      
      //if the dragon is dead then the dragon is then erase from the player dragon vector so m_myDragon vector.
      if(checkDragonStats == false){
        m_myDragons.erase(m_myDragons.begin()+(userChoiceFight - 1));
      }

    }else{
      cout << "That is not a vaild Choice!" << endl;
    }
  }
}

// Name: DisplayAllDragons (Test Function)
// Desc - Used to test that all dragons were loaded into m_dragons correctly
// Preconditions - Requires file with valid dragon data
// Postconditions - m_dragons is displayed (all relevant data from m_dragons)

void Game::DisplayAllDragons(){

  //This is a test function that checks if i stored all the information to the vector m_dragons correctly 
  //just iterating through the vector.
  int sizeOfmyDragons;

  sizeOfmyDragons = m_dragons.size();
  for(int i = 0; i < sizeOfmyDragons; i++){
    cout << m_dragons.at(i).GetName()<< endl;
    cout << m_dragons.at(i).GetType()<< endl;
  }

}
