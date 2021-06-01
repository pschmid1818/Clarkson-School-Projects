#include "stack.h"
#include <iostream>

using namespace std;

Dual_stack::Dual_stack()
{
	current_size_first = 0;
	current_size_second = 0;	
}

Dual_stack::~Dual_stack()
{
	if(is_empty_first() && is_empty_second())
	{
		return;
	}
	for(int i = 0; i <= current_size_first - 1; i++);
	{
		cout << pop_first();
	}
	for(int i = current_size_first; i <= current_size_first + current_size_second - 1; i++)
	{
		cout << pop_second();
	}
}

void Dual_stack::push_first(int elem)
{
	if(is_full())
	{
		return;
	}

	elements[current_size_first] = elem;
	current_size_first++;
}

int Dual_stack::pop_first()
{	
	if(is_empty_first())
	{
		return 42;
	}

	int first = elements[current_size_first - 1];
	elements[current_size_first-1] = elements[current_size_first];
	current_size_first--;
	
	return first;
}

bool Dual_stack::is_empty_first()
{
	bool is = false;
	if(current_size_first == 0)
	{
		is = true;
	}
	return is;
}

bool Dual_stack::is_full()
{
	bool is = false;
	if(current_size_first + current_size_second == 10)
	{
		is = true;
	}
	return is;		
}

void Dual_stack::push_second(int elem)
{
	if(is_full())
        {
                return;
        }
	
	elements[current_size_second] = elem;
        current_size_second++;
}

int Dual_stack::pop_second()
{
	if(is_empty_second())
        {
                return 69;
        }

        int first = elements[current_size_second - 1];
        elements[current_size_second - 1] = elements[current_size_second];
        current_size_second--;

        return first;
}

bool Dual_stack::is_empty_second()
{
	bool is = false;
	if(current_size_second == 0)
	{
		is = true;
	}
	return is;
}
