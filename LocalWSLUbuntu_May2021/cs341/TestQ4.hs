--Due Date: 2017-11-02 23:59:59.999999

module TestQ4 (BinaryTree(..),inOrderSearch,insertm,insList,findm,Employee(..),getSalary,addEmployee,sumSalary) where

import Debug.Trace
import Data.Maybe

-- Part 1 =========================================================================
{-
A BinaryTree is either a Leaf or a Node.  A Node contains a key,
a value, a left subtree and a right subtree.

This structure will hold a binary search tree, where the keys are
compared when inserting items.  In other words, all nodes in the
left subtree of a node n have a smaller key than n, and all nodes 
in the right subtree have a larger key than n.  Note this means 
that there can be no duplicate keys in a tree.
-}
data BinaryTree a b = Leaf | Node a b (BinaryTree a b) (BinaryTree a b) 

-- Sample BinaryTrees
t1 ::  BinaryTree Int String
t1 = Leaf
t2 ::  BinaryTree Int String
t2 = Node 20 "abc" Leaf Leaf
t3 ::  BinaryTree Int String
t3 = Node 20 "abc" Leaf (Node 30 "def" Leaf Leaf)
t4 ::  BinaryTree Int String
t4 = Node 20 "abc" (Node 10 "ghi" Leaf Leaf) (Node 30 "def" Leaf Leaf)
t5 ::  BinaryTree Int String
t5 = Node 10 "ghi" Leaf (Node 30 "def" (Node 20 "abc" Leaf Leaf) Leaf)
t6 ::  BinaryTree Int String
t6 = Node 10 "jkl" Leaf (Node 20 "mno" Leaf (Node 30 "pqr" Leaf Leaf))

-- Question 1 ---------------------------------------------------------------------
{-
BinaryTree is an instance of Show. A Binary Tree is shown as follows:
  - A Leaf appears as a dollar sign.
  - A Node appears as the key and value in parentheses, separated by a colon
    followed by "<", followed by the left subtree, followed by a comma,
    followed by the right subtree, followed by ">".
  - As a special case, a Node with no children just appears as the
    key and value in parentheses, separated by a colon.
    ^^^ I should've just thought harder... thats on me
-}
instance (Show a, Show b) => Show (BinaryTree a b) where
  show Leaf = "$"
  show (Node _ _ Leaf Leaf) = ""
  show (Node a b n1 n2) = "(" ++ show a ++ ":" ++ show b ++ ")<" ++ show n1 ++ "," ++ show n2 ++ ">"
  

-- Question 2 ---------------------------------------------------------------------
{-
findm takes a key and a Binary Tree.  It returns a Maybe Binary Tree. 
If the key is not in the tree it returns Nothing. 
Otherwise it returns Just the associated value.
-}
findm :: Ord a => a -> BinaryTree a b -> Maybe b
findm _ Leaf
 = Nothing
findm key (Node a b n1 n2)
  | key == a = Just b
  | key < a  = findm key n1
  | key > a  = findm key n2

-- Once I finished insertm I realized this was cleaner but wanted to push forward seeing as it worked, no matter how bad

-- Question 3 ---------------------------------------------------------------------
{-
insertm inserts a key and a value into a BinaryTree.
It returns a Maybe BinaryTree.  If the key is already in the tree,
it returns Nothing.  If the key is not already in the tree, it inserts
it into the proper place and returns Just that BinaryTree.
-}
insertm :: (Ord a, Show a, Show b) =>
  a -> b -> BinaryTree a b -> Maybe (BinaryTree a b)
insertm key str Leaf 
  = Just (Node key str Leaf Leaf)
insertm key str (Node a b n1 n2) 
  | key == a = Nothing
  | key < a  = do new <- insertm key str n1
                  return (Node a b new n2)
  | key > a  = do new <- insertm key str n2 
                  return (Node a b n1 new)


-- Question 4 ---------------------------------------------------------------------
{-
insList take a list of key value pairs and a Maybe Binary Tree
and inserts all those keys value pairs into the Maybe Binary Tree
in order.  If any key appears twice in the list then this whole
process will return Nothing.

Examples:
*TestQ4> insList [(10,"ghi"),(30,"def"),(20,"abc"),(25,"vw")] (Just Leaf)
Just (10:"ghi")<$,(30:"def")<(20:"abc")<$,(25:"vw")>,$>>
*TestQ4> insList [(10,"ghi"),(30,"def"),(10,"abc"),(25,"vw")] (Just Leaf)
Nothing
*TestQ4>
-}
insList :: (Ord a, Show a, Show b) =>
  [(a,b)] -> Maybe(BinaryTree a b) -> Maybe (BinaryTree a b)

insList ((key,val):xs) (Just Leaf)
  = insList xs (insertm key val Leaf)
insList [] (Just (Node a b n1 n2)) 
  = (Just (Node a b n1 n2))
insList ((key,val):xs) (Just (Node a b n1 n2)) 
  = insList xs (insertm key val (Node a b n1 n2))

{-
insList list (Just (Node a b n1 n2)) 
 = foldl (\t (x,y) -> t >>= insertm x y (Node a b n1 n2)) (Just (Node a b n1 n2)) list

insList list (Just Leaf) 
  = foldl (\t (x,y) -> t >>= insertm x y Leaf) (Just (Leaf)) list
-}

-- Question 5 ---------------------------------------------------------------------
{-
inOrderSearch performs an inOrder search of a BinaryTree.
It returns a list of key value pairs out of the tree, such that the left
subtree of a node appears before that node, and the right subtree appears after.
-}
inOrderSearch :: BinaryTree a b -> [(a,b)]
inOrderSearch Leaf
  = []
inOrderSearch (Node a b n1 n2)
  = inOrderSearch n1 ++ [(a,b)] ++ inOrderSearch n2


-- Question 6 ---------------------------------------------------------------------
{-
BinaryTree is an instance of Eq.  Two BinaryTrees are equal if they
contain exactly the same key value pairs.
-}
instance (Eq a, Eq b) => Eq (BinaryTree a b) where
  t1 == t2 = inOrderSearch t1 == inOrderSearch t2




-- Part 2 =========================================================================
{-
Employee is a data structure for an employee of a company.
It contains the person's name, their salary, and a list of
all the employees whom they are the direct boss of.

As a special case, if that employee is not the boss of anybody,
then the list of employees under them will be empty.

Employee is also allowed to have the value Nobody.  That value
will only be used when there is nobody in the company.
-}
data Employee a b = Nobody | Boss a b [Employee a b]
  deriving (Show, Eq)

-- Question 7 ---------------------------------------------------------------------
{-
addEmployee adds an Employee to the company.
It takes a person's name, their salary and their boss.
That person then becomes a new Employee of the company,
working under the specified boss.

If the boss is not working in the company, the function
does not add the new employee.

One exception is that if nobody works at the company, then
the new pereson is added as the only employee, and the boss
parameter is ignored.
-}
addEmployee :: Eq a => a -> b -> a -> Employee a b -> Employee a b
addEmployee name sal _ Nobody = (Boss name sal [])
addEmployee name sal bname (Boss a b others) 
  | bname == a = Boss a b ([Boss name sal []] ++ others)
  | otherwise      = Boss a b (map (addEmployee name sal bname) others)

e1 = addEmployee "ann" 1 "blah" Nobody
e2 = addEmployee "bill" 2 "ann" e1
e3 = addEmployee "chuck" 3 "ann" e2
e4 = addEmployee "dave" 4 "bill" e3

-- Question 8 ---------------------------------------------------------------------
{-
getSalary takes an Employees name n and an Employee e.
It finds the salary of n in the company where Employee
e is the main boss.  If n doesn't work there it returns Nothing,
otherwise it returns Just n's salary.
-}

getSalary :: (Eq a, Eq b) => a -> Employee a b -> (Maybe b)
getSalary _ Nobody = Nothing
getSalary name (Boss a b others)
  | name == a = Just b
  | null([y | y <- (map (getSalary name) others), y /= Nothing]) = Nothing
  | otherwise = head([y | y <- (map (getSalary name) others), y /= Nothing])
 
-- Question 9 ---------------------------------------------------------------------
{-
sumSalary returns the sum of the salaries of everybody working
at the company with the given Employee as the big boss.  If nobody
works at the company, return 0.
-}
sumSalary :: Num b => Employee a b -> b
sumSalary Nobody 
  = 0
sumSalary (Boss a b others)
  = b + (sum(map sumSalary others))

  
