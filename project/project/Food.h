/**
 * Defines the header for the Food class.
 */

#ifndef __FOOD_H
#define __FOOD_H

#include <string>
#include <vector>

using std::string;
using std::vector;

/**
 * Represents an ingredient or a recipe made of food.
 */
class Food {

	int id;

	string name;

	string foodGroup;

	int calories;

	double fat;

	double protein;

	double fiber;

	double sugar;

	double carbohydrates;

	vector<Food> ingredients;

	public:

	Food(int id, string name, string foodGroup, int calories, double fat, double protein,
			double fiber, double sugar, double carbohydrates) {};

	Food(vector<Food> ingredients);

	~Food() {};

	void calculateNutrients() {};

	int getId();

	string getName();

	string getFoodGroup();

	int getCalories();

	double getFat();

	double getProtein();

	double getFiber();

	double getSugar();

	double getCarbohydrates();

	vector<Food> getIngredients();

	bool isIngredient();

	bool isRecipe();

};

#endif