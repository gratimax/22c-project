/**
 * Implements the FileIO class.
 */
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "FileIO.h"
#include "Food.h"
#include "UI.h"

using std::string;
using std::vector;
using std::stringstream;
using std::ofstream;
using std::ifstream;
using std::cerr;

const string FileIO::failMsg = "Failed to read line from file, continuing.";

/**
 * Utility method that converts a food into a string, representing all of its
 * state.
 */
string foodToString(Food food) {
  stringstream foodStr;
  foodStr << food.isIngredient() << " ";
  foodStr << food.getId() << " ";
  foodStr << "\"" << food.getName() << "\""
          << " ";

  if (food.isIngredient()) {
    foodStr << "\"" << food.getFoodGroup() << "\""
            << " ";
    foodStr << food.getCalories() << " ";
    foodStr << food.getFat() << " ";
    foodStr << food.getProtein() << " ";
    foodStr << food.getFiber() << " ";
    foodStr << food.getSugar() << " ";
    foodStr << food.getCarbohydrates();
  } else {
    vector<int> ingredients = food.getIngredients();

    for (int i = 0; i < ingredients.size(); i++) {
      foodStr << ingredients[i];
      if (i < ingredients.size() - 1) {
        foodStr << " ";
      }
    }
  }
  return foodStr.str();
}

bool FileIO::save(string file, vector<Food> *food) {
  ofstream f(file);
  for (int i = 0; i < food->size(); i++) {
    f << foodToString(food->operator[](i)) << "\n";
  }
  return true;
};

vector<Food> *FileIO::load(string file) {
  ifstream f(file);
  if (!f.good()) {
    throw "File 'foods.txt' not found or cannot be read from, try again.";
  }
  vector<Food> *vec = new vector<Food>;
  string line;
  int i = 0;
  while (std::getline(f, line)) {
    i++;
    stringstream s(line);
    if (line.size() == 0) {
      continue;
    }
    if (std::count(line.begin(), line.end(), '"') % 2 != 0) {
      cerr << failMsg << " On line " << i << "."
           << " Number of quotes must be even." << std::endl;
      continue;
    }
    bool isIngredient;
    if (!(s >> isIngredient)) {
      cerr << failMsg << " On line " << i << "." << std::endl;
      continue;
    }
    int id;
    if (!(s >> id) || id <= 0) {
      cerr << failMsg << " On line " << i << "." << std::endl;
      continue;
    };
    string name;
    s.ignore(2, '"');
    std::getline(s, name, '"');
    if (isIngredient) {
      s.ignore(2, '"');
      string foodGroup;
      std::getline(s, foodGroup, '"');
      int calories;
      if (!(s >> calories)) {
        cerr << failMsg << " On line " << i << "." << std::endl;
        continue;
      }
      double fat;
      if (!(s >> fat)) {
        cerr << failMsg << " On line " << i << "." << std::endl;
        continue;
      }
      double protein;
      if (!(s >> protein)) {
        cerr << failMsg << " On line " << i << "." << std::endl;
        continue;
      }
      double fiber;
      if (!(s >> fiber)) {
        cerr << failMsg << " On line " << i << "." << std::endl;
        continue;
      }
      double sugar;
      if (!(s >> sugar)) {
        cerr << failMsg << " On line " << i << "." << std::endl;
        continue;
      }
      double carbs;
      if (!(s >> carbs)) {
        cerr << failMsg << " On line " << i << "." << std::endl;
        continue;
      }
      Food food(id, name, foodGroup, calories, fat, protein, fiber, sugar,
                carbs);
      vec->push_back(food);
    } else {
      vector<int> ingredients;
      int nextId;
      while (s >> nextId) {
        ingredients.push_back(nextId);
      }
      if (ingredients.size() == 0) {
        cerr << failMsg << " On line " << i << "."
             << " Recipe cannot have 0 ingredients." << std::endl;
        continue;
      }
      Food food(id, name, ingredients);
      vec->push_back(food);
    }
  }
  return vec;
}
