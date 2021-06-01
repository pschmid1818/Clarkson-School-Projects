// Difference between x0 and y

method f(x0: int,y: int) returns (r: int)
requires x0 >= 0 && x0 < y
ensures r == y - x0
{
    var x := x0;
    var d := 0;
    while x < y
    invariant x == d + x0
    decreases y - d 
    {
        x := x + 1;
        d := d + 1;
    }
    return d;
}

    // The result of bubbling up on the path from requires to invariant is:
        // [x0 >= 0 && x0 < y  ->  x0 = 0 + x0]
        // assume x0 >= 0 && x0 < y
        // [x0 == 0 + x0]
        // x := x0
        // [x == 0 + x0]
        // d := 0
        // [x == d + x0]

    // The result of bubbling up on the path from invariant to invariant is:
        // [x == d + x0  ->  x < y  ->  (x+1) == (d+1) + x0]
        // assume x == d + x0   
        // [x < y  ->  (x+1) == (d+1) + x0]
        // assume x < y
        // [(x+1) == (d+1) + x0]
        // x := x + 1
        // [x == (d+1) + x0]
        // d := d + 1
        // [x == d + x0]

    // The result of bubbling up on the path from invariant to ensures is:
        // [d == d]
        // [d == d + x0 - x0]
        // [x == d + x0  ->  d == x - x0]
        // ^^^ Just for me to double check (the others were easier to see at a glance)

        // [x == d + x0  ->  x == y  ->  d == y - x0]
        // assume x == d + x0   
        // [x == y  ->  d == y - x0]
        // assume x == y
        // [d == y - x0]
        // r := d
        // [r == y - x0]