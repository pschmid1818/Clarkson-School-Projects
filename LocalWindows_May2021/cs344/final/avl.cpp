//Paul Schmid
//Final Project

#include "avl.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <cstddef>

using namespace std;

AVL::AVL()
{
	root = NULL;
}

//since height is stored as a variable in the nodes this just outputs it
int height(node *n)
{
    if(n == NULL)
    {
        return -1;
    }

    return n->height;
}

//this updates the height but finding the max height of its two children and updates the bf by subtracting them
void computeBF(node *n)
{
	n->height = max(height(n->left_child), height(n->right_child)) + 1;
	n->bf = height(n->left_child) - height(n->right_child);
}

//right rotaion and then updates the height and bf
node *rightRotate(node *y)
{
    node *x = y->left_child;
    node *beta = x->right_child;

    x->right_child = y;
    y->left_child = beta;

    computeBF(y);
    computeBF(x);

    return x;
}

//left rotation and then updates the height and bf
node *leftRotate(node *x)
{
    node *y = x->right_child;
    node *beta = y->left_child;

    y->left_child = x;
    x->right_child = beta;

    computeBF(x);
    computeBF(y);

    return y;
}

//by using the balance factor the code checks the 4 cases
node *balance(node *n)
{
    computeBF(n);
	
	if(n->bf == 2 && n->left_child->bf >= 0)
	{
		//leftleft case
		return rightRotate(n);
	}
	else if(n->bf == 2 && n->left_child->bf == -1)
	{
		//leftright case
		n->left_child = leftRotate(n->left_child);
		return rightRotate(n);
	}
	if(n->bf == -2 && n->right_child->bf <= 0)
	{
		//rightright case
		return leftRotate(n);
	}
	else if(n->bf == 2 && n->right_child->bf == 1)
	{
		//leftright case
		n->right_child = rightRotate(n->right_child);
		return leftRotate(n);
	}

	return n;
}

//sorts through the avl tree and places the node where it belongs basen on the students id, it then gets balanced to fit the avl property
node* insert_helper(node *n, student s)
{
	if(n == NULL)
	{
		return new node(s, 0, 0, NULL, NULL);
	}	
	if(s.id == n->s.id){
		return n;
	}
	else if(s.id > n->s.id)
		n->right_child = insert_helper(n->right_child, s);
	else
		n->left_child = insert_helper(n->left_child, s);
	
	return balance(n);
}

//calls insert helper at root 
void AVL::insert(student s)
{
	root = insert_helper(root, s);
}


//finds the minimum id by going to the left-most child
int findMin(node *n){
	if(n->left_child == NULL)
		return n->s.id;
	else
		return findMin(n->left_child);
}


//starts by checking the balance and then checking for the id
//when the id is found that node is deleted
//children of the node are saved and returned
node* delete_helper(node* n, int id)
{
	n = balance(n);
	if(n == NULL)
		return NULL;
	else if(id > n->s.id){
		n->right_child = delete_helper(n->right_child, id);
		
		return n;
	}
	else if(id < n->s.id){
		n->left_child = delete_helper(n->left_child, id);
		
		return n;
	}
	else{
		if(n->left_child == NULL && n->right_child == NULL){
			delete n;
			return NULL;
		}
		else if(n->left_child == NULL){
			node *a = n->right_child;
			delete n;
			return balance(a);
		}
		else if(n->right_child == NULL){
			node *a = n->left_child;
			delete n;
			return balance(a);
		}
		else{
			n->s.id = findMin(n->right_child);
			n->right_child = delete_helper(n->right_child, n->s.id);
			return balance(n);
		}
	}
}

//calls delete_helper on root
void AVL::deleteID(int id)
{
	root = delete_helper(root, id);
}

//reads the height of root
void AVL::showHeight()
{
	cout <<"Height of the tree is " <<height(root)<< "\n";
}

//sorts through the list in order by printing the leftmost child until it prints the rightmost child
void printHelper(node *n)
{
	if(n == NULL)
	{
		return;
	}

	printHelper(n->left_child);
	
	cout <<"Student ID: " <<n->s.id <<"\n";
	cout <<"Name: " <<n->s.name <<"\n";
	cout <<"GPA: " <<n->s.gpa <<"\n\n";
	
	printHelper(n->right_child);
}

//starts printing from the root
void AVL::printAll()
{
	return printHelper(root);
}

//finds the gpa of a specified student by searching for their id
float GPAHelper(node *n, int id)
{
	if(n == NULL)
	{
		return -1;
	}
	else if(id > n->s.id)
	{
		return GPAHelper(n->right_child, id);
	}
	else if(id < n->s.id)
	{
		return GPAHelper(n->left_child, id);
	}
	else
	{
		return n->s.gpa;
	}
}

//calls gpaHelper from root
float AVL::GPA(int id)
{
    return GPAHelper(root, id);
}

//by searching for the largest gpa through all the nodes in order it finds the max
float findMax(node *n, float max)
{
	if(n == NULL)
	{
		return max;
	}

	max = findMax(n->left_child, max);

	if(max <= n->s.gpa)
	{
		max = n->s.gpa;
	}

	max = findMax(n->right_child, max);

	return max;
}

//calls findMax on the root with a max of 0 as a baseline
float AVL::maxGPA()
{
	return findMax(root, 0);
}
