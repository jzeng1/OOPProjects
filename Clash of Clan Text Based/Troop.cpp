/****************************************************
 **File: Troop.cpp
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

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <iomanip>
using namespace std;

// Name: Troop() - Overloaded constructor
// Desc - Used to build a new troop
// Preconditions - Requires name, health, damage, target, and isFlying (from file)
// Postconditions - Creates a new troop

Troop::Troop(string name, int health, int damage, string target, bool isFlying){
  m_name = name;
  m_health = health;
  m_damage = damage;
  m_target = target;
  m_isFlying = isFlying;
}


// Name: GetName()
// Desc - Getter for troop name
// Preconditions - Troop exists
// Postconditions - Returns the name of the troop
string Troop::GetName(){
  return (m_name);
}


// Name: SetName(string)
// Desc - Allows the user to change the name of the troop
// Preconditions - Troop exists
// Postconditions - Sets name of troop
void Troop::SetName(string name){
  m_name = name;
}


// Name: GetHealth()
// Desc - Getter for troop health
// Preconditions - Troop exists
// Postconditions - Returns the health of the troop
int Troop::GetHealth(){
  return (m_health);
}


// Name: SetName(int)
// Desc - Allows the user to change the health of the troop
// Preconditions - Troop exists
// Postconditions - Sets health of troop
void Troop::SetHealth(int health){
  m_health = health;
}


// Name: GetDamage()
// Desc - Getter for troop name
// Preconditions - Troop exists
// Postconditions - Returns the damage of the troop
int Troop::GetDamage(){
  return (m_damage);
}


// Name: GetTarget()
// Desc - Getter for troop target ("Both" can attack ground + air)
//                                ("Ground" can ONLY attack ground)
// Preconditions - Troop exists
// Postconditions - Returns what the troop can target
string Troop::GetTarget(){
  return (m_target);
}


// Name: GetIsFlying()
// Desc - Getter for troop flying (1 is flying and only things with target both)
//                                (0 is not flying)
// Preconditions - Troop exists
// Postconditions - Returns if the troop is flying
bool Troop::GetIsFlying(){
  return (m_isFlying);
}


// Name: AttackTroop(Troop&)
// Desc - Allows the user to attack an enemy troop
// Checks to see if 1. Attacking troop can attack "both" or "ground"
//                  2. If the target is flying or not.
//                  3. Updates health of target (current health - damage)
// Preconditions - Troops exist
// Postconditions - Health of target is updated
void Troop::AttackTroop(Troop &Target){

  int totalNum = 0;
  
  //This part checks the attacking troop if they are target is both vs both, both vs ground, ground vs ground, ground vs both. 
  if ((Target.GetTarget() == "Both") && (GetTarget() == "Both")){
    
    //This code takes the health of the targeted troop and subtracts the damage of the attacking troop.
    totalNum = GetHealth() - Target.GetDamage(); 
    
    //Then it is set into the SetHealth function to be updated.
    SetHealth(totalNum);

    //This code here is if the health reach below zero then it wll not do anything or else it pring the stuff under else.
    if((Target.GetHealth() < 0) || (GetHealth() < 0)){

    }else{
      cout << Target.GetName() << " attack " << GetName() << " on the ground!" << endl;
      cout << "Damage Occuring " << Target.GetDamage() << endl;
      cout << GetName() << " attack " << Target.GetName() << " on the ground!" << endl;
      cout << "Damage Occuring " << GetDamage() << endl;
    }
    
  
    //This pretty much is copy code from the top, but they are conditions for ground vs ground
  }else if ((Target.GetTarget() == "Ground") && (GetTarget() == "Ground")){
    if ((Target.GetIsFlying() == 1) && (GetIsFlying() == 1)){
      cout << "This is going to be an Infinte loop, They cant attack each other." << endl;

    }else if ((Target.GetIsFlying() == 0) && (GetIsFlying() == 0)){
      totalNum = GetHealth() - Target.GetDamage();
      SetHealth(totalNum); 

      //This right here checks if the troop is flying or ground. it goes for all diffrent possibility so flying vs flying, ground vs ground, flying vs ground, 
      //ground vs flying.
      if((Target.GetHealth() < 0) || (GetHealth() < 0)){

      }else{ 
	cout << Target.GetName() << " attack " << GetName() << " on the ground!" << endl;
	cout << "Damage Occuring " << Target.GetDamage() << endl;
	cout << GetName() << " attack " << Target.GetName() << " on the ground!" << endl;
	cout << "Damage Occuring " << GetDamage() << endl;
      }
      
      //The rest of this is pretty much copy code.
    }else if ((Target.GetIsFlying() == 1) && (GetIsFlying() == 0)){
      totalNum = GetHealth() - Target.GetDamage();
      SetHealth(totalNum);

      if((Target.GetHealth() < 0) || (GetHealth() < 0)){

      }else{
	cout << Target.GetName() << " attack " << GetName() << " in the Sky!" << endl;
	cout << "Damage Occuring " << Target.GetDamage() << endl;
	cout << GetName() << " attack " << Target.GetName() << " on the ground!" << endl;
	cout << "Damage Occuring " << GetDamage() << endl;
      }

    }else if ((Target.GetIsFlying() == 0) && (GetIsFlying() == 1)){
      totalNum = GetHealth() - Target.GetDamage();
      SetHealth(totalNum);
      
      if((Target.GetHealth() < 0) || (GetHealth() < 0)){

      }else{
	cout << Target.GetName() << " attack " << GetName() << " on the ground!" << endl;
	cout << "Damage Occuring " << Target.GetDamage() << endl;
	cout << GetName() << " attack " << Target.GetName() << " in the Sky!" << endl;
	cout << "Damage Occuring " << GetDamage() << endl;
      }
    }
    
    // Conditions for Ground Vs Both
  }else if ((Target.GetTarget() == "Ground") && (GetTarget() == "Both")){

    if ((Target.GetIsFlying() == 1) && (GetIsFlying() == 1)){

      if(Target.GetIsFlying() == 1){
	  cout << "Your Attack Miss" << endl;
	  cout << Target.GetName() << " attack " << GetName() << " in the Sky!" << endl;
          cout << "Damage Occuring " << 0 << endl;
          cout << GetName() << " attack " << Target.GetName() << " in the Sky!" << endl;
          cout << "Damage Occuring " << GetDamage() << endl;


      }else if (GetIsFlying() == 1){
	totalNum = GetHealth() - Target.GetDamage();
	SetHealth(totalNum);
	
	if((Target.GetHealth() < 0) || (GetHealth() < 0)){

	}else{
	  cout << Target.GetName() << " attack " << GetName() << " in the Sky!" << endl;
	  cout << "Damage Occuring " << Target.GetDamage() << endl;
	  cout << GetName() << " attack " << Target.GetName() << " in the Sky!" << endl;
	  cout << "Damage Occuring " << GetDamage() << endl;
	}
      }
      
    }else if ((Target.GetIsFlying() == 0) && (GetIsFlying() == 0)){
      totalNum = GetHealth() - Target.GetDamage();
      SetHealth(totalNum);
      
      if((Target.GetHealth() < 0) || (GetHealth() < 0)){

      }else{
	cout << Target.GetName() << " attack " << GetName() << " on the ground!" << endl;
	cout << "Damage Occuring " << Target.GetDamage() << endl;
	cout << GetName() << " attack " << Target.GetName() << " on the ground!" << endl;
	cout << "Damage Occuring " << GetDamage() << endl;
      }


    }else if ((Target.GetIsFlying() == 1) && (GetIsFlying() == 0)){
      totalNum = GetHealth() - Target.GetDamage();
      SetHealth(totalNum);
      
      if((Target.GetHealth() < 0) || (GetHealth() < 0)){

      }else{
	cout << Target.GetName() << " attack " << GetName() << " in the Sky!" << endl;
	cout << "Damage Occuring " << Target.GetDamage() << endl;
	cout << GetName() << " attack " << Target.GetName() << " on the ground!" << endl;
	cout << "Damage Occuring " << GetDamage() << endl;
      }

    }else if ((Target.GetIsFlying() == 0) && (GetIsFlying() == 1)){
      if (Target.GetIsFlying() == 0){
	cout << "Your Attack Miss" << endl;
	cout << Target.GetName() << " attack " << GetName() << " on the ground!" << endl;
	cout << "Damage Occuring " << Target.GetDamage() << endl;
	cout << GetName() << " attack " << Target.GetName() << " in the Sky!" << endl;
	cout << "Damage Occuring " << GetDamage() << endl;

      
      }else if (GetIsFlying() == 1){
	totalNum = GetHealth() - Target.GetDamage();
        SetHealth(totalNum);

	if((Target.GetHealth() < 0) || (GetHealth() < 0)){

	}else{
	  cout << Target.GetName() << " attack " << GetName() << " on the ground!" << endl;
	  cout << "Damage Occuring " << Target.GetDamage() << endl;
	  cout << GetName() << " attack " << Target.GetName() << " in the Sky!" << endl;
	  cout << "Damage Occuring " << GetDamage() << endl;
	}
      }
    }
    //Conditions for Both Vs Ground
  }else if ((Target.GetTarget() == "Both") && (GetTarget() == "Ground")){
    
    if ((Target.GetIsFlying() == 1) && (GetIsFlying() == 1)){
      
      if(Target.GetIsFlying() == 1){
	totalNum = GetHealth() - Target.GetDamage();
	SetHealth(totalNum);
	
	if((Target.GetHealth() < 0) || (GetHealth() < 0)){
	  
	}else{
	  cout << Target.GetName() << " attack " << GetName() << " in the Sky!" << endl;
	  cout << "Damage Occuring " << Target.GetDamage() << endl;
	  cout << GetName() << " attack " << Target.GetName() << " in the Sky!" << endl;
	  cout << "Damage Occuring " << GetDamage() << endl;
	}

      }else if (GetIsFlying() == 1){
	cout << "Your Attack Miss" << endl;
	cout << Target.GetName() << " attack " << GetName() << " in the Sky!" << endl;
	cout << "Damage Occuring " << 0 << endl;
	cout << GetName() << " attack " << Target.GetName() << " in the Sky!" << endl;
	cout << "Damage Occuring " << GetDamage() << endl;
      }
      
    }else if ((Target.GetIsFlying() == 0) && (GetIsFlying() == 0)){
      totalNum = GetHealth() - Target.GetDamage();
      SetHealth(totalNum);
      
      if((Target.GetHealth() < 0) || (GetHealth() < 0)){
	
      }else{
	cout << Target.GetName() << " attack " << GetName() << " on the ground!" << endl;
	cout << "Damage Occuring " << Target.GetDamage() << endl;
	cout << GetName() << " attack " << Target.GetName() << " on the Sky!" << endl;
	cout << "Damage Occuring " << GetDamage() << endl;
      }
      
    }else if ((Target.GetIsFlying() == 1) && (GetIsFlying() == 0)){
      totalNum = GetHealth() - Target.GetDamage();
      SetHealth(totalNum);
      
      if((Target.GetHealth() < 0) || (GetHealth() < 0)){
	
      }else{
	cout << Target.GetName() << " attack " << GetName() << " in the Sky!" << endl;
	cout << "Damage Occuring " << Target.GetDamage() << endl;
	cout << GetName() << " attack " << Target.GetName() << " on the ground!" << endl;
	cout << "Damage Occuring " << GetDamage() << endl;
      }
      
    }else if ((Target.GetIsFlying() == 0) && (GetIsFlying() == 1)){
      if (Target.GetIsFlying() == 0){
	totalNum = GetHealth() - Target.GetDamage();
	SetHealth(totalNum);
	
	if((Target.GetHealth() < 0) || (GetHealth() < 0)){
	  
	}else{
	  cout << Target.GetName() << " attack " << GetName() << " on the ground!" << endl;
	  cout << "Damage Occuring " << Target.GetDamage() << endl;
	  cout << GetName() << " attack " << Target.GetName() << " in the Sky!" << endl;
	  cout << "Damage Occuring " << GetDamage() << endl;
	}
      }else if (GetIsFlying() == 1){
	cout << "Your Attack Miss" << endl;
	cout << Target.GetName() << " attack " << GetName() << " on the ground!" << endl;
	cout << "Damage Occuring " << 0 << endl;
	cout << GetName() << " attack " << Target.GetName() << " in the Sky!" << endl;
	cout << "Damage Occuring " << GetDamage() << endl;
      }
    }
  }
}

