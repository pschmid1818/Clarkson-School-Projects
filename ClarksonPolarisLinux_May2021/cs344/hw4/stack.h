#ifndef STACK_H
#define STACK_H

class Dual_stack{
	private:
		int elements[10];
		int current_size_first;		//number of elements in 1st stack
		int current_size_second;	//number of elements in 2nd stack
	public:
		Dual_stack();
		~Dual_stack();

		void push_first(int elem);	//push "elem" onto 1st stack
		int pop_first();		//pop an element from 1st stack
		bool is_empty_first();		//check if 1st stack is empty

		void push_second(int elem);	//push "elem" onto 2nd stack
		int pop_second();		//pop an element from 2nd stack
		bool is_empty_second();		//check if 2nd stack is empty

		bool is_full();			//check if the entire array if full
};

#endif
