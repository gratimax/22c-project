/**
 * Implements the BST and BSTNode classes.
 */

#include "BST.h"

template <class Type>
BSTNode<Type>::BSTNode(Type t) {
  data = t;
  right = nullptr;
  left = nullptr;
}

template <class Type>
void BSTNode<Type>::setData(Type d) {
  data = d;
}

template <class Type>
Type BSTNode<Type>::getData() {
  return data;
}

template <class Type>
BST<Type>::BST() {
  root = nullptr;
  size = 0;
}

template <class Type>
BSTNode<Type> *BST<Type>::getRoot() {
  return root;
}

template <class Type>
void BST<Type>::insert(Type data) {
  root = insert(root, data);
}

template <class Type>
BSTNode<Type> *BST<Type>::get(Type data) {
  return get(root, data);
}

template <class Type>
BSTNode<Type> *BST<Type>::insert(BSTNode<Type> *subRoot, Type data) {
  BSTNode<Type> *newNode = new BSTNode<Type>(data);
  if (subRoot == nullptr) {
    subRoot = newNode;
    size++;
    return subRoot;
  }
  if (data < subRoot->getData()) {
    subRoot->left = insert(subRoot->left, data);
    if (getHeight(subRoot->left) > getHeight(subRoot->right) + 1) {
      subRoot = leftBalance(subRoot);
    }
  } else {
    subRoot->right = insert(subRoot->right, data);
    if (getHeight(subRoot->right) > getHeight(subRoot->left) + 1) {
      subRoot = rightBalance(subRoot);
    }
  }
  size++;
  return subRoot;
}

template <class Type>
BSTNode<Type> *BST<Type>::get(BSTNode<Type> *subRoot, Type data){
  std::cout << "subroot is now " << subRoot << "\n";
  if (subRoot == nullptr) {
      return nullptr;
  } else if (subRoot->getData() < data) {
    std::cout << "navigates left\n";
    return get(subRoot->left, data);
  } else if (subRoot->getData() > data) {
    std::cout << "navigates right\n";
    return get(subRoot->right, data);
  } else {
    std::cout << "we got here yay\n";
    return subRoot;
  }
}

template <class Type>
BSTNode<Type> *BST<Type>::AVLDelete(BSTNode<Type> *subRoot, Type data,
                                    bool success) {
  if (subRoot == nullptr) {
    success = false;
    return nullptr;
  }
  if (data < subRoot->getData()) {
    int originalHeight = getHeight(root);
    subRoot->left = AVLDelete(subRoot->left, data, success);
    if (originalHeight > getHeight(root)) subRoot = deleteLeftBalance(subRoot);
  } else if (data > subRoot->getData()) {
    int originalHeight = getHeight(root);
    subRoot->right = AVLDelete(subRoot->right, data, success);
    if (originalHeight > getHeight(root)) subRoot = deleteRightBalance(subRoot);
  } else {
    BSTNode<Type> *newRoot = subRoot;
    BSTNode<Type> *tempNode = subRoot->left;
    if (subRoot->right == nullptr) {
      success = true;
      return subRoot->left;
    } else if (subRoot->left == nullptr) {
      success = true;
      return subRoot->right;
    } else {
      while (tempNode->right != nullptr) tempNode = tempNode->right;
      Type largest = tempNode->getData();
      subRoot->setData(largest);
      int originalHeight = getHeight(root);
      subRoot->left = AVLDelete(subRoot->left, largest, success);
      if (originalHeight > getHeight(root))
        subRoot = deleteRightBalance(subRoot);
    }
  }
  return subRoot;
}

template <class Type>
BSTNode<Type> *BST<Type>::deleteRightBalance(BSTNode<Type> *subRoot) {
  if (getHeight(subRoot->left) + 1 < getHeight(subRoot->right)) {
    BSTNode<Type> *rightOfRight = subRoot->right;
    if (getHeight(rightOfRight->left) > getHeight(rightOfRight->right) + 1) {
      BSTNode<Type> *leftOfRight = rightOfRight->left;
      subRoot->right = rotateRight(rightOfRight);
      subRoot = rotateLeft(subRoot);
    } else {
      subRoot = rotateLeft(subRoot);
    }
  }
  return subRoot;
}

template <class Type>
BSTNode<Type> *BST<Type>::deleteLeftBalance(BSTNode<Type> *subRoot) {
  if (getHeight(subRoot->right) + 1 < getHeight(subRoot->left)) {
    BSTNode<Type> *leftOfLeft = subRoot->left;
    if (getHeight(leftOfLeft->right) > getHeight(leftOfLeft->left) + 1) {
      BSTNode<Type> *RightOfLeft = leftOfLeft->right;
      subRoot->left = rotateLeft(leftOfLeft);
      subRoot = rotateRight(subRoot);
    } else {
      subRoot = rotateRight(subRoot);
    }
  }
  return subRoot;
}

template <class Type>
BSTNode<Type> *BST<Type>::leftBalance(BSTNode<Type> *subRoot) {
  if (getHeight(subRoot->left->left) > getHeight(subRoot->left->right)) {
    subRoot = rotateRight(subRoot);
  } else {
    subRoot->left = rotateLeft(subRoot->left);
    subRoot = rotateRight(subRoot);
  }
  return subRoot;
}

template <class Type>
BSTNode<Type> *BST<Type>::rightBalance(BSTNode<Type> *subRoot) {
  if (getHeight(subRoot->right->right) > getHeight(subRoot->right->left)) {
    subRoot = rotateLeft(subRoot);
  } else {
    subRoot->right = rotateRight(subRoot->right);
    subRoot = rotateLeft(subRoot);
  }
  return subRoot;
}

template <class Type>
BSTNode<Type> *BST<Type>::rotateLeft(BSTNode<Type> *subRoot) {
  BSTNode<Type> *tempRoot = subRoot->right;
  subRoot->right = subRoot->right->left;
  tempRoot->left = subRoot;
  return tempRoot;
}

template <class Type>
BSTNode<Type> *BST<Type>::rotateRight(BSTNode<Type> *subRoot) {
  BSTNode<Type> *tempRoot = subRoot->left;
  subRoot->left = subRoot->left->right;
  tempRoot->right = subRoot;
  return tempRoot;
}

template <class Type>
int BST<Type>::getHeight(BSTNode<Type> *subRoot) {
  if (subRoot == nullptr) {
    return 0;
  }
  if (subRoot->left == nullptr && subRoot->right == nullptr) {
    return 1;
  }
  if (subRoot->left == nullptr) {
    return (1 + getHeight(subRoot->right));
  }
  if (subRoot->right == nullptr) {
    return (1 + getHeight(subRoot->left));
  }
  int r = getHeight(subRoot->right);
  int l = getHeight(subRoot->left);
  if (r > l) {
    return r + 1;
  }
  return l + 1;
}

template <class Type>
bool BST<Type>::isEmpty() {
  return !size;
}

template <class Type>
vector<Type> *BST<Type>::getSorted(BSTNode<Type> *subRoot){
  vector<Type> *v = new vector<Type>;
  if (subRoot->left != nullptr) {
    vector<Type> *leftVector = getSorted(subRoot->left);
    for (int i = 0; i < leftVector->size(); i++) {
      v->push_back(leftVector->operator[](i));
    }
    delete leftVector;
  }
  v->push_back(subRoot->getData());
  if (subRoot->right != nullptr) {
    vector<Type> *rightVector = getSorted(subRoot->right);
    for (int i = 0; i < rightVector->size(); i++) {
      v->push_back(rightVector->operator[](i));
    }
    delete rightVector;
  }
  return v;
}

template class BSTNode<Food>;
template class BST<Food>;
