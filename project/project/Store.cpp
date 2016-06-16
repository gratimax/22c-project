/**
 * Implements the Store class.
 */

#include <time.h>
#include <sstream>
#include <vector>

#include "BST.h"
#include "Efficiency.h"
#include "FileIO.h"
#include "HashTable.h"
#include "Store.h"

using std::vector;

Store::Store(string filename) {
  this->filename = filename;
  this->fileIO = new FileIO();
  this->bst = new BST<Food>();
}

Store::~Store() {
  delete this->fileIO;
  delete this->bst;
}

Food Store::randomize() {
  int r = 0;
  do {
    r = rand() % maxId + 1;
  } while (!foodWithIdExists(r));
  return hashBrownTable.getItemByKey(r)->getData();
}

void Store::initializeFoods() {
  vector<Food> *foods = fileIO->load(filename);
  std::cout << "size of foods: " << foods->size() << "\n";
  for (int i = 0; i < foods->size(); i++) {
    Food food = foods->operator[](i);
    bst->insert(food);
    if (food.getId() > maxId) {
      maxId = food.getId();
    }
    numFoods++;
  }
  for (int i = 0; i < foods->size(); i++) {
    Food food = foods->operator[](i);
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
  delete foods;
}

bool Store::foodWithIdExists(int id) {
  try {
    hashBrownTable.getItemByKey(id);
    return true;
  } catch (const char *str) {
  }
  return false;
}

bool Store::addFood(Food food) {
  if (food.getId() != getNextId()) {
    throw "Food has invalid id #";
    return false;
  }
  bst->insert(food);
  hashBrownTable.insertItem(food.getId(), bst->get(food));
  numFoods++;
  maxId++;
  return true;
}

bool Store::anyRecipeReferences(int id) {
  vector<Food> *v = getInHashTableOrder();
  for (int i = 0; i < v->size(); i++) {
    Food food = v->operator[](i);
    if (food.isRecipe()) {
      vector<int> ingredients = food.getIngredients();
      for (int j = 0; j < ingredients.size(); j++) {
        if (ingredients[j] == id) {
          delete v;
          return true;
        }
      }
    }
  }
  delete v;
  return false;
}

Food Store::getById(int id) {
  if (foodWithIdExists(id)) return hashBrownTable.getItemByKey(id)->getData();
  throw "nope";
}

int Store::getNextId() { return maxId + 1; }

int Store::getNumFoods() { return numFoods; }

string Store::lower(string s) {
  stringstream new_s;
  for (int i = 0; i < s.size(); i++) {
    new_s << (char)std::tolower(s[i]);
  }
  return new_s.str();
}

vector<Food> *Store::getMatching(vector<string> keywords) {
  vector<Food> *foods = getInSortedOrder();
  vector<Food> *ret = new vector<Food>();
  for (int i = 0; i < foods->size(); i++) {
    Food food = foods->operator[](i);
    bool matching = false;
    for (int j = 0; j < keywords.size(); j++) {
      if (lower(food.getName()).find(keywords[j]) != -1) {
        matching = true;
      }
    }
    if (matching) {
      ret->push_back(food);
    }
  }
  delete foods;
  return ret;
}

vector<Food> *Store::getInSortedOrder() {
  if (bst->getRoot() == nullptr) {
    vector<Food> *vec = new vector<Food>;
    return vec;
  } else {
    return bst->getSorted(bst->getRoot());
  }
}

vector<Food> *Store::getInHashTableOrder() {
  vector<BSTNode<Food> *> *v = hashBrownTable.putInVector();
  vector<Food> *foods = new vector<Food>;
  for (int i = 0; i < v->size(); i++) {
    BSTNode<Food> *b = v->operator[](i);
    foods->push_back(v->operator[](i)->getData());
  }
  return foods;
}

vector<Food> *Store::generateRecipe(string nutrient, int amount) {
  vector<Food> *recipe = new vector<Food>;
  if (amount <= 0)
    throw "We have yet to find any food item that has negative " + nutrient;
  if (nutrient == "fat") {
    int total = 0;
    int count = 0;
    while (total < amount && count < 20) {
      Food r = randomize();
      if (r.getFat() + total < amount) {
        recipe->push_back(r);
        total += r.getFat();
      }
      count++;
    }
    return recipe;
  } else if (nutrient == "calories") {
    int total = 0;
    int count = 0;
    while (total < amount && count < 20) {
      Food r = randomize();
      if (r.getCalories() + total < amount) {
        recipe->push_back(r);
        total += r.getCalories();
      }
      count++;
    }
    return recipe;
  } else if (nutrient == "protein") {
    int total = 0;
    int count = 0;
    while (total < amount && count < 20) {
      Food r = randomize();
      if (r.getProtein() + total < amount) {
        recipe->push_back(r);
        total += r.getProtein();
      }
      count++;
    }
    return recipe;
  } else if (nutrient == "fiber") {
    int total = 0;
    int count = 0;
    while (total < amount && count < 20) {
      Food r = randomize();
      if (r.getFiber() + total < amount) {
        recipe->push_back(r);
        total += r.getFiber();
      }
      count++;
    }
    return recipe;
  } else if (nutrient == "sugar") {
    int total = 0;
    int count = 0;
    while (total < amount && count < 20) {
      Food r = randomize();
      if (r.getSugar() + total < amount) {
        recipe->push_back(r);
        total += r.getSugar();
      }
      count++;
    }
    return recipe;
  } else if (nutrient == "carbohydrates") {
    int total = 0;
    int count = 0;
    while (total < amount && count < 20) {
      Food r = randomize();
      if (r.getCarbohydrates() + total < amount) {
        recipe->push_back(r);
        total += r.getCarbohydrates();
      }
      count++;
    }
    return recipe;
  }
  throw string(
      "Sadly, we do not have enough information about your nutrient and "
      "therefore can not generate a recipe");
  return nullptr;
}

bool Store::deleteFood(int id) {
  bool success;
  success =
      (bst->AVLDelete(bst->getRoot(),
                      hashBrownTable.getItemByKey(id)->getData(), false) &&
       hashBrownTable.removeItem(id));
  numFoods--;
  return success;
}

string verticalBar = "\u2502";
string horizontalBar = "\u2500";
string lJunction = "\u2514";
string tJunctionRight = "\u251C";
string tJunctionDown = "\u252C";

string nodeFoodAsString(BSTNode<Food> *node, string bef) {
  stringstream stream;
  Food food = node->getData();
  stream << bef << food.getId() << " " << food.getName();
  return stream.str();
}

string printOut(string prefix, BSTNode<Food> *node, bool rightNode, bool root) {
  string s;
  if (rightNode) {
    string nodeStringBef = horizontalBar;
    Efficiency::totalDataStructureOperations += 2;
    if (node->left != nullptr || node->right != nullptr) {
      nodeStringBef = tJunctionDown;
    }
    s = prefix + lJunction + horizontalBar +
        nodeFoodAsString(node, nodeStringBef) + "\n";
    prefix += "  ";
  } else {
    if (root) {
      s = nodeFoodAsString(node, "") + "\n";
    } else {
      string nodeStringBef = horizontalBar;
      Efficiency::totalDataStructureOperations += 2;
      if (node->left != nullptr || node->right != nullptr) {
        nodeStringBef = tJunctionDown;
      }
      s = prefix + tJunctionRight + horizontalBar +
          nodeFoodAsString(node, nodeStringBef) + "\n";
      prefix += verticalBar + " ";
    }
  }
  string left = "";
  if (node->left != nullptr) {
    string p = (node->right == nullptr) ? " " : verticalBar;
    Efficiency::totalDataStructureOperations++;
    left = printOut(prefix, node->left, false, false);
  }
  string right = "";
  if (node->right != nullptr) {
    Efficiency::totalDataStructureOperations++;
    right = printOut(prefix, node->right, true, false);
  }
  return s + left + right;
}

string Store::getPrintOut() {
  Efficiency::totalDataStructureOperations++;
  if (bst->getRoot() == nullptr) {
    return "";
  } else {
    return printOut("", bst->getRoot(), false, true);
  }
}
