/*
 * The home of the main function.
 */

#include <iostream>
#include <vector>

#include "Food.h"
#include "UI.h"

using std::vector;
using std::cout;
using std::cerr;

void ending(bool hadError) {
	cout << "Thanks for using Fruitlog! ";
	if (hadError) {
		cout << "Sorry for the error! ";
	}
	cout << "Bye now!\n";
}

int main() {
	UI ui;
	try {
		vector<Food>* food = ui.getFileIO()->load("food.txt");
		cout << food->size() << " foods loaded" << std::endl;
		ui.mainScreen(true);
		ending(true);
		return 1;
	} catch (const char* err) {
		cerr << err << std::endl;
		ending(false);
		return 1;
	}
}
