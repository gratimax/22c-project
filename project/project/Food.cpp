#include "Food.h"

bool Food::isIngredient() {
	return ingredients == nullptr;
}

bool Food::isRecipe() {
	return ingredients != nullptr;
}
