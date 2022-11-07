#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed by the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;

    template<typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> & tree);
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;
    Value& operator[](const Key& key);
    Value const & operator[](const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here
		void clearHelper(Node<Key, Value>* n); // for clear()
		int calculateHeightIfBalanced(const Node<Key, Value>* n) const; // for isBalanced()
		static Node<Key, Value>* successor(Node<Key, Value>* current);


protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr)
{
    // TODO

    // current_ is the node the iterator is pointing to, so we set current_
    // to the pointer to the node that is passed in by the call to the explicit
    // constructor
    current_ = ptr;
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() 
{
    // TODO

    // current_ is the node the iterator is pointing to, so we set current_
    // to the nullptr since this is the default constructor
    current_ = nullptr;

}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO

    //return (this -> getItem() == rhs -> getItem());
    // check if the node being pointed to is equivalent to the node being 
    // pointed to by the iterator RHS
    return (current_ == rhs.current_);
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    //return (this -> getItem() != rhs ->getItem());
    // check if the node being pointed to is not equivalent to the  
    // node being pointed to by the iterator RHS
    return (current_ != rhs.current_);

}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    // TODO
    
		// simply calling successor on current
		//Node<Key, Value>* succ = successor(current_);
		//return succ;
		// Node<Key, Value> *curr = this -> current_;
		// Node<Key, Value>* successor = successor(curr);
    // BinarySearchTree<Key, Value>::iterator it(successor);
    // return it;
		current_ = successor(current_);
		return *this;

}


/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() 
{
    // TODO
    root_ = nullptr;
    
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    // TODO

    clear();

}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * @precondition The key exists in the map
 * Returns the value associated with the key
 */
template<class Key, class Value>
Value& BinarySearchTree<Key, Value>::operator[](const Key& key)
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}
template<class Key, class Value>
Value const & BinarySearchTree<Key, Value>::operator[](const Key& key) const
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
* Recall: If key is already in the tree, you should 
* overwrite the current value with the updated value.
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
	// TODO

	// If the tree is empty, set root equal to the new node
	if (root_ == nullptr)
	{
		Node<Key, Value>* newNode = new Node<Key,Value>(keyValuePair.first, keyValuePair.second, nullptr);
		root_ = newNode;
		return;
	}

	// Check if the node exists
	Node<Key, Value>* search = internalFind(keyValuePair.first);

	// If the node exists, just update its value
	if (search != nullptr)
	{
		search -> setValue(keyValuePair.second);
		return;
	}

	// Else, create a new node and update pointers
	else
	{
		Node<Key, Value>* newNode = new Node<Key,Value>(keyValuePair.first, keyValuePair.second, nullptr);
		Node<Key, Value>* parent = root_;

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
					return;
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
					return;
				}

				// If not, keep iterating
				else
				{
					parent = parent -> getRight();
				}
			}
		}
	}
}


/**
* A remove method to remove a specific key from a Binary Search Tree.
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
	// Base-Case: tree is empty
	if (root_ == nullptr)
	{
		return;
	}

	// Base-Case: there is only one node
	if (root_ -> getKey() == key && root_ -> getLeft() == nullptr && root_ -> getRight() == nullptr)
	{
		delete root_;
		root_ = nullptr;
		return;
	}

	Node<Key, Value>* toRemove = internalFind(key);
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
			Node<Key, Value>* pred = predecessor(toRemove);
			nodeSwap(toRemove, pred);
		}

		Node<Key, Value>* parent = toRemove -> getParent();

		// 0 CHILD Case
		if (toRemove -> getLeft() == nullptr && toRemove -> getRight() == nullptr)
		{
			// If we are at the root, then set the new root to be nullptr
			if (toRemove == root_ || parent == nullptr)
			{
				root_ = nullptr;
				return;
			}

			// If not, find out if it is its parent's left or right child
			else
			{
				// If the node we want to remove is the parent's left child:
				if (parent -> getLeft() == toRemove)
				{
					parent -> setLeft(nullptr);
					//toRemove -> setParent(nullptr);
					delete toRemove;
					return;
				}

				// If the node we want to remove is the parent's right child
				else
				{
					parent -> setRight(nullptr);
					//toRemove -> setParent(nullptr);
					delete toRemove;
					return;
				}
			}
		}

		// ONE CHILD CASES
		// If the one child is the left child
		else if (toRemove -> getLeft() != nullptr && toRemove -> getRight() == nullptr)
		{
			Node<Key, Value>* lChild = toRemove -> getLeft();
			// If we are at the root, then set the new root to be the left child
			if (toRemove == root_ || parent == nullptr)
			{
				//root_ -> setLeft(nullptr);
				lChild -> setParent(nullptr);
				//delete root_;
				delete toRemove;
				//toRemove -> setParent(nullptr);
				root_ = lChild;
				return;
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
					//toRemove -> setParent(nullptr);
					//toRemove -> setLeft(nullptr);
					delete toRemove;
					return;
				}

				// If we are removing the parent's right node, update parent's right pointers
				else
				{
					parent -> setRight(lChild);
					lChild -> setParent(parent);
					//toRemove -> setParent(nullptr);
					//toRemove -> setLeft(nullptr);
					delete toRemove;
					return;
				}
			}
		}

		// If the one child is the right child
		else if (toRemove -> getLeft() == nullptr && toRemove -> getRight() != nullptr)
		{
			Node<Key, Value>* rChild = toRemove -> getRight();

			// If we are at the root, then set the new root to be the right children
			if (toRemove == root_ || parent == nullptr)
			{
				//root_ -> setRight(nullptr);
				rChild -> setParent(nullptr);
				delete root_;
				//toRemove -> setParent(nullptr);
				//toRemove -> setRight(nullptr);
				//delete toRemove;
				root_ = rChild;
				return;
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
					//toRemove -> setParent(nullptr);
					//toRemove -> setLeft(nullptr);
					delete toRemove;
					return;
				}

				// If we are removing the parent's right node, update parent's right pointers
				else
				{
					parent -> setRight(rChild);
					rChild -> setParent(parent);
					//toRemove -> setParent(nullptr);
					//toRemove -> setRight(nullptr);
					delete toRemove;
					return;
				}
			}
		}
	}
}

template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    // TODO

		// If the tree is empty, there is no predecessor -> return nullptr
		if (current == nullptr)
		{
			return nullptr;
		}

		// If the node has a left child, then the predecessor is the right-most
		// child of this left child
		if (current -> getLeft() != nullptr)
		{
			// Step left once
			current = current -> getLeft();

			// Continue stepping right until you can't
			while (current -> getRight() != nullptr)
			{
				current = current -> getRight();
			}

			// Exiting the for loop means you are at the right-most node
			return current;

		}

		// If the node does not have a left child, then walk up the ancestor
		// chain until you traverse the first right-child pointer
		else if (current -> getRight() != nullptr)
		{
			Node<Key, Value>* parent = current -> getParent();
			while (current != nullptr)
			{
				// If the parent's right child is the current node, then we found the 
				// appropriate predecessor
				if (parent -> getRight() == current)
				{
					return current;
				}

				current = parent;
				parent = current -> getParent();
			}
		}

		// If we exit the loop (and, implicitly, the conditional) without having found 
		// a right child, then no predecessor exists
		return nullptr;

}

template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::successor(Node<Key, Value>* current)
{
	// If the tree is empty, there is no successor -> return nullptr
	if (current == nullptr)
	{
		return nullptr;
	}

	// If the node has a right child, then the successor is the left-most
	// child of this right child
		if (current -> getRight() != nullptr)
		{
			// Step right once
			current = current -> getRight();

			// Continue stepping left until you can't
			while (current -> getLeft() != nullptr)
			{
				current = current -> getLeft();
			}

			// Exiting the for loop means you are at the left-most node
			return current;

		}

		// If the node does not have a right child, then walk up the ancestor
		// chain until you traverse the first left-child pointer
		else if (current -> getRight() != nullptr)
		{
			Node<Key, Value>* parent = current -> getParent();
			while (current != nullptr)
			{
				// If the parent's right child is the current node, then we found the 
				// appropriate successor
				if (parent -> getLeft() == current)
				{
					return current;
				}

				current = parent;
				parent = current -> getParent();
			}
		}

		// If we exit the loop (and, implicitly, the conditional) without having found 
		// a left child, then no successor exists
		return nullptr;
}

/**
* A helper function to recursively delete nodes
* starting from the left-most leaf node
*/

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clearHelper(Node<Key, Value>* n)
{
	if (n == nullptr)
	{
		return;
	}

	// Deleting left and right subtrees
	clearHelper(n -> getLeft());
	clearHelper(n -> getRight());

	// Deleting the specific node
	delete n;
}

/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    // TODO

		// Calling the recurisve helper function on root_
		clearHelper(root_);

		// Setting root_ to nullptr, thus becoming an empty tree
		root_ = nullptr;

}


/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    // TODO

		// If the tree is empty, return nullptr
		if (root_ == nullptr)
		{
			return nullptr;
		}

		// If the root is the only node in the tree, return the root
		if (root_ -> getLeft() == nullptr && root_ -> getRight() == nullptr)
		{
			return root_;
		}

		// Smallest node will be the left-most node
		Node<Key, Value>* current = root_;
		while (current -> getLeft() != NULL)
		{
			current = current -> getLeft();
		}

		// Once we exit the loop, we are at the left-most node
		return current;
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    // TODO

		Node<Key, Value>* current = root_;

		// While we are at a valid node
		while (current != nullptr)
		{
			// If the current key is less than the target, traverse left
			if (key < current -> getKey())
			{
				current = current -> getLeft();
			}

			// If the current key is greater than the target, traverse right
			else if (key > current -> getKey())
			{
				current = current -> getRight();
			}

			// If the current key is equal to the target, it was found -> return the node
			else if (key == current -> getKey())
			{
				return current;
			}
		}

		// If the above conditional isn't met, then the node must not exist
		return nullptr;
}

/**
* Helper function to recursively calculate the height of the 
* tree if it is balanced, thus reducing runtime complexity
*/
template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::calculateHeightIfBalanced(const Node<Key, Value>* n) const {
	// Base case: an empty tree is always balanced and has a height of 0
	if (n == nullptr) return 0;

	// Think about cases to handle:
	// - What if at least one subtree is NOT balanced?
	// - What if BOTH are balanced?

	int heightLeft = calculateHeightIfBalanced(n -> getLeft());
	// If the left subtree isn't balanced, whole tree isn't balanced
	if (heightLeft == -1)
	{
		return -1;
	}

	int heightRight = calculateHeightIfBalanced(n -> getRight());
	// If the right subtree isn't balanced, whole tree isn't balanced
	if (heightRight == -1)
	{
		return -1;
	}

	// If subtrees are balanced, check the height differences
	// If the difference between the subtree heights is greater than 1, it is not balanced
	if (abs(heightLeft - heightRight) > 1)
	{
		return -1;
	}

	// If the difference isn't greater, return the max of the subtree heights
	else if (heightLeft < heightRight)
	{
		return heightRight + 1;
	} 

	return heightLeft + 1;
}
/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
	Node<Key, Value>* node = root_;

	// Call the helper function
  if (calculateHeightIfBalanced(node) == -1)
		{
			return false;
		}

		return true;
}



template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif
