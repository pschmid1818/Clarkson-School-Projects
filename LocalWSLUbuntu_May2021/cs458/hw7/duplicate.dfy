method Duplicate(A: array<int>) returns(r: bool)
requires A.length >= 2                              //needs two elements to find a duplicate           
ensures exists i :: 0 <= i < A.length ==> r == A[i] // There exists an i such that r = A[i]
{
  var i := 0;
  var j;
  while i < A.Length
  invariant true
  decreases A.Length - i 
  {
    j := i + 1;
    while j < A.Length
    invariant true
    decreases A.Length - j 
    {
      if A[i] == A[j]
      {
        return true;
      }
      j := j + 1;
    }
    i := i + 1;
  }
  return false;
}

method Testing()
{
var a := new int[5];
a[0],a[1],a[2],a[3],a[4] := 2,4,6,4,4;
var r := Duplicate(a);
assert 0 <= 1 < 3 < a.Length;
assert a[1] == a[3];
assert r == true;
}