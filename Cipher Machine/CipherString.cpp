/****************************************************
 **File: CipherString.cpp
 **Author: Jason Zeng
 **Date: 10/29/2017
 **Section: 10
 **E-mail: jzeng1@umbc.edu
 **
 **This program is to implement a system that can be used to encrypt
 **or decrypt three different ciphers. These being Caesar Cipher,
 **Vigenere Cipher, Ong Cipher. We do this by using a linked List.
 ******************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <iomanip>

#include "Node.h"
#include "Cipher.h"
#include "CipherString.h"

using namespace std;

// Name: CipherString - default constructor
// Preconditions - None
// Postconditions - Creates a new CipherString
CipherString::CipherString(){
  m_head = NULL;
  m_size = 0;
}

// Name: CipherString - overloaded constructor
// Preconditions - None
// Postconditions - Creates a new CipherString (using char*)
CipherString::CipherString(const char *charString){
  
  //create new node for the link list
  m_head = new Node();
  m_size = 1;

  //inputing the char value form the txt file to the linked list
  m_head->setChar(charString[0]);
  m_head->setNext(NULL);

  Node *temp = m_head;

  int i = 1;
  while(charString[i] != NULL){

    temp->setNext(new Node());
    temp = temp->getNext();
    temp->setChar(charString[m_size]);
    m_size++;
    i++;
  }
}

// Name: ~CipherString - destructor
// Preconditions - None
// Postconditions - Destroys CipherString
CipherString::~CipherString(){
  Node *current = m_head;
  while(current != 0){
    Node *m_next = current->getNext();
    delete current;
    current = m_next;
    m_size--;
  }
  m_head = NULL;
}

// Name: loadMessage
// Preconditions - File (with text in it) is passed to function
// Postconditions - Opens file and loads one character at a time into the linked list
void CipherString::loadMessage(const char* theTxtFile){
  
  string theMessage;
  
  //opens the txt file
  ifstream myFile (theTxtFile, fstream::in);
  
  //move all the elements inside the txt file into a string.
  getline(myFile, theMessage, '\0');
  //cout << theMessage << endl;
  
  //close the text file that was open
  myFile.close();
  
  if(m_head == NULL){
    m_head = new Node();
    m_size = 1;
    
    m_head->setChar(theMessage[0]);
    m_head->setNext(NULL);
  }
  
  Node *temp = m_head;
  for(unsigned int i = 1; i < theMessage.length(); i++){
    
    temp->setNext(new Node());
    temp = temp->getNext();
    temp->setChar(theMessage[m_size]);
    m_size++;
  }
}

// Name: addCharacter
// Preconditions - Linked list exists
// Postconditions - Adds character to end of linked list
void CipherString::addCharacter(char theChar){
  Node *temp = m_head;
  for(int i = 1; i < m_size; i++){

    temp->setNext(new Node());
    temp = temp->getNext();
    temp->setChar(theChar);
    m_size++;
  }
}

// Name: encryptOng
// Preconditions - Linked list exists
// Postconditions - For each consonent, adds a node with "o", adds a node with "n"
// adds a node with "g". Every "letter" is separated with a "-" and each word is
// seperated by a space.
void CipherString::encryptOng(){
  string text = "";
  string encryptOngs = "";
  string theWord = "ong";

  if(m_size == 0){
    cout << "The linked list is empty" << endl;

  }else{
    Node *temp = m_head;
    for(int i = 0; i < m_size; i++){
      text = text + (temp->getChar());
      temp = temp->getNext();
    }
  }

  for(unsigned int i; i < text.length();i++){
    if ((text[i] == 'a') || (text[i] == 'e') || (text[i] == 'i') || (text[i] == 'o') || (text[i] == 'u') || (text[i] == ' ')){ 
      encryptOngs = encryptOngs + text[i] + " ";

    }else if ((text[i] == 'A') || (text[i] == 'E') || (text[i] == 'I') || (text[i] == 'O') || (text[i] == 'U') || (text[i] == ' ')){
      encryptOngs = encryptOngs + text[i] + " ";

    }else{
      encryptOngs = encryptOngs + text[i] + theWord + " "; 
    }
  }
  cout << encryptOngs << endl;
}

// Name: decryptOng
// Preconditions - Linked list exists
// Postconditions - For each consonent, adds a node with "o", adds a node with "n"
// adds a node with "g". Every "letter" is separated with a "-" and each word is
// seperated by a space
void CipherString::decryptOng(){
  string text = "";

  if(m_size == 0){
    cout << "The linked list is empty" << endl;

  }else{
    Node *temp = m_head;
    for(int i = 0; i < m_size; i++){
      text = text + (temp->getChar());
      temp = temp->getNext();
    }
    cout << text << endl;
  }
}

// Name: encryptCaesar
// Preconditions - Linked list exists
// Postconditions - Shifts each character "right" by the int provided.
// See project document for additional details.
void CipherString::encryptCaesar(int numberOfShifts){
      
  //you need to be able to move this into here.
  string text = "";
  string encryptMessage = "";

  if(m_size == 0){
    cout << "The linked list is empty" << endl;

  }else{
    Node *temp = m_head;
    for(int i = 0; i < m_size; i++){
      text = text + (temp->getChar());
      temp = temp->getNext();
    }
  }

  //Iterates through the string of text
  for (unsigned int i = 0; i < text.length(); i++){
    
    //This is just formatting so it look better so that the messages are not
    //put together with no space.
    if (text[i] == ' '){
      encryptMessage += ' ';
    }
    
    //Checks for upper and lower case letters
    if (isupper(text[i])){
      encryptMessage += char(int(text[i] + numberOfShifts - 65) %26 + 65);
      
      //using the ASCII table i had set a range of 1 - 25 Shift
      //where all the letters in the ASCII table.
    }else if(islower(text[i])){
      encryptMessage += char(int(text[i] + numberOfShifts - 97) %26 + 97);
    }
  }
  cout << encryptMessage << endl;
}

// Name: decryptCaesar
// Preconditions - Linked list exists
// Postconditions - Shifts each character "left" by the int provided.
// See project document for additional details.
void CipherString::decryptCaesar(int numberOfShifts){

  //I got to somehow get this encrypt message to here
  string text = "";
  string encryptMessage = "";
  string decryptMessage = "";

  //this iterates through the linked list and concadinates it to a string
  if(m_size == 0){
    cout << "The linked list is empty" << endl;
    
  }else{
    Node *temp = m_head;
    for(int i = 0; i < m_size; i++){
      text = text + (temp->getChar());
      temp = temp->getNext();
    }
  }

  for (unsigned int i = 0; i < text.length(); i++){

    //This is just formatting so it look better so that the messages are not
    //put together with no space.
    if (text[i] == ' '){
      encryptMessage += ' ';
    }

    //Checks for upper and lower case letters
    if (isupper(text[i])){
      encryptMessage += char(int(text[i] + numberOfShifts - 65) %26 + 65);

      //using the ASCII table i had set a range of 1 - 25 Shift
      //where all the letters in the ASCII table.
    }else if(islower(text[i])){
      encryptMessage += char(int(text[i] + numberOfShifts - 97) %26 + 97);
    }
  }

  //Iterates through the string of text
  for (unsigned int i = 0; i < encryptMessage.length(); i++){
    
    //This is just formatting so it look better so that the messages are not 
    //put together with no space.
    if (text[i] == ' '){
      decryptMessage += ' ';
    }
    
    //Checks for upper and lower case letters
    if (isupper(encryptMessage[i])){

      //using the ASCII table i had set a range of 1 - 25 Shift 
      //where all the letters in the ASCII table.
      decryptMessage += char(int(encryptMessage[i] - numberOfShifts - 65) %26 + 65);

    }else if(islower(text[i])){
      decryptMessage += char(int(encryptMessage[i] - numberOfShifts - 97) %26 + 97);
    }
  }
  cout << decryptMessage << endl;
}

// Name: encryptVigenere
// Preconditions - Linked list exists
// Postconditions - Shifts each character by the character (in string) provided.
// See project document for additional details.
void CipherString::encryptVigenere(string keyWord){
  string text = "";
  string encryptMessage = "";

  //iterating through a linked list to get the the text in the linked list char
  //by char.
  if(m_size == 0){
    cout << "The linked list is empty" << endl;

  }else{
    Node *temp = m_head;
    for(int i = 0; i < m_size; i++){
      text = text + (temp->getChar());
      temp = temp->getNext();
    }
  }

  int totalValue = 0;
  int keepTrack = 0;
  int count = -1;
  int lengthKey = 0;
  
  for (unsigned int i = 0; i < text.length(); i++){
    
    //This is the length of the keyWord
    lengthKey = (keyWord.length() - 1);
    
    count++;
    //if there are spaces then the count is set back by 1 
    if (text[i] == ' '){
      encryptMessage += ' ';
      count = count - 1;

    //if the text is lowercase it goes here.
    }else if (islower(text[i])){
      keepTrack = int((((text[i] - 97) + (keyWord[count] - 97)) %26) + 97) + 1;
      
      //This checks to see that the char must be in range in the ASCII table if over 122 then it resets back to 96 
      //counting by how much it went pass 122.
      if (keepTrack > 122){
	totalValue = keepTrack - 122;
	encryptMessage += char(int(96 + totalValue));
	
	//if this is in range then it just goes here and puts all the characters togeter
      }else{
	encryptMessage += char(int((((text[i] - 97) + (keyWord[count] - 97)) %26) + 97) + 1);
      }
      //TO RIGHT HERE
      //if the text is uppercase it goes here.
    }else if (isupper(text[i])){
      keepTrack = int((((text[i] - 65) + (keyWord[count] - 65)) %26) + 65) + 1;
      
      //this is pretty much the same concept that is applied to the code in the top.
      if (keepTrack > 90){
	totalValue = keepTrack - 90;
	encryptMessage += char(int(64 + totalValue));
	
      }else{
	encryptMessage += char(int((((text[i] - 65) + (toupper(keyWord[count]) - 65)) %26) + 65) + 1);
      }
    }

    //This is added to reset the count once it reaches the end of the key word.
    if (count == lengthKey){
      count = -1;
    } 
  }
  cout << encryptMessage << endl;
  m_encrypt = encryptMessage;
}
  

// Name: decryptVigenere
// Preconditions - Linked list exists
// Postconditions - Shifts each character by the character (in string) provided
// See project document for additional details.
void CipherString::decryptVigenere(string keyWord){

  string text = m_encrypt;
  string decryptMessage = "";

  int totalValue = 0;
  int keepTrack = 0;
  int count = -1;
  int lengthKey = 0;

  int keyWordCount = 0;
  int textCount = 0;
  int numShifts = 0;

  for (unsigned int i = 0; i < text.length(); i++){
    
    //This is the length of the keyWord
    lengthKey = (keyWord.length() - 1);

    count++;
    //if there are spaces then the count is set back by 1
    if (text[i] == ' '){
      decryptMessage += ' ';
      count = count - 1;
      
    }else if (islower(text[i])){
      keepTrack = int((((text[i] - 97) - (keyWord[count] - 97)) %26) + 97) - 1;
      keyWordCount = (int(((keyWord[count] - 97) %26) +97));
      textCount = (int(((text[i] - 97) %26) +97));

      //This checks to see that the char must be in range in the ASCII table if less than 97 then it resets back to 96
      //counting by how much it went pass 122.
      if (keepTrack < 97){
	numShifts = textCount - 97;
        totalValue = ((keyWordCount - 97) + 1) - numShifts;
        decryptMessage += char(int(123 - totalValue));
	
      }else{
	decryptMessage += char(int((((text[i] - 97) - (keyWord[count] - 97)) %26) + 97) - 1);	
      }

    }else if (isupper(text[i])){
      keepTrack = int((((text[i] - 65) - (toupper(keyWord[count]) - 65)) %26) + 65) - 1;
      keyWordCount = (int(((keyWord[count] - 97) %26) +97));
      textCount = (int(((text[i] - 65) %26) +65));
      
      if (keepTrack < 65){
	numShifts = textCount - 65;
        totalValue = ((keyWordCount - 97) + 1) - numShifts;
	decryptMessage += char(int(91 - totalValue));
	
      }else{
	decryptMessage += char(int((((text[i] - 65) - (toupper(keyWord[count]) - 65)) %26) + 65) - 1);
      }
    }
    if (count == lengthKey){
      count = -1;
    }
  }
  cout << decryptMessage << endl; 
}

// Name: getSize
// Preconditions - Linked list exists
// Postconditions - Return size of structure
int CipherString::getSize(){
  return m_size;
}

// Name: operator<< (overloaded insertion operator)
// Preconditions - Linked list exists
// Postconditions - Iterates over the linked list and prints each char in each node
ostream& operator<<(ostream &theOutput, const CipherString &linkedList){
  
  Node *temp = linkedList.m_head;
  if (temp != NULL){
      
    //this traverse through the linked list then is being print out in 
    //Cipher.cpp in the printString() function.
      while (temp->getNext() != NULL){
	theOutput << temp->getChar();
	temp = temp->getNext();
      }
      theOutput << temp->getChar() << endl;
    }
  return theOutput;
}


