/**
 * Defines the FileIO class.
 */
#ifndef __FILE_IO_H
#define __FILE_IO_H

#include <vector>
#include <string>

#include "Food.h"

using std::string;

/**
 * Handles file operations related to food.
 *
 * File format for food:
 * <isIngredient> <id> "<name>" <rest...>
 * for ingredients, <rest...> = "<foodGroup>" <calories> <fat> <protein> <fiber> <sugar> <carbs>
 * for recipes, <rest...> = <ingredient1> <ingredient2> <ingredient3>...
 */
class FileIO {

const static string failMsg;

public:

/**
 * Save the given vector of food into the given file as a string.
 * Returns true if the operation was successful, and false otherwise.
 */
bool save(string file, vector<Food> food);

/**
 * Load a vector of food from the given file as as string.
 */
vector<Food>* load(string file);

};

#endif
