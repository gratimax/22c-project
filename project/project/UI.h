/**
 * Defines the UI namespace.
 */

#ifndef __UI_H
#define __UI_H

#include "Food.h"

namespace UI {

void mainScreen(bool showWelcome);

void addDataScreen();

void deleteDataScreen();

void findByIdScreen();

void listFoodsHashedSequenceScreen();

void listFoodsBSTSequenceScreen();

void indentedTreeScreen();

void printEfficiency();

void generateRecipeScreen();

}

#endif
