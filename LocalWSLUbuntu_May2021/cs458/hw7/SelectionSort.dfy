predicate sorted(A: array<int>, i: int, j: int)
reads A
{forall k :: 0 <= i <= k < j < A.Length ==> A[k] <= A[k+1] }

predicate all_smaller(A: array<int>, a: int, b: int, c: int)
reads A
{forall i :: 0 <= a <= i <= b < A.Length && 0 <= c < A.Length ==> A[i] <= A[c]}

method MaxIndex(A: array<int>, size: nat) returns(r: nat)
requires size >= 0 && size <= A.Length 
ensures forall i :: 0 <= i < size ==> r >= A[i]
{
  r := 0;
  var i := 1;
  while i < size
  invariant A[r] >= A[i]
  decreases size - i
  {
    if A[r] < A[i]
    {
    r := i;
    }
    i := i + 1;
  }
  return r;
}

method SelectionSort(A: array<int>)
modifies A
requires true
ensures sorted(A,0,A.Length)
ensures multiset(A[..]) == multiset(old(A[..]))
{
  var i := A.Length;
  var m;
  while i >= 2
  invariant A[m] >= A[i-1]
  decreases i - 2
  {
    m := MaxIndex(A,i);
    A[i-1],A[m] := A[m],A[i-1];
    i := i - 1;
  }
}

method Testing()
{
var a := new int[10];
var size := 5;
a[0],a[1],a[2],a[3],a[4] := 2,4,6,4,4;
SelectionSort(a);
assert a[2] <= a[3];
}