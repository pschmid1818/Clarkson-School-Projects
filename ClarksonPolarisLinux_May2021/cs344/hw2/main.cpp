#include "linkedlist.h"

int main(){
	LinkedList l;
	l.insertAt(1, 1);
	l.insertAt(2, 2);
	l.insertAt(3, 3);
	l.insertAt(4, 4);
	l.reverse_and_duplicate();	

	l.print();
	//printing 4 -> 4 -> 3 -> 3 -> 2 -> 2 -> 1 -> 1
}
