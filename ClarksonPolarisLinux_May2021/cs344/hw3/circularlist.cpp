#include "circularlist.h"
#include <iostream>

using namespace std;

Linkedlist::Linkedlist(){
	rear = NULL;
}

Linkedlist::~Linkedlist(){
	if(is_empty())
		return;
	while(rear->next != rear){
		node *n = rear->next->next;
		delete rear->next;
		rear->next = n;
	}
	delete rear;
}

bool Linkedlist::is_empty(){
	return (rear == NULL);
}

void Linkedlist::insertRear(int id){
	if(is_empty())
	{
		rear = new node(id, 0);
		rear->next = rear;
	}
	else
	{
		node *n = new node(id, 0);
		n->next = rear->next;
		rear->next = n;
		rear = n;
	}
}

void Linkedlist::deleteFront(){
	if(rear->next == rear){
		delete rear;
		rear = NULL;
	}
	else{
		node *n = rear->next;
		rear->next = rear->next->next;
		delete n;
	}
}

void Linkedlist::run_a_process(){
	if(is_empty())
		return;
	rear->next->percentage += 0.25;
	if(rear->next->percentage == 1){
		cout << "Process " << rear->next->process_id << " finished execution." << endl;
		deleteFront();
	}
	else{
		cout << "Process " << rear->next->process_id << ": " << rear->next->percentage << " percent completed." << endl;
		rear = rear->next;
		//rear->next = rear->next->next;
	}
}

//as of writing this I am getting an error that it only runs the process on 'process 1'
//this is to check if it builds the linked list wrong or the process is wrong
//edit: prints '1 -> 2 -> 3 -> 4' I will assume that run_a_process() is wrong
//final edit: commented part was extranious, in my removal of front I thought this was still needed
void Linkedlist::printtest()
{
	if(is_empty())
	{
		cout <<"No available Linked List!\nTest Done\n";
		return;
	}
	else
	{
		node *current = rear->next;
		while(current != rear)
		{
			cout << current->process_id <<" -> ";
			current = current->next;
		}
		cout << rear->process_id <<"\nTest Done\n";
	}
}
