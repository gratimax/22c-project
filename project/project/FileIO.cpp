/**
 * Implements the FileIO class.
 */
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>

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
		foodStr << food.getFiber() << " ";
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
	ifstream f(file);
	if (!f.good()) {
		throw "File 'foods.txt' not found or cannot be read from, try again.";
	}
	vector<Food>* vec = new vector<Food>;
	string line;
	while (std::getline(f, line)) {
		stringstream s(line);
		bool isIngredient;
		if (!(s >> isIngredient)) {
			cerr << failMsg;
			continue;
		}
		int id;
		if (!(s >> id) || id <= 0) {
			cerr << failMsg;
			continue;
		};
		string name;
		s.ignore();
		std::getline(s, name, '"');
		if (isIngredient) {
			string foodGroup;
			std::getline(s, foodGroup, '"');
			int calories;
			if (!(s >> calories)) {
				cerr << failMsg;
				continue;
			}
			double fat;
			if (!(s >> fat)) {
				cerr << failMsg;
				continue;
			}
			double protein;
			if (!(s >> protein)) {
				cerr << failMsg;
				continue;
			}
			double fiber;
			if (!(s >> fiber)) {
				cerr << failMsg;
				continue;
			}
			double sugar;
			if (!(s >> sugar)) {
				cerr << failMsg;
				continue;
			}
			double carbs;
			if (!(s >> carbs)) {
				cerr << failMsg;
				continue;
			}
			Food food(id, name, foodGroup, calories, fat, protein, fiber, sugar, carbs);
			vec->push_back(food);
		} else {
			vector<int> ingredients;
			int nextId;
			while (!(s >> nextId)) {
				ingredients.push_back(s);
			}
			Food food(id, name, ingredients);
			vec->push_back(food);
		}
	}
	return vec;
}

