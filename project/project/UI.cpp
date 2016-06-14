/*
 * Implements the UI namespace.
 */
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <exception>

#include "Food.h"
#include "UI.h"

using std::string;
using std::stringstream;
using std::vector;
using std::cout;
using std::cin;

string foodToHumanString(Food food) {
	stringstream foodStr;
	foodStr << "isIngredient = " << food.isIngredient() << "\n";
	foodStr << food.getId() << ": " << food.getName() << "\n";

	if (food.isIngredient()) {
		foodStr << "food group: " << "\"" << food.getFoodGroup() << "\"" << "\n";
		foodStr << food.getCalories() << " calories" << "\n";
		foodStr << food.getFat() << "g fat" << "\n";
		foodStr << food.getProtein() << "g protein" << "\n";
		foodStr << food.getSugar() << "g sugar" << "\n";
		foodStr << food.getCarbohydrates() << "g carbs" << "\n";
	} else {
		vector<Food> ingredients = food.getIngredients();

		foodStr << "ingredients:" << "\n";

		for (int i = 0; i < ingredients.size(); i++) {
			foodStr << ingredients[i].getId();
			if (i < ingredients.size() - 1) {
				foodStr << ",\n";
			}
		}

	}
	return foodStr.str();
}

template <class T>
T prompt(string prompt, string failPrompt, bool lineWithoutQuotes = false) {
	T val;
	cout << prompt << "\n>>> ";
	string line;
	getline(cin, line);
	stringstream s(line);
	if (lineWithoutQuotes && line.find("\"") == -1) {
		return line;
	}
	if (s >> val) {
		return val;
	}
	while (true) {
		cout << failPrompt << "\n>>> ";
		string line;
		getline(cin, line);
		stringstream s(line);
		if (lineWithoutQuotes && line.find("\"") == -1) {
			return line;
		}
		if (s >> val) {
			return val;
		}
	}
}

bool isMainScreenOption(string option) {
	return (option == "a" || option == "d" || option == "f" || option == "h" || option == "b" ||
			option == "i" || option == "e" || option == "r");
}

void mainScreenPrompt() {
	cout << "(a)dd food, (d)elete food, (f)ind by id, list foods by (h)ash sequence, " << "\n";
	cout << "list foods by (b)st sequence, print (i)ndented tree, print (e)fficiency, " << "\n";
	cout << "make (r)ecipe" << "\n";
	cout << ">>> ";
}

void UI::mainScreen() {
	cout << "Welcome to Fruitlog!" << "\n";
	cout << "22c Project by Keivan, Max, Ori, Tomer" << "\n";
	cout << "How may I be of service?" << "\n";
	mainScreenPrompt();
	string doNext;
	std::getline(cin, doNext);	
	while (!isMainScreenOption(doNext)) {
		cout << "That is not an option, try again!" << "\n";
		mainScreenPrompt();
		std::getline(cin, doNext);
	}
}

void UI::addDataScreen() {
}

void UI::deleteDataScreen() {
}

void UI::findByIdScreen() {
}

void UI::listFoodsHashedSequenceScreen() {
}

void UI::listFoodsBSTSequenceScreen() {
}

void UI::indentedTreeScreen() {
}

void UI::printEfficiency() {
}

void UI::generateRecipeScreen() {
}


