#ifndef BST_H
#define BST_H

#include "ADTNode.h"
#include<iostream>
#include<fstream>
#include<string>

template <class Type>
class BST{
private:
	ADTNode<Type>* root;
	int size;
public:
	BST(){
		root = nullptr;
		size = 0;
	}
    ADTNode<Type>* getRoot(){return root;};
    void insert(Type data){
        root = insert(root, data);
    }
	/**
	Use recursion to insert a node into an AVL tree
	@Pre: 	root is pointer to first node in AVL tree/subtree
	@pre:	newData is pointer to new node to be inserted
	@post:	new node has been inserted
	@return:	root returned recursively up the tree
	*/
	ADTNode<Type>* insert(ADTNode<Type>* subRoot, Type data){
        ADTNode<Type>* newNode = new ADTNode<Type>(data);
		if (subRoot == nullptr){
			subRoot = newNode;
			size++;
			return subRoot;
		} if (data < subRoot->getData()){
			subRoot->left = insert(subRoot->left, data);
			if (getHeight(subRoot->left) > getHeight(subRoot->right) + 1){
                subRoot = leftBalance(subRoot);
			}
		}
		else {
			subRoot->right = insert(subRoot->right, data);
			if (getHeight(subRoot->right) > getHeight(subRoot->left) + 1){
                subRoot = rightBalance(subRoot);
			}
		}
		size++;
		return subRoot;
	}

	/**
	This algorithm deletes a node from an AVL tree and rebalances if necessary
	@Pre:	root is a pointer to a [sub]tree
			data is the key of node to be deleted
			success is a reference to a boolean variable
	@Post:	node deleted if found, tree unchanged if not.
			success set true or false
	@return:	pointer to root of [potential] new subtree
	*/
	ADTNode<Type>* AVLDelete(ADTNode<Type>* subRoot, Type data, bool success){
		if (subRoot == nullptr){
			success = false;
			return nullptr;
		}
		if (data < subRoot->getData()){
			int originalHeight = getHeight(root);
			subRoot->left = AVLDelete(subRoot->left, data, success);
			if (originalHeight > getHeight(root))
				subRoot = deleteLeftBalance(subRoot);
		}
		else if (data > subRoot->getData()) {
			int originalHeight = getHeight(root);
			subRoot->right = AVLDelete(subRoot->right, data, success);
			if (originalHeight > getHeight(root))
				subRoot = deleteRightBalance(subRoot);
		}
		else {
			ADTNode<Type>* newRoot = subRoot;
			ADTNode<Type>* tempNode = subRoot->left;
			if (subRoot->right == nullptr){
				success = true;
				return subRoot->left;
			}
			else if (subRoot->left == nullptr){
				success = true;
				return subRoot->right;
			}
			else {
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

	/**
	The [sub]tree is shorter after a deletion on the left branch.
	If necessary, balance the tree by rotating.
	@Pre:	tree is shorter
	@post	balance restored
	@return:	new root
	*/
	ADTNode<Type>* deleteRightBalance(ADTNode<Type>* subRoot){
		if (getHeight(subRoot->left) + 1 < getHeight(subRoot->right)){
			ADTNode<Type>* rightOfRight = subRoot->right;
			if (getHeight(rightOfRight->left) > getHeight(rightOfRight->right) + 1){
				ADTNode<Type>* leftOfRight = rightOfRight->left;
				subRoot->right = rotateRight(rightOfRight);
				subRoot = rotateLeft(subRoot);
			}
			else {
				subRoot = rotateLeft(subRoot);
			}
		}
		return subRoot;
	}

	/**
	The [sub]tree is shorter after a deletion on the right branch.
	If necessary, balance the tree by rotating.
	@Pre:	tree is shorter
	@post	balance restored
	@return:	new root
	*/
	ADTNode<Type>* deleteLeftBalance(ADTNode<Type>* subRoot){
		if (getHeight(subRoot->right) + 1 < getHeight(subRoot->left)){
			ADTNode<Type>* leftOfLeft = subRoot->left;
			if (getHeight(leftOfLeft->right) > getHeight(leftOfLeft->left) + 1){
				ADTNode<Type>* RightOfLeft = leftOfLeft->right;
				subRoot->left = rotateLeft(leftOfLeft);
				subRoot = rotateRight(subRoot);
			}
			else {
				subRoot = rotateRight(subRoot);
			}
		}
		return subRoot;
	}

	/**
	This algorithm is entered when the root is left high(the left subtree is higher than the right subtree).
	@pre:	root is a pointer to the root of the subtree
	@post:	root has been updated (if necessary)
	*/
	ADTNode<Type>* leftBalance(ADTNode<Type>* subRoot){
		if (getHeight(subRoot->left->left) > getHeight(subRoot->left->right)){
			subRoot = rotateRight(subRoot);
		} else {
			subRoot->left = rotateLeft(subRoot->left);
			subRoot = rotateRight(subRoot);
		}
		return subRoot;
	}

	/**
	This algorithm is entered when the root is right high(the right subtree is higher than the left subtree).
	@pre:	root is a pointer to the root of the subtree
	@post:	root has been updated (if necessary)
	*/
	ADTNode<Type>* rightBalance(ADTNode<Type>* subRoot){
		if (getHeight(subRoot->right->right) > getHeight(subRoot->right->left)){
			subRoot = rotateLeft(subRoot);
		}
		else {
			subRoot->right = rotateRight(subRoot->right);
			subRoot = rotateLeft(subRoot);
		}
		return subRoot;
	}
	/**
	This algorithm exchanges pointers to rotate the tree right
	@pre:	root points to tree to be rotated
	@post:	node rotated and root updated
	*/
	ADTNode<Type>* rotateLeft(ADTNode<Type>* subRoot){
		ADTNode<Type>* tempRoot = subRoot->right;
		subRoot->right = subRoot->right->left;
        tempRoot->left = subRoot;
        return tempRoot;
	}

	/**
	This algorithm exchanges pointers to rotate the tree left
	@pre:	root points to tree to be rotated
	@post:	node rotated and root updated
	*/
	ADTNode<Type>* rotateRight(ADTNode<Type>* subRoot){
		ADTNode<Type>* tempRoot = subRoot->left;
		subRoot->left = subRoot->left->right;
        tempRoot->right = subRoot;
		return tempRoot;
	}

	int getHeight(ADTNode<Type>* subRoot){
        if (subRoot == nullptr){
            return 0;
        }
		if (subRoot->left == nullptr && subRoot->right == nullptr){
			return 1;
		}
		if (subRoot->left == nullptr){
			return (1 + getHeight(subRoot->right));
		}
		if (subRoot->right == nullptr){
			return (1 + getHeight(subRoot->left));
		}
		int r = getHeight(subRoot->right);
		int l = getHeight(subRoot->left);
		if (r > l){
			return r + 1;
		}
		return l + 1;
	}

	/**
	This algorithm will put all data on the file in order requested
	@Pre:	outFile exists and is able to be opened
		mode is set to 1 (pre-order), 2 (in-order), 3 (post-order), 4 (breadth-first)
		fileName is the correct name of the file to be opened
	*/
	void writeToFile(int mode, ofstream& outFile, string fileName){
		if (mode == 1){
			preOrderDisplay(root, outFile, fileName);
		} else if (mode == 2){
			inOrderDisplay(root, outFile, fileName);
		} else if (mode == 3){
			postOrderDisplay(root, outFile, fileName);
		} else if (mode == 4){
			breadthFirstDisplay(root, outFile, fileName);
		}
	}

	void preOrderDisplay(ADTNode<Type>* subRoot, ofstream& outFile, string fileName){
        if (subRoot != nullptr){
            outFile.open(fileName);
            outFile << subRoot->getData();
            outFile.close();
            preOrderDisplay(subRoot->left, outFile, fileName);
            preOrderDisplay(subRoot->right, outFile, fileName);
        }
	}
	
	void inOrderDisplay(ADTNode<Type>* subRoot, ofstream& outFile, string fileName){
		if (subRoot != nullptr){
            inOrderDisplay(subRoot->left, outFile, fileName);
            outFile.open(fileName);
            outFile << subRoot->getData();
            outFile.close();
            inOrderDisplay(subRoot->right, outFile, fileName);
        }
    }
	
	void postOrderDisplay(ADTNode<Type>* subRoot, ofstream& outFile, string fileName){
        if (subRoot != nullptr){
            postOrderDisplay(subRoot->left, outFile, fileName);
            postOrderDisplay(subRoot->right, outFile, fileName);
            outFile.open(fileName);
            outFile << subRoot->getData();
            outFile.close();

        }
    }
	
	void breadthFirstDisplay(ADTNode<Type>* subRoot, ofstream& outFile, string fileName){
		ADTNode<Type>* currentNode = subRoot;
		ADTNode<Type>** queue = new ADTNode<Type>*[size];
		int enqueue = 0;
		int dequeue = 0;
		while(currentNode != nullptr){
            outFile.open(fileName);
            outFile << currentNode->getData();
            outFile.close();
			if (currentNode->left != nullptr){
				queue[enqueue] = currentNode->left;
				enqueue++;
			} if (currentNode->right != nullptr){
				queue[enqueue] = currentNode->right;
				enqueue++;
			} if (dequeue != enqueue){
				currentNode = queue[dequeue];
				dequeue++;
			} else {
				currentNode = nullptr;
			}
		}
		delete queue;
	}
	bool isEmpty(){
		return !size;
	}

};


#endif // !BST_H
