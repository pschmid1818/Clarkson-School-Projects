--print out all triples between 1 - 100
triples 
 = [(x,y,z) | x <- [1..100], y <- [1..100], z <- [1..100], x^2 + y^2 == z^2]