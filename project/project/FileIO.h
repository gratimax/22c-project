#ifndef __FILE_IO_H
#define __FILE_IO_H

#include <vector>
#include <string>

#include "Food.h"

using std::string;

namespace FileIO {
	
	bool save(string file, vector<Food> food);
	
	vector<Food>*  load(string file);

};

#endif
