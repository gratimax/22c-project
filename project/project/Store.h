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
int maxId;

void initializeFoods(vector<Food>* foods); // add the foods to the BST and hash table

public:

Store(string filename); // load the file, calculate nutrients for recipes

~Store();

bool foodWithIdExists(int id); // checks if a food with that id exists.

bool addFood(Food food); // should check that the food's id is the output of getNextId()

bool anyRecipeReferences(int id); /// checks if any recipe references a food with an id

Food getById(int id); // gets a food by the id it has. throws exception if the food isn't there

int getNextId();

vector<Food>* getMatching(vector<string> keywords); // get all, then filter by keywords

vector<Food>* getInSortedOrder();

vector<Food>* getInHashTableOrder();

bool deleteFood(int id);

void getBst();

FileIO* getFileIO();

};

#endif
