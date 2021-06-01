import Debug.Trace
import Data.Char
import Text.ParserCombinators.ReadP
import Data.List.Split

parse :: ReadP a -> String -> a
parse p s 
    | null parses        = error "There is no parses"
    | length parses > 2 = error "There is more than one parse"
    | otherwise          = head parses
        where parses = [x | (x,"") <- readP_to_S p s]

parsews :: ReadP a -> String -> a
parsews p s = parse p [c | c <- s, not (isSpace c)]

data Expression = Plus Expression Expression |
                  Minus Expression Expression |
                  Times Expression Expression |
                  Divide Expression Expression |
                  Var String |
                  Num Int
  deriving Show

num :: ReadP Expression
num = do 
  x <- munch1 isDigit
  let n = read x :: Int
  return $ Num n

var :: ReadP Expression
var = do 
  s <- munch1 isAlpha
  return $ Var s

makeExp :: Char -> Expression -> Expression -> Expression
makeExp '+' e1 e2 = Plus e1 e2
makeExp '-' e1 e2 = Minus e1 e2
makeExp '*' e1 e2 = Times e1 e2
makeExp '/' e1 e2 = Divide e1 e2


expr :: ReadP Expression
expr = complex <++ var <++ num

complex :: ReadP Expression
complex = do 
    char '('
    e1 <- expr
    op <- char '+' <++ char '-' <++ char '*' <++ char '/'
    e2 <- expr
    char ')'
    return $ makeExp op e1 e2


type Memory = [(String,Int)]

eval :: Expression -> Memory -> Int
eval (Num n) _ = n
eval (Plus e1 e2) mem = eval e1 mem + eval e2 mem
eval (Minus e1 e2) mem = eval e1 mem - eval e2 mem
eval (Times e1 e2) mem = eval e1 mem * eval e2 mem
eval (Divide e1 e2) mem = eval e1 mem  `div` eval e2 mem
eval (Var v) mem
  | answer == Nothing     = error $ v ++ " is not assigned"
  | otherwise            = val
    where answer = lookup v mem 
          Just val = answer

run :: String -> Memory -> Int
run s m = eval (parsews exprn s) m

-- To read no parenthesis

-- handle + and -
exprn :: ReadP Expression
exprn = chainl1 factor plus

plus :: ReadP (Expression -> Expression -> Expression)
plus = do
    op <- char '+' <++ char '-'
    return $ makeExp op

-- handle * and /
factor :: ReadP Expression
factor = chainl1 base times

times :: ReadP (Expression -> Expression -> Expression)
times = do
    op <- char '*' <++ char '/'
    return $ makeExp op

-- handles Variables and Numbers
base :: ReadP Expression
base = num +++ var +++ parens

parens = do
    char '('
    e <- expr
    char ')'
    return e