/**
 * Implements the Store class.
 */

#include <vector>
#include <sstream>

#include "Store.h"
#include "BST.h"
#include "FileIO.h"
#include "HashTable.h"

using std::vector;

Store::Store(string filename) {
  this->fileIO = new FileIO();
  this->bst = new BST<Food>();
}

Store::~Store() {
  delete this->fileIO;
  delete this->bst;
}

void initializeFoodsBst(BST<Food> bst) {

}

void Store::initializeFoods() {
  vector<Food>* foods = fileIO->load(filename);
  for (int i = 0; i < foods->size(); i++) {
    Food food = foods->operator[](i);
    bst->insert(food);
    if (food.getId() > maxId) {
      maxId = food.getId();
    }
    // add to hash table
  }
  // check nutrients
  for (int i = 0; i < foods->size(); i++) { // has to work with BST
    Food food = foods->operator[](i);
    if (food.isRecipe()) {
      vector<int> ingredients = food.getIngredients();
      vector<Food> ingredientsFood;
      for (int i = 0; i < ingredients.size(); i++) {
        int id = ingredients[i];
        if (!foodWithIdExists(id)) {
          std::stringstream s;
          s << "Food " << food.getName() << " referencing invalid id " << id;
          throw s.str();
        } else {
          ingredientsFood.push_back(getById(id));
        }
      }
      food.calculateNutrients(ingredientsFood);
    }
  }
}

void Store::saveFoods() {
  vector<Food>* foods = getInSortedOrder();
  fileIO->save(filename, foods);
}

bool Store::foodWithIdExists(int id) {
  // using hash table
}

bool Store::addFood(Food food) {
  if (food.getId() != getNextId()) {
    throw "Food has invalid id #";
  }
  bst->insert(food);
  maxId++;
} // should check that the food's id is the output of
                         // getNextId(). save to file

bool Store::anyRecipeReferences(int id) {
  // check in hash table
}

Food Store::getById(int id) {
  // get by hash table
} // gets a food by the id it has. throws exception if the
                      // food isn't there

int Store::getNextId() {
  return maxId + 1;
}

int Store::getNumFoods() {
  return numFoods;
}

vector<Food> * Store::getMatching(vector<string> keywords) {
  vector<Food>* foods = getInSortedOrder();
}

vector<Food> * Store::getInSortedOrder() {

}

vector<Food> * Store::getInHashTableOrder() {

}

bool Store::deleteFood(int id) {
  numFoods--;
} // delete food with id, save to file.

string Store::getPrintOut() {
  
}
