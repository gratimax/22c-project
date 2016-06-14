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
using std::ifstream;

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

bool FileIO::save(string file, vector<Food> food) {
	ofstream f(file);
	for (int i = 0; i < food.size(); i++) {
		f << foodToString(food[i]) << "\n";
	}
	return true;
};

vector<Food>* FileIO::load(string file) {
	vector<Food>* vec = new vector<Food>;
	ifstream f(file);
	string line;
	while (std::getline(f, line)) {
	}
	return vec;
}

