module TestQ5 (run,stmt,evalStmt) where
import Debug.Trace
import Data.Char
import Text.ParserCombinators.ReadP
import Data.List.Split

parse :: ReadP a -> String -> a
parse p s 
    | null parses        = error "There is no parses"
    | length parses > 2  = error "There is more than one parse"
    | otherwise          = head parses
        where parses = [x | (x,"") <- readP_to_S p s]

parsews :: ReadP a -> String -> a
parsews p s = parse p [c | c <- s, not (isSpace c)]

{-
A statement is one of the following
  1. An if-else statement
     When we read it in, it is of the form:
       if (condition) statement else statement
  2. A while statement
     When we read it in, it is of the form:
       while (condition) statement
  3. An assignment statement
     When we read it in, it is of the form:
       variable = expression;
  4. A block of statements
     When we read it in, it is of the form:
       { statement statement ... statement }
     with zero or more statements in curly brackets
  5. A declaration of a variable
     When we read it in, it is of the form:
       int variable;
     so the only data type is integer
     A variable is initialized as zero when declared
     A variable is made up entirely of letters
-}
data Statement = IfElse Condition Statement Statement |
                 While Condition Statement |
                 Assign Expression Expression |
                 Block [Statement] |
                 Declare Expression
  deriving Show

-- declare like (IfElse (>= x y) [] [])
--              (While (>= x y) [])
--              (Assign x 5)
--              (Block [])
--              (Declare x)

{-
A condition is read in as one of the following forms:
  1. expression < expression
  2. expression > expression
  3. expression <= expression
  4. expression >= expression
  5. expression == expression
  6. expression != expression
  7. condition && condition
  8. condition || condition
  9. ! condition
Note:  Comparison operators have th highest precedence
  followed by "!", followed by "&&" followed by "||"
-}
data Condition = Less Expression Expression |
                 Greater Expression Expression |
                 LessEq Expression Expression |
                 GreaterEq Expression Expression |
                 Equal Expression Expression |
                 NotEqual Expression Expression |
                 And Condition Condition |
                 Or Condition Condition |
                 Not Condition
  deriving Show

-- Creates conditions >, <, =, >=, <=, and !=
makeCon :: String -> Expression -> Expression -> Condition
makeCon "==" e1 e2 = Equal e1 e2
makeCon ">" e1 e2 = Greater e1 e2
makeCon "<" e1 e2 = Less e1 e2
makeCon ">=" e1 e2 = GreaterEq e1 e2
makeCon "<=" e1 e2 = LessEq e1 e2
makeCon "!=" e1 e2 = NotEqual e1 e2

-- Creates conditions && and ||
makeConAO :: String -> Condition -> Condition -> Condition
makeConAO "&&" c1 c2 = And c1 c2
makeConAO "||" c1 c2 = Or c1 c2 

-- Creates condtion !
makeConN :: Char -> Condition -> Condition
makeConN '!' c = Not c

{-
An expression is read in as one of the folowing forms:
  1. expression + expression
  2. expression - expression
  3. expression * expression
  4. expression / expression
  5. variable
  6. number
Note:  "*" and "/" have precedence over "+" and "-"
-}
data Expression = Plus Expression Expression |
                  Minus Expression Expression |
                  Times Expression Expression |
                  Divide Expression Expression |
                  Var String |
                  Num Int
  deriving Show

-- Creates Numbers
num :: ReadP Expression
num = do 
  x <- munch1 isDigit
  let n = read x :: Int
  return $ Num n

-- Creates Variables
var :: ReadP Expression
var = do 
  s <- munch1 isAlpha
  return $ Var s

-- Creates Expressions for +, -, *, and /
makeExp :: Char -> Expression -> Expression -> Expression
makeExp '+' e1 e2 = Plus e1 e2
makeExp '-' e1 e2 = Minus e1 e2
makeExp '*' e1 e2 = Times e1 e2
makeExp '/' e1 e2 = Divide e1 e2

{-
Memory is a set of pairs consisting of
  - a variable
  - the current value of that variable
Variables could be duplicated in memory
  then I will assume the first occurrence
  of a variable gives the current value
-}
type Memory = [(String,Int)]



-- Question 1 --------------------------------------------------------------------------
{-
This function will parse your input and run the program
A program is a list of statements surrounded by curly brackets
  in other words, a program is a statement
When you run your program, initially the memory is empty
This function will return the memory when the program is completed
-}
run :: String -> Memory
-- fill in your code here
run p = runHelper p []

runHelper :: String -> Memory -> Memory
runHelper p mem = evalStmt (parsews stmt p) mem


-- Question 2 ---------------------------------------------------------------------------
{-
To evaluate a statement you give
  1. the statement
  2. the current memory
It returns the memory after the statement is executed
-}
evalStmt :: Statement -> Memory -> Memory 
evalStmt (IfElse c s1 s2) mem = if (evalCond c mem) then evalStmt s1 mem else evalStmt s2 mem
evalStmt (While c s) mem = if (evalCond c mem) then evalStmt s mem else evalStmt s mem
evalStmt (Assign (Var e1) e2) mem 
  | answer == Nothing     = error $ e1 ++ " is not assigned"
  | otherwise             = (e1, evalExp e2 mem):mem
    where answer = lookup e1 mem 
          Just val = answer
evalStmt (Block []) mem = mem
evalStmt (Block (s:ss)) mem = evalStmt (Block ss) (evalStmt s mem)
evalStmt (Declare (Var e)) mem = (e, 0):mem

-- Question 3 ---------------------------------------------------------------------------
{-
To evaluate a condition you give
  1. the condition
  2. the current memory
It returns a bool indicating if the condition is true
-}
evalCond :: Condition -> Memory -> Bool
evalCond (Equal e1 e2) mem = (evalExp e1 mem) == (evalExp e2 mem)
evalCond (Greater e1 e2) mem = (evalExp e1 mem) > (evalExp e2 mem)
evalCond (Less e1 e2) mem = (evalExp e1 mem) < (evalExp e2 mem)
evalCond (GreaterEq e1 e2) mem = (evalExp e1 mem) >= (evalExp e2 mem)
evalCond (LessEq e1 e2) mem = (evalExp e1 mem) <= (evalExp e2 mem)
evalCond (NotEqual e1 e2) mem = (evalExp e1 mem) /= (evalExp e2 mem)
evalCond (And c1 c2) mem = (evalCond c1 mem) && (evalCond c2 mem)
evalCond (Or c1 c2) mem = (evalCond c1 mem) || (evalCond c2 mem)
evalCond (Not c) mem = not (evalCond c mem)

-- Question 4 ---------------------------------------------------------------------------
{-
To evaluate an expression you give
  1. the expression
  2. the current memory
It returns the value of the expression
-}
evalExp :: Expression -> Memory -> Int
evalExp (Num n) _ = n
evalExp (Plus e1 e2) mem = evalExp e1 mem + evalExp e2 mem
evalExp (Minus e1 e2) mem = evalExp e1 mem - evalExp e2 mem
evalExp (Times e1 e2) mem = evalExp e1 mem * evalExp e2 mem
evalExp (Divide e1 e2) mem = evalExp e1 mem  `div` evalExp e2 mem
evalExp (Var v) mem
  | answer == Nothing     = error $ v ++ " is not assigned"
  | otherwise             = val
    where answer = lookup v mem 
          Just val = answer


-- Question 5 ---------------------------------------------------------------------------
-- This parses a statement and stores the result
stmt :: ReadP Statement
stmt = ifelse +++ while +++ assign +++ block +++ declare

ifelse :: ReadP Statement
ifelse = do
    string "if"
    c <- cond
    s1 <- stmt
    string "else"
    s2 <- stmt
    return $ IfElse c s1 s2

while :: ReadP Statement
while = do
      string "while"
      c <- cond
      s <- stmt
      return $ While c s

assign :: ReadP Statement
assign = do
      e1 <- expr
      char '='
      e2 <- expr
      string ";"
      return $ Assign e1 e2

block :: ReadP Statement
block = do
      string "{"
      s <- many stmt
      string "}"
      return $ Block s

declare :: ReadP Statement
declare = do
      string "int"
      e <- expr
      string ";"
      return $ Declare e

-- Question 6 --------------------------------------------------------------------------
-- This parses a condition and stores the result
cond :: ReadP Condition
cond = chainl1 rest gate

rest :: ReadP Condition
rest = comp <++ no <++ parensCon 


comp :: ReadP Condition
comp = do
      e1 <- expr
      con <- string "==" <++ string ">" <++ string "<" <++ string "!=" <++ string ">=" <++ string "<="
      e2 <- expr
      return $ makeCon con e1 e2

gate :: ReadP (Condition -> Condition -> Condition)
gate = do
    con <- string "&&" <++ string "||"
    return $ makeConAO con

no :: ReadP Condition
no = do 
    con <- char '!'
    c <- cond
    return $ makeConN con c

parensCon :: ReadP Condition
parensCon = do
          string "("
          c <- cond
          string ")"
          return c

-- Question 7 ---------------------------------------------------------------------------
-- This parses an exprssion and stores the result
expr :: ReadP Expression
expr = chainl1 factor plus

plus :: ReadP (Expression -> Expression -> Expression)
plus = do
    op <- char '+' <++ char '-'
    return $ makeExp op

factor :: ReadP Expression
factor = chainl1 base times

times :: ReadP (Expression -> Expression -> Expression)
times = do
    op <- char '*' <++ char '/'
    return $ makeExp op

base :: ReadP Expression
base = num +++ var +++ parens

parens = do
    char '('
    e <- exprp
    char ')'
    return e

exprp :: ReadP Expression
exprp = complex <++ var <++ num

complex :: ReadP Expression
complex = do 
    char '('
    e1 <- expr
    op <- char '+' <++ char '-' <++ char '*' <++ char '/'
    e2 <- expr
    char ')'
    return $ makeExp op e1 e2

