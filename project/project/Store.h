/**
 * Defines the Store class.
 */

#ifndef __STORE_H
#define __STORE_H

#include <vector>

#include "BST.h"
#include "FileIO.h"
#include "Food.h"
#include "HashTable.h"

using std::vector;

class Store {

  BST<Food> *bst;
  string filename;
  FileIO *fileIO;
  int maxId;
  int numFoods;

public:
  Store(string filename);

  ~Store();

  void initializeFoods(); // load file, calculate nutrients, add the foods to
                          // the BST and hash table

  void saveFoods(); // save to file

  bool foodWithIdExists(int id); // checks if a food with that id exists.

  bool addFood(Food food); // should check that the food's id is the output of
                           // getNextId(). save to file

  bool anyRecipeReferences(
      int id); /// checks if any recipe references a food with an id

  Food getById(int id); // gets a food by the id it has. throws exception if the
                        // food isn't there

  int getNextId();

  int getNumFoods(); // count number of foods

  vector<Food> *
  getMatching(vector<string> keywords); // get all, then filter by keywords

  vector<Food> *getInSortedOrder();

  vector<Food> *getInHashTableOrder();

  bool deleteFood(int id); // delete food with id, save to file.

  string getPrintOut();
};

#endif
