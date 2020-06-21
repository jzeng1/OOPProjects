/*****************************************
 ** File:    StarWars.cpp
 ** Project: StarWars
 ** Author:  Jason Zeng
 ** Date:    5/8/2018
 ** Section: 22
 ** E-mail:  Jzeng1@umbc.edu
 **
 **   This programs manages the loading of the input, sorting,
 **   and the creation of the two teams and the battle. 
 **   which populates the vector and using a queue to manage the
 **   battle.
 **
 ***********************************************/

#include "StarWars.h"
//#include "Tqueue.cpp"

// Name: StarWars (Default Constructor)
// Preconditions: None
// Postconditions: Creates a new Star War object
StarWars::StarWars(){
  
  //This is here so that it will randomly change after a certain time.
  srand(time(NULL));
  srand(rand());
}

// Name: ~StarWars (Destructor)
// Preconditions: None
// Postconditions: Destructs Star War object
StarWars::~StarWars(){
  
  //iterating throught the vector to delete every single element freeing memeory.
  for(unsigned int i = 0; i < m_imperialShips.size(); i++){
    delete m_imperialShips[i];
  }
  
  for(unsigned int i = 0; i < m_rebelShips.size(); i++){
    delete m_rebelShips[i];
  }
}

// Name: loadShips
// Preconditions: Two files (imperial ships then rebel ships) passed in array
// Postconditions: Populates m_imperialShips and m_rebelShips (returns 1 on success)
bool StarWars::loadShips(char* files[]){
  
  string theLine,imShipName,imShipType,imAttack,imDefense;
  string reShipName,reShipType,reAttack,reDefense;
  
  int theImAttack,theImDefense,theReAttack,theReDefense;
  
  Imperial *infoShip;
  Rebel *infoShips;
  
  fstream myImperial (files[0]);
  fstream myRebelShips (files[1]);
  
  //Check to see if both the imperal and the rebel txt file is open.
  if(myImperial.is_open() && myRebelShips.is_open()){
    
    while(getline(myImperial, theLine)){
      
      //i used sstream to split the variables based on the delimiter ","
      stringstream linestream(theLine);
      
      getline(linestream, imShipName, ',');
      getline(linestream, imShipType, ',');
      getline(linestream, imAttack, ',');
      getline(linestream, imDefense, ',');

      //converted the string to an int
      theImAttack = atoi(imAttack.c_str());
      theImDefense = atoi(imDefense.c_str());
      
      //storage the infomation to the vector of imerialships and rebel at the bottom.
      infoShip = new Imperial(imShipName,imShipType,theImAttack,theImDefense);
      m_imperialShips.push_back(infoShip);
    }
    
    while(getline(myRebelShips, theLine)){

      stringstream linestream(theLine);

      getline(linestream, reShipName, ',');
      getline(linestream, reShipType, ',');
      getline(linestream, reAttack, ',');
      getline(linestream, reDefense, ',');
      
      theReAttack = atoi(reAttack.c_str());
      theReDefense = atoi(reDefense.c_str());

      infoShips = new Rebel(reShipName,reShipType,theReAttack,theReDefense);
      m_rebelShips.push_back(infoShips);     
    }

  }else{
    
    //close the file 
    myImperial.close();
    myRebelShips.close();
    cout << "The File was not opened properly!" << endl;
    return 0;

  }

  //close the file
  myImperial.close();
  myRebelShips.close();
  return 1;
}

// Name: Start
// Desc: Manages the game (loadsShips, requests team size, createsTeams, and Battles)
// Preconditions: Two files (imperial ships then rebel ships) passed in array
// Postconditions: None (game ends when it ends)
void StarWars::Start(char* files[]){
  
  int numShips = 0;

  //what this code does is send the c_str of the txt file to loadShips.
  char* theFiles[] = {files[0],files[1]};
  loadShips(theFiles);

  //User input of how many ships
  cout << "How many ships would you like on a team?" << endl;
  cin >> numShips;
  
  //call create teams and battle
  createTeams(numShips);
  battle();

}

// Name: createTeams
// Desc: Populates two Tqueues of ships randomly
//        Tqueue m_myShips is populated from m_rebelShips (enqueue)
//        Tqueue m_imperialShips is populated from m_imperialShips (enqueue)
// Preconditions: None
// Postconditions: Teams created
void StarWars::createTeams(int numShips){
  
  int randomNumIm,randomNumRe,sizeOfImperial,sizeOfRebel;

  //iterate throught the numShips that the user input.
  for(int i = 0; i < numShips; i++){

    //size of the vectro of imperialShips and rebelShips
    sizeOfImperial = m_imperialShips.size();
    sizeOfRebel = m_rebelShips.size();
    
    //a random ships is being chosen
    randomNumIm = rand() % (sizeOfImperial);
    randomNumRe = rand() % (sizeOfRebel);
    
    //storage the data to the enqueue in Tqueue
    //it goes the same for the stuff in the bottom.
    m_enemyShips.enqueue(m_rebelShips[randomNumRe]);
    m_myShips.enqueue(m_imperialShips[randomNumIm]);

  }  
}

// Name: battle
// Desc: Manages the battles (random team starts
//       Front of Tqueue attacks front of second Tqueue
//       If a member is destroyed, dequeued from Tqueue
//       Alternate turns and repeat until one of the Tqueues is empty
//       Note: If a ship is destroyed, it does not attack
// Preconditions: Two Tqueues of ships are populated
// Postconditions: A winner must be displayed
void StarWars::battle(){
  
  int checkDamage;
  
  //a random player starts every time.
  srand(time(NULL));
  srand(rand());

  //alternates 0 or 1.
  int alterPlayer = rand() % 2;

  cout << "The battle begins... " << endl;
  
  //if the either Ships is empty stop the while loop
  while(m_myShips.isEmpty() != 1 && m_enemyShips.isEmpty() != 1){
  
    //alternate 0 and 1 when the random start player choses who goes first.
    alterPlayer = 1 - alterPlayer;
    
    //Player 1 check the front of the queue for both enemy and myShips.
    if(alterPlayer == 0){
      checkDamage = m_myShips[m_myShips.getFront()]->attack(m_enemyShips[m_enemyShips.getFront()]);
      cout << "The" << *m_myShips[0] << m_myShips[m_myShips.getFront()]->getName() << " attacks the" << *m_enemyShips[0] << m_enemyShips[m_enemyShips.getFront()]->getName() << "." << endl;
      //if damage goes here
      if(checkDamage == 0){
	cout << "The" << *m_myShips[0] << m_myShips[m_myShips.getFront()]->getName() << " was damaged." << endl;
      }

      //if destroyed goes here
      if(checkDamage == 1){
	cout << "The" << *m_myShips[0] << m_myShips[m_myShips.getFront()]->getName() << " was destoryed." << endl;
	m_enemyShips.dequeue();
      }
    }

    //Player 2 it goes for the same for the previous code that i have on top.
    if(alterPlayer == 1){
      checkDamage = m_enemyShips[m_enemyShips.getFront()]->attack(m_myShips[m_myShips.getFront()]);
      cout << "The" << *m_enemyShips[0] << m_enemyShips[m_enemyShips.getFront()]->getName() << " attacks the" << *m_myShips[0] << m_myShips[m_myShips.getFront()]->getName() << "." << endl;


      if(checkDamage == 0){
	cout << "The" << *m_enemyShips[0] << m_enemyShips[m_enemyShips.getFront()]->getName() << " was damaged." << endl;
      }

      if(checkDamage == 1){
	cout << "The" << *m_enemyShips[0] << m_enemyShips[m_enemyShips.getFront()]->getName() << " was destroyed." << endl;
	m_myShips.dequeue();
      }
    }

    //if isEmpty is empty for either myShips or m_enemyShips then it will display you loes 
    //or you will so which one become empty first will display first.
    if(m_myShips.isEmpty() == 1){ 
      cout << "You lose!" << endl;
    }else if(m_enemyShips.isEmpty() == 1){
      cout << "You Win!" << endl;
    }
  }
}
