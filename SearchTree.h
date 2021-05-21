#pragma once
#include "Tree.h"
#include <iostream>
using namespace std;

template<class T>
class SearchTree : public Tree<T>
{

public:
	void add(T value);
	bool  search(T value)
	{
		return search(Tree<T>::root, value);
	}
	void remove(T val);
	T successor(T val);
	void deleteDuplicates();
private:
	void add(typename Tree<T>::Node* current, T val);
	bool  search(typename Tree<T>::Node* current, T val);
	
	//help methoods
	typename Tree<T>::Node* Remove(typename Tree<T>::Node* current, T val);
	T minimumValue(typename Tree<T>::Node* root);
	T  findSuccessor(typename Tree<T>::Node* root, typename Tree<T>::Node* succ);
	typename Tree<T>::Node* deleteNode(typename Tree<T>::Node* root);
	typename Tree<T>::Node* helpSearch(typename Tree<T>::Node* current, T val);//find the temp successor the is value is ==to val
};

template <class T>
void SearchTree<T>::add(T val)
{
	// add value to binary search tree 
	if (!Tree<T>::root)
	{
		Tree<T>::root = new typename Tree<T>::Node(val);
		return;
	}
	add(Tree<T>::root, val);
}

template <class T>
void SearchTree<T>::add(typename Tree<T>::Node* current, T val)
{
	/*if (val == current->value)
	{
		(current->counter)++;
	}*/
	if (current->value < val)

		if (!current->right)
		{
			current->right = new typename Tree<T>::Node(val);
			
			return;
		}
		else add(current->right, val);
	else

		if (!current->left)
		{
			current->left = new typename Tree<T>::Node(val);
			
			return;
		}
		else add(current->left, val);
}

template <class T>
bool SearchTree<T>::search(typename Tree<T>::Node* current, T val)
{
	// see if argument value occurs in tree
	if (!current)
		return false;	// not found
	if (current->value == val)
		return true;
	if (current->value < val)
		return search(current->right, val);
	else
		return search(current->left, val);
}

template<class T>
inline void SearchTree<T>::remove(T val)
{
	Remove(Tree<T>::root, val);

}

template<class T>
inline T SearchTree<T>::successor(T val)
{
	if (!search(val))
		throw "no sucssesor";
	typename Tree<T>::Node* suc = helpSearch(Tree<T>::root, val);    //a pointer to the value
	suc->value = findSuccessor(Tree<T>::root, suc);                 //send the pointer to find his successor
	return suc->value;
}

template<class T>
inline void SearchTree<T>::deleteDuplicates()
{
	deleteNode( Tree<T>::root);
}

template<class T>
inline typename Tree<T>::Node* SearchTree<T>::Remove(typename Tree<T>::Node* current, T val)
{
	if (!search(current, val))       //if the value is not in tree 
	{
		throw "ERROR";
	}

	if (current == NULL)       //if its null return null
		return current;

	if (val < current->value)    //if the value is smaller than the current root, return to this function with his left side
	{
		current->left = Remove(current->left, val);
		/*current->left->counter--;   *///**

	}
	else if (val > current->value)    //if the value is bigger than the current root, return to this function with his right side
	{
		current->right = Remove(current->right, val);
		//current->right->counter--;   //**
	}

	else 
	{                      // node with only one child or no child
		if (current->left == NULL)
			return current->right;
		else if (current->right == NULL)
			return current->left;

		// node with two children: Get the inorder
		current->value = minimumValue(current->right);

		// Delete the inorder successor
		current->right = Remove(current->right, current->value);
	}

	return current;
}

template<class T>
inline T SearchTree<T>::minimumValue(typename Tree<T>::Node* root)
{
	typename Tree<T>::Node* current = root;
	// loop down to find the leftmost leaf becuse its a bts tree
	while (current->left != NULL) {
		current = current->left;
	}
	return current->value;
}

template<class T>
inline T SearchTree<T>::findSuccessor(typename Tree<T>::Node* root, typename Tree<T>::Node* n)
{
           	if (n->right != NULL)   // 
			{ 
				 
				return   minimumValue(n->right);
			}
		
			typename Tree<T>::Node* newSucc = NULL;
		
			// Start from root and search for
			// successor down the tree
			while (root != NULL)
			{
				if (n->value < root->value)
				{
					newSucc = root;
					root = root->left;
				}
				else if (n->value > root->value)
					root = root->right;
				else
					break;
			}
		
			return newSucc->value;
}
template<class T>
inline typename Tree<T>::Node* SearchTree<T>::deleteNode(typename Tree<T>::Node* root)
{
	if (root == NULL)
	{
		return NULL;
	}
	int valueToSerch;
	//else if (root->counter > 1)
	//{
	//	Remove(root->left, root->left->value);
	//	root->left->counter--;
	//}
	//else if (root->counter > 1)
	//{
	//	Remove(root->right, root->right->value);
	//	root->right->counter--;
	//}

	valueToSerch = root->value;                //value 
	typename Tree<T>::Node* current = root;   //current pointer to a node in tree
	if (current->right != NULL && current->left != NULL)
	{
		if (current->value == valueToSerch)
			Remove(current,current->value);
		valueToSerch = current->value;

		deleteNode(current->right);
		deleteNode(current->left);
	}
	return root;
}

template<class T>
inline typename Tree<T>::Node* SearchTree<T>::helpSearch(typename Tree<T>::Node* current, T val)
{
	// see if argument value occurs in tree
	if (!current)
		throw"no successor";	// not found
	if (current->value == val)
		return current;
	if (current->value < val)
		return helpSearch(current->right, val);
	else
		return helpSearch(current->left, val);
}

