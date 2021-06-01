//Paul Schmid
//HW 5

#include <iostream>

using namespace std;

void most_frequent(int arr[], int n)
{
   	for (int i = 0; i < n-1; i++) 	//loop for sorting array
	{
		int old;
      		int min = i;			//sets current index as the minimum
      		
		for (int j = i+1; j < n; j++)	//test i against the rest of the array 
		{
        		if (arr[j] < arr[min])	//if any value is smaller than the current minimum
			{
        			min = j;	//sets j to the new min value and continues to search
			}
		}
      		
		old = arr[i];			//sets a temp variable to the value of current index
      		arr[i] = arr[min];		//replaces the current index with the new lowest number
      		arr[min] = old;			//places the old index at the index of the new minimum
	}

	int longest = arr[0];				 //longest starts as the first element of the array
	int test;					 //create a test variable
	int lcount = 0;					 //start a count for the longest
	int tcount = 0; 				 //start a count for the test

	for(int i = 0; i < n-1; i++)			 //start finding the frequency of numbers
	{	
		if (arr[i] == longest)			 //+1 for the current longest
		{
			lcount++;
		}
		if (arr[i] == test)			 //+1 for the test number
		{
			tcount++;
		}
		if (arr[i] != longest && arr[i] != test) //if the current index isnt the same as test or longest, set it to test and restart the count
		{
			test = arr[i];
			tcount = 1;
		}
		if(tcount > lcount)			 //if test's count gets larger than the current longest set test to longest 
		{
			longest = test;			 
			lcount = tcount;
		}
	}

	cout <<longest <<endl;
}

int main()
{
	int array1[] = {9, -2101, 1926, -2101, -101, 9, -4, 9};
	cout << "In 1st array, the most frequent element is: ";
	most_frequent(array1, 8);						//output 9

	int array2[] = {104, 10, -10, 104, 9918, 10, 206, -1311, 289};
	cout << "In 2nd array, the most frequent element is: ";
	most_frequent(array2, 9);						//output 10 or 104
}
