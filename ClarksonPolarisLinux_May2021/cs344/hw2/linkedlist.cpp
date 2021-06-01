#include "linkedlist.h"
#include <iostream>

using namespace std;

LinkedList::LinkedList(){
	head = new node(0, NULL);
	size = 0;
}

LinkedList::~LinkedList(){
	while(head != NULL){
		node *p = head->next;
		delete head;
		head = p;
	}
}

void LinkedList::print(){
	if(size == 0)
		return;
	node *p = head->next;
	cout << p->item;
	p = p->next;
	while(p != NULL){
		cout << " -> " << p->item;
		p = p->next;
	}
	cout << endl;
}

bool LinkedList::searchFor(int d){
	node *p = head->next;
	while(p != NULL){
		if(p->item == d)
			return true;
		p = p->next;
	}
	return false;
}

void LinkedList::update(int pos, int data){
	if(pos < 1 || pos > size){
		cout << "error";
		return;
	}
	node *p = head->next;
	int i = 1;
	while(i < pos){
		p = p-> next;
		i++;
	}
	p->item = data;
}


void LinkedList::insertAt(int pos, int data){
	if(pos < 1 || pos > size + 1){
		cout << "error";
		return;
	}

	node *p = head;
	int i = 0;
	while(i < pos - 1){
		p = p->next;
		i++;
	}

	node *n = new node(data, NULL);
	n->next = p->next;
	p->next = n;
	size++;
}

void LinkedList::deleteAt(int pos){
	if(pos < 1 || pos > size){
		cout << "error";
		return;
	}

	node *p = head;
	int i = 0;
	while(i < pos - 1){
		p = p->next;
		i++;
	}

	node *n = p->next;
	p->next = n->next;
	delete n;
	size--;
}

void LinkedList::reverse_and_duplicate(){
	
	//this initialize the current, previous, and next pointers

	node *current = head;
	node *next = current->next;
	node *previous = NULL;
	
	//Start the switch

	while(current != NULL)
	{
		next = current->next;     //this stores the next value
		current->next = previous; //this reverses the current nodes pointer
		previous = current;       //this sets previous equal to the current node
		current = next;           //this sets the current node equal to the next node
	}
	head = previous;                  //this leaves the last value as the head, which doesnt get printed
	insertAt(1,previous->item);       //this adds a new node which copies the current head
	deleteAt(size);                   //this deletes the old head
	head->item = 0; 	          //this changes the new head to 0
	
	//Start the duplication 
	
	current = head->next;                   //this sets the current node back to the start but skips the head
	int i = 1;				//this initializes a counter variable
	
	while(current != NULL)			//the null being the first value throws this all off if the while loops were together thus they're duplicated
	{
		next = current->next;		//stores the next value
		insertAt(i,current->item);	//adds a node equal to the current where i is
		current = next;			//sets the current node to the next
		i=i+2;				//the counter for i as it needs to skip 2 spaces
	}
		
}



