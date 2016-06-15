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
 * For recipes, holds a bunch of foods that make up the recipes' ingredients.
 * For ingredients, holds all the nutrients the ingredient has.
 */
class Food {
  /**
   * The ID number of the food (at least one, autoincrementing).
   */
  int id;

  /**
   * The name of the food as a string (no quotes).
   */
  string name;

  /**
   * The name of the food's food group as a string (no quotes).
   */
  string foodGroup;

  /**
   * The number of calories (energy) the food contains in kcal.
   */
  int calories;

  /**
   * The amount of fat the food contains in grams.
   */
  double fat;

  /**
   * The amount of protein the food contains in grams.
   */
  double protein;

  /**
   * The amount of fiber the food contains in grams.
   */
  double fiber;

  /**
   * The amount of sugar the food contains in grams.
   */
  double sugar;

  /**
   * The amount of carbohydrates the food contains in grams.
   */
  double carbohydrates;

  /**
   * The ingredients of the food as expressed by their id #s.
   */
  vector<int> ingredients;

 public:
  /**
   * Constructs an empty food object.
   */
  Food();

  /**
   * Constructs an ingredient given its name, food group, and nutrients.
   */
  Food(int id, string name, string foodGroup, int calories, double fat,
       double protein, double fiber, double sugar, double carbohydrates);

  /**
   * Constructs a recipe given its name and ingredients.
   */
  Food(int id, string name, vector<int> ingredients);

  /**
   * Deconstructs the food object.
   */
  ~Food(){};

  /**
   * Calculates the nutrients for the food given its ingredients (this is needed
   * to avoid
   * copying the food objects).
   */
  void calculateNutrients(vector<Food> ingredients);

  /**
   * Returns the ID of the food.
   */
  int getId() const;

  /**
   * Returns the name of the food.
   */
  string getName();

  /**
   * Returns the food group of the food.
   */
  string getFoodGroup();

  /**
   * Returns how many calories the food has.
   */
  int getCalories();

  /**
   * Returns how much fat is in the food.
   */
  double getFat();

  /**
   * Returns how much protein is in the food.
   */
  double getProtein();

  /**
   * Returns how much fiber is in the food.
   */
  double getFiber();

  /**
   * Returns how much sugar is in the food.
   */
  double getSugar();

  /**
   * Returns how many carbohydrates are in the food.
   */
  double getCarbohydrates();

  /**
   * Returns the ingredients of the food as a vector.
   */
  vector<int> getIngredients();

  /**
   * Checks if the food is an ingredient.
   */
  bool isIngredient();

  /**
   * Checks if the food is a recipe.
   */
  bool isRecipe();

  /**
   * Compares two foods to see which one is greater according to their ID
   * numbers.
   */
  friend bool operator<(const Food &p1, const Food &p2);

  /**
   * Compares two foods to see which one is smaller according to their ID
   * numbers.
   */
  friend bool operator>(const Food &p1, const Food &p2);
};

#endif
