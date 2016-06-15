//
//  HashTable.h
//  Hashtables
//
//  Created by Ori Klein on 6/14/16.
//  Copyright (c) 2016 Ori Klein. All rights reserved.
//

#ifndef HashTable_h
#define HashTable_h

#include "Food.h"
#include "SinglyLinkedList.h"
#include <string>

//*****************************************************************
// Hash Table objects store a fixed number of Linked Lists.
//*****************************************************************
template <class Type>
class HashTable
{
private:
    
    // Array is a reference to an array of Linked Lists.
    SinglyLinkedList<Type> * array;

    // Length is the size of the Hash Table array.
    int length;
    
    // Returns an array location for a given item key.
    int hash( int key );
    
public:
    
    HashTable();
    
    // Constructs the empty Hash Table object.
    // Array length is set to 991 by default.
    HashTable(int tableLength);
    
    // Adds an item to the Hash Table.
    void insertItem(int key, Type newItem );
    
    // Deletes an Item by key from the Hash Table.
    // Returns true if the operation is successful.
    bool removeItem( int key );
    
    // Returns an item from the Hash Table by key.
    // If the item isn't found, a null pointer is returned.
    Type getItemByKey( int key );
    
    // Display the contents of the Hash Table to console window.
    void printTable();
    
    // Prints a histogram illustrating the Item distribution.
    void printHistogram();
    
    // Returns the number of locations in the Hash Table.
    int getLength();
    
    // Returns the number of Items in the Hash Table.
    int getNumberOfItems();
    
    // De-allocates all memory used for the Hash Table.
    ~HashTable();
};

template class HashTable<int>;
template class HashTable<Food>;

#endif // !HashTable_h
