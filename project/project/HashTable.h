/**
 * Defines the HashTable and associated classes.
 * By MOKT (Max Ovsiankin, Ori Klein, Keivan Safavi, Tomer Erlich)
 */
#ifndef HashTable_h
#define HashTable_h

#include <iostream>
#include <string>
#include <vector>
#include "Food.h"

using namespace std;

/**
 * Represents a node in a linked list in the hash table.
 */
template <class Type>
class LinkedListNode {
 private:
  Type data;

 public:
  LinkedListNode* next;
  int key;
  LinkedListNode(Type t, int k);

  void setData(Type d);

  int getKey();

  Type getData();
};

/*
Template class that creates a singly linked list with the ability to add a node
anywhere, remove from anywhere,
empty, extract data from node.
head is an LinkedListNode pointer that points to the first node in the list,
without holding data
rear is an LinkedListNode pointer that points to the last node in the list,
without holding data
index of first node is 0, index of last node is size -1.
*/
template <class Type>
class SinglyLinkedList {
 private:
  int size;
  LinkedListNode<Type>* head;
  LinkedListNode<Type>* rear;

 public:
  /**
  Creates an instance of a SinglyLinkedList
  */
  SinglyLinkedList();
  /**
  * adds a node at the end of the list
  */
  void addLast(Type data, int key);

  /**
  * deletes node from existance at indicated key
  */
  bool remove(int key);

  /**
  * extracts data from node at specified index
  */
  Type get(int key);

  /**
   * converts from linkedlist to vector
   */
  vector<Type> convertToVector();

  /**
  * returns size
  */
  int getSize();
  /**
  * deletes all nodes
  */
  void empty();
};

//*****************************************************************
// Hash Table objects store a fixed number of Linked Lists.
//*****************************************************************
template <class Type>
class HashTable {
 private:
  /**
   * Array is a reference to an array of Linked Lists.
  */
  SinglyLinkedList<Type>* array;

  /**
   * Length is the size of the Hash Table array.
  */
  int length;

  /**
   * Returns an array location for a given item key.
  */
  int hash(int key);

 public:
  /**
   * Constructs the empty Hash Table object.
   * Array length is set to 991 by default.
  */
  HashTable();

  /**
   * Constructs the empty Hash Table object.
   * Array length is set to 991 by default.
  */
  HashTable(int tableLength);

  /**
   * Adds an item to the Hash Table.
  */
  void insertItem(int key, Type newItem);

  /**
   * Deletes an Item by key from the Hash Table.
   * Returns true if the operation is successful.
  */
  bool removeItem(int key);

  /**
   * Returns an item from the Hash Table by key.
   * If the item isn't found, a null pointer is returned.
  */
  Type getItemByKey(int key);

  /**
   * Prints a histogram illustrating the Item distribution.
  */
  void printHistogram();

  /**
   * Returns the number of locations in the Hash Table.
  */
  int getLength();

  /**
   * Returns the number of Items in the Hash Table.
   */
  int getNumberOfItems();

  /**
   * Empty the hashtable
   */
  void empty();

  /**
   * Puts all linkedlist vectos in vector
   */
  vector<vector<Type> >* putInVector();

  /**
   * De-allocates all memory used for the Hash Table.
  */
  ~HashTable();
};

#endif  // !HashTable_h
