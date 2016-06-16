/**
 * Implements the Store class.
 */

#include <sstream>
#include <vector>
#include <time.h>

#include "BST.h"
#include "FileIO.h"
#include "HashTable.h"
#include "Store.h"

using std::vector;

Store::Store(string filename) {
  this->fileIO = new FileIO();
  this->bst = new BST<Food>();
}

Store::~Store() {
  delete this->fileIO;
  delete this->bst;
}

Food Store::randomize(){
  int r = 0;
  do{
    r = rand() % maxId + 1;
  }
  while (foodWithIdExists(r));
    return hashBrownTable.getItemByKey(r)
}

void initializeFoodsBst(BST<Food> bst) {}

void Store::initializeFoods() {
  vector<Food> *foods = fileIO->load(filename);
  for (int i = 0; i < foods->size(); i++) {
    Food food = foods->operator[](i);
    bst->insert(food);
    if (food.getId() > maxId) {
      maxId = food.getId();
    }
    // add to hash table
  }
  // check nutrients
  for (int i = 0; i < foods->size(); i++) {  // has to work with BST
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
  vector<Food> *foods = getInSortedOrder();
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
}  // should check that the food's id is the output of
// getNextId(). save to file

bool Store::anyRecipeReferences(int id) {
  // check in hash table
}

Food Store::getById(int id) {
  // get by hash table
}  // gets a food by the id it has. throws exception if the
// food isn't there

int Store::getNextId() { return maxId + 1; }

int Store::getNumFoods() { return numFoods; }

vector<Food> *Store::getMatching(vector<string> keywords) {
  vector<Food> *foods = getInSortedOrder();
}

vector<Food> *Store::getInSortedOrder() {}

vector<Food> *Store::getInHashTableOrder() {}

vector<Food> *Store::generateRecipe(string nutrient, int amount){
  vector<Food> recipe;
  if (amount <= 0)
    throw "We have yet to find any food item that has negative " + nutrient;
  if (nutrient == fat){
    int total = 0;
    int count = 0;
    while(total < amount && count < 20){
      Food r = randomize();
      if (r.getFat() + total < amount){
        recipe.add(recipe.begin(), r);
        total += r.getFat();
      }
      count++;
    }
    return &recipe;
  } else if (nutrient == calories){
    int total = 0;
    int count = 0;
    while(total < amount && count < 20){
      Food r = randomize();
      if (r.getCalories() + total < amount){
        recipe.add(recipe.begin(), r);
        total += r.getCalories();
      }
      count++;
    }
    return &recipe;
  } else if (nutrient == protein){
    int total = 0;
    int count = 0;
    while(total < amount && count < 20){
      Food r = randomize();
      if (r.getProtein() + total < amount){
        recipe.add(recipe.begin(), r);
        total += r.getProtein();
      }
      count++;
    }
    return &recipe;
  } else if (nutrient == fiber){
    int total = 0;
    int count = 0;
    while(total < amount && count < 20){
      Food r = randomize();
      if (r.getFiber() + total < amount){
        recipe.add(recipe.begin(), r);
        total += r.getFiber();
      }
      count++;
    }
    return &recipe;
  } else if (nutrient == sugar){
    int total = 0;
    int count = 0;
    while(total < amount && count < 20){
      Food r = randomize();
      if (r.getSugar() + total < amount){
        recipe.add(recipe.begin(), r);
        total += r.getSugar();
      }
      count++;
    }
    return &recipe;
  } else if (nutrient == carbohydrates){
    int total = 0;
    int count = 0;
    while(total < amount && count < 20){
      Food r = randomize();
      if (r.getCarbohydrates() + total < amount){
        recipe.add(recipe.begin(), r);
        total += r.getCarbohydrates();
      }
      count++;
    }
    return &recipe;
  }
  throw "Sadly, we do not have enough information about your nutrient and therefore can not generate a recipe";
  return nullptr;
}

bool Store::deleteFood(int id) {
  numFoods--;
}  // delete food with id, save to file.

string Store::getPrintOut() {}
