#include <string>

#include "Food.h"

using std::string;

bool Food::isIngredient() {
	return ingredients.empty();
}

bool Food::isRecipe() {
	return !ingredients.empty();
}

int Food::getId() {
	return id;
}

string Food::getName() {
	return name;
}

string Food::getFoodGroup() {
	return foodGroup;
}

int Food::getCalories() {
	return calories;
}

double Food::getFat() {
	return fat;
}

double Food::getProtein() {
	return protein;
}

double Food::getFiber() {
	return fiber;
}

double Food::getSugar() {
	return sugar;
}

double Food::getCarbohydrates() {
	return carbohydrates;
}

vector<Food> Food::getIngredients() {
	return ingredients;
}

