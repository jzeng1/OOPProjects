/*****************************************
 ** File:    MusicPlayer.cpp
 ** Project: UMBC MUSIC, Fall 2018
 ** Author:  Jason Zeng
 ** Date:    11/19/2017
 ** Section: 10
 ** E-mail:  jzeng1@umbc.edu
 **
 **   The Music player controls the music catalog. It also 
 **   manages copying songs from the catalog into the play list
 **   
 ***********************************************/


#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "Song.h"
#include "Tqueue.cpp"
#include "MusicPlayer.h"

const static int MAX_YEAR = 2013;
const static int MIN_YEAR = 1983;
const static int MAX_NUMBER = 3100;

using namespace std;

//Name: MusicPlayer - Default Constructor
//Precondition: None
//Postcondition: Creates a new MusicPlayer
MusicPlayer::MusicPlayer(){  
}



//Name: MusicPlayer - Overloaded Constructor
//Precondition: None
//Postcondition: Creates a new MusicPlayer and passes the music filename
MusicPlayer::MusicPlayer(string filename){

  //this passes the filename to the LoadCatalog function
  LoadCatalog(filename);
}



//Name: ~MusicPlayer - Destructor
//Precondition: None
//Postcondition: Creates a new MusicPlayer
MusicPlayer::~MusicPlayer(){ 

  //this take cares of the memory leaks that occur when creating a dynamically 
  //alocated memory in the object pointer inside the vector.
  for(unsigned int i = 0; i < m_songCatalog.size(); ++i){
    delete m_songCatalog[i];
  }
}


//Name: LoadCatalog(string filename)
//Precondition: Requires filename
//Postcondition: Loads the file into the m_songCatalog (as songs)
void MusicPlayer::LoadCatalog(string filename){
  
  ifstream myFile (filename.c_str());

  string theNumber,theYear;
  string theSong,theAuthor;
  string theLine;

  while(getline(myFile,theLine)){

    stringstream linestream(theLine);

    //the delimiter is a comma which is ignored which pass data into
    //sperate variables.
    getline(linestream, theNumber, ',');
    getline(linestream, theSong, ',');
    getline(linestream, theAuthor, ',');
    getline(linestream, theYear, ',');
    
    //changes the string to an integer using atof function
    int theNumberInt = atof(theNumber.c_str());
    int theYearInt = atof(theYear.c_str());
    
    Song* infoSong = new Song(theSong,theAuthor,theYearInt,theNumberInt);

    //storage the info from the txt file into the vector called m_songCatalog.
    m_songCatalog.push_back(infoSong);
   
  }  

  //closes the file
  myFile.close();
}


//Name: MainMenu
//Precondition: None
//Postcondition: Manages the application and the menu
void MusicPlayer::MainMenu(){

  int userChoice = 0;

  do{
    
    cout << "What would you like to do?" << endl;
    cout << "1. Display Songs by Year" << endl;
    cout << "2. Add Song" << endl;
    cout << "3. Display Playlist" << endl;
    cout << "4. Quit" << endl;
    
    cin >> userChoice;

    //check for validation
    while((userChoice < 1) || (userChoice > 4)){
      cout << "That is not a valid option" << endl;
      cout << "Which option would you like to choice? ";
      cin >> userChoice;
    }
    
    if(userChoice == 1){
      DisplaySongs();

    }else if(userChoice == 2){
      AddSong();

    }else if (userChoice == 3){
      DisplayPlaylist();
    }

  }while(userChoice != 4);
  cout << "Thank You for using the UMBC Music Player!" << endl;
}


//Name: DisplaySongs
//Precondition: User enters year (1983-2013)
//Postcondition: Lists all songs (numbered) for that year
void MusicPlayer::DisplaySongs(){
  int userYear;

  //ask user input on year
  cout << "Which year whould you like to display? (1983-2013)" << endl;
  cin >> userYear;
  
  //check if the year is with in range
  while((userYear < MIN_YEAR) || (userYear > MAX_YEAR)){
    cout << "That is not a valid option" << endl;
    cout << "Which option would you like to choice? ";
    cin >> userYear;
  }
  
  cout << "******" << userYear << "******" << endl;

  //iterating through the vector and print out the song content.
  for(unsigned int i = 0; i < m_songCatalog.size(); i++){
    if(m_songCatalog.at(i)->getYear() == userYear){
      cout << i + 1 << ". " << m_songCatalog.at(i)->getTitle() << " by " << m_songCatalog.at(i)->getArtist() << endl;
    }
  }
}


//Name: AddSong
//Precondition: m_songCatalog is populated
//Postcondition: Displays the current list and adds a song (by year)
//               to the m_playList
void MusicPlayer::AddSong(){

  int userNumber,theYear;
  int theNumberInt;
  string theTitle,theAuthor;
  
  //This checks if the playlist is empty or not 
  if(m_playList.isEmpty() == 1){

    cout << "***Current Playlist is Empty***" << endl;
    cout << "Choose the song you would like to add to the playlist." << endl;
  
    DisplaySongs();
    
    cout << "Enter the number of the song you would like to add: " << endl;
    cin >> userNumber;
  
    //Check if the userNumber is in range of the amount of songs in the txt file.
    while((userNumber <= 0) || (userNumber > MAX_NUMBER)){
      cout << "That is not a valid option" << endl;
      cout << "Enter the number of the song you would like to add: ";
      cin >> userNumber;
    }
    
    //gathering the infomation seting it to a variable from the vector m_songCatalog
    //which is a pointer to the Song object.
    theNumberInt = m_songCatalog.at(userNumber - 1)->getRank();
    theTitle = m_songCatalog.at(userNumber - 1)->getTitle();
    theAuthor = m_songCatalog.at(userNumber - 1)->getArtist();
    theYear = m_songCatalog.at(userNumber - 1)->getYear();
    
    //Passing the all of the infomation to the Song overloaded constructor.
    Song theInfo(theTitle,theAuthor,theYear,theNumberInt);
    
    //sending all the info of song to enqueue which is then dynamically aloccated to an array 
    //in Tqueue.cpp
    m_playList.enqueue(theInfo);
     
    //if the queue is not empty then it goes here.
  }else if(m_playList.isEmpty() == 0){
    
    cout << "Choose the song you would like to add to the playlist." << endl;

    DisplaySongs();

    cout << "Enter the number of the song you would like to add: " << endl;
    cin >> userNumber;

    while((userNumber <= 0) || (userNumber > MAX_NUMBER)){
      cout << "That is not a valid option" << endl;
      cout << "Enter the number of the song you would like to add: ";
      cin >> userNumber;
    }

    theNumberInt = m_songCatalog.at(userNumber - 1)->getRank();
    theTitle = m_songCatalog.at(userNumber - 1)->getTitle();
    theAuthor = m_songCatalog.at(userNumber - 1)->getArtist();
    theYear = m_songCatalog.at(userNumber - 1)->getYear();
    
    //Passing the all of the infomation to the Song overloaded constructor.
    Song theInfo(theTitle,theAuthor,theYear,theNumberInt);

    m_playList.enqueue(theInfo);

  }
}


//Name: DisplayPlaylist
//Precondition: None (can be empty)
//Postcondition: Displays the playlist
void MusicPlayer::DisplayPlaylist(){

  //displaying all the song that the user has chosen in the play list. 
  for(int i = 0; i < m_playList.size(); i++){
    cout << i + 1 << ". " << m_playList[i].getTitle() << " by " << m_playList[i].getArtist() << " from " << m_playList[i].getYear() << endl;
  }
}
