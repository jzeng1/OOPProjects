/****************************************************
 **File: Game.cpp
 **Author: Jason Zeng
 **Date: 10/9/2017
 **Section: 10
 **E-mail: jzeng1@umbc.edu
 **
 **This program is a text-based version of Clash Royale for this game
 **it is going to build random team of troops to fight against a random
 **team of computer troops so it (Player vs Computer). Each team will 
 **fight depending on which troop the player chose to use. If either the
 **player or the computer runs out of troops, the game ends.
 **
 ******************************************************/

#include "Troop.h"
#include "Game.h"

#include <string>
#include <fstream>
#include <ctime>
#include <cstdlib> 

/* Name: Game() Default Constructor
  // Desc - Builds a new game by:
  // 1. Asking user for their name,
  // 2. Asking number of troops on team,
  // 3. Loading all troops from file (function call)
  // 4. Randomizes both teams (function call)
  // 5. Starts game (function call)
  // Preconditions - None
  // Postconditions - m_players is populated (each player has a team)
  //                  and all troops on team - game started
  */

//Default Constructor
Game::Game(){

  cout << "Welcome to Clash UMBC " << endl;
  cout << "What is your name? " << endl;
  getline(cin,m_name,'\n');

  cout << "How many troops would you like? (2-5) " << endl;
  cin >> m_max;
    
  //This whlie loop check validation troop must be between 2-5
  while ((m_max < 2) || (m_max > 5)){
    cout << "That is not a valid option" << endl;
    
    cout << "How many troops would you like? (2-5) " << endl;
    cin >> m_max;
  }

  cout << "Both teams have been populated. " << endl;
  
  LoadTroops();
  
  //Changes the Random when the program runs again.
  srand(time(NULL));
  
  //Randomize the amount of time of the user choice in the number of troops they want.
  for (int i = 0; i < m_max; i++){
    srand(rand());
    RandomizeTeam();
  }

  StartGame();
}
  
  
// Name: LoadTroops
// Desc - Loads each troop into m_troop from file
// Preconditions - Requires file with valid troop data
// Postconditions - m_troop is populated with Troop objects
void Game::LoadTroops(){

  string troopName;
  int troopHealth;
  int troopDamage;
  string troopTarget;
  int troopIsFlying;

  //Opens the txt file changes the string to a c-string
  ifstream myFile (PROJ2_TROOPS.c_str());

  //Run a while loop going through every element inside the txt file
  while (myFile >> troopName){

    //Assigning each element to a certain variable
    myFile >> troopHealth >> troopDamage >> troopTarget >> troopIsFlying;

    //Overloading Constructor that take in all the variables.
    Troop info(troopName,troopHealth,troopDamage,troopTarget,troopIsFlying);

    //Load each troop into the m_troop vector
    m_troop.push_back(info);
  }
}

// Name: RandomizeTeam
// Desc - Randomly chooses a troop and puts it on a team
// Preconditions - m_troop is populated
// Postconditions - m_player and m_computer is populated
void Game::RandomizeTeam(){
  
  int sizeOfTroop;
  int randomNum;
  int randomNumCom;

  string troopName;
  int troopHealth;
  int troopDamage;
  string troopTarget;
  int troopIsFlying;
  
  //find the size of m_troop which is 48 elements
  sizeOfTroop = m_troop.size();
  
  //set a range of 0 to 48 for the rand() function to only pick numbers 
  //between the range
  randomNum = rand() % (sizeOfTroop);
  
  troopName = m_troop.at(randomNum).GetName();
  troopHealth = m_troop.at(randomNum).GetHealth(); 
  troopDamage = m_troop.at(randomNum).GetDamage();
  troopTarget = m_troop.at(randomNum).GetTarget(); 
  troopIsFlying = m_troop.at(randomNum).GetIsFlying(); 

  //my overloaded constructor taking in all the info for the troops chosen 
  //rand() function.
  Troop info(troopName,troopHealth,troopDamage,troopTarget,troopIsFlying);

  //storage the troops info to the vector of player.
  m_player.push_back(info);
  
  //all of this code in the bottom are repeated code that are similar to the
  //top but for the computer.
  randomNumCom = rand() % (sizeOfTroop);
  
  troopName = m_troop.at(randomNumCom).GetName();
  troopHealth = m_troop.at(randomNumCom).GetHealth();
  troopDamage = m_troop.at(randomNumCom).GetDamage();
  troopTarget = m_troop.at(randomNumCom).GetTarget();
  troopIsFlying = m_troop.at(randomNumCom).GetIsFlying();
  
  Troop infoComp(troopName,troopHealth,troopDamage,troopTarget,troopIsFlying);
  m_computer.push_back(infoComp);
}


// Name: StartGame()
// Desc - Manages the game itself including win conditions continually
//         calling the main menu
// Preconditions - Both players have teams with troops
// Postconditions - Continually checks to see if player/computer has troops
void Game::StartGame(){

  int userChoiceNum = 0;

  // A do while loop to display the menu and have options 
  do{
    MainMenu();
    cin >> userChoiceNum;

    if (userChoiceNum == 1){
      DisplayTroops();

    }else if (userChoiceNum == 2){
      ChangeTroop();

    }else if (userChoiceNum == 3){
      Attack();
      
      //if computer troop all dies you win if all players troop dies they win
      if(m_computer.size() == 0){
	cout << "You Win!" << endl;
      }else if(m_player.size() == 0){
	cout << "You loes!" << endl;
      }
    }
    
    //This portion of the code if the user enter 4 then it will exit the program it does 
    //the same for if all troops for either computer or player when all there troops are defeated
  }while((userChoiceNum != 4) && (m_computer.size() != 0)  && (m_player.size() != 0)); 
}



// Name: DisplayTroops()
// Desc - Displays the current teams (both user and computer)
// Preconditions - Players have a team with troops
// Postconditions - Displays a numbered list of troops
void Game::DisplayTroops(){

  cout << "********************" << endl;

  cout << m_name << "'s Team" << endl;
  
  //iterating through the vector with the size of m_player which is all of the troops in the txt file.
  for (unsigned int i = 0; i < m_player.size(); i++){

    //print out the name of the troop and health.
    //it goes the same for the bottom code.
    cout << m_player.at(i).GetName() << " " << m_player.at(i).GetHealth() << endl;
  }
  cout << "********************" << endl;

  cout << "Computer's Team" << endl;

  for (unsigned int i = 0; i < m_computer.size(); i++){
    cout << m_computer.at(i).GetName() << " " << m_computer.at(i).GetHealth() << endl;
  }

  cout << "********************" << endl;

}


// Name: ChangeTroop()
// Desc - Allows the user to change current troop
// Preconditions - Players have troops and have not lost
// Postconditions - Displays a numbered list of troops and m_curTroop is updated
void Game::ChangeTroop(){

  DisplayTeam();
  
  cout << "Which troop do you want to use?" << endl;
  cin >> m_curTroop;
  
  //if the user trys to pick a troop that is over the max then it will tell 
  //user to enter an acceptable number
  while ((m_curTroop <= 0) || (m_curTroop > m_max)){
    cout << "That is not a valid option" << endl;

    cout << "Which troop do you want to use?" << endl;
    cin >> m_curTroop;
  }
}


// Name: MainMenu()
// Desc - Displays and manages menu
// Preconditions - Players have a team with troops
// Postconditions - Displays a numbered list of troops
void Game::MainMenu(){

  DisplayTroops();

  cout << "What would you like to do?" << endl;
  cout << "1. Display Team" << endl;
  cout << "2. Change Current Troop" << endl;
  cout << "3. Attack!" << endl;
  cout << "4. Quit" << endl;
}

  
// Name: DisplayTeams()
// Desc - Displays the current teams (both player and computer)
// Preconditions - m_player/m_computer have a team with troops
// Postconditions - Displays a numbered list of troops
void Game::DisplayTeams(){

  cout << "********************" << endl;

  cout << m_name << "'s Team" << endl;

  for (unsigned int i = 0; i < m_player.size(); i++){
    cout << m_player.at(i).GetName() << " " << m_player.at(i).GetHealth() << endl;
  }
  cout << "********************" << endl;

  cout << "Computer's Team" << endl;

  for (unsigned int i = 0; i < m_computer.size(); i++){
    cout << m_computer.at(i).GetName() << " " << m_computer.at(i).GetHealth() << endl;
  }

  cout << "********************" << endl;
}



// Name: DisplayTeam()
// Desc - Displays just player team (for changing current troop)
// Preconditions - Player and Computer both have troops left
// Postconditions - Displays a numbered menu
void Game::DisplayTeam(){

  cout << "********************" << endl;

  cout << m_name << "'s Team" << endl;

  for (unsigned int i = 0; i < m_player.size(); i++){
    cout << m_player.at(i).GetName() << " " << m_player.at(i).GetHealth() << endl;
  }
  cout << "********************" << endl;
}


// Name: Attack()
// Desc - Manages the troops attacking each other
// If a troop has less than or equal to 0 health, removes "dead" troop from vector
// FYI: remove element at front of a vector is m_computer.erase(m_computer.begin());
// If player or computer has no troops left, declares winner
// Preconditions - Player and Computer both have troops left
// Postconditions - Depending on whose turn it is, calls attacks
void Game::Attack(){
  
  if (m_curTroop == 0){
    m_curTroop = 1;
  }

  //Alternating Turn Between Player and Computer
  if (m_curPlayer == 0){
    //This would be Player
    m_curPlayer = 1;

  }else{
    //This would be Computer
    m_curPlayer = 0;
  }

  //Player 1 Turn attack Computer Troop once the health reach to zero it is removed from the vector.
  if (m_curPlayer == 1){
    
    //Called the AttackTroop function in Troop.cpp to check what it targets and if the troop is flying or ground.
    //it also goes the same for the code in the bottom.
    m_computer.at(0).AttackTroop(m_player.at(m_curTroop - 1));

    //if the health goes below 0 it remove the components of the troop out of the vector.
    if (m_computer.at(0).GetHealth() <= 0){
      
      cout << m_player.at(m_curTroop - 1).GetName() << " attack " << m_computer.at(0).GetName() << " on the ground!" << endl;
      cout << "Damage Occuring " << m_player.at(m_curTroop - 1).GetDamage() << endl;
      cout << m_computer.at(0).GetName() << " attack " << m_player.at(m_curTroop -1).GetName() << " on the ground!" << endl;
      cout << m_computer.at(0).GetName() << " dies!" << endl; 
      
      //removes all the componets of that troop out of the vector
      m_computer.erase(m_computer.begin());
    }
  }

  //Player 2 Turn attack Player Troop once the health reach to zero it is removed from the vector.
  if (m_curPlayer == 0){

    //Called the AttackTroop function in Troop.cpp to check what it targets and if the troop is flying or ground.
    m_player.at(m_curTroop - 1).AttackTroop(m_computer.at(0));

    if (m_player.at(m_curTroop - 1).GetHealth() <= 0){

      cout << m_computer.at(0).GetName() << " attack " << m_player.at(m_curTroop -1).GetName() << " on the ground!" << endl;
      cout << "Damage Occuring " << m_computer.at(0).GetDamage() << endl;
      cout << m_player.at(m_curTroop - 1).GetName() << " attack " << m_computer.at(0).GetName() << " on the ground!" << endl;
      cout << m_player.at(m_curTroop - 1).GetName() << " dies!" << endl;
 
      m_player.erase(m_player.begin()+(m_curTroop - 1));
      m_curTroop = 1;
    }
  }    
}
