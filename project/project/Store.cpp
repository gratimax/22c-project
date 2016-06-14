/**
 * Implements the Store class.
 */

#include "Store.h"
#include "BST.h"
#include "FileIO.h"
#include "HashTable.h"

Store::Store(string filename) { this->fileIO = new FileIO; }

Store::~Store() { delete this->fileIO; }
