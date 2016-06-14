/*
 * Implements the UI class.
 */
#include <string>
#include <sstream>
#include <iostream>
#include <vector>

#include "FileIO.h"
#include "Food.h"
#include "UI.h"
#include "Store.h"

using std::string;
using std::stringstream;
using std::vector;
using std::cout;
using std::cin;

string UI::foodToHumanString(Food food) {
	stringstream foodStr;
	string i = "  ";
	foodStr << "{" << "\n";
	foodStr << i << "ingredient or recipe: " <<
		(food.isIngredient() ? "ingredient" : "recipe") << "\n";
	foodStr << i << "#" << food.getId() << " " << food.getName() << "\n";

	if (food.isIngredient()) {
		foodStr << i << "food group: " << "\"" << food.getFoodGroup() << "\"" << "\n";
		foodStr << i << food.getCalories() << " calories" << "\n";
		foodStr << i << food.getFat() << "g fat" << "\n";
		foodStr << i << food.getProtein() << "g protein" << "\n";
		foodStr << i << food.getFiber() << "g fiber" << "\n";
		foodStr << i << food.getSugar() << "g sugar" << "\n";
		foodStr << i << food.getCarbohydrates() << "g carbs" << "\n";
	} else {
		vector<int> ingredients = food.getIngredients();

		foodStr << i << "ingredients:" << "\n";

		for (int i = 0; i < ingredients.size(); i++) {
			// TODO add as ingredients
			foodStr << "    " << ingredients[i];
			if (i < ingredients.size() - 1) {
				foodStr << ",";
			}
			foodStr << "\n";
		}

	}
	foodStr << "}" << "\n";
	return foodStr.str();
}

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

UI::UI(Store* store) {
	this->store = store;
}

UI::~UI() {
}

bool isMainScreenOption(string option) {
	return (option == "a" || option == "d" || option == "f" || option == "s" || option == "h" ||
			option == "b" || option == "i" || option == "e" || option == "r" || option == "q");
}

void mainScreenPrompt() {
	cout << "(a)dd food, (d)elete food, (f)ind by id, (s)earch by name, " << "\n";
	cout << "list foods by (h)ash sequence, list foods by (b)st sequence, print (i)ndented tree, \n";
	cout << "print (e)fficiency, make (r)ecipe, (q)uit" << "\n";
	cout << ">>> ";
}

void UI::mainScreen(bool showWelcome) {
	if (showWelcome) {
		cout << "Welcome to Fruitlog!" << "\n";
		cout << "22c Project by Keivan, Max, Ori, Tomer" << "\n";
		cout << "How may I be of service?" << "\n";
	}
	mainScreenPrompt();
	string doNext;
	std::getline(cin, doNext);
	while (!isMainScreenOption(doNext)) {
		cout << "That is not an option, try again!" << "\n";
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
	string foodName = promptLineWithoutQuotes("What is it called?",
			"Name cannot have quotes, try again.");
	string isRecipeStr = promptLineWithoutQuotes("Is the food a recipe? (y)es/(n)o",
			"Try again. Is it a recipe? (y)es/(n)o");
	bool isRecipe = isRecipeStr == "y" || isRecipeStr == "yes";
	if (isRecipe) {
		cout << "Continuing with new recipe. Let's add an ingredient:\n";
		vector<int> ingredients;
		bool addIngredient = true;
		while (addIngredient) {
			int id = prompt<int>("What is the ingredient's id?",
					"Not a positive integer, what is the ingredient's id #?");
			ingredients.push_back(id);
			string addIngredientS = promptLineWithoutQuotes("Add another ingredient? (y)es/(n)o",
					"Try again. Add another ingredient? (y)es/(n)o");
			addIngredient = addIngredientS == "y" || addIngredientS == "yes";
		}
		Food food(1, foodName, ingredients);
		cout << "Ok. Just created food:\n";
		cout << foodToHumanString(food);
	} else {
		cout << "Continuing with new ingredient.\n";
		string foodGroup = promptLineWithoutQuotes("What is its food group?",
				"Food group cannot have quotes, try again.");
		int calories = prompt<int>("How many calories does it have (kcal)?",
				"Calories must be a positive integer, try again");
		double fat = prompt<double>("How many grams of fat does it have?",
				"Fat must be a positive double, try again");
		double protein = prompt<double>("How many grams of protein does it have?",
				"Protein must be a positive double, try again");
		double fiber = prompt<double>("How many grams of fiber does it have?",
				"Fiber must be a positive double, try again!");
		double sugar = prompt<double>("How many grams of sugar does it have?",
				"Sugar must be a positive double, try again!");
		double carbohydrates = prompt<double>("How many grams of carbohydrates does it have?",
				"Carbohydrates must be a positive double, try again!");
		Food food(0, foodName, foodGroup, calories, fat, protein, fiber, sugar, carbohydrates);
		cout << "Ok. Just created food:\n";
		cout << foodToHumanString(food);
	}
}

void UI::deleteDataScreen() {
	int id = prompt<int>("What is the food item's ID?", "Invalid ID#. What is the food item's ID?");
	cout << id << " deleted!\n";
}

void UI::findByIdScreen() {
	int id = prompt<int>("What is the food item's ID?", "Invalid ID#. What is the food item's ID?");
}

void UI::searchByNameScreen() {
	string key = promptLineWithoutQuotes("What keywords would you like to search for? (separate with spaces)",
			"Cannot have quotes in keywords. Try again.");
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

