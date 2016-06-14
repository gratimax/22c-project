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

void ending(bool hadError) {
  cout << "Thanks for using Fruitlog! ";
  if (hadError) {
    cout << "Sorry for the error! ";
  }
  cout << "Bye now!\n";
}

int main() {
  Store *store = new Store("food.txt");
  UI *ui = new UI(store);
  try {
    store->initializeFoods();
    cout << store->numFoods() << " foods loaded" << std::endl;
    ui->mainScreen(true);
    store->saveFoods();
    cout << store->numFoods() << " foods saved" << std::endl;
    ending(false);
    return 0;
  } catch (const char *err) {
    cerr << err << std::endl;
    ending(true);
    delete ui;
    delete store;
    return 1;
  }
}
