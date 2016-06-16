/**
 * Defines the UI class.
 * By MOKT (Max Ovsiankin, Ori Klein, Keivan Safavi, Tomer Erlich)
 */

#ifndef __UI_H
#define __UI_H

#include "Food.h"
#include "Store.h"

/**
 * Represents the state of the user interface as presented through the command
 * line to the user.
 */
class UI {
  /**
   * The Store object that holds all the data related to the project model.
   */
  Store *store;

 public:
  /**
   * Constructs a UI object given its store.
   */
  UI(Store *store);

  /**
   * Deconstructs a UI object.
   */
  ~UI();

  /**
   * Returns the human-readable string version of the object.
   */
  string foodToHumanString(Food food);

  /**
   * Shows the main screen (giving possible options) to the user.
   * If the boolean `showWelcome` is true, show a welcome, otherwise just show
   * options.
   */
  void mainScreen(bool showWelcome);

  /**
   * Shows the screen that adds a new recipe or ingredient and prompts the user
   * for its contents.
   */
  void addDataScreen();

  /**
   * Shows the screen that deletes a recipe or ingredient.
   */
  void deleteDataScreen();

  /**
   * Shows the screen that finds a recipe by its ID.
   */
  void findByIdScreen();

  /**
   * Shows the screen that finds a food by possible keywords.
   */
  void searchByNameScreen();

  /**
   * Shows the screen that lists the foods by their sequence in the hash table.
   */
  void listFoodsHashedSequenceScreen();

  /**
   * Shows the screen that lists the foods by their sequence in the binary
   * search tree.
   */
  void listFoodsBSTSequenceScreen();

  /**
   * Shows the screen that prints the binary search tree in indented format.
   */
  void indentedTreeScreen();

  /**
   * Shows the screen that gives the efficiency of the program to the user.
   */
  void printEfficiency();

  /**
   * Shows the screen that generates a recipe for the user.
   */
  void generateRecipeScreen();
};

#endif
