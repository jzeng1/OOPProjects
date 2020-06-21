/****************************************************
 **File: Dragon.cpp
 **Author: Jason Zeng
 **Date: 3/8/2018
 **Section: 22
 **E-mail: jzeng1@umbc.edu
 **In this game, we will load in a large file of dragons (and their respective characteristics)
 **and work to hatch eggs so that they become dragons. Once dragons have been hatched, they will
 **fight in order to grow bigger and bigger to show dominance on the battlefield!
 ******************************************************/
#include "Dragon.h"

// Name: Dragon() - Overloaded constructor
// Desc - Used to build a new dragon
// Preconditions - Requires name, type, isHatched, curSize, maxSize, and rarity (from file)
// Postconditions - Creates a new dragon

Dragon::Dragon(string name, string type, bool isHatched, dragonSize curSize,dragonSize maxSize, int rarity){
  m_name = name;
  m_type = type;
  m_isHatched = isHatched;
  m_curSize = curSize;
  m_maxSize = maxSize;
  m_rarity = rarity;
}

// Name: GetName()
// Desc - Getter for Dragon name
// Preconditions - Dragon exists
// Postconditions - Returns the name of the dragon

string Dragon::GetName(){
  return (m_name);
}

// Name: SetName(string)
// Desc - Allows the user to change the name of the dragon
// Preconditions - Dragon exists
// Postconditions - Sets name of dragon

void Dragon::SetName(string name){
  m_name = name;
}    

// Name: GetType()
// Desc - Getter for dragon type
// Preconditions - Dragon Exists
// Postconditions - Returns the type of the dragon

string Dragon::GetType(){
  return(m_type);
}

// Name: SetType(string)
// Desc - Allows the user to change the type of the dragon
// Preconditions - Dragon exists
// Postconditions - Sets type of dragon

void Dragon::SetType(string Type){
  m_type = Type;
}

// Name: GetIsHatched()
// Desc - Getter for if dragon is hatched
// Preconditions - Dragon exists
// Postconditions - Returns if the dragon has hatched from an egg

bool Dragon::GetIsHatched(){
  return(m_isHatched);
}

// Name: HatchDragon()
// Desc - Setter for if dragon is hatched
// Preconditions - Unhatched Dragon (In Egg form) exists
// Postconditions - If unhatched, changes isHatched to 1

void Dragon::HatchDragon(){
  m_isHatched = true;
}

// Name: GetCurSize()
// Desc - Getter for dragon's current size
// Preconditions - Dragon exists
// Postconditions - Returns current size from 1 - 5

dragonSize Dragon::GetCurSize(){
  return(m_curSize);
}

// Name: SetCurSize(int)
// Desc - Setter for the current dragon size
// Preconditions - Dragon exists
// Postconditions - Sets size of dragon (1-5)

void Dragon::SetCurSize(dragonSize curSize){
  m_curSize = curSize;
}

// Name: GetMaxSize()
// Desc - Getter for dragon max size
// Preconditions - Dragon exists
// Postconditions - Returns maximum size from 1 - 5

dragonSize Dragon::GetMaxSize(){
  return(m_maxSize);
}

// Name: SetMaxSize(int)
// Desc - Setter for the maximum dragon size
// Preconditions - Dragon exists
// Postconditions - Sets maximum size of dragon (1-5)

void Dragon::SetMaxSize(dragonSize maxSize){
  m_maxSize = maxSize;
}

// Name: GetRarity()
// Desc - Getter for dragon rarity
// Preconditions - Dragon exists
// Postconditions - Returns rarity of dragon (1-10)

int Dragon::GetRarity(){
  return(m_rarity);
}

// Name: SetRarity()
// Desc - Setter for dragon rarity
// Preconditions - Dragon exists
// Postconditions - Sets rarity of dragon from (1-10)

void Dragon::SetRarity(int rarity){
  m_rarity = rarity;
}

// Name: AttemptGrow()
// Desc - After a dragon wins a fight, if possible, it grows larger
// Preconditions - Dragons exist
// Postconditions - If possible, curSize increases, if increases, returns true else false

bool Dragon::AttemptGrow(){
  
  //if the player dragon size reach it max size then it return false else it return true
  if (m_curSize == m_maxSize){
    return false;

  }else{
    return true;
  }  
}

// Name: AttackDragon(Dragon&)
// Desc - Allows the user to attack an enemy dragon
// Preconditions - Dragons exist
// Postconditions - Returns if dragon lives or dies (true lives, dies false)

bool Dragon::AttackDragon(Dragon &enemyDragon){  
  
  int randomSize,theMaxSizeEnemy,theCurSizePlayer;
  string checkType;
  bool checkIncrease;
  
  //there is something WRONG WITH THE RAND SO FIX IT I THINK THECURSIZE IS NOT AN INT
  theMaxSizeEnemy = enemyDragon.GetMaxSize();
  theCurSizePlayer = m_curSize;
  
  //enemy has random current size within the range of the dragon max size
  randomSize = (rand() % theMaxSizeEnemy) + 1;
  
  //constantly check the m_curSize to the Max size of the dragon in the function AttemptGrow();
  checkIncrease = AttemptGrow();

  //if the players dragon size is bigger than the enemy dragon
  if(randomSize < theCurSizePlayer){
    
    //There is a 5% chance that it will use it special ability to kill the enemy dragon
    if(rand() % 100 < 5){
      BreathAttack();
      
      cout << "Your " << GetName() << " attacks the " << enemyDragon.GetName() << "!" << endl;
      cout << "Your " << GetName() << " defeats the enemy " << enemyDragon.GetName() << "!" << endl;
      
      //if m_curSize has not reach it max size then go throught this if statement to increase it size if 
      //the max size is reach then it will go to the else statment.
      //it goes the same of the code in the bottom also it return true if dragon is still alive 
      //it return false if it is dead.
      if(checkIncrease == true){
        cout << "Your dragon grows a bit larger!" << endl;

        theCurSizePlayer += 1;
	
	//This portion right here updates the player curSize 
        SetCurSize(dragonSize(theCurSizePlayer));
        return true;


      }else{
        cout << "Your dragon cannot grow any larger!" << endl;
        return true;
      }
   
    }else{
      
      cout << "Your " << GetName() << " attacks the " << enemyDragon.GetName() << "!" << endl;
      cout << "Your " << GetName() << " defeats the enemy " << enemyDragon.GetName() << "!" << endl;
      
      if(checkIncrease == true){
        cout << "Your dragon grows a bit larger!" << endl;

        theCurSizePlayer += 1;
        SetCurSize(dragonSize(theCurSizePlayer));
        return true;

      }else{
        cout << "Your dragon cannot grow any larger!" << endl;
        return true;
      }
    }

    //if the enemy and the player dragon are the same
  }else if(randomSize == theCurSizePlayer){

    if(rand() % 100 < 5){
      BreathAttack();
      
      cout << "Your " << GetName() << " attacks the " << enemyDragon.GetName() << "!" << endl;
      cout << "Your " << GetName() << " defeats the enemy " << enemyDragon.GetName() << "!" << endl;
      
      if(checkIncrease == true){
        cout << "Your dragon grows a bit larger!" << endl;
	
        theCurSizePlayer += 1;
        SetCurSize(dragonSize(theCurSizePlayer));
        return true;
	
      }else{
        cout << "Your dragon cannot grow any larger!" << endl;
        return true;
      }
      
    }else{
      
      cout << "Your " << GetName() << " attacks the " << enemyDragon.GetName() << "!" << endl;
      cout << "The Battle reults in a draw " << endl;
      
      if(checkIncrease == true){
	cout << "Your dragon grows a bit larger!" << endl;
	
	theCurSizePlayer += 1;
	SetCurSize(dragonSize(theCurSizePlayer));
	return true;
	
      }else{
        cout << "Your dragon cannot grow any larger!" << endl;
        return true;	
      }
    }

    //if the enemy dragons size is bigger than the player dragon size.
  }else if(randomSize > theCurSizePlayer){

    if(rand() % 100 < 5){
      BreathAttack();
      
      cout << "Your " << GetName() << " attacks the " << enemyDragon.GetName() << "!" << endl;
      cout << "Your " << GetName() << " defeats the enemy " << enemyDragon.GetName() << "!" << endl;
 
      if(checkIncrease == true){
	cout << "Your dragon grows a bit larger!" << endl;
	
	theCurSizePlayer += 1;
	SetCurSize(dragonSize(theCurSizePlayer));
	return true;
	
      }else{
	cout << "Your dragon cannot grow any larger!" << endl;
	return true;
      }
      
    }else{
      
      cout << "Your " << GetName() << " attacks the " << enemyDragon.GetName() << "!" << endl;
      cout << "The enemy " << enemyDragon.GetName() << " defeated your " << GetName() << "!" << endl;
      return false;
    }
  }
  return true;
}


// Name: BreathAttack(Dragon&)
// Desc - Allows the user to attack an enemy dragon using a special breath attack
//        Returns the string of the specific attack (different for acid, water, ice, fire, wind)
// Preconditions - During normal attack, 5% chance a special breath attack called
// Postconditions -  Automatically kills enemy dragon

string Dragon::BreathAttack(){
  //This is if activated it return the type of special attack.
  cout << "Your special attack has activated " << GetType() << " Breath is being used." << endl;
  return GetType();
}
