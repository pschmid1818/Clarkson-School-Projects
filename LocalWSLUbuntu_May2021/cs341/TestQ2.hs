module TestQ2_clynch (prefix,subList,addb,multdig,multlist,addDigits,divisible3,divisible7,threeN,exec,test_exec) where
import Debug.Trace

{-
Prefix takes two lists.  
It returns true if the first list is a prefix of the second list

Example:
prefix "abc" "abcdef"
True
prefix "abc" "abc"
True
-}
prefix :: Eq a => [a] -> [a] -> Bool
-- Fill in your code here
prefix [] _ = True
prefix _ [] = False
prefix (x:xs) (y:ys)
  | x == y = prefix xs ys  
  | otherwise = False

  
{-
subList takes two lists.
It returns true if the first list is a sublist of the second list.

Example:
subList "bcd" "abcdef"
True
subList "bce: "abcdef"
False
-}
subList :: Eq a => [a] -> [a] -> Bool
-- Fill in your code here
subList [] _ = True
subList _ [] = False
subList xs (y:ys)
  | prefix xs (y:ys) = True
  | otherwise = subList xs ys

   
{-
Digit is a digit in base 10, in other words an Int in [0..9]
-}
type Digit = Int
{-
Number is a list of digits representing a positive integer
  the list will be in reverse (i.e., from lower order to higher order digit)
  the list will not have leading zeroes
-}
type Number = [Digit]


{-
addb takes 3 arguments
  1. A positive integer, represented as a list of digits, in reverse
       (In other words, it goes from lowest order digit to highest order digit,
        and not containing any leading zeroes)
  2. Another positive integer, represented as a list of digits, in reverse
  3. A carry, which will always be 0 or 1
addb returns the result of adding the two positive integers plus the carry

Example:
addb [5,7] [9,8] 0
[4,6,1]

-}
addb :: Number -> Number -> Digit -> Number
-- Fill in your code here
addb [] x 0 = x
addb x [] 1 = addb x [1] 0
addb x [] 0 = x
addb [] x 1 = addb [1] x 0
addb (d1:d1s) (d2:d2s) carry
  | sum < 10     = sum : addb d1s d2s 0
  | otherwise    = sum-10 : addb d1s d2s 1
    where sum = d1 + d2 + carry


{-
multdig takes two digits and returns the result of multiplying them

Example:
multdig 8 4
[2,3]

-}
multdig :: Digit -> Digit -> Number
-- Fill in your code here
multdig d e
  | de < 10     = [de]
  | otherwise   = [mod de 10, div de 10]
    where de = d * e


{-
multlist takes two lists of digits and returns their dot product,
  i.e.,the sum of the products of corresponding elements
Note that a list of digits can also be a number

Example:
multdig [2,3,4] [5,6,7]
[6,5]

Explanation of example: 2*5 + 3*6 + 4*7 = 56
-}

multlist :: [Digit] -> [Digit] -> Number
-- Fill in your code here
multlist [] _ = []
multlist _ [] = []
multlist (x:xs) (y:ys) = addb (multdig x y) (multlist xs ys) 0


{-
addDigits takes a list of digits and returns its sum
Note that a list of digits can also be a number

Example:
addDigits [2,0,5,5,5,5,8]
[0,3]
-}

addDigits ::[Digit] -> Number
-- Fill in your code here
addDigits [] = [0]
addDigits (d:ds) = addb [d] (addDigits ds) 0 


{-
divisible3 takes a number and returns a Bool indicating whether it is divisible by 3
Use the following algorithm to solve this:
1. If the number only has one digit, check if that digit is 3,6 or 9
2. Otherwise add the digits and call divisible3 on the sum

Example:
divisible3 [9,9,9]
True
-}

divisible3 :: Number -> Bool
-- Fill in your code here
divisible3 [d] = mod d 3 == 0
divisible3 ds = divisible3 (addDigits ds)


{-
divisible7 takes a number and returns a Bool indicating whether it is divisible by 7
Use the following algorithm to solve this:
1. If the number only has one digit, check if that digit is 7
2. Otherwise starting with the lower order digit, multiply the digits successively
  by 1,3,2,6,4,5, and repeat for the length of the number.  Call divisible7 recursively
  on the sum of those products.  
Hint:  Use cycle.

Example:
divisible7 [1,2,3,4,5,6,7,8,9,3]
True

Explanation of example:
1*1 + 3*2 + 2*3 + 6*4 + 4*5 + 5*6 + 1*7 + 3*8 + 2*9 + 6*3 = 154
1*4 + 3*5 + 2*1 = 21
1*1 + 3*2 = 7
-}

divisible7 :: Number -> Bool
-- Fill in your code here
divisible7 [d] = mod d 7 == 0
divisible7 ds = divisible7 (multlist ds (cycle [1,3,2,6,4,5]))  


{-
threeN takes a list of Integers as argument.
It extends to the beginning of the list in the following way until the first element becomes 1.
1. If the first element is even, it puts n/2 in front
2. If the first element is odd, it puts 3n+1 in front

Example:
threeN [3]
[1,2,4,8,16,5,10,3]
-}
threeN :: [Integer] -> [Integer]
-- Fill in your code here
threeN (n:ns)
  | n == 1     = n:ns
  | odd n     = threeN ((3*n+1): n : ns)
  | otherwise  = threeN (div n 2 : n : ns) 
 
  
{-
Statement is an assembly language statement with three parts
  1. an instruction i
  2. a variable name v
  3. an integer n
Program is a list of Statements, to be executed in order
  implicitly think of each statement in the program to have a line number
  with the first instruction at line number 0
Memory represents the memory of the computer
  Memory is a list of pairs of a variable and its assigned value
The meaning of each instruction is as follows:
  1. load v n
    give variable v the value n in memory
  2. add v n
    add n to the value of v in memory
  3. jmp v n
    go to line number n, note that v is ignored so anything is allowed
  4. blz v n
    if the value of v is <= 0 then go line n
      otherwise proceed to the next line in the program
  5. ret v n
    quit the program and return the value v, here n is ignored
-}

type Inst = String
type Variable = String 
type Statement = (Inst,Variable,Int)
type Program = [Statement]
type Memory = [(Variable,Int)]  
  
exec :: Program -> Program -> Memory -> Int  
-- Uncomment the following line if you want to trace your code
-- exec prog cur mem | trace ("exec " ++ show  (head cur) ++ "  " ++ show mem) False = undefined 
-- Fill in your code here 
--exec _ [] mem = 0
exec prog (("load",var,num):rest) mem 
  = exec prog rest ((var,num):mem)
exec prog (("blz",var,num):rest) mem 
  | lookup' mem var <= 0 = exec prog (drop num prog) mem
  | otherwise = exec prog rest mem
exec prog (("add",var,num):rest) mem 
  = exec prog rest ((var,num + lookup' mem var):mem)
exec prog (("jmp",_,num):_) mem 
  = exec prog (drop num prog) mem
exec prog (("ret",var,_):_) mem 
  = lookup' mem var


{-
Initially calling exec function

test_exec prog1
9

-}
test_exec :: Program -> Int
--No need to fill in code here
test_exec p = exec p p []


{-
Example program
-}
prog1 :: Program
prog1 = [("load","x",4),("load","y",5),("load","z",0),
         ("blz","y",7),("add","z",1),("add","y",(-1)),("jmp","",3),
         ("blz","x",11),("add","z",1),("add","x",(-1)),("jmp","",7),("ret","z",0)] 
         
         
{-
lookup' takes a list of pairs
if an element exists as the first element of a pair
  then it returns the second element of its first occurence
else it produces an error message
-}
lookup' :: (Eq a,Show a,Show b) => [(a,b)] -> a -> b
lookup' store x
  | null found = error ("No match for " ++ show x ++ " in " ++ show store)
  | otherwise = head found  
    where found = [y | (x',y) <- store, x == x']           

  
-- The last problem is optional.  A version of this will be included in the next homework
-- So it doesn't hurt to solve it

  
{-
geography takes as arguments two lists of words, A and B.
It returns a list of all words C with the following properties:
1. B is a suffix of C.
2. Every word in C, except the first, must have the same last letter
     as the first letter of the word before it.
3. C contains all the words of A but no other words.  
You can assume the following:
1. B has property 2.
2. All the words in B are in A.
3. A has no duplicate words.
4. B has no duplicate words.

Example:
geography ["tiger","elephant","spot","rat","turtle"] ["spot"]
[["elephant","turtle","rat","tiger","spot"],["rat","tiger","elephant","turtle","spot"]]
-}
geography :: [String] -> [String] -> [[String]]
-- Uncomment the following line if you want to trace your code
-- geography _ listSoFar | trace ("geography " ++ show  listSoFar) False = undefined 
-- Fill in your code here
geography wordList listSoFar@(w:_)
  | length wordList == length listSoFar = [listSoFar]
  | otherwise = concat [geography wordList (newWord:listSoFar) |
                          newWord <- wordList,
                          notElem newWord listSoFar,
                        head newWord == last w]  