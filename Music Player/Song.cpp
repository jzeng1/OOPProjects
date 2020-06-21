/*****************************************
 ** File:    Song.cpp
 ** Project: UMBC MUSIC, Fall 2018
 ** Author:  Jason Zeng
 ** Date:    11/19/2017
 ** Section: 10
 ** E-mail:  jzeng1@umbc.edu
 **
 **   The song class is very simple with just information about 
 **   the song. Artist, title, year, and rank are the member variable 
 **   included in this function.
 **
 ***********************************************/

#include <iostream>
#include <string>
#include "Song.h"


using namespace std;

//Name: Song - Default Constructor
//Precondition: None
//Postcondition: Creates a default song
Song::Song(){
}


//Name: Song - Overloaded Constructor
//Precondition: Requires title, artist, year and rank
//Postcondition: Creates a song based on passed parameters
Song::Song(string title, string artist, int year, int rank ){
  m_title = title;
  m_artist = artist;
  m_year = year;
  m_rank = rank;
}

//Name: Mutators and Accessors
//Precondition: None
//Postcondition: Sets and Gets private member variables
string Song::getTitle()const{ // return title
  return (m_title);

}

string Song::getArtist()const{ // return artist
  return (m_artist);

}

int Song::getYear()const{ // return year
  return (m_year);

}

int Song::getRank()const{ // return rank (1-100 from that year)
  return (m_rank);

}

void Song::setTitle(string title){
  m_title = title;
}


void Song::setArtist(string artist){
  m_artist = artist;
}

void Song::setYear(int year){
  m_year = year;
}

void Song::setRank(int rank){
  m_rank = rank;
}
