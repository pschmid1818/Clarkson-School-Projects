#include "circularlist.h"
#include <iostream>

using namespace std;

int main(){
	Linkedlist l;
	l.insertRear(1);
	l.insertRear(2);
	l.insertRear(3);
	l.insertRear(4);
	l.printtest();
	int i = 1;
	while(i <= 20){
		cout << "At time " << i << ": " << endl;
		l.run_a_process();
		i++;
	}
}
