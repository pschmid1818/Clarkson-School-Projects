-- Finds the max of a tuple in a list (needs uncurry stop doing)
maxpair :: (Ord a, Num a) => [(a,a)] -> [a]
maxpair [(x,y)] = map (\(x,y) -> max x y) [(x,y)]

maxpair :: (Ord a, Num a) => [(a,a)] -> [a]
maxpairProf = map (uncurry max)

-- between that takes small letters x and y and a string
-- zs in small letters. It returns a list of all the elements in zs between x and y in the
-- alphabet.
--I used list comp
between :: Ord a => a -> a -> [a] -> [a]
between x y zs = [a | a <- zs, head(zs) >= x && head(zs) <= y]

betweenProf :: Ord a => a -> a -> [a] -> [a]
betweenProf x y = filter (>= x) . filter (<= y)

-- negsquare that takes a list of Ints and returns the
-- square of all the negative numbers in that list.

negsquareProf :: [Int] -> [Int]
negsquareProf = map (^2) . filter (>0)

-- funcpair takes two functions f and g as arguments. 
-- It returns a function that takes a pair and applies f to the first argument of the
-- pair and g to the second.
funcPair :: (a -> a) -> (b -> b) -> (a,b) -> (a,b)
funcPair f g (a,b) = (f a, g b)

-- posneg takes x and y as arguments. It returns
-- a function that takes an Int as argument and returns x if the integer is positive and y 
-- if it is not.
posNeg :: a -> a -> (Int -> a)
posNeg x y = \z -> if z > 0 then x else y



data Person = P String String Char Int
    deriving Show

--Return a list of a person with different ages
diffages :: Person -> [Int] -> [Person]
diffages (P fname lname sex _) ages
    = map (\x -> (P fname lname sex x)) ages

--Persons are equal when names are equal
instance Eq Person where
    P fname1 lname1 _ _ == P fname2 lname2 _ _ = fname1 == fname2 && lname1 == lname2



data Tree a = Node a [Tree a]
    deriving Show

testtree :: Tree Int
testtree = Node 5 ([Node 6 [Node 6 [],Node 2 []],Node 7 [Node 9 [Node 4 []],Node 6 []],Node 6 []])

-- counts all instances of x in a tree
countall :: Eq a => a -> Tree a -> Int
countall x (Node a leaves) = (if x == a then 1 else 0) + sum(map (countall x) leaves)

-- Takes a tree of ints and returns a tree where the keys are their heights
numchildren :: Tree Int -> Tree Int
numchildren (Node a leaves) = (Node (length leaves) (map numchildren leaves))

-- Takes a funtion and a tree and performs the funtion of the keys of the tree
functree :: (a -> b) -> Tree a -> Tree b
functree f (Node a leaves) = (Node (f a) (map (functree f) leaves))
