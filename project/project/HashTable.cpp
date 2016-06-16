//
//  HashTable.cpp
//  Hashtables
//
//  Created by Ori Klein on 6/14/16.
//  Copyright (c) 2016 Ori Klein. All rights reserved.
//

#include "HashTable.h"
#include <stdio.h>
#include "BST.h"
#include "Efficiency.h"

template <class Type>
LinkedListNode<Type>::LinkedListNode(Type t, int k) {
  data = t;
  next = nullptr;
  key = k;
}

template <class Type>
void LinkedListNode<Type>::setData(Type d) {
  Efficiency::totalDataStructureOperations++;
  data = d;
}

template <class Type>
int LinkedListNode<Type>::getKey() {
  Efficiency::totalDataStructureOperations++;
  return key;
}

template <class Type>
Type LinkedListNode<Type>::getData() {
  return data;
}

template <class Type>
SinglyLinkedList<Type>::SinglyLinkedList() {
  size = 0;
  head = nullptr;
  rear = nullptr;
}

template <class Type>
void SinglyLinkedList<Type>::addLast(Type data, int key) {
  LinkedListNode<Type>* newNode = new LinkedListNode<Type>(data, key);
  if (size == 0) {
    Efficiency::totalDataStructureOperations++;
    head = newNode;
    rear = newNode;
    newNode->next = nullptr;
    size++;
    return;
  }
  Efficiency::totalDataStructureOperations++;
  rear->next = newNode;
  newNode->next = nullptr;
  rear = newNode;
  size++;
}

template <class Type>
bool SinglyLinkedList<Type>::remove(int key) {
  if (size <= 0) {
    return false;
  }
  LinkedListNode<Type>* pLoc = head;
  LinkedListNode<Type>* pPre = nullptr;
  while (pLoc->next != nullptr && pLoc->getKey() != key) {
    Efficiency::totalDataStructureOperations++;
    pPre = pLoc;
    pLoc = pLoc->next;
  }
  if (pLoc->getKey() != key) return false;
  if (pLoc == head) {
    Efficiency::totalDataStructureOperations++;
    head = pLoc->next;
    size--;
    return true;
  }
  pPre->next = pLoc->next;
  if (pPre->next == nullptr) rear = pPre;
  delete pLoc;
  size--;
  Efficiency::totalDataStructureOperations++;
  return true;
}

template <class Type>
Type SinglyLinkedList<Type>::get(int key) {
  LinkedListNode<Type>* pLoc = head;
  while (pLoc != nullptr) {
    if (pLoc->getKey() == key) {
      Efficiency::totalDataStructureOperations++;
      return pLoc->getData();
    }
    Efficiency::totalDataStructureOperations++;
    pLoc = pLoc->next;
  }
  throw "not found";
}

template <class Type>
vector<Type> SinglyLinkedList<Type>::convertToVector() {
  vector<Type> v;
  if (size == 0) return v;
  LinkedListNode<Type>* pLoc = head;
  while (pLoc->next != nullptr) {
    Efficiency::totalDataStructureOperations++;
    v.push_back(pLoc->getData());
    pLoc = pLoc->next;
  }
  Efficiency::totalDataStructureOperations++;
  v.push_back(pLoc->getData());
  return v;
}

template <class Type>
int SinglyLinkedList<Type>::getSize() {
  return size;
}

template <class Type>
void SinglyLinkedList<Type>::empty() {
  int s = size;
  for (int i = 0; i < s; i++) {
    Efficiency::totalDataStructureOperations++;
    LinkedListNode<Type>* pLoc = head;
    head = head->next;
    delete pLoc;
  }
  head = nullptr;
  rear = nullptr;
}

template <class Type>
HashTable<Type>::HashTable() {
  array = new SinglyLinkedList<Type>[991];
  length = 991;
}

// Constructs the empty Hash Table object.
// Array length is set to 13 by default.

template <class Type>
HashTable<Type>::HashTable(int tableLength) {
  if (tableLength <= 0) tableLength = 991;
  array = new SinglyLinkedList<Type>[tableLength];
  length = tableLength;
}

// Returns an array location for a given item key.
template <class Type>
int HashTable<Type>::hash(int key) {
  return (3 * key + 7) % length;
}

// Adds an item to the Hash Table.
template <class Type>
void HashTable<Type>::insertItem(int key, Type newItem) {
  int index = hash(key);
  array[index].addLast(newItem, key);
  Efficiency::totalDataStructureOperations++;
}

// Deletes an Item by key from the Hash Table.
// Returns true if the operation is successful.
template <class Type>
bool HashTable<Type>::removeItem(int key) {
  int index = hash(key);
  Efficiency::totalDataStructureOperations++;
  return array[index].remove(key);
}

// Returns an item from the Hash Table by key.
// If the item isn't found, a null pointer is returned.
template <class Type>
Type HashTable<Type>::getItemByKey(int key) {
  int index = hash(key);
  Efficiency::totalDataStructureOperations++;
  return array[index].get(key);
}

// Prints a histogram illustrating the Item distribution.
template <class Type>
void HashTable<Type>::printHistogram() {
  cout << "\n\nHash Table Contains ";
  cout << getNumberOfItems() << " Items total\n";
  for (int i = 0; i < length; i++) {
    cout << i + 1 << ":\t";
    for (int j = 0; j < array[i].getSize(); j++) cout << " X";
    cout << "\n";
  }
}

// Returns the number of locations in the Hash Table.
template <class Type>
int HashTable<Type>::getLength() {
  return length;
}

// Returns the number of Items in the Hash Table.
template <class Type>
int HashTable<Type>::getNumberOfItems() {
  int itemCount = 0;
  for (int i = 0; i < length; i++) {
    Efficiency::totalDataStructureOperations++;
    itemCount += array[i].getSize();
  }
  return itemCount;
}

// Empty the hashtable
template <class Type>
void HashTable<Type>::empty() {
  for (int i = 0; i < length; i++) {
    Efficiency::totalDataStructureOperations++;
    array[i].empty();
  }
}

template <class Type>
vector<Type>* HashTable<Type>::putInVector() {
  vector<Type>* v = new vector<Type>;
  for (int i = 0; i < length; i++) {
    vector<Type> vec = array[i].convertToVector();
    for (int j = 0; j < vec.size(); j++) {
      Efficiency::totalDataStructureOperations++;
      v->push_back(vec[j]);
    }
  }
  return v;
}

// De-allocates all memory used for the Hash Table.
template <class Type>
HashTable<Type>::~HashTable() {
  delete[] array;
}

template class LinkedListNode<BSTNode<Food>*>;
template class SinglyLinkedList<BSTNode<Food>*>;
template class HashTable<BSTNode<Food>*>;
