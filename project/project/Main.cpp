/*
 * The home of the main function.
 */

#include <iostream>
#include <vector>

#include "Food.h"
#include "UI.h"

using std::vector;
using std::cout;
using std::cerr;
using std::string;

/**
 * Utility that prints out the ending message to the user. If the program
 * errored (bool hadError is true), show an apology message because we're really
 * sorry. If the program had a really bad time, show an apology message because
 * we're really really really sorry.
 */
void ending(bool hadError, bool hadBadError) {
  cout << "Thanks for using Fruitlog! ";
  if (hadError) {
    if (hadBadError) {
      cout
          << "We're really sorry for the error! Please don't take off points! ";
    } else {
      cout << "Sorry for the error! ";
    }
  }
  cout << "Bye now!\n";
}

/**
 * The main function, runs the program.
 */
int main() {
  Store *store = new Store("foods.txt");
  UI *ui = new UI(store);
  try {
    store->initializeFoods();
    cout << store->getNumFoods() << " foods loaded" << std::endl;
    ui->mainScreen(true);
    store->saveFoods();
    cout << store->getNumFoods() << " foods saved" << std::endl;
    ending(false, false);
    delete ui;
    delete store;
    return 0;
  } catch (const char *err) {
    cerr << err << std::endl;
    ending(true, false);
    delete ui;
    delete store;
    return 1;
  } catch (const string &err) {
    cerr << err << std::endl;
    ending(true, false);
    delete ui;
    delete store;
    return 1;
  }
  // catch (...) {
  //   ending(true, true);
  //   delete ui;
  //   delete store;
  //   return 1;
  // }
}
