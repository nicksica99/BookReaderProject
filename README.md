# BookReaderProject
E-Reader book project for school
Class 1 – Lqueue – It is used to manage the reading list. It uses a linked list to store the information about whatever it is designed to hold (in this case a list of books). As a linked list, is uses templated nodes to store data. Implements normal queue functions such as Push (which inserts in the end or at the beginning – see the function definition for details), Pop (which removes from front), Display(which displays data in each node), Front(which returns the first element in the queue), Swap (which swaps two nodes – not just the data – it swaps the nodes themselves), and Clear (which removes all nodes from the lqueue). 

Class 2: EReader – This is the class that manages the master list of books and the readers list of books. It is called directly from driver.cpp. There is one data file which is loaded into a vector that stores all dynamically allocated books (this can change but there are currently 150 books). You can display all books available, add a book to your reading list, display your reading list, or sort the reading list by price (greatest to lowest). 

Class 3: Book – This is the class that contains all of the information about each book. Each book has a title, author, rank, and price (in dollars). There is an overloaded << operator and a < operator (for sorting).
