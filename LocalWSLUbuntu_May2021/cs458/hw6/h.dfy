// Add half of x0 into y0
// if x0 is odd, round down (x0 = 11 & y0 = 6 -> 11/2 = 5.5 -> 5.5 = 5 -> r = 6 + 5)

method h(x0: int, y0: int) returns (r: int)
requires x0 > 0 
ensures r == y0 + (x0 / 2)
{
    var x := x0;
    var y := y0;
    while x > 0
    invariant y == y0 + x / 2
    decreases y0 + x / 2
    {
        x := x - 2;
        y := y + 1;
    }
return y;
}