#include "stack.h"
#include <iostream>

using namespace std;

int main(){
	int i;
	Dual_stack s;
	
	cout << "Pushing 10 elements onto 1st stack." << endl;
	for(i = 1;i <= 10; i++){
		if(s.is_full())
			cout << "There is no more space." << endl;
		else
			s.push_first(i);
	}
	
	cout << "Popping 10 elements off from 1st stack: ";
	for(i = 1;i <= 10; i++){
		if(s.is_empty_first())
			cout << "1st stack is empty." << endl;
		else
			cout << s.pop_first() << " ";
	}

	cout << endl << "Pushing 10 elements onto 2nd stack." << endl;
	for(i = 1;i <= 10; i++){
		if(s.is_full())
			cout << "There is no more space." << endl;
		else
			s.push_second(i);
	}

	cout << "Popping 10 elements off from 1st stack: ";
	for(i = 1;i <= 10; i++){
		if(s.is_empty_second())
			cout << "2nd stack is empty." << endl;
		else
			cout << s.pop_second() << " ";
	}

	cout << endl << endl << "Pushing 5 elements onto 1st stack." << endl;
	for(i = 1;i <= 5; i++){
		if(s.is_full())
			cout << "There is no more space when pushing the " << i << "-th element." << endl;
		else
			s.push_first(i);
	}
	
	cout << "Pushing 6 elements onto 2nd stack." << endl;
	for(;i <= 11; i++){
		if(s.is_full())
			cout << "There is no more space when pushing the " << i << "-th element." << endl;
		else
			s.push_second(i);
	}
}
