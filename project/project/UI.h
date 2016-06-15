/**
 * Defines the UI class.
 */

#ifndef __UI_H
#define __UI_H

#include "Food.h"
#include "Store.h"

class UI {
  Store *store;

 public:
  UI(Store *store);

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

  FileIO *getFileIO();
  Store *getStore();
};

#endif
