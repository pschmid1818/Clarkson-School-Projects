#include <iostream>

using namespace std;

int main()
{
    int arr[10] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    int i = 0;                          
    int j = 0;                          
    int n = 10;                         //size of array

    cout << "Initial array: ";
    while(i < n)
    {
        cout <<arr[i] <<" ";
        i = i+1;
    }
    cout <<endl;
    i = 0;

    while (i < n)
    {
        int old;
        int min = i;                    //sets current index as the minimum
        j = i+1;
        while (j < n)                   //test i against the rest of the array
        {
            if (arr[j] < arr[min])      //if any value is smaller than the current minimum
            {
                min = j;                //sets j to the new min value and continues to search
            }
            j = j+1;
        }
        old = arr[i];                   //sets a temp variable to the value of current index
        arr[i] = arr[min];              //replaces the current index with the new lowest number
        arr[min] = old;                 //places the old index at the index of the new minimum
        i = i+1;
    }
    int longest = arr[0];               //longest starts as the first element of the array
    int test;                           //create a test variable
    int lcount = 0;                     //start a count for the longest
    int tcount = 0;                     //start a count for the test
	
    i = 0;
    cout << "Sorted array:  ";
    while(i < n)
    {
        cout <<arr[i] <<" ";
        i = i+1;
    }
    cout <<endl;

    return 0;
}
