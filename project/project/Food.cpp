#include <string>

#include "Food.h"

using std::string;

Food::Food() {}

Food::Food(int id, string name, string foodGroup, int calories, double fat,
           double protein, double fiber, double sugar, double carbohydrates) {
  this->id = id;
  this->name = name;
  this->foodGroup = foodGroup;
  this->calories = calories;
  this->fat = fat;
  this->protein = protein;
  this->fiber = fiber;
  this->sugar = sugar;
  this->carbohydrates = carbohydrates;
}

Food::Food(int id, string name, vector<int> ingredients) {
  this->id = id;
  this->name = name;
  this->ingredients = ingredients;
}

bool Food::isIngredient() { return ingredients.empty(); }

bool Food::isRecipe() { return !ingredients.empty(); }

int Food::getId() const { return id; }

string Food::getName() { return name; }

string Food::getFoodGroup() { return foodGroup; }

int Food::getCalories() { return calories; }

double Food::getFat() { return fat; }

double Food::getProtein() { return protein; }

double Food::getFiber() { return fiber; }

double Food::getSugar() { return sugar; }

double Food::getCarbohydrates() { return carbohydrates; }

vector<int> Food::getIngredients() { return ingredients; }

bool operator<(const Food &f1, const Food &f2) {
  return (f1.getId() < f2.getId());
};

bool operator>(const Food &f1, const Food &f2) {
  return (f1.getId() > f2.getId());
};

void Food::calculateNutrients(vector<Food> ingredients) {
  fat = 0;
  protein = 0;
  fiber = 0;
  sugar = 0;
  carbohydrates = 0;
  for (int i = 0; i < ingredients.size(); i++) {
    Food f = ingredients[i];
    fat += f.fat;
    protein += f.protein;
    fiber += f.fiber;
    sugar += f.sugar;
    carbohydrates += f.carbohydrates;
  }
}
