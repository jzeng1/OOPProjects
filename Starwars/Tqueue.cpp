
/*****************************************
 ** File:    Tqueue.cpp
 ** Project: StarWars
 ** Author:  Jason Zeng
 ** Date:    5/08/2018
 ** Section: 22
 ** E-mail:  Jzeng1@umbc.edu
 **
 **   This program manages the teams of ships. it
 **   uses a dynamically allocated array to store the 
 **   infomation about whatever it is designed to hold
 **   in a template class.
 **
 ***********************************************/

#ifndef TQUEUE_H
#define TQUEUE_H

#include <iostream>
#include <cstdlib>
//#include "Ship.h"

using namespace std;

template <class T>
class Tqueue {
public:
  //Name: Tqueue - Default Constructor
  //Precondition: None (Must be templated)
  //Postcondition: Creates a queue using dynamic array
  Tqueue(); //Default Constructor
  //Name: Copy Constructor
  //Precondition: Existing Tqueue
  //Postcondition: Copies an existing Tqueue
  Tqueue( const Tqueue<T>& x ); //Copy Constructor
  //Name: Destructor
  //Precondition: Existing Tqueue
  //Postcondition: Destructs existing Tqueue
  ~Tqueue(); //Destructor
  //Name: enqueue
  //Precondition: Existing Tqueue
  //Postcondition: Adds item to back of queue.
  //If queue is at capacity, doubles size and copies everything starting at 0
  void enqueue(T data); //Adds item to queue (to back)
  //Name: dequeue
  //Precondition: Existing Tqueue
  //Postcondition: Removes item from front of queue
  //If queue is less than half capacity, halves capacity
  //and copies everything starting at 0 
  void dequeue(); //Removes item from queue (from front)
  //Name: queueFront
  //Precondition: Existing Tqueue
  //Postcondition: Returns front item in queue (does not remove it)
  T& queueFront();    // Retrieve front (does not remove it)
  //Name: getBack()
  //Precondition: Existing Tqueue
  //Postcondition: Retrieve int of m_back
  int getBack();
  //Name: getFront()
  //Precondition: Existing Tqueue
  //Postcondition: Retrieve int of m_front
  int getFront();
  //Name: isEmpty
  //Precondition: Existing Tqueue
  //Postcondition: Returns 1 if queue is empty else 0
  int isEmpty(); //Returns 1 if queue is empty else 0
  //Name: size
  //Precondition: Existing Tqueue
  //Postcondition: Returns size of queue (not capacity but m_back - m_front)
  int size(); //Returns size of queue
  //Name: Overloaded assignment operator
  //Precondition: Existing Tqueue
  //Postcondition: Sets one Tqueue to same as a second Tqueue using =
  Tqueue<T>& operator=( const Tqueue<T> &y); //Overloaded assignment operator for queue
  //Name: Overloaded [] operator
  //Precondition: Existing Tqueue
  //Postcondition: Returns object from Tqueue using []
  T& operator[] (int x);//Overloaded [] operator to pull data from queue
  //Name: displayTqueue (Test function)
  //Precondition: Existing Tqueue
  //Postcondition: Used to display all members in the Tqueue
  void displayTqueue();
private:
  T* m_data; //Data of the queue (Must be dynamically allocated array)
  int m_front; //Front of the queue
  int m_back; //Back of the queue
  int m_capacity; //Capacity of the queue
};

//Name: Tqueue - Default Constructor
//Precondition: None (Must be templated)
//Postcondition: Creates a queue using dynamic array
template <class T>
Tqueue<T>::Tqueue(){ //Default Constructor
  m_front = 0;
  m_back = 0;
  m_capacity = 1;
  m_data = new T[m_capacity];
}

//Name: Copy Constructor
//Precondition: Existing Tqueue
//Postcondition: Copies an existing Tqueue
template <class T>
Tqueue<T>::Tqueue( const Tqueue<T> &x ){ //Copy Constructor

  //copy the right hand side to the left hand side of things
  m_front = x.m_front;
  m_back = x.m_back;
  m_capacity = x.m_capacity;

  m_data = new T[m_capacity];

  for(int i = m_front; i < m_back; i++){
    m_data[i] = x.m_data[i];
  }
}

//Name: Destructor
//Precondition: Existing Tqueue
//Postcondition: Destructs existing Tqueue
template <class T>
Tqueue<T>::~Tqueue(){ //Destructor
 
  //clears the memory leaks for tqueue
  delete [] m_data;
  m_data = NULL;
}

//Name: enqueue
//Precondition: Existing Tqueue
//Postcondition: Adds item to back of queue.
//If queue is at capacity, doubles size and copies everything starting at 0
template <class T>
void Tqueue<T>::enqueue(T data){ //Adds item to queue (to back)

  //if size of the queue reach max capacity it double the size
  if(size() == m_capacity){
    m_capacity = m_capacity * 2;
    
    //create a temp dynamically allocated array  
    T* tempArr = new T[m_capacity];
  
    //this changes the front of the array
    for(int i = m_front; i < m_back; i++){
      tempArr[i - m_front] = m_data[i];
    }

    //deletes the old array storage the new one in 
    delete [] m_data;
    m_data = tempArr;
    
  }

  //set the data to m_data
  m_data[m_back++] = data;
}

//Name: dequeue
//Precondition: Existing Tqueue
//Postcondition: Removes item from front of queue
//If queue is less than half capacity, halves capacity
//and copies everything starting at 0
template <class T>
void Tqueue<T>::dequeue(){ //Removes item from queue (from front)

  //if m_front is greater than m_back then it increase the size 
  //this code is here so that if it dequeue more than what it acutally holding 
  //then it ignores the count.
  if(m_front < m_back){
    m_front++;

    if(size() < m_capacity / 2){
      m_capacity = m_capacity / 2;
    }

    T* tempArr = new T[m_capacity];

    for(int i = m_front; i < m_back; i++){
      tempArr[i - m_front] = m_data[i];
    }

    delete [] m_data;
    m_data = tempArr;
    m_back = m_back - m_front;
    m_front = 0;
  }
}  
  
//Name: queueFront
//Precondition: Existing Tqueue
//Postcondition: Returns front item in queue (does not remove it)
template <class T>
T& Tqueue<T>::queueFront(){    // Retrieve front (does not remove it)
  return m_data[m_front];
}

//Name: getBack()
//Precondition: Existing Tqueue
//Postcondition: Retrieve int of m_back
template <class T>
int Tqueue<T>::getBack(){
  return m_back;
}

//Name: getFront()
//Precondition: Existing Tqueue
//Postcondition: Retrieve int of m_front
template <class T>
int Tqueue<T>::getFront(){
  return m_front;
}

//Name: isEmpty
//Precondition: Existing Tqueue
//Postcondition: Returns 1 if queue is empty else 0
template <class T>
int Tqueue<T>::isEmpty(){ //Returns 1 if queue is empty else 0

  //if the size of the queue is zero then return 1 else 0 
  if(size() == 0){
    return 1;

  }else{
    return 0;
  }
}

//Name: size
//Precondition: Existing Tqueue
//Postcondition: Returns size of queue (not capacity but m_back - m_front)
template <class T>
int Tqueue<T>::size(){ //Returns size of queue
  return m_back - m_front;
}

//Name: Overloaded assignment operator
//Precondition: Existing Tqueue
//Postcondition: Sets one Tqueue to same as a second Tqueue using =
template <class T>
Tqueue<T>& Tqueue<T>::operator=( const Tqueue<T> &y){ //Overloaded assignment operator for queue.
   
  //set everything back to zero just in case
  m_front = 0;
  m_back = 0;
  m_capacity = 0;
 
  //delete the old 
  delete [] m_data;
  m_data = NULL;
 
  //do a deep copy of the m_data.
  m_front = y.m_front;
  m_back = y.m_back;
  m_capacity = y.m_capacity;

  m_data = new T[m_capacity];

  for(int i = m_front; i < m_back; i++){
    m_data[i] = y.m_data[i];
  }

  return *this;
}

//Name: Overloaded [] operator
//Precondition: Existing Tqueue
//Postcondition: Returns object from Tqueue using []
template <class T>
T& Tqueue<T>::operator[] (int x){//Overloaded [] operator to pull data from queue
  return m_data[x-m_front];
}

//Name: displayTqueue (Test function)
//Precondition: Existing Tqueue
//Postcondition: Used to display all members in the Tqueue
template <class T>
void Tqueue<T>::displayTqueue(){
  
  //iterating through the m_data to see what inside the dynamically allocated array.
  for(int i = m_front; i < m_back; i++){
    cout << m_data[i] << endl;;
  }
}


// This is the type of code you should test your Tqueue with
// Once you have coded all of the functions, compile just Tqueue and test it

/*int main () {
  cout << "newQ" << endl;
  Tqueue<int> newQ;
  cout << "This is enqueue" << endl;
  //newQ.displayTqueue();
  newQ.enqueue(10);
  //newQ.displayTqueue();
  newQ.enqueue(20);
  //newQ.displayTqueue();
  newQ.enqueue(30);
  newQ.displayTqueue();

  cout << "This is dequeue" << endl;
  newQ.dequeue();
  //newQ.displayTqueue();
  newQ.dequeue();
  //newQ.displayTqueue();
  newQ.dequeue();
  //newQ.displayTqueue();
  //newQ.dequeue();
  //newQ.dequeue();
  //newQ.dequeue();
  //newQ.dequeue();
  newQ.dequeue();
  
  newQ.displayTqueue();

  cout << "add after dequeuing" << endl;
  newQ.enqueue(40);
  newQ.enqueue(50);
  newQ.enqueue(60);
  newQ.enqueue(70);
  newQ.enqueue(80);
  newQ.displayTqueue();
  
 
  cout << "newQ2 using assignment operator" << endl;
  Tqueue<int> newQ2;
  newQ2 = newQ;
  newQ2.displayTqueue();

  cout << "newQ3 using copy constructor" << endl;
  Tqueue<int> newQ3(newQ2);
  newQ3.displayTqueue();
 
  cout << endl << "newQ after two dequeue" << endl;
  newQ.dequeue();
  newQ.dequeue();
  newQ.dequeue();
  newQ.enqueue(100);
  newQ.dequeue();
  //newQ.enqueue(200);
  //newQ.dequeue();
  newQ.displayTqueue();
  cout << endl;

  cout << "newQ4 using copy with deletes" << endl;
  Tqueue<int> newQ4(newQ);
  newQ4.dequeue();
  newQ4.dequeue();
  newQ4.dequeue();
  newQ4.dequeue();
  newQ4.displayTqueue();

  newQ3 = newQ4;
  newQ3.displayTqueue();
  
  Tqueue<int> newQ5;

  for(int i = 0; i < 400; i++){
    newQ5.enqueue(i);
  }

  cout << "size()=" << newQ5.size() << endl;
  newQ5.displayTqueue();
  

  return 0;
  }*/


#endif
