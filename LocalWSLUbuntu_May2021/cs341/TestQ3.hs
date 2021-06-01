module TestQ3 (beginA,pigLatin,longest,search,geogDone,geogNext,modify,encryptf,exec',test_exec') where

import Debug.Trace
import Data.List -- for elemIndex in Question 5

-- Question 1 ------------------------------------------------------------ Done
-- beginA takes a list of words and returns a list of 
-- all those words that being with capital A. 
beginA :: [String] -> [String]
beginA list 
 = filter(\x -> head(x) == 'A') list

-- Question 2 ------------------------------------------------------------ Done
-- pigLatin takes a list of words and removes the first letter
-- from each of those words and adds "way" to the end.
pigLatin :: [String] -> [String]
pigLatin list 
 = map (++ "way") [tail(x) | x <- list]

-- Question 3 ------------------------------------------------------------ Done
-- longest takes a nonempty list of words and returns the longest
-- word in that list.  If there is more than one longest
-- word, it returns the first of them.
longest :: [String] -> String
longest list
 = if (length(list) > 0)
   then foldl1 (\y x -> if (length y) > (length x) then y else x) list
   else "Error: Empty List"

-- Question 4 ------------------------------------------------------------ Done
-- modify takes
--   1. an element x of type a
--   2. an element y of type b
--   3. a function f from a's to b's
-- it returns a function that is identical to f except it maps x to y
modify x y f
 = \z -> 
 if (z == x)
 then y
 else f z

-- Question 5 ------------------------------------------------------------ Done
-- encryptf takes
--   1. a list xs of a's
--   2. a list ys of a's
-- it returns a function that
--   maps elements of xs to the corresponding element of ys
--   and maps everything else to itself
encryptf :: Eq a => [a] -> [a] -> (a -> a)
encryptf xs ys 
 = \z ->
 if (z `elem` xs)
 then ys!!(head(elemIndices z xs)) -- would use elemIndex but dont know how to convert Maybe Int -> Int
 else z

-- Question 6 ------------------------------------------------------------
-- Statement is an assembly language statement with three parts
--   1. an instruction i
--   2. a variable name v
--  3. an integer n
-- Program is a list of Statements, to be executed in order
--   implicitly think of each statement in the program to have a line number
--   with the first instruction at line number 0
-- Memory represents the memory of the computer
--   Memory is a list of pairs of a variable and its assigned value
-- The meaning of each instruction is as follows:
--   1. load v n
--     give variable v the value n in memory
--   2. add v n
--     add n to the value of v in memory
--   3. jmp v n
--     go to line number n, note that v is ignored so anything is allowed
--   4. blz v n
--     if the value of v is <= 0 then go line n
--       otherwise proceed to the next line in the program
--   5. ret v n
--     quit the program and return the value v, here n is ignored
type Inst = (String,String,Int)
type Memf = String -> Int
exec' :: [Inst] -> [Inst] -> Memf -> Int  
exec' _ [] _ 
 = 0
exec' prog (("load", var, num) : partial) memf 
 = exec' prog partial (modify var num memf)
exec' prog (("add", var, num): partial) memf
 = exec' prog partial (modify var (num+memf var)  memf)
exec' prog (("jmp", var, num): partial) memf 
 = exec' prog new memf
 where new = drop num prog
exec' prog (("blz", var, num): partial) memf
 = if (memf var) <= 0
 then exec' prog new memf 
 else exec' prog partial memf
 where new = drop num prog
exec' prog (("ret", var, num): partial) memf 
 = memf var

-- test_exec' calls exec' as in the previous assignment
-- The only difference is that all variables are should be set to zero
test_exec' :: [Inst] -> Int
test_exec' prog -- = 0
 = exec' prog prog (\z -> 0)

prog1 :: [Inst]
prog1 = [("load","x",4),("load","y",5),("load","z",0),
         ("blz","y",7),("add","z",1),("add","y",(-1)),("jmp","",3),
         ("blz","x",11),("add","z",1),("add","x",(-1)),("jmp","",7),("ret","z",0)]

-- Question 7 ------------------------------------------------------------         
-- search takes the following parameters
--   1. A function to check if the search is done
--     - this function takes:
--       a. the global information for the problem
--       b. the partial solution
--     - the function returns a bool indicating if solution is complete
--   2. A function to find the valid next states to go to
--     - this function takes:
--       a. the global information for the problem
--       b. a partial solution
--     - the funtion returns a list of valid next states
--   3. Global information for the problem
--   4. A partial solution
--     - a partial solution is a list of states in reverse
-- 
-- search returns a list of all full solutions reachable from
--   the partial solution
--     - full solutions will be in forward order
search :: (Show a, Show b) =>
  (a -> [b] -> Bool) -> (a -> [b] -> [b]) -> a -> [b] -> [[b]]
search isDone nextStates global partial
  | isDone global partial   = [reverse partial]
  | otherwise               = concat [ search isDone nextStates global (newpos:partial) |
                                       newpos <- (nextStates global partial)]

-- Global maze information includes:
--   1. Size of the maze
--   2. List of blocked cells
--   3. End of the maze
type Cell = (Int,Int)
type MazeSolution = [Cell]
type MazeGlobal = (Int,[Cell],Cell)

mazeDone :: MazeGlobal -> MazeSolution -> Bool
mazeDone (_,_,end) (cur:_) = end == cur

mazeNext :: MazeGlobal -> MazeSolution -> [Cell]
mazeNext (size,blocked,_) ((x,y):rest)
  =  filter (`notElem` rest) $
     filter (legalMove size blocked)
       [(x+1,y),(x-1,y),(x,y+1),(x,y-1)]

legalMove :: Int -> [Cell] -> Cell -> Bool
legalMove size blocked (x,y)
  = notElem (x,y) blocked && x <= size && y <= size && x >=1 && y >= 1

blocks1 :: [(Int,Int)]
blocks1 = [(1,3),(2,1),(2,5),(3,1),(3,2),(3,3),(3,4),(3,5),(5,6),(2,6)]

blocks2 :: [(Int,Int)]
blocks2 = [(1,3),(2,1),(2,5),(3,1),(3,2),(3,3),(3,4),(3,5),(5,6)]

-- geography takes as arguments two lists of words, A and B.
-- It returns a list of all words C with the following properties:
-- 1. B is a suffix of C.
-- 2. Every word in C, except the first, must have the same last letter
--      as the first letter of the word before it.
-- 3. C contains all the words of A but no other words.  
-- You can assume the following:
-- 1. B has property 2.
-- 2. All the words in B are in A.
-- 3. A has no duplicate words.
-- 4. B has no duplicate words.
geogDone :: [String] -> [String] -> Bool
geogDone geogGlobal geogPartial 
 = if(length geogGlobal == length geogPartial)
   then True
   else False

geogNext :: [String] -> [String] -> [String]
geogNext geogGlobal (current:geogPartial) 
 = [x | x <- geogGlobal, head x == last current, notElem x (current:geogPartial)]

wl1 :: [String]
wl1 = ["ant","tiger","elephant","tree"]

wl2 :: [String]
wl2 = ["ab","ba","acb","bca","aa"]