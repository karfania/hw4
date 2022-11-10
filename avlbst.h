#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor and setting
* the color to red since every new node will be red when it is first inserted.
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
		void insertFix(AVLNode<Key, Value>* parent, AVLNode<Key, Value>* child);
		void removeFix(AVLNode<Key, Value>* n, int8_t diff);
		void rightRotate(AVLNode<Key, Value>* n1); // to make rotation calls more streamlined
		void leftRotate(AVLNode<Key, Value>* n1); // to make rotation calls more streamlined
 
};


/*
 * Helper function to implement
 * a right rotation on a node
 */
template<class Key, class Value>
void AVLTree<Key, Value>::rightRotate(AVLNode<Key, Value>* z)
{

	// Get the direct child of the node causing the imbalance (y)
	// and the node acting as the root of the subtree that 
	// needs to change parents (switchedTree)
	AVLNode<Key,Value>* y = z -> getLeft();
	AVLNode<Key, Value>* switchedTree = y -> getRight();

	// y is the new root of the subtree, where it's original parent 
	// is now to the right of it
	if (this -> root_ == z)
	{
		this -> root_ = y;
		y -> setParent(nullptr);
	}

	// Connecting the parent of z to y
	else
	{
		y -> setParent(z -> getParent());
		if (z -> getParent() -> getLeft() == z)
		{
			z -> getParent() -> setLeft(y);
		}
		else if (z -> getParent() -> getRight() == z)
		{
			z -> getParent() -> setRight(y);
		}
		
	}

	// Disconnect z's connections
	z -> setParent(y);
	y -> setRight(z);

	// swap the node that was to the right of the new root to be the left
	// child of the old parent 
	z -> setLeft(switchedTree);
	if (switchedTree != nullptr)
	{
		switchedTree -> setParent(z);
	}
}

/*
 * Helper function to implement
 * a left rotation on a node
 */
template<class Key, class Value>
void AVLTree<Key, Value>::leftRotate(AVLNode<Key, Value>* z)
{

	// Get the direct child of the node causing the imbalance (y)
	// and the node acting as the root of the subtree that 
	// needs to change parents (switchedTree)
	AVLNode<Key,Value>* y = z -> getRight();
	AVLNode<Key, Value>* switchedTree = y -> getLeft();

	// y is the new root of the subtree, where it's original parent 
	// is now to the left of it
	if (this -> root_ == z)
	{
		this -> root_ = y;
		y -> setParent(nullptr);
	}

	// Connecting the parent of z to y
	else
	{
		y -> setParent(z -> getParent());
		if (z -> getParent() -> getLeft() == z)
		{
			z -> getParent() -> setLeft(y);
		}
		else if (z -> getParent() -> getRight() == z)
		{
			z -> getParent() -> setRight(y);
		}
	}

	// Disconnect z's connections
	z -> setParent(y);
	y -> setLeft(z);

	// swap the node that was to the left of the new root to be the right
	// child of the old parent 
	z -> setRight(switchedTree);
	if (switchedTree != nullptr)
	{
		switchedTree -> setParent(z);
	}
}

/*
 * Helper function to balance and rotate tree
 * upon an insertion that causes imbalance
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insertFix(AVLNode<Key, Value>* parent, AVLNode<Key, Value>* child)
{
	// Base cases
	if (parent == nullptr || parent == this -> root_)
	{
		return;
	}

	// If not, then update balances and check if a rotation is necessary
	AVLNode<Key, Value>* grandParent = parent -> getParent();

	// If parent is a left node of grandParent, update balance by -1
	if (grandParent -> getLeft() == parent)
	{
		grandParent -> updateBalance(-1);

		// If we are balanced after the insertion, you're done
		if (grandParent -> getBalance() == 0)
		{
			return;
		}

		// Recurse up to check for higher-level imbalance
		else if (grandParent -> getBalance() == -1)
		{
			insertFix(grandParent, parent);
		} 

		// If we are imbalanced at grandParent, check which type
		// of imabalance and do proper rotation(s) to fix
		else if (grandParent -> getBalance() == -2)
		{
			// Zig-zig scenario
			if (parent -> getLeft() == child)
			{
				// Fixing balances
				grandParent -> setBalance(0);
				parent -> setBalance(0);
				
				// Single rotation in the opposite direction
				rightRotate(grandParent);
			}

			// Zig-zag scenario
			else if (parent -> getRight() == child)
			{
				// Updating the balances
				if (child -> getBalance() == -1)
				{
					parent -> setBalance(0);
					grandParent -> setBalance(1);
					child -> setBalance(0);
				}
				else if (child -> getBalance() == 0)
				{
					parent -> setBalance(0);
					grandParent -> setBalance(0);
				}
				else if (child -> getBalance() == 1)
				{
					parent -> setBalance(-1);
					grandParent -> setBalance(0);
					child -> setBalance(0);
				}

				// Executing rotations
				leftRotate(parent);
				rightRotate(grandParent);
			}

			// Once we fix the balance, we are done
			return;
		}
	}

	// If parent is a right node of grandParent, update balance by +1
	else if (grandParent -> getRight() == parent)
	{
		grandParent -> updateBalance(+1);

		// If we are balanced after the insertion, you're done
		if (grandParent -> getBalance() == 0)
		{
			return;
		}

		// Recurse up to check for higher-level imbalance
		else if (grandParent -> getBalance() == 1)
		{
			insertFix(grandParent, parent);
		} 

		// If we are imbalanced at grandParent, check which type
		// of imabalance and do proper rotation(s) to fix
		else if (grandParent -> getBalance() == 2)
		{
			// Zig-zig scenario
			if (parent -> getRight() == child)
			{
				// Fixing balances
				grandParent -> setBalance(0);
				parent -> setBalance(0);
				
				// Single rotation in the opposite direction
				leftRotate(grandParent);
			}

			// Zig-zag scenario
			else if (parent -> getLeft() == child)
			{
				// Updating the balances
				if (child -> getBalance() == 1)
				{
					parent -> setBalance(0);
					grandParent -> setBalance(-1);
					child -> setBalance(0);
				}
				else if (child -> getBalance() == 0)
				{
					parent -> setBalance(0);
					grandParent -> setBalance(0);
				}
				else if (child -> getBalance() == -1)
				{
					parent -> setBalance(1);
					grandParent -> setBalance(0);
					child -> setBalance(0);
				}

				// Executing rotations
				rightRotate(parent);
				leftRotate(grandParent);				
			}
			// Once we fix the balance, we are done
			return;
		}
	}
}


/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
  // Same basic code as BST insert function

	// If the tree is empty, set root equal to the new node
	if (this -> root_ == nullptr)
	{
		AVLNode<Key, Value>* newNode = new AVLNode<Key,Value>(new_item.first, new_item.second, nullptr);
		this -> root_ = newNode;
		return;
	}

	
	// Check if the node exists
	AVLNode<Key, Value>* search = static_cast<AVLNode<Key, Value>*> (this -> internalFind(new_item.first));

	// If the node exists, just update its value
	if (search != nullptr)
	{
		search -> setValue(new_item.second);
		return;
	}

	// Else, create a new node and update pointers
	else
	{
		AVLNode<Key, Value>* newNode = new AVLNode<Key,Value>(new_item.first, new_item.second, nullptr);
		AVLNode<Key, Value>* parent = static_cast<AVLNode<Key, Value>*>(this -> root_);
		//parent -> setBalance(0);
		//int8_t parentBalance = parent -> getBalance();

		while (parent != nullptr)
		{
			// If the new node's value is less than it's parent/current node, 
			// traverse left
			if (newNode -> getKey() < parent -> getKey())
			{
				// If there's no node to the left, then set the new left to be the inserted node
				if (parent -> getLeft() == nullptr)
				{
					parent -> setLeft(newNode);
					newNode -> setParent(parent);
					break;
				} 

				// If not, keep iterating
				else
				{
					parent = parent -> getLeft();
				}
				
			}
			else
			{
				// If there's no node to the right, then set the new right to be the inserted node
				if (parent -> getRight() == nullptr)
				{
					parent -> setRight(newNode);
					newNode -> setParent(parent);
					break;
				}

				// If not, keep iterating
				else
				{
					parent = parent -> getRight();
				}
			}
		}
	
		// After insertion, call insertFix if necessary
		if (parent -> getBalance() == -1 || parent -> getBalance() == 1)
		{
			parent -> setBalance(0);
		}

		else if (parent -> getBalance() == 0)
		{
			if (parent -> getLeft() == newNode)
			{
				parent -> updateBalance(-1);
			}
			else if (parent -> getRight() == newNode)
			{
				parent -> updateBalance(+1);
			}
			insertFix(parent, newNode);
		}	
	}
}

/*
 * Helper function to balance and rotate tree
 * upon a deletion that causes imbalance
 */
 template<class Key, class Value>
 void AVLTree<Key, Value>::removeFix(AVLNode<Key, Value>* n, int8_t diff)
 {
	 // If the tree is empty, nothing to fix
	  if (n == nullptr)
	  {
		  return;
	  }

	 int8_t ndiff;

	 AVLNode<Key, Value>* p = n -> getParent();
	 AVLNode<Key, Value>* c;
	 AVLNode<Key, Value>* g;
	 ndiff = -1;
	 if (p != nullptr)
	 {
		 // If n is a left child to the parent
		 if (p -> getLeft() == n)
		 {
			 ndiff = 1;
		 }
	 }

	 // WHEN DIFF == -1
	 
	 if (diff == -1)
	 {
		 // Case 1
		if (n -> getBalance() + diff == -2)
		{
				c = n -> getLeft();

			// Case 1(a): zig-zig
			if (c -> getBalance() == -1)
			{
				// Rotate n
				rightRotate(n);

				// Update balance
				n -> setBalance(0);
				c -> setBalance(0);

				// Make recursive call
				removeFix(p, ndiff);
			}

			// Case 1(b): zig-zig case
			else if (c -> getBalance() == 0)
			{
				// Rotate n
				rightRotate(n);
				n -> setBalance(-1);
				c -> setBalance(1);
				return;
			}

			// Case 1(c): zig-zag case
			else if (c -> getBalance() == 1)
			{
				// Get the grandchild of n
				g = c -> getRight();
				
				// Do rotations
				leftRotate(c);
				rightRotate(n);

				// Update balance factors
				if (g -> getBalance() == 1)
				{
					n -> setBalance(0);
					c -> setBalance(-1);
					g -> setBalance(0);
				}
				else if (g -> getBalance() == 0)
				{
					n -> setBalance(0);
					c -> setBalance(0);
					g -> setBalance(0);
				}
				else if (g -> getBalance() == -1)
				{
					n -> setBalance(1);
					c -> setBalance(0);
					g -> setBalance(0);
				}

				// Recursive call after changes/updates
				removeFix(p, ndiff);
			}
		}

		// Case 2
		else if (n -> getBalance() + diff == -1)
		{
			n -> setBalance(-1);
			return;
		}

		// Case 3
		else if (n -> getBalance() + diff == 0)
		{
			n -> setBalance(0);
			removeFix(p, ndiff);
		}
	 }

	// WHEN DIFF == 1
	 else if (diff == 1)
	 {

		// Case 1
		if (n -> getBalance() + diff == 2)
		{
				c = n -> getRight();

			// Case 1(a): zig-zig
			if (c -> getBalance() == 1)
			{
				// Rotate n
				leftRotate(n);

				// Update balance
				n -> setBalance(0);
				c -> setBalance(0);

				// Make recursive call
				removeFix(p, ndiff);
			}

			// Case 1(b): zig-zig case
			else if (c -> getBalance() == 0)
			{
				// Rotate n
				leftRotate(n);
				n -> setBalance(1);
				c -> setBalance(-1);
				return;
			}

			// Case 1(c): zig-zag case
			else if (c -> getBalance() == -1)
			{
				// Get the grandchild of n
				g = c -> getLeft();
				
				// Do rotations
				rightRotate(c);
				leftRotate(n);

				// Update balance factors
				if (g -> getBalance() == -1)
				{
					n -> setBalance(0);
					c -> setBalance(1);
					g -> setBalance(0);
				}
				else if (g -> getBalance() == 0)
				{
					n -> setBalance(0);
					c -> setBalance(0);
				}
				else if (g -> getBalance() == 1)
				{
					n -> setBalance(-1);
					c -> setBalance(0);
					g -> setBalance(0);
				}

				// Recursive call after changes/updates
				removeFix(p, ndiff);
			}
		}

		// Case 2
		else if (n -> getBalance() + diff == 1)
		{
			n -> setBalance(1);
			return;
		}

		// Case 3
		else if (n -> getBalance() + diff == 0)
		{
			n -> setBalance(0);
			removeFix(p, ndiff);
		}
	}
 }

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{

	// Same basic code as BST remove function

  // Base-Case: tree is empty
	if (this -> root_ == nullptr)
	{
		return;
	}

	// Base-Case: there is only one node
	if (this ->root_ -> getKey() == key && this -> root_ -> getLeft() == nullptr && this -> root_ -> getRight() == nullptr)
	{
		delete this -> root_;
		this -> root_ = nullptr;
		return;
	}

	AVLNode<Key, Value>* toRemove = static_cast<AVLNode<Key, Value>* > (this -> internalFind(key));
	int8_t diff;
	// If the node doesn't exist in the tree, do nothing
	if (toRemove == nullptr)
	{
		return;
	}

	// If the node does exist, go through the child cases
	else
	{
		// If there are two children, swap since the zero child and one child processes are the
		// same after the nodeSwap
		if (toRemove -> getLeft() != nullptr && toRemove -> getRight() != nullptr)
		{
			AVLNode<Key, Value>* pred = static_cast<AVLNode<Key, Value>* > (this ->predecessor(toRemove));
			nodeSwap(toRemove, pred);
		}

		AVLNode<Key, Value>* parent = toRemove -> getParent();

		// 0 CHILD Case
		if (toRemove -> getLeft() == nullptr && toRemove -> getRight() == nullptr)
		{
			// If we are at the root, then set the new root to be nullptr
			if (parent == nullptr)
			{
				this -> root_ = nullptr;
				//return;
			}

			// If not, find out if it is its parent's left or right child
			else
			{
				// If the node we want to remove is the parent's left child:
				if (parent -> getLeft() == toRemove)
				{
					parent -> setLeft(nullptr);
					//delete toRemove;
					diff = 1;
				}

				// If the node we want to remove is the parent's right child
				else
				{
					parent -> setRight(nullptr);
					//delete toRemove;
					diff = -1;
				}
			}
		}

		// ONE CHILD CASES
		// If the one child is the left child
		else if (toRemove -> getLeft() != nullptr && toRemove -> getRight() == nullptr)
		{
			AVLNode<Key, Value>* lChild = toRemove -> getLeft();
			// If we are at the root, then set the new root to be the left child
			if (parent == nullptr)
			{
				lChild -> setParent(nullptr);
				//delete toRemove;
				this -> root_ = lChild;
				//return;
			}

			// If we are not at the root, then set the parent's next to be the left child
			// Set the left child's parent to be toRemove's parent, and delete toRemove
			else
			{

				// If we are removing the parent's left node, update parent's left pointers
				if (parent -> getLeft() == toRemove)
				{
					parent -> setLeft(lChild);
					lChild -> setParent(parent);
					//delete toRemove;
					diff = 1;
				}

				// If we are removing the parent's right node, update parent's right pointers
				else
				{
					parent -> setRight(lChild);
					lChild -> setParent(parent);
					//delete toRemove;
					diff = -1;
				}
			}
		}

		// If the one child is the right child
		else if (toRemove -> getLeft() == nullptr && toRemove -> getRight() != nullptr)
		{
			AVLNode<Key, Value>* rChild = toRemove -> getRight();

			// If we are at the root, then set the new root to be the right children
			if (parent == nullptr)
			{
				rChild -> setParent(nullptr);
				//delete this-> root_;
				this -> root_ = rChild;
				//return;
			}

			// If we are not at the root, then set the parent's next to be the right child
			// Set the right child's parent to be toRemove's parent, and delete toRemove
			else
			{
				// If we are removing the parent's left node, update parent's left pointers
				if (parent -> getLeft() == toRemove)
				{
					parent -> setLeft(rChild);
					rChild -> setParent(parent);
					//delete toRemove;
					diff = 1;
				}

				// If we are removing the parent's right node, update parent's right pointers
				else
				{
					parent -> setRight(rChild);
					rChild -> setParent(parent);
					//delete toRemove;
					diff = -1;
				}
			}
		}
		delete toRemove;
		removeFix(parent, diff);
	}
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
