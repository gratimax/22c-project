/**
 * Implements the FileIO namespace.
 */
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

#include "FileIO.h"
#include "Food.h"
#include "UI.h"

using std::string;
using std::vector;
using std::stringstream;
using std::ofstream;

string foodToString(Food food) {
	stringstream foodStr;
	foodStr << food.isIngredient() << " ";
	foodStr << food.getId() << " ";
	foodStr << "\"" << food.getName() << "\"" << " ";

	if (food.isIngredient()) {
		foodStr << "\"" << food.getFoodGroup() << "\"" << " ";
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

bool FileIO::save(string file, vector<Food> food) {
	ofstream f(file);
	for (int i = 0; i < food.size(); i++) {
		f << foodToString(food[i]);
	}
	return true;
};

