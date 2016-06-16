//
//  HashTable.h
//  Hashtables
//
//  Created by Ori Klein on 6/14/16.
//  Copyright (c) 2016 Ori Klein. All rights reserved.
//

#ifndef HashTable_h
#define HashTable_h

#include <iostream>
#include <string>
#include <vector>
#include "Food.h"
#include "BST.h"

using namespace std;

template <class Type>
class LinkedListNode {
 private:
  Type data;

 public:
  LinkedListNode* next;
  int key;
  LinkedListNode(Type t, int k) {
    data = t;
    next = nullptr;
    key = k;
  }

  void setData(Type d) { data = d; }

  int getKey() { return key; }

  Type getData() { return data; }
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
  SinglyLinkedList() {
    size = 0;
    head = nullptr;
    rear = nullptr;
  }
  /**
  * adds a node at the end of the list
  */
  void addLast(Type data, int key) {
    LinkedListNode<Type>* newNode = new LinkedListNode<Type>(data, key);
    if (size == 0) {
      head = newNode;
      rear = newNode;
      newNode->next = nullptr;
      size++;
      return;
    }
    rear->next = newNode;
    newNode->next = nullptr;
    rear = newNode;
    size++;
  }
  /**
  * deletes node from existance at indicated key
  */
  bool remove(int key) {
    if (size <= 0) {
      return false;
    }
    LinkedListNode<Type>* pLoc = head;
    LinkedListNode<Type>* pPre = nullptr;
    while (pLoc->next != nullptr && pLoc->getKey() != key) {
      pPre = pLoc;
      pLoc = pLoc->next;
    }
    if (pLoc->getKey() != key) return false;
    if (pLoc == head) {
      head = pLoc->next;
      size--;
      return true;
    }
    pPre->next = pLoc->next;
    if (pPre->next == nullptr) rear = pPre;
    delete pLoc;
    size--;
    return true;
  }
  /**
  * extracts data from node at specified index
  */
  Type get(int key) {
    LinkedListNode<Type>* pLoc = head;
    while (pLoc->next != nullptr && pLoc->getKey() != key) {
      pLoc = pLoc->next;
    }
    return pLoc->getData();
  }
  /**
   * converts from linkedlist to vector
   */
  vector<Type> convertToVector(){
   vector<Type> v;
   if (size == 0)
    return v;
   LinkedListNode<Type> *pLoc = head;
   while(pLoc->next != nullptr){
    v.push_back(pLoc->getData());
    pLoc = pLoc->next;
   }
   v.push_back(pLoc->getData());
   return v;
  }
  /**
  * returns size
  */
  int getSize() { return size; }
  /**
  * deletes all nodes
  */
  void empty() {
    int s = size;
    for (int i = 0; i < s; i++) {
      LinkedListNode<Type>* pLoc = head;
      head = head->next;
      delete pLoc;
    }
    head = nullptr;
    rear = nullptr;
  }
};

template class SinglyLinkedList<BSTNode<Food>*>;

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
   * Display the contents of the Hash Table to console window.
  */
  void printTable();

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
  vector<Type> *putInVector();

  /**
   * De-allocates all memory used for the Hash Table.
  */
  ~HashTable();
};

template class HashTable<BSTNode<Food>*>;

#endif  // !HashTable_h
