/**
 * Defines the UI class.
 */

#ifndef __UI_H
#define __UI_H

#include "FileIO.h"
#include "Store.h"
#include "Food.h"

class UI {

FileIO* fileIO;
Store* store;

public:

UI();

~UI();

string foodToHumanString(Food food);

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
Store* getStore();

};

#endif
