/**
 * Defines the Store class.
 */

#ifndef __STORE_H
#define __STORE_H

#include <vector>

#include "BST.h"
#include "HashTable.h"
#include "Food.h"
#include "FileIO.h"

using std::vector;

class Store {

string filename;
FileIO* fileIO;

void initializeFoods(vector<Food>* foods);

public:

Store(string filename);

~Store();

bool foodWithIdExists(int id);

bool addFood(Food food);

bool anyRecipeReferences(int id);

Food getById(int id);

vector<Food>* getMatching(vector<string> keywords);

vector<Food>* getInSortedOrder();

vector<Food>* getInHashTableOrder();

bool deleteFood(int id);

void getBst();

FileIO* getFileIO();

};

#endif
