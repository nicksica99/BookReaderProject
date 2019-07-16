/******************************
//File: Lqueue.h
//Project: CMSC 202 Project 5, Spring 2019
//Author: Nick Sica
//Section: 07
//E-mail: nsica1@umbc.edu
//
// This file manages the reading list. It has a linked list to stroe the 
// information about the books
******************************/



#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

template <class T>
class Node {
public:
  Node( const T& data ); //Node Constructor
  T& GetData(); //Node Data Getter
  void SetData( const T& data ); //Node Data Setter
  Node<T>* GetNext(); //Node m_next getter
  void SetNext( Node<T>* next ); //Node m_next setter
private:
  T m_data; //Holds templated data
  Node<T>* m_next; //Pointer to next node
};

template <class T>
Node<T>::Node( const T& data ) {
   m_data = data;
   m_next = nullptr;
}

template <class T>
T& Node<T>::GetData() {
   return m_data;
}

template <class T>
void Node<T>::SetData( const T& data ) {
   m_data = data;
}

template <class T>
Node<T>* Node<T>::GetNext() {
   return m_next;
}

template <class T>
void Node<T>::SetNext( Node<T>* next ) {
   m_next = next;
}

template <class T>
class Lqueue {
 public:
  // Name: Lqueue() (Linked List Queue) - Default Constructor
  // Desc: Used to build a new linked queue (as a linked list)
  // Preconditions: None
  // Postconditions: Creates a new lqueue where m_head and m_tail point to nullptr
  Lqueue();
  // Name: ~Lqueue() - Destructor
  // Desc: Used to destruct a Lqueue
  // Preconditions: There is an existing lqueue with at least one node
  // Postconditions: An lqueue is deallocated (including dynamically allocated nodes)
  //                 to have no memory leaks!
 ~Lqueue();
  // Name: Lqueue (Copy Constructor)
  // Preconditions: Creates a copy of existing LQueue
  //                Requires a Lqueue
  // Postconditions: Copy of existing Lqueue
  Lqueue(const Lqueue&);
  // Name: operator= (Overloaded Assignment Operator)
  // Preconditions: Copies an Lqueue into an existing Lqueue
  //                Requires a Lqueue
  // Postconditions: Copy of existing Lqueue
  Lqueue<T>& operator= (const Lqueue&);
  // Name: Push
  // Preconditions: Takes in data. Creates new node. 
  //                Requires a Lqueue
  // Postconditions: If the bool = true, adds to front else adds a new node to the
  //                 end of the lqueue.
  void Push(const T&, bool);
  // Name: Pop
  // Preconditions: Lqueue with at least one node. 
  // Postconditions: Removes first node in the lqueue, returns data from first node.
  T Pop();
  // Name: Display
  // Preconditions: Outputs the lqueue.
  // Postconditions: Displays the data in each node of lqueue
  void Display();
  // Name: Front
  // Preconditions: Requires a populated lqueue
  // Postconditions: Returns whatever data is in front 
  T Front();
  // Name: IsEmpty
  // Preconditions: Requires a lqueue
  // Postconditions: Returns if the lqueue is empty.
  bool IsEmpty();
  // Name: GetSize
  // Preconditions: Requires a lqueue
  // Postconditions: Returns m_size
  int GetSize();
  // Name: Swap(int)
  // Preconditions: Requires a lqueue
  // Postconditions: Swaps the nodes at the index with the node prior to it.
  void Swap(int);
  // Name: Clear
  // Preconditions: Requires a lqueue
  // Postconditions: Removes all nodes in a lqueue
  void Clear();
  // Name: TestHeadTail() (Optional test function)
  // Preconditions: Requires a lqueue
  // Postconditions: Returns the value of the head and the tail (used for main below)
  void TestHeadTail();
  // Name: operator<< (Overloaded << operator)
  // Preconditions: Requires a lqueue
  // Postconditions: Returns an ostream with the data from each node on different line
  template <class U>
  friend ostream& operator<<(ostream& output, const Lqueue<U>&);
  //Name: Overloaded [] operator
  //Precondition: Existing Lqueue
  //Postcondition: Returns object from Lqueue using []
  T& operator[] (int x);//Overloaded [] operator to pull data from Lqueue
private:
  Node <T> *m_head; //Node pointer for the head
  Node <T> *m_tail; //Node pointer for the tail
  int m_size; //Number of nodes in queue
};
//*****************************************************************
//Implement Lqueue here
// Name: Lqueue() (Linked List Queue) - Default Constructor
// Desc: Used to build a new linked queue (as a linked list)
// Preconditions: None
// Postconditions: Creates a new lqueue where m_head and m_tail point to nullptr
template <class T>
Lqueue<T>::Lqueue() {
  //creates new Lqueue where the variables are null/0
  m_head = nullptr;
  m_tail = nullptr;
  m_size = 0;
}

// Name: ~Lqueue() - Destructor
// Desc: Used to destruct a Lqueue
// Preconditions: There is an existing lqueue with at least one node
// Postconditions: An lqueue is deallocated (including dynamically allocated nodes)
//                 to have no memory leaks!
template <class T>
Lqueue<T>::~Lqueue() {
  //deletes the book objects
  Clear();

}
// Name: Lqueue (Copy Constructor)
// Preconditions: Creates a copy of existing LQueue
//                Requires a Lqueue
// Postconditions: Copy of existing Lqueue
template <class T>
Lqueue<T>::Lqueue(const Lqueue& newQueue) {
  //copies the Lqueue
  Node <T> *newNode = newQueue.m_head;

  m_head = nullptr;
  m_tail = nullptr;
  m_size = 0;
  //gets the data for the Lqueue
  while(newNode != nullptr) {
    Push(newNode->GetData(),!IsEmpty());
    newNode = newNode->GetNext();
  }
  
}
// Name: operator= (Overloaded Assignment Operator)
// Preconditions: Copies an Lqueue into an existing Lqueue
//                Requires a Lqueue
// Postconditions: Copy of existing Lqueue
template <class T>
Lqueue<T>& Lqueue<T>::operator= (const Lqueue& myQueue) {
  Node <T> *newNode = myQueue.m_head;
  //deletes the Lqueue 
  if(m_head != nullptr) {
    Clear();
  }
  //gets the data of the Lqueue for the new Lqueue and sets it
  while(newNode != nullptr) {
    Push(newNode->GetData(), !IsEmpty());
    newNode = newNode->GetNext();
  }
  //if its the same Lqueue then it returns the other one
  if(this == &myQueue) {
    return (*this);

  }
  //return the Lqueue
  return *this;

}
// Name: Push
// Preconditions: Takes in data. Creates new node.
//                Requires a Lqueue
// Postconditions:  If the bool = false, adds to front else adds a new node to the
//                 end of the lqueue.
template <class T>
void Lqueue<T>::Push(const T& object, bool canPush) {
  //creates a new Node
  Node <T> *newNode = new Node <T>(object);
  Node <T> *temp = m_head;
  //sets the data and the next
  newNode->SetData(object);
  newNode->SetNext(nullptr);
  //if the Lqueue is empty then it sets the head and tail to the new Node
  if(m_head == nullptr) {
    m_head = newNode;
    m_tail = newNode;
    m_size = 1;
  }
  //if the boolean is false it adds to the front
  else if(canPush == false) {
    
    m_head = newNode;
    m_head->SetNext(temp);
    m_size++;


  }
  //bool is true, it adds to the back
  else if(canPush == true) {
    m_tail->SetNext(newNode);
    m_tail = newNode;
    m_size++;
      }
}
// Name: Pop
// Preconditions: Lqueue with at least one node.
// Postconditions: Removes first node in the lqueue, returns data from first node.
template <class T>
T Lqueue<T>::Pop() {
  Node <T> *temp = m_head;
  T data;
  
  //if the list is empty 
  if(m_head == nullptr) {
    cout << "The list is already empty" << endl;
  }
  else {
    //pops the first node in the queue off 
    data = m_head->GetData();
    m_head = m_head->GetNext();
    m_size--;
    delete temp;
    
  }//returns the data from the first node
  return data;
}
// Name: Display
// Preconditions: Outputs the lqueue.
// Postconditions: Displays the data in each node of lqueue
template <class T>
void Lqueue<T>::Display() {
  //if list is empty 
  if(IsEmpty() == true) {
    cout << "The list is empty" << endl;
  }
  else {
    //creates a temp node
    Node <T> *temp = m_head;
    //for loop that goes through and gets all of the data and displays it 
    for(int i = 0; i < m_size; i++) {
      
      cout << temp->GetData() << endl;
      
      temp = temp->GetNext();
    }  
    
  }
  cout << "END" << endl;
}
// Name: Front
// Preconditions: Requires a populated lqueue
// Postconditions: Returns whatever data is in front
template <class T>
T Lqueue<T>::Front() {
  //gets the front data and returns it
  T frontData = m_head->GetData();
  return frontData;
 
}
// Name: IsEmpty
// Preconditions: Requires a lqueue
// Postconditions: Returns if the lqueue is empty.
template <class T>
bool Lqueue<T>::IsEmpty() {
  //if the head is empty than its empty otherwise its not
  if(m_head == nullptr) {
    return true;
  }
  return false;
}

// Name: GetSize
// Preconditions: Requires a lqueue
// Postconditions: Returns m_size
template <class T>
int Lqueue<T>::GetSize() {
  return m_size; //return size
}
// Name: Swap(int)
// Preconditions: Requires a lqueue
// Postconditions: Swaps the nodes at the index with the node prior to it.
template <class T>
void Lqueue<T>::Swap(int dataNode) {
  //temp nodes 
  Node <T> *current = m_head;
  Node <T> *previous = m_head;
  Node <T> *temp = m_head;
  //if the swap is at the first node
  if(dataNode == 1) {
    //sets the previous to the head and the current to the next one
    previous = m_head;
    current = m_head->GetNext();
    //sets the locations of previous and current
    //the old location of m_head was current
    previous->SetNext(current->GetNext());
    
    current->SetNext(previous);
    m_head = current;
    //if there are two nodes in the list
    if(m_size == 2) {
      //the tail is now the previous node
      m_tail = previous;
    }
  }
  else {
    //gets the node 2 back from the current node
    for(int i = 0; i < dataNode - 2; i++) {
      temp = temp->GetNext();
    }
    //gets the node previous of the current node
    for(int j = 0; j < dataNode - 1; j++) {
      previous = previous->GetNext();
    }
    //gets the current node 
    for(int k = 0; k < dataNode; k++) {
      current = current->GetNext();
    }
    //values of the nodes are assigned 
    previous->SetNext(current->GetNext());
    temp->SetNext(current);
    current->SetNext(previous);
    
    if(m_size == dataNode + 1) {
      //tail is set to the previous node when moving the last node 
      m_tail = previous;
    }
  }
}

// Name: Clear
// Preconditions: Requires a lqueue
// Postconditions: Removes all nodes in a lqueue
template <class T>
void Lqueue<T>::Clear() {
  Node <T> *temp = m_head;
  //goes through the lqueue and deletes the nodes one by one
  while(temp != nullptr) {
    temp = m_head->GetNext();
    delete m_head;
    m_head = temp;
  }
  //sets the member variables back to null/0
  m_head = nullptr;
  m_tail = nullptr;
  m_size = 0;

}
// Name: TestHeadTail() (Optional test function)
// Preconditions: Requires a lqueue
// Postconditions: Returns the value of the head and the tail (used for main below)
template <class T>
void Lqueue<T>::TestHeadTail() {
  //test for the test in main, shows the data of the head and tail
  cout << m_head->GetData() << endl;
  cout << m_tail->GetData() << endl;

}

// Name: operator<< (Overloaded << operator)
// Preconditions: Requires a lqueue
// Postconditions: Returns an ostream with the data from each node on different line
template <class U>
ostream& operator<<(ostream& output, const Lqueue<U>& myQueue) {
  //if the list is empty 
  if(myQueue.m_head == nullptr) {
    cout << "The list is empty" << endl;
  }
  else {
    Node <U> *temp = myQueue.m_head;
    //goes through the queue and displays the data associated with it 
    for(int i = 0; i < myQueue.m_size; i++) {
      output << temp->GetData() << endl;
      temp = temp->GetNext();
    }
  }
  //returns the data
  return output;
}


//Name: Overloaded [] operator
//Precondition: Existing Lqueue
//Postcondition: Returns object from Lqueue using []
template <class T>
T& Lqueue<T>::operator[] (int x) { //Overloaded [] operator to pull data from Lqueue

  Node <T> *temp = m_head;
  //if list is empty 
  if(m_head == nullptr) {
    cout << "The list is empty" << endl;
  }
  else {
    //goes through and gets the data from the temp node
    for(int i = 0; i < x; i++)
      {
	temp = temp->GetNext();
      }
  }
  return temp->GetData();
  
}


//****************************************************************
// To test just Lqueue follow these instructions:
//   1.  mv Lqueue.h Lqueue.cpp
//   2.  Uncomment out int main below
//   3.  make Lqueue
//   4.  ./Lqueue (try valgrind too!)

/*
int main () {
  //Test 1 - Default Constructor and Push
  cout << "Test 1 - Default Constructor and Push Running" << endl;
  //Test Default Constructor
  Lqueue <int> newLQ1;
  //Push 4 nodes into Lqueue
  newLQ1.Push(10, 1);
  newLQ1.Push(11, 1);
  newLQ1.Push(12, 1);
  newLQ1.Push(13, 1);
  cout << endl;
  
  //Test 2 - Copy Constructor and Assignment Operator
  cout << "Test 2 - Copy Constructor and Assignment Operator Running" << endl;
  //Test Copy constructor
  Lqueue <int> newLQ2(newLQ1);
  //Test Overloaded Assignment Operator
  Lqueue <int> newLQ3;
  newLQ3 = newLQ1;
  cout << endl;

  //Test 3 - Test Display and Overloaded <<
  cout << "Test 3 - Display and Overloaded << Running" << endl;
  cout << "newLQ1" << endl;
  newLQ1.Display();
  cout << "newLQ2" << endl;
  newLQ2.Display();
  cout << "newLQ3" << endl;
  newLQ3.Display();
  cout << "newLQ1" << endl;
  cout << newLQ1;
  cout << "newLQ2" << endl;
  cout << newLQ2;
  cout << "newLQ3" << endl;
  cout << newLQ3;
  cout << endl;


    
  //Test 4 - Test Front and Pop
  cout << "Test 4 - Front and Pop Running" << endl;
  //Test Front()
  cout << "Testing Front - Output 10" << endl;
  cout << newLQ1.Front() << endl;
  //Test Pop with Display of Pop
  cout << "Popping one node and displaying it" << endl;
  cout << newLQ1.Pop() << endl;
  //Test Pop with Display of Pop
  cout << "Popping one node and displaying it" << endl;
  cout << newLQ1.Pop() << endl;
  cout << endl;


  //Test 5 - Test GetSize and Clear
  cout << "Test 5 - GetSize and Clear Running" << endl;
  //Test GetSize()
  cout << "Outputting the size" << endl;
  cout << newLQ1.GetSize() << endl;
  //Test Clear()
  cout << "Clearing all nodes" << endl;
  newLQ1.Clear();
  cout << endl;

  
  //Test 6 - Test Swap
  cout << "Test 6 - Swap Running" << endl;
  newLQ2.Swap(2);
  cout << "Swap 2 - Should display 10->12->11->13->END" << endl;
  newLQ2.Display();
  //Testing to make sure head and tail point at the correct node
  newLQ2.TestHeadTail();
  cout << "Should display head 10 and tail 13" << endl;
  cout << endl;  

  return 0;
}
  
*/

