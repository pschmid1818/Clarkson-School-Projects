#ifndef CIRCULARLIST_H
#define CIRCULARLIST_H

struct node{
	int process_id;
	float percentage;
	node *next;
	node(int id, float percent)
	{process_id = id; percentage = percent;}
};

class Linkedlist{
	private:
		node *front, *rear;
	public:
		Linkedlist();
		~Linkedlist();
		bool is_empty();
		void insertRear(int id);
		void deleteFront();
		void run_a_process();
		void printtest();
};

#endif
