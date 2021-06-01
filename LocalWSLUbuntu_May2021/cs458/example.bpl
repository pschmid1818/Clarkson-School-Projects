procedure PriceIsRight(guess1:int, guess2:int, price:int) returns(r:int)
requires price > 0 && guess1 > 0 && guess2 > 0;
ensures r <= price;
ensures r == guess1 || r == guess2 || r ==-1;
{    
    r := -1;
    if (guess1 <= price) {      
        r := guess1;
        if(guess2 >= r && guess2 <= price) {
            r := guess2;
        }
    }
    else {
        if(guess2 <= price) {
            r := guess2;
        }
    }
}
