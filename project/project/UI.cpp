/*
 * Implements the UI class.
 */
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "FileIO.h"
#include "Food.h"
#include "Store.h"
#include "UI.h"

using std::string;
using std::stringstream;
using std::vector;
using std::cout;
using std::cin;

string UI::foodToHumanString(Food food) {
  stringstream foodStr;
  string i = "  ";
  foodStr << "{"
          << "\n";
  foodStr << i << "ingredient or recipe: "
          << (food.isIngredient() ? "ingredient" : "recipe") << "\n";
  foodStr << i << "#" << food.getId() << " " << food.getName() << "\n";

  if (food.isIngredient()) {
    foodStr << i << "food group: "
            << "\"" << food.getFoodGroup() << "\""
            << "\n";
    foodStr << i << food.getCalories() << " calories"
            << "\n";
    foodStr << i << food.getFat() << "g fat"
            << "\n";
    foodStr << i << food.getProtein() << "g protein"
            << "\n";
    foodStr << i << food.getFiber() << "g fiber"
            << "\n";
    foodStr << i << food.getSugar() << "g sugar"
            << "\n";
    foodStr << i << food.getCarbohydrates() << "g carbs"
            << "\n";
  } else {
    vector<int> ingredients = food.getIngredients();

    foodStr << i << "ingredients:"
            << "\n";

    for (int i = 0; i < ingredients.size(); i++) {
      // TODO add as ingredients
      foodStr << "    " << ingredients[i];
      if (i < ingredients.size() - 1) {
        foodStr << ",";
      }
      foodStr << "\n";
    }
  }
  foodStr << "}"
          << "\n";
  return foodStr.str();
}

/**
 * Utility function that prompts the user for a value of a certain type.
 */
template <class T>
T prompt(string prompt, string failPrompt) {
  T val;
  cout << prompt << "\n>>> ";
  string line;
  getline(cin, line);
  stringstream s(line);
  if (s >> val && val >= 0) {
    return val;
  }
  while (true) {
    cout << failPrompt << "\n>>> ";
    string line;
    getline(cin, line);
    stringstream s(line);
    if (s >> val && val >= 0) {
      return val;
    }
  }
}

/**
 * Utility function that prompts the user for a string that has no quotes.
 */
string promptLineWithoutQuotes(string prompt, string failPrompt) {
  string val;
  cout << prompt << "\n>>> ";
  string line;
  getline(cin, line);
  if (line.find("\"") == -1) {
    return line;
  }
  while (true) {
    cout << failPrompt << "\n>>> ";
    string line;
    getline(cin, line);
    if (line.find("\"") == -1) {
      return line;
    }
  }
}

UI::UI(Store *store) { this->store = store; }

UI::~UI() {}

/**
 * Uitlity that checks if the given option is one that is provided by the
 * project.
 */
bool isMainScreenOption(string option) {
  return (option == "a" || option == "d" || option == "f" || option == "s" ||
          option == "h" || option == "b" || option == "i" || option == "e" ||
          option == "r" || option == "q");
}

/**
 * Utility that prints the main screen's prompt.
 */
void mainScreenPrompt() {
  cout << "(a)dd food, (d)elete food, (f)ind by id, (s)earch by name, "
       << "\n";
  cout << "list foods by (h)ash sequence, list foods by (b)st sequence, print "
          "(i)ndented tree, \n";
  cout << "print (e)fficiency, make (r)ecipe, (q)uit"
       << "\n";
  cout << ">>> ";
}

void UI::mainScreen(bool showWelcome) {
  if (showWelcome) {
    cout << "Welcome to Fruitlog!"
         << "\n";
    cout << "22c Project by Keivan, Max, Ori, Tomer"
         << "\n";
    cout << "How may I be of service?"
         << "\n";
  }
  mainScreenPrompt();
  string doNext;
  std::getline(cin, doNext);
  while (!isMainScreenOption(doNext)) {
    cout << "That is not an option, try again!"
         << "\n";
    mainScreenPrompt();
    std::getline(cin, doNext);
  }
  if (doNext == "a") {
    addDataScreen();
  } else if (doNext == "d") {
    deleteDataScreen();
  } else if (doNext == "f") {
    findByIdScreen();
  } else if (doNext == "s") {
    searchByNameScreen();
  } else if (doNext == "h") {
    listFoodsHashedSequenceScreen();
  } else if (doNext == "b") {
    listFoodsBSTSequenceScreen();
  } else if (doNext == "i") {
    indentedTreeScreen();
  } else if (doNext == "e") {
    printEfficiency();
  } else if (doNext == "r") {
    generateRecipeScreen();
  } else if (doNext == "q") {
    cout << "Quitting...\n";
    return;
  }
  mainScreen(false);
}

void UI::addDataScreen() {
  string foodName = promptLineWithoutQuotes(
      "What is it called?", "Name cannot have quotes, try again.");
  string isRecipeStr =
      promptLineWithoutQuotes("Is the food a recipe? (y)es/(n)o",
                              "Try again. Is it a recipe? (y)es/(n)o");
  bool isRecipe = isRecipeStr == "y" || isRecipeStr == "yes";
  if (isRecipe) {
    cout << "Continuing with new recipe. Let's add an ingredient:\n";
    vector<int> ingredients;
    bool addIngredient = true;
    while (addIngredient) {
      int id =
          prompt<int>("What is the ingredient's id?",
                      "Not a positive integer, what is the ingredient's id #?");
      if (store->foodWithIdExists(id)) {
        if (store->getById(id).isRecipe()) {
          cout << "That food is a recipe, try again.\n";
        }
      } else {
        cout << "That id does not exist, try again.\n";
        continue;
      }
      ingredients.push_back(id);
      string addIngredientS = promptLineWithoutQuotes(
          "Add another ingredient? (y)es/(n)o",
          "Try again. Add another ingredient? (y)es/(n)o");
      addIngredient = addIngredientS == "y" || addIngredientS == "yes";
    }
    int id = store->getNextId();
    Food food(id, foodName, ingredients);
    store->addFood(food);
    store->saveFoods();
    cout << "Ok. Just created food:\n";
    cout << foodToHumanString(food);
  } else {
    cout << "Continuing with new ingredient.\n";
    string foodGroup = promptLineWithoutQuotes(
        "What is its food group?", "Food group cannot have quotes, try again.");
    int calories =
        prompt<int>("How many calories does it have (kcal)?",
                    "Calories must be a positive integer, try again");
    double fat = prompt<double>("How many grams of fat does it have?",
                                "Fat must be a positive double, try again");
    double protein =
        prompt<double>("How many grams of protein does it have?",
                       "Protein must be a positive double, try again");
    double fiber =
        prompt<double>("How many grams of fiber does it have?",
                       "Fiber must be a positive double, try again!");
    double sugar =
        prompt<double>("How many grams of sugar does it have?",
                       "Sugar must be a positive double, try again!");
    double carbohydrates =
        prompt<double>("How many grams of carbohydrates does it have?",
                       "Carbohydrates must be a positive double, try again!");
    int id = store->getNextId();
    cout << "lol " << id << "\n";
    Food food(id, foodName, foodGroup, calories, fat, protein, fiber, sugar,
              carbohydrates);
    store->addFood(food);
    store->saveFoods();
    cout << "Ok. Just created food:\n";
    cout << foodToHumanString(food);
  }
}

void UI::deleteDataScreen() {
  int id = prompt<int>("What is the food item's ID?",
                       "Invalid ID#. What is the food item's ID?");
  if (store->foodWithIdExists(id)) {
    if (store->anyRecipeReferences(id)) {
      cout << "Recipes reference that food, so you can't delete it!\n";
    } else {
      Food food = store->getById(id);
      store->deleteFood(id);
      store->saveFoods();
      cout << foodToHumanString(food);
    }
  } else {
    cout << id << " is not a valid ID or was deleted, try again.\n";
  }
}

void UI::findByIdScreen() {
  int id = prompt<int>("What is the food item's ID?",
                       "Invalid ID#. What is the food item's ID?");
  if (store->foodWithIdExists(id)) {
    Food food = store->getById(id);
    cout << "We found the food! Here it is:\n";
    cout << foodToHumanString(food);
  } else {
    cout << id << " is not a valid ID or was deleted, try again.\n";
  }
}

/**
 * Utility that makes a comma-separated list out of food ID numbers and names.
 */
string makeCompactString(vector<Food> *foods) {
  stringstream s;
  int sz = foods->size();
  for (int i = 0; i < sz; i++) {
    Food food = foods->operator[](i);
    s << "# " << food.getId() << " " << food.getName();
    if (i < (sz - 1)) {
      s << ", ";
    }
  }
  return s.str();
}

/**
 * Utility to pull keywords from a string of space separated keywords.
 */
vector<string> getKeywordsFromString(string keywords) {
  vector<string> keys;
  stringstream s(keywords);
  string nextKeyword;
  while (s >> nextKeyword) {
    keys.push_back(nextKeyword);
  }
  return keys;
}

/**
 * Utility that prints out matches snazzily for the given name with the given
 * keywords.
 */
string printMatches(string name, vector<string> keywords) {
	int l = name.size();
	if (l <= 0){
		return "";
	}
	bool *matchField = new bool[l];
  for (int i = 0; i < name.size(); i++) {
    matchField[i] = false;
  }
  for (int i = 0; i < keywords.size(); i++) {
    string keyword = keywords[i];
    int startIndex = name.find(keyword);
    if (startIndex != -1) {
      for (int j = startIndex; j < startIndex + keyword.size(); j++) {
        matchField[j] = true;
      }
    }
  }
  stringstream out;
  for (int i = 0; i < name.size(); i++) {
    if (matchField[i]) {
      out << "^";
    } else {
      out << " ";
    }
  }
  return out.str();
}

void UI::searchByNameScreen() {
  string key = promptLineWithoutQuotes(
      "What keywords would you like to search for? (separate with spaces)",
      "Cannot have quotes in keywords. Try again.");
  vector<string> keywords = getKeywordsFromString(key);
  vector<Food> *foods = store->getMatching(keywords);
  cout << "Matching foods:\n";
  for (int i = 0; i < foods->size(); i++) {
    Food food = foods->operator[](i);
    string matches = printMatches(food.getName(), keywords);
    cout << food.getName() << " "
         << "id #" << food.getId() << "\n";
    cout << matches << "\n";
  }
}

void UI::listFoodsHashedSequenceScreen() {
  vector<Food> *foods = store->getInHashTableOrder();
  string ids = makeCompactString(foods);
  cout << "Foods in hash table sequence: \n";
  cout << ids << "\n";
  delete foods;
}

void UI::listFoodsBSTSequenceScreen() {
  vector<Food> *foods = store->getInSortedOrder();
  string ids = makeCompactString(foods);
  cout << "Foods in sorted sequence: \n";
  cout << ids << "\n";
  delete foods;
}

void UI::indentedTreeScreen() {
  cout << "Indented tree:\n";
  cout << store->getPrintOut() << "\n";
}

void UI::printEfficiency() {
  cout << "Total number of operations thus far:\n";
  // print efficiency
}

void UI::generateRecipeScreen() {
  string nutrient = promptLineWithoutQuotes(
      "What nutrient would you like? (calories,fat,protein,sugar,fiber,carbohydrates)",
      "Cannot have quotes in nutrient. Try again.");
  int amount =
      prompt<int>("What is the maximum amount of this nutrient you'd like?",
                  "Not a positive integer, what is maximum amount?");
  try {
    vector<Food> *foods = store->generateRecipe(nutrient, amount);
    cout << "Here are the foods\n";
    cout << makeCompactString(foods) << "\n";
    string name = promptLineWithoutQuotes(
        "What nutrient would you like? (calories,fat,protein,sugar,fiber,carbohydrates)",
        "Cannot have quotes in nutrient. Try again.");
  } catch (const string &err) {
    cerr << err << "\n";
    std::cout << "Try again!\n";
  }
}
