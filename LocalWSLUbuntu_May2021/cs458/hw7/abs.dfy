method abs(A: array<int>, size: nat)
modifies A
requires size > 0 && size <= A.Length               //size cant be zero or less and cant be more than the size of the array
ensures forall i :: 0 <= i < A.Length ==> A[i] >= 0 //every element of array needs to be positive or zero
{
  var i := 0;
	while i < size
    invariant A[i] >= 0       //the new element needs to be be positive or zero
    decreases size - i        //the difference between size and i will always decrease but never reach zero
	{
		if (A[i] < 0) 
    {
			A[i] := -A[i];
		}
    i := i + 1;
	}
}

method Testing()
{
var a := new int[10];
var size := 5;
a[0],a[1],a[2],a[3],a[4] := 2,-4,6,-3,-2;
abs(a,5);
assert a[1] == 4;
}