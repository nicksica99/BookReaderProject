
/*****************************
** File: Book.cpp
** Project: CMSC 202 Project 5, Spring 2019
** Author: Nick Sica
** Date: 4/22/19
** Section: 07
** E-mail: nsica1@umbc.edu
**
** This file contains the main code for the Book class, it allows
** for the creation of Book objects and allows the user to set and get
** the Book's properties 
***************************/

 
#include "Book.h"
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
//formatting constants
const int WIDTH = 45;
const int MEDIUMWIDTH = 25;
const int SMALLWIDTH = 10;
const char SEPARATE = ' ';

//Name: Book - Default Constructor
//Precondition: None
//Postcondition: Creates a default book
Book::Book() {
  //intializes all the member variables
  m_title = "";
  m_author = "";
  m_rank = 0;
  m_price = 0.0;
}

//Name: Book - Overloaded Constructor
//Precondition: Requires title, author, rank and price (in dollars)
//Postcondition: Creates a book based on passed parameters
Book::Book(string title, string author, int rank,  double price) {
  //creates a book based on passed parameters
  m_title = title;
  m_author = author;
  m_rank = rank;
  m_price = price;
}
//Name: getTitle 
//Precondition: There are books
//Postcondition: returns the title of the book
string Book::getTitle()const {

  return m_title;// return title
}

//Name: getAuthor
//Precondition: There are books
//Postcondtion: Returns the author of the book
string Book::getAuthor()const {

  return m_author;// return author

}
//Name: getRank
//Precondition: There are books
//Postcondtion: Returns the rank of the book
int Book::getRank()const {

  return m_rank;// return rank (1-150)
}
//Name: getPrice
//Precondition: There are books
//Postcondtion: Returns the price of the book
double Book::getPrice()const {

  return m_price;// return price
}
//Name: setTitle
//Precondition: There are books
//Postcondtion: Sets the title of the book
void Book::setTitle(string title) {

  m_title = title; //set the title
}

//Name: setAuthor
//Precondition: There are books
//Postcondtion: Sets the author of the book
void Book::setAuthor(string author) {

  m_author = author; //set the author
}

//Name: setRank
//Precondition: There are books
//Postcondtion: Sets the rank of the book
void Book::setRank(int rank) {

  m_rank = rank; //set rank
}

//Name: setPrice
//Precondition: There are books
//Postcondtion: Sets the price of the book
void Book::setPrice(double price) {

  m_price = price; //set price

}

// Overloaded << - Prints the details of a book
*// Preconditions: all variables are set valid
// Postconditions: returns an ostream with details of a book
ostream& operator<<(ostream& output, Book& myBook) {
  //formats the output when the << operator called on a book object
  output << left << setw(SMALLWIDTH) << setfill(SEPARATE) << myBook.getRank() //rank
	 << setw(WIDTH) << setfill(SEPARATE) << myBook.getTitle() //title
	 << setw(MEDIUMWIDTH) << setfill(SEPARATE) << myBook.getAuthor() //author
	 << setw(0) << setfill(SEPARATE) << "($"
	 << setw(0) << setfill(SEPARATE)
	 << myBook.getPrice() << ")" << endl; //price
	  
	 

  return output;
}
	 

// Overloaded < - compares the price of the book
// Preconditions: all variables are set valid
// Postconditions: returns true if lhs price is less than rhs price
bool operator< (Book const & lhs, Book const & rhs) {
  bool prices;
  //if the price is less than bool = true
  if(lhs.getPrice() < rhs.getPrice()) {
    prices = true;
  }
  else {
    prices = false;
  }
  //returns the boolean
  return prices;
}









