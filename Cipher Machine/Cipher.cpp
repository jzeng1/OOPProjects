/****************************************************
 **File: Cipher.cpp
 **Author: Jason Zeng
 **Date: 10/29/2017
 **Section: 10
 **E-mail: jzeng1@umbc.edu
 **
 **This program is to implement a system that can be used to encrypt 
 **or decrypt three different ciphers. These being Caesar Cipher,
 **Vigenere Cipher, Ong Cipher. We do this by using a linked List.
 ******************************************************/

#include "CipherString.h"
#include "Cipher.h"
#include <string>
#include <fstream>

enum Mode{CAESAR=1, ONG=2, VIGENERE=3};

// Name: Cipher(char) - Overloaded constructor for Caesar cipher
// Preconditions - Caesar cipher is defined
// Postconditions - Constructor for the Caesar cipher (sets m_mode to CAESAR)
Cipher::Cipher(char theChar){
  m_mode = CAESAR;
  m_caesar_key = theChar;
}

// Name: Cipher(string) - Overloaded constructor for Vigenere cipher
// Preconditions - Vigenere cipher is defined
// Postconditions - Constructor for the Vigenere cipher (sets m_mode to VIGENERE)
Cipher::Cipher(string theWord){
  m_mode = VIGENERE;
  m_vig_key = theWord;
}

// Name: Cipher() - Overloaded constructor for Vigenere cipher
// Preconditions - Ong Cipher is defined
// Postconditions - Constructor for the Ong cipher (sets m_mode to ONG)
Cipher::Cipher(){
  m_mode = ONG;
}

//Name: ~Cipher() - Destructor 
//Preconditions - None
//postconditons - Destructor for m_cipherString
Cipher::~Cipher(){
  //delete m_cipherString;
}

// Name: setPlainText
// Preconditions - File with text is available (in current directory)
// Postconditions - Stores file text in m_cipherString
void Cipher::setPlainText(string theTextFile){
  m_cipherString = new CipherString();
  //char* test = theTextFile;
  m_cipherString->loadMessage(theTextFile.c_str());
}

// Name: encrypt
// Preconditions - m_cipherString populated
// Postconditions - Calls correct encryption function based on the cipher chosen
void Cipher::encrypt(){

  //Create the object calling it theKey to be able to call function in the 
  //ChipherString Class.

  
  //if the user selects a number it goes to either Caesar, Ong, or Vigenere Bas\ed on
  //what it corralates to in enum.
  if (m_mode == CAESAR){
    m_cipherString->encryptCaesar(m_caesar_key);

  }else if (m_mode == ONG){
    m_cipherString->encryptOng();

  }else if (m_mode == VIGENERE){
    m_cipherString->encryptVigenere(m_vig_key);
  }  
}

// Name: decrypt
// Preconditions - m_cipherString populated and encrypted
// Postconditions - Calls correct decryption function based on the cipher chosen
void Cipher::decrypt(){

  if (m_mode == CAESAR){
    m_cipherString->decryptCaesar(m_caesar_key);

  }else if (m_mode == ONG){
    m_cipherString->decryptOng();

  }else if (m_mode == VIGENERE){
    m_cipherString->decryptVigenere(m_vig_key);
  }
}

// Name: changeKey
// Preconditions - key exists
// Postconditions - Key is updated
void Cipher::changeKey(string theWord){
  
  //Need to create an object to be able to access function in CipherString.
  
  if (m_mode == CAESAR){

    int changedKey;
    cout << "Please enter your key (positive integer): ";
    cin >> changedKey;

    //Takes in the updated key to both encrypt/decrypt functions.
    m_cipherString->encryptCaesar(changedKey);
    m_cipherString->decryptCaesar(changedKey);
    
  }else if (m_mode == VIGENERE){
    
    string changedKey;
    cout << "Please enter your key (word): ";
    cin >> changedKey;

    //Takes in the updated key to both encrypt/decrypt functions.
    m_cipherString->encryptVigenere(changedKey);
    m_cipherString->decryptVigenere(changedKey);
  }
}

// Name: printString
// Preconditions - m_cipherString populated
// Postconditions - Outputs the value of m_cipherString
void Cipher::printString(){
  cout << *m_cipherString << endl;
}
