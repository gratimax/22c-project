#include "Food.h"

bool Food::isIngredient() {
	return ingredients.empty();
}

bool Food::isRecipe() {
	return !ingredients.empty();
}
