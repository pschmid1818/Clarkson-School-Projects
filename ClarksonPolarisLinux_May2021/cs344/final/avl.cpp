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

int height(node *n)
{
    if(n == NULL)
    {
        return -1;
    }

    return n->height;
}

void computeBF(node *n)
{
	n->height = max(height(n->left_child), height(n->right_child)) + 1;
	n->bf = height(n->left_child) - height(n->right_child);
}

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

node* insert_helper(node *n, student s)
{
	if(n == NULL)
		return new node(s, 0, 0, NULL, NULL);
		
	if(s.id == n->s.id){
		return n;
	}
	else if(s.id > n->s.id)
		n->right_child = insert_helper(n->right_child, s);
	else
		n->left_child = insert_helper(n->left_child, s);
	
	return balance(n);
}

void AVL::insert(student s)
{
	root = insert_helper(root, s);
}

int findMin(node *n){
	//Find the min node in the subtree rooted by r.
	if(n->left_child == NULL)
		return n->s.id;
	else
		return findMin(n->left_child);
}

node* delete_helper(node* n, int id)
{
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
			return a;
		}
		else if(n->right_child == NULL){
			node *a = n->left_child;
			delete n;
			return a;
		}
		else{
			n->s.id = findMin(n->right_child);
			n->right_child = delete_helper(n->right_child, n->s.id);
			
			return n;
		}
	}
}

void AVL::deleteID(int id)
{
	root = delete_helper(root, id);
}

void AVL::showHeight()
{
	cout <<"Height of the tree is " <<height(root)<< "\n";
}

void printHelper(node *n)
{
	if(n = NULL)
	{
		return;
	}
	
	printHelper(n->left_child);
	
	cout <<"Student ID: " <<n->s.id <<"\n";
	cout <<"Name: " <<n->s.name <<"\n";
	cout <<"GPA: " <<n->s.gpa <<"\n\n";
	
	printHelper(n->right_child);
}

void AVL::printAll()
{
	return printHelper(root);
}

float GPAHelper(node *n, int id)
{
	if(n == NULL)
		return NULL;
	else if(id > n->s.id)
	{
		GPAHelper(n->right_child, id);
	}
	else if(id < n->s.id)
	{
		GPAHelper(n->left_child, id);
	}
	else
	{
		return n->s.gpa;
	}
}

float AVL::GPA(int id)
{
    return GPAHelper(root, id);
}

float findMax(node *n)
{
	if(n->right_child == NULL)
		return n->s.gpa;
	else
		return findMax(n->right_child);
}

float AVL::maxGPA()
{
	findMax(root);
}
