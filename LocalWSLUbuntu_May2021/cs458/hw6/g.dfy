// Double x

method g(x: int) returns (r: int)
requires x >= 0
ensures r == 2 * x
{
    var y := 0;
    var i := 0;
    while i < x
    invariant y == 2 * i
    decreases x - i
    {
        y := y + 2;
        i := i + 1;
    }
    return y;
}

// The result of bubbling up on the path from requires to invariant is:
    // [x >= 0  ->  0 == 2 * 0]
    // assume x >= 0
    // [0 == 2 * 0]
    // y := 0
    // [y == 2 * 0]
    // i := 0
    // [y == 2 * i]

// The result of bubbling up on the path from invariant to invariant is:
    // [y == 2 * i  ->  x >= 0  ->  (y+2) == 2 * (i+1)]
    // assume y == 2 * i
    // [x >= 0  ->  (y+2) == 2 * (i+1)]
    // assume x >= 0
    // [(y+2) == 2 * (i+1)]
    // y := y + 2
    // [y == 2 * (i+1)]
    // i := i + 1
    // [y == 2 * i]

// The result of bubbling up on the path from invariant to ensures is:
    // [y == 2 * i  ->  y == 2 * i]
    // assume y == 2 * i
    // [y == 2 * i]
    // i == x
    // [y == 2 * x]
    // r := y
    // [r == 2 * x]