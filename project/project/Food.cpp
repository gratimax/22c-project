#include <string>

#include "Food.h"

using std::string;

Food::Food(int id, string name, string foodGroup, int calories, double fat, double protein,
		double fiber, double sugar, double carbohydrates) {
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

vector<int> Food::getIngredients() {
	return ingredients;
}

