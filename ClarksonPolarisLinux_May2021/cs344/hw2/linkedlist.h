#ifndef LINKEDLIST_H
#define LINKEDLIST_H

struct node{
	int item;
	node *next;
	node(int d, node *p){item = d; next = p;}
};

class LinkedList{
	private:
		node *head;
		int size;
	public:
		LinkedList();
		~LinkedList();
		void print();
		bool searchFor(int d);
		void insertAt(int pos, int data);
		void deleteAt(int pos);
		void update(int pos, int data);

		void reverse_and_duplicate();
};

#endif
