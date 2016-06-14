/**
 * Implements the Store class.
 */

#include "Store.h"
#include "BST.h"
#include "FileIO.h"
#include "HashTable.h"

Store::Store(string filename) {
  this->fileIO = new FileIO;
  this->bst = new BST<Food>;
}

Store::~Store() {
  delete this->fileIO;
  delete this->bst;
}
