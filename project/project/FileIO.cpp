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

bool FileIO::save(string file, vector<Food> food) {
	ofstream f(file);
	for (int i = 0; i < food.size(); i++) {
		f << UI::foodToString(food[i]);
	}
	return true;
};

