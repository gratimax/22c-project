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
  while (!foodWithIdExists(r));
    return hashBrownTable.getItemByKey(r)->getData();
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
    hashBrownTable.insertItem(food.getId(), bst->get(food));
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
  try {
    hashBrownTable.getItemByKey(id);
  } catch (const string* str){
    return false;
  }
  return true;
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
  if (foodWithIdExists(id))
    return hashBrownTable.getItemByKey(id)->getData();
  throw "nope";
}

int Store::getNextId() { return maxId + 1; }

int Store::getNumFoods() { return numFoods; }

vector<Food> *Store::getMatching(vector<string> keywords) {
  vector<Food> *foods = getInSortedOrder();
}

vector<Food> *Store::getInSortedOrder() {
  return bst->getSorted(bst->getRoot());
}

vector<Food> *Store::getInHashTableOrder() {
  vector<BSTNode<Food> *> *v = hashBrownTable.putInVector();
  vector<Food> *foods = new vector<Food>;
  for (int i = 0; i < v->size(); i++) {
    foods->push_back(v->operator[](i)->getData());
  }
  return foods;
}

vector<Food> *Store::generateRecipe(string nutrient, int amount){
  vector<Food> *recipe = new vector<Food>;
  if (amount <= 0)
    throw "We have yet to find any food item that has negative " + nutrient;
  if (nutrient == "fat"){
    int total = 0;
    int count = 0;
    while(total < amount && count < 20){
      Food r = randomize();
      if (r.getFat() + total < amount){
        recipe->push_back(r);
        total += r.getFat();
      }
      count++;
    }
    return recipe;
  } else if (nutrient == "calories"){
    int total = 0;
    int count = 0;
    while(total < amount && count < 20){
      Food r = randomize();
      if (r.getCalories() + total < amount){
        recipe->push_back(r);
        total += r.getCalories();
      }
      count++;
    }
    return recipe;
  } else if (nutrient == "protein"){
    int total = 0;
    int count = 0;
    while(total < amount && count < 20){
      Food r = randomize();
      if (r.getProtein() + total < amount){
        recipe->push_back(r);
        total += r.getProtein();
      }
      count++;
    }
    return recipe;
  } else if (nutrient == "fiber"){
    int total = 0;
    int count = 0;
    while(total < amount && count < 20){
      Food r = randomize();
      if (r.getFiber() + total < amount){
        recipe->push_back(r);
        total += r.getFiber();
      }
      count++;
    }
    return recipe;
  } else if (nutrient == "sugar"){
    int total = 0;
    int count = 0;
    while(total < amount && count < 20){
      Food r = randomize();
      if (r.getSugar() + total < amount){
        recipe->push_back(r);
        total += r.getSugar();
      }
      count++;
    }
    return recipe;
  } else if (nutrient == "carbohydrates"){
    int total = 0;
    int count = 0;
    while(total < amount && count < 20){
      Food r = randomize();
      if (r.getCarbohydrates() + total < amount){
        recipe->push_back(r);
        total += r.getCarbohydrates();
      }
      count++;
    }
    return recipe;
  }
  throw "Sadly, we do not have enough information about your nutrient and therefore can not generate a recipe";
  return nullptr;
}

bool Store::deleteFood(int id) {
	bool success;
	success = (hashBrownTable.removeItem(id) && bst->AVLDelete(bst->getRoot(), hashBrownTable.getItemByKey(id)->getData(), false));
  numFoods--;
  return success;
}

string Store::getPrintOut() {}
