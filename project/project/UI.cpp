/*
 * Implements the UI namespace.
 */
#include <string>
#include <sstream>
#include <vector>

#include "Food.h"
#include "UI.h"

using std::string;
using std::stringstream;
using std::vector;

string UI::foodToString(Food food) {
	stringstream foodStr;
	foodStr << food.isIngredient() << " ";
	foodStr << food.getId() << " ";
	foodStr << "\"" << food.getName() << "\"" << " ";

	if (food.isIngredient()) {
		foodStr << food.getCalories() << " ";
		foodStr << food.getFat() << " ";
		foodStr << food.getProtein() << " ";
		foodStr << food.getSugar() << " ";
		foodStr << food.getCarbohydrates() << " ";
	} else {
		vector<Food> ingredients = food.getIngredients();

		for (int i = 0; i < ingredients.size(); i++) {
			foodStr << ingredients[i].getId();
			if (i < ingredients.size() - 1) {
				foodStr << " ";
			}
		}

	}
	return foodStr.str();
}

