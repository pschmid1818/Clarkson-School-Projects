module TestQ1 (pairFirst,encryptChar,encryptString,howManyValues,numInvalid,distinctMap,ownInverse,subset,allMapped,mapLetters) where

-- Code is a type synonym
-- it says that a Code is a list of Pairs of Chars
type Code = [(Char,Char)]

-- domain of our code
domain1 :: [Char]
domain1 = ['a'..'z']
domain2 = ['a','b','a']

-- associated range
range1 :: [Char]
range1 = ['z','y'..'a']
range2 = ['a','c','c']

-- Turns two strings into a code
makeCode :: [Char] -> [Char] -> Code
makeCode domain range = zip domain range

-- create a code out of our domain and range
-- I will call each pair a mapping from the first element of the pair to the second
code1 :: Code
code1 = makeCode domain1 range1
code2 = makeCode domain2 range2




-- Question 1 ------------------------------------------------------------------------ 
-- pairFirst takes a Code and Char
-- returns the list of all Pairs which have that Char as first element
pairFirst :: Code -> Char -> Code
pairFirst code ch 
 = [(a,b) | (a,b) <- code, a == ch]


-- Question 2 ------------------------------------------------------------------------
-- uses a code to encrypt a Char
-- if the Char has no mapping then the Char encrypts as itself
-- if more than one mapping just use the first value
encryptChar :: Code -> Char -> Char 
encryptChar code ch 
 = if null [b | (a,b) <- code, a == ch]
   then ch
   else head [b | (a,b) <- code, a == ch]


-- Question 3 ------------------------------------------------------------------------
-- uses a Code to encrypt a String
encryptString :: Code -> String -> String
encryptString code chars 
  = [encryptChar code x | x <- chars]
  

-- Question 4 ------------------------------------------------------------------------
-- takes a Code and returns the number of elements a Char is mapped to in that Code
howManyValues :: Code -> Char -> Int
howManyValues code ch 
 = length [(a,b) | (a,b) <- code, a == ch]


-- Question 5 
-- takes a Code and returns the number of small letters mapped to more than one element
numInvalid :: Code -> Int
numInvalid code
 = negate (sum [invalidHelper code x | x <- ['a'..'z']] `div` 2 + sum [howManyValues code x | x <- ['a'..'z']] `div` 2 - length code)

invalidHelper :: Code -> Char -> Int
invalidHelper code ch
 = length [(a,b) | (a,b) <- code, b == ch]

-- Question 6 ------------------------------------------------------------------------
-- takes a Code and returns True if no Char maps to itself
distinctMap :: Code -> Bool
distinctMap code 
 = null [(a,b) | (a,b) <- code, a == b]


-- Question 7 ------------------------------------------------------------------------
-- checks that whenever you encrypt a small letter twice you get the original letter back
ownInverse :: Code -> Bool
ownInverse code 
 = if [encryptChar code a | a <- [encryptChar code a | a <- ['a'..'z']]] == [ a | a <- ['a'..'z']]
   then True
   else False


-- Question 8 ------------------------------------------------------------------------
-- checks if everything in first String is contained in second String
subset :: String -> String -> Bool 
subset s1 s2 
 = null [a | a <- s1, elem a s2 == False]
   

-- Question 9 ------------------------------------------------------------------------
-- checks if every small letter is the first element of a pair in Code
allMapped :: Code -> Bool
allMapped code 
 = if length [a | (a,b) <- code, elem a "abcdefghijklmnopqrstuvwxyz"] == 26
   then True
   else False


-- Question 10 ------------------------------------------------------------------------
-- checks if everything in Code maps to a small letter
mapLetters :: Code -> Bool
mapLetters code 
 = null [a | (a,b) <- code, elem a "ABCDEFGHIJKLMNOPQRSTUVWXYZ"]
