/**
 * Implements the BST and ADTNode classes.
 */

#include "BST.h"

template <class Type> ADTNode<Type>::ADTNode(Type t) {
  data = t;
  right = nullptr;
  left = nullptr;
  next = nullptr;
}

template <class Type> void ADTNode<Type>::setData(Type d) { data = d; }

template <class Type> Type ADTNode<Type>::getData() { return data; }

template <class Type> BST<Type>::BST() {
  root = nullptr;
  size = 0;
}

template <class Type> ADTNode<Type> *BST<Type>::getRoot() { return root; }

template <class Type> void BST<Type>::insert(Type data) {
  root = insert(root, data);
}

template <class Type>
ADTNode<Type> *BST<Type>::insert(ADTNode<Type> *subRoot, Type data) {
  ADTNode<Type> *newNode = new ADTNode<Type>(data);
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
ADTNode<Type> *BST<Type>::AVLDelete(ADTNode<Type> *subRoot, Type data,
                                    bool success) {
  if (subRoot == nullptr) {
    success = false;
    return nullptr;
  }
  if (data < subRoot->getData()) {
    int originalHeight = getHeight(root);
    subRoot->left = AVLDelete(subRoot->left, data, success);
    if (originalHeight > getHeight(root))
      subRoot = deleteLeftBalance(subRoot);
  } else if (data > subRoot->getData()) {
    int originalHeight = getHeight(root);
    subRoot->right = AVLDelete(subRoot->right, data, success);
    if (originalHeight > getHeight(root))
      subRoot = deleteRightBalance(subRoot);
  } else {
    ADTNode<Type> *newRoot = subRoot;
    ADTNode<Type> *tempNode = subRoot->left;
    if (subRoot->right == nullptr) {
      success = true;
      return subRoot->left;
    } else if (subRoot->left == nullptr) {
      success = true;
      return subRoot->right;
    } else {
      while (tempNode->right != nullptr)
        tempNode = tempNode->right;
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
ADTNode<Type> *BST<Type>::deleteRightBalance(ADTNode<Type> *subRoot) {
  if (getHeight(subRoot->left) + 1 < getHeight(subRoot->right)) {
    ADTNode<Type> *rightOfRight = subRoot->right;
    if (getHeight(rightOfRight->left) > getHeight(rightOfRight->right) + 1) {
      ADTNode<Type> *leftOfRight = rightOfRight->left;
      subRoot->right = rotateRight(rightOfRight);
      subRoot = rotateLeft(subRoot);
    } else {
      subRoot = rotateLeft(subRoot);
    }
  }
  return subRoot;
}

template <class Type>
ADTNode<Type> *BST<Type>::deleteLeftBalance(ADTNode<Type> *subRoot) {
  if (getHeight(subRoot->right) + 1 < getHeight(subRoot->left)) {
    ADTNode<Type> *leftOfLeft = subRoot->left;
    if (getHeight(leftOfLeft->right) > getHeight(leftOfLeft->left) + 1) {
      ADTNode<Type> *RightOfLeft = leftOfLeft->right;
      subRoot->left = rotateLeft(leftOfLeft);
      subRoot = rotateRight(subRoot);
    } else {
      subRoot = rotateRight(subRoot);
    }
  }
  return subRoot;
}

template <class Type>
ADTNode<Type> *BST<Type>::leftBalance(ADTNode<Type> *subRoot) {
  if (getHeight(subRoot->left->left) > getHeight(subRoot->left->right)) {
    subRoot = rotateRight(subRoot);
  } else {
    subRoot->left = rotateLeft(subRoot->left);
    subRoot = rotateRight(subRoot);
  }
  return subRoot;
}

template <class Type>
ADTNode<Type> *BST<Type>::rightBalance(ADTNode<Type> *subRoot) {
  if (getHeight(subRoot->right->right) > getHeight(subRoot->right->left)) {
    subRoot = rotateLeft(subRoot);
  } else {
    subRoot->right = rotateRight(subRoot->right);
    subRoot = rotateLeft(subRoot);
  }
  return subRoot;
}

template <class Type>
ADTNode<Type> *BST<Type>::rotateLeft(ADTNode<Type> *subRoot) {
  ADTNode<Type> *tempRoot = subRoot->right;
  subRoot->right = subRoot->right->left;
  tempRoot->left = subRoot;
  return tempRoot;
}

template <class Type>
ADTNode<Type> *BST<Type>::rotateRight(ADTNode<Type> *subRoot) {
  ADTNode<Type> *tempRoot = subRoot->left;
  subRoot->left = subRoot->left->right;
  tempRoot->right = subRoot;
  return tempRoot;
}

template <class Type> int BST<Type>::getHeight(ADTNode<Type> *subRoot) {
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

template <class Type> bool BST<Type>::isEmpty() { return !size; }

template class ADTNode<Food>;
template class BST<Food>;
