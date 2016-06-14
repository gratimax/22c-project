/**
 * Defines the UI class.
 */

#ifndef __UI_H
#define __UI_H

#include "FileIO.h"
#include "Food.h"

class UI {

FileIO* fileIO;

public:

UI();

~UI();

static string foodToHumanString(Food food);

void mainScreen(bool showWelcome);

void addDataScreen();

void deleteDataScreen();

void findByIdScreen();

void searchByNameScreen();

void listFoodsHashedSequenceScreen();

void listFoodsBSTSequenceScreen();

void indentedTreeScreen();

void printEfficiency();

void generateRecipeScreen();

FileIO* getFileIO();

};

#endif
