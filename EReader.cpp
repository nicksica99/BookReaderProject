/*****************************
 ** File: EReader.cpp
 ** Project: CMSC 202 Project 5, Spring 2019
 ** Author: Nick Sica
 ** Date: 4/23/19
 ** Section: 07
 ** E-mail: nsica1@umbc.edu
 **
 ** This file contains the main code for the EReader class, it allows
 ** for the management of the master list of books and the readers 
 ** list of books
 ***************************/


#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "EReader.h"

using namespace std;
//constant for the integer exit = 5
const int EXIT = 5;
const int MAX = 150;

//Name: EReader - Default Constructor
//Precondition: None
//Postcondition: Creates a new EReader
EReader::EReader() {
  //Loads the books using a string literal
  LoadCatalog("proj5_books.txt");

}

//Name: EReader - Overloaded Constructor
//Precondition: None
//Postcondition: Creates a new EReader and passes the book filename
EReader::EReader(string filename) {
  //loads the books using the parameter name
  LoadCatalog(filename);

}
//Name: ~EReader - Destructor
//Precondition: None
//Postcondition: Creates a new EReader
EReader::~EReader() {
  //goes through the book catalog vector and deallocates all of the books
  for(int i = 0; i < (int) m_bookCatalog.size(); i++) {
    delete m_bookCatalog[i];
  }

}
//Name: LoadCatalog(string filename)
//Precondition: Requires filename
//Postcondition: Loads the file into the m_bookCatalog (as books)
void EReader::LoadCatalog(string filename) {
  ifstream inputStream; //file in
  string title,author; //title and author
  int rank; //rank 
  double price; //price
  int count = 0;
  //opens file
  inputStream.open(filename);
  //while it reads in a title 
  while(getline(inputStream, title, ',') && title != "\n") {
    //if the beginning of the string has a \n then erase it
    if(title[0] == '\n') {
      title.erase(0,1);
    }
    //if the title does not have \n 
    if(title != "\n") {
      //gets the author
      getline(inputStream, author, ',');
      //gets rank
      inputStream >> rank;
      //ignores the , after the rank 
      if(inputStream.peek() == ',') {
	inputStream.ignore();
      }
      //gets the price of the book
      inputStream >> price;
      //creates a new book
      Book* newBook = new Book(title, author, rank, price);
      //adds the book into the vector
      m_bookCatalog.push_back(newBook);
      //increment count
      count++;
    }
    
  }
  cout << count << " Books loaded" << endl;
  //close file
  inputStream.close();
}

//Name: MainMenu
//Precondition: None
//Postcondition: Manages the application and the menu
void EReader::MainMenu() {
  int choice;
  //do while loop for the menu so it runs correctly
  do {
    cout << "What would you like to do?:" << endl;
    cout << "1. Display All Books" << endl;
    cout << "2. Add Book to Readlist" << endl;
    cout << "3. Display ReadList" << endl;
    cout << "4. Sort Readlist by Price" << endl;
    cout << "5. Quit" << endl;
    //user input
    cin >> choice;
    //input validation
    if((choice <= 0) || (choice > EXIT)) {
      cout << "That was an invalid selection, try again" << endl;
      cout << endl;

      cout << "What would you like to do?:" << endl;
      cout << "1. Display All Books" << endl;
      cout << "2. Add Book to Readlist" << endl;
      cout << "3. Display ReadList" << endl;
      cout << "4. Sort Readlist by Price" << endl;
      cout << "5. Quit" << endl;

      cin >> choice;
    }
  
    //switch statement for the menu choices
    switch(choice) {
    case 1:
      //displays All books
      DisplayBooks();
      break;
    case 2:
      //Adds Book to readlist
      AddBook();
      break;
    case 3:
      //displays the read list
      DisplayReadlist();
      break;
    case 4:
      //Sort readlist by price
      SortReadlist();
      break;
    case 5:
      //exit
      cout << "Thank you for using the UMBC E-Reader" << endl;
      break;

    }
    //runs the do while unless the choice is exit
  }while(choice != EXIT);
}
//Name: DisplayBooks
//Precondition: Displays all 150 books
//Postcondition: Lists all books (numbered)
void EReader::DisplayBooks() {
  //calls the overloaded << operator in Book.cpp to display and format the output
  for(int i = 0; i < (int) m_bookCatalog.size(); i++) {
    cout << *m_bookCatalog.at(i);
  }
}
//Name: AddBook
//Precondition: m_bookCatalog is populated
//Postcondition: Displays the current list and adds a book
//               to the m_readList
void EReader::AddBook() {
  int choice;
  int size = m_readList.GetSize();
  //choose the book and displays the books to pick from
  cout << "Choose the book you would like to add to your reading list" << endl;
  DisplayBooks();
  cout << "Enter the number of the book you would like to add: " << endl;
  cin >> choice;
  //input validation 
  if(choice <= 0 || choice > MAX) {
    cout << "Invalid index, try again" << endl;
    cout << "Enter the number of the book you would like to add: " << endl;
    cin >> choice;
  }
  //gets the book and adds it into the users read list 
  m_readList.Push(*m_bookCatalog.at(choice - 1), true);
  //sets the rank for the read list 
  m_readList[size].setRank(size + 1);
}


//Name: DisplayReadlist
//Precondition: None (can be empty)
//Postcondition: Displays the readlist
void EReader::DisplayReadlist() {
  for(int i = 0; i < m_readList.GetSize(); i++)
    {//calls the overloaded << operator in Lqueue.h to display and format the info
      cout << m_readList[i];
    }
  
}

//Name: SortReadlist()
//Precondition: Requires Readlist
//Postcondition: Uses the overloaded < operator in Book to sort
//               the prices from high to low in the m_readList
void EReader::SortReadlist() {
  bool swapBool = false;
  int count = 0;
  //while loop that goes through the read list as many times as there are objects
  //so it will always be fully sorted 
  while(count != m_readList.GetSize()) {
    //for loop to go through the read list 
    for(int i = 0; i < m_readList.GetSize() - 1; i++) {
      //calls the overloaded < operator to check if one book is less than the other 
      swapBool = m_readList[i] < m_readList[i + 1]; 
      //swaps the books if swapBool is true
      if(swapBool == true) {
	m_readList.Swap(i + 1);
	
      }
      
    }//resets the ranks
    for(int j = 0; j < m_readList.GetSize(); j++) {
      m_readList[j].setRank(j + 1);
	}
    //increments count for the while loop 
      count++;
  }
}
    






