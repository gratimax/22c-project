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

/**
 * Represents how the data objects in Fruitlog are stored. Abstracts away
 * accessing data from how
 * the data is actually stored.
 */
class Store {
  /**
   * A pointer to a binary search tree of food objects.
   */
  BST<Food> *bst;

  /**
   * A HashTable to Food pointers
   */ 
  HashTable<Food*> hashBrownTable;
  
  /**
   * The filename where the food will be stored.
   */
  string filename;

  /**
   * The FileIO object that handles saving and loading from the file.
   */
  FileIO *fileIO;

  /**
   * The maximum ID # the store has seen so far (so it can assign new ID
   * numbers).
   */
  int maxId;

  /**
   * The number of foods the store is logging.
   */
  int numFoods;

  /**
   * Generate a random food item.
   */
  Food randomize(); 

 public:
  /**
   * Constructs a store that reads/writes from a file.
   */
  Store(string filename);

  /**
   * Deconstructs a store.
   */
  ~Store();

  /**
   * Loads the file the store is from, adds the foods to the BST and hash table,
   * and calculates
   * nutrients in certain foods.
   */
  void initializeFoods();

  /**
   * Save the foods to the file.
   */
  void saveFoods();

  /**
   * Checks if a food with the given ID exists in the store.
   */
  bool foodWithIdExists(int id);

  /**
   * Adds the given food to the store.
   * Checks that the food's ID is the output of getNextId().
   */
  bool addFood(Food food);

  /**
   * Checks if any recipe references a food with a certain ID.
   */
  bool anyRecipeReferences(int id);

  /**
   * Gets a food by its id. Throws an error if a food with that ID does not
   * exist.
   */
  Food getById(int id);

  /**
   * Gets the next ID number for adding a new food object.
   */
  int getNextId();

  /**
   * Counts the number of foods stored.
   */
  int getNumFoods();

  /**
   * Gets which foods match the given keywords.
   */
  vector<Food> *getMatching(vector<string> keywords);

  /**
   * Gets the foods in their sorted order by the BST.
   */
  vector<Food> *getInSortedOrder();

  /**
   * Gets the foods by their hash table order.
   */
  vector<Food> *getInHashTableOrder();
  
  /**
   * Generates recipe given a nutrient and an amount
   */
  vector<Food> *generateRecipe(string nutrient, int amount);

  /**
   * Deletes the food with the given ID. Throws an error if that ID doesn't
   * exist.
   */
  bool deleteFood(int id);

  /**
   * Gets a print out of the binary tree as an indented printout.
   */
  string getPrintOut();
};

#endif
