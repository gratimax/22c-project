/**
 * Implements the Store class.
 */

#include "BST.h"
#include "HashTable.h"
#include "Store.h"
#include "FileIO.h"

Store::Store(string filename) {
	this->fileIO = new FileIO;
}

Store::~Store() {
	delete this->fileIO;
}
