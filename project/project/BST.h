/**
 * Defines the BST and ADTNode classes.
 */
#ifndef __BST_H
#define __BST_H

#include <fstream>
#include <iostream>
#include <string>

template <class Type> class ADTNode {
private:
  Type data;

public:
  ADTNode *right;
  ADTNode *left;
  ADTNode *next;
  ADTNode(Type t);
  void setData(Type d);
  Type getData();
};

template <class Type> class BST {
private:
  ADTNode<Type> *root;
  int size;

public:
  BST();
  ADTNode<Type> *getRoot();
  void insert(Type data);
  /**
  Use recursion to insert a node into an AVL tree
  @Pre: 	root is pointer to first node in AVL tree/subtree
  @pre:	newData is pointer to new node to be inserted
  @post:	new node has been inserted
  @return:	root returned recursively up the tree
  */
  ADTNode<Type> *insert(ADTNode<Type> *subRoot, Type data);

  /**
  This algorithm deletes a node from an AVL tree and rebalances if necessary
  @Pre:	root is a pointer to a [sub]tree
                  data is the key of node to be deleted
                  success is a reference to a boolean variable
  @Post:	node deleted if found, tree unchanged if not.
                  success set true or false
  @return:	pointer to root of [potential] new subtree
  */
  ADTNode<Type> *AVLDelete(ADTNode<Type> *subRoot, Type data, bool success);

  /**
  The [sub]tree is shorter after a deletion on the left branch.
  If necessary, balance the tree by rotating.
  @Pre:	tree is shorter
  @post	balance restored
  @return:	new root
  */
  ADTNode<Type> *deleteRightBalance(ADTNode<Type> *subRoot);

  /**
  The [sub]tree is shorter after a deletion on the right branch.
  If necessary, balance the tree by rotating.
  @Pre:	tree is shorter
  @post	balance restored
  @return:	new root
  */
  ADTNode<Type> *deleteLeftBalance(ADTNode<Type> *subRoot);

  /**
  This algorithm is entered when the root is left high(the left subtree is
  higher than the right subtree).
  @pre:	root is a pointer to the root of the subtree
  @post:	root has been updated (if necessary)
  */
  ADTNode<Type> *leftBalance(ADTNode<Type> *subRoot);

  /**
  This algorithm is entered when the root is right high(the right subtree is
  higher than the left subtree).
  @pre:	root is a pointer to the root of the subtree
  @post:	root has been updated (if necessary)
  */
  ADTNode<Type> *rightBalance(ADTNode<Type> *subRoot);

  /**
  This algorithm exchanges pointers to rotate the tree right
  @pre:	root points to tree to be rotated
  @post:	node rotated and root updated
  */
  ADTNode<Type> *rotateLeft(ADTNode<Type> *subRoot);

  /**
  This algorithm exchanges pointers to rotate the tree left
  @pre:	root points to tree to be rotated
  @post:	node rotated and root updated
  */
  ADTNode<Type> *rotateRight(ADTNode<Type> *subRoot);

  int getHeight(ADTNode<Type> *subRoot);

  /**
  This algorithm will put all data on the file in order requested
  @Pre:	outFile exists and is able to be opened
          mode is set to 1 (pre-order), 2 (in-order), 3 (post-order), 4
  (breadth-first)
          fileName is the correct name of the file to be opened
  */
  void writeToFile(int mode, ofstream &outFile, string fileName) {
    outFile.open(fileName);
    if (mode == 1) {
      preOrderDisplay(root, outFile, fileName);
    } else if (mode == 2) {
      inOrderDisplay(root, outFile, fileName);
    } else if (mode == 3) {
      postOrderDisplay(root, outFile, fileName);
    } else if (mode == 4) {
      breadthFirstDisplay(root, outFile, fileName);
    }
    outFile.close();
  }

  void preOrderDisplay(ADTNode<Type> *subRoot, ofstream &outFile,
                       string fileName) {
    if (subRoot != nullptr) {
      outFile << subRoot->getData();
      preOrderDisplay(subRoot->left, outFile, fileName);
      preOrderDisplay(subRoot->right, outFile, fileName);
    }
  }

  void inOrderDisplay(ADTNode<Type> *subRoot, ofstream &outFile,
                      string fileName) {
    if (subRoot != nullptr) {
      inOrderDisplay(subRoot->left, outFile, fileName);
      outFile << subRoot->getData();
      inOrderDisplay(subRoot->right, outFile, fileName);
    }
  }

  void postOrderDisplay(ADTNode<Type> *subRoot, ofstream &outFile,
                        string fileName) {
    if (subRoot != nullptr) {
      postOrderDisplay(subRoot->left, outFile, fileName);
      postOrderDisplay(subRoot->right, outFile, fileName);
      outFile << subRoot->getData();
    }
  }

  void breadthFirstDisplay(ADTNode<Type> *subRoot, ofstream &outFile,
                           string fileName) {
    ADTNode<Type> *currentNode = subRoot;
    ADTNode<Type> **queue = new ADTNode<Type> *[size];
    int enqueue = 0;
    int dequeue = 0;
    while (currentNode != nullptr) {
      outFile << currentNode->getData();
      if (currentNode->left != nullptr) {
        queue[enqueue] = currentNode->left;
        enqueue++;
      }
      if (currentNode->right != nullptr) {
        queue[enqueue] = currentNode->right;
        enqueue++;
      }
      if (dequeue != enqueue) {
        currentNode = queue[dequeue];
        dequeue++;
      } else {
        currentNode = nullptr;
      }
    }
    delete queue;
  }
  bool isEmpty() { return !size; }
};

#endif // !__BST_H
