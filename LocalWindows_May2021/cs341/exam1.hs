newpair :: [(Int,Int)] -> [(Int,Int)]
newpair list = 
    [(x,y) | (x,y) <-list]

--eveninsec :: [Int] -> [Int] -> Bool
--eveninsec list1 list2 = 
--if [(x,y) | x <- list1, y == list2, x==y]
--then True
--else False

--rmheaddup :: [string] -> [string]
--rmheaddup list =
--    [tail(x) | x <- list, rmheaddupHelp(x) == True]

--rmheaddupHelp :: [Char] -> Bool
--rmheaddupHelp x =
--    if (head(x)) == (head(tail(x)))
--    then True
--    else False

--squareorhalf :: [Int] -> [Int]
--squareorhalf list= 
--    [x*x | x <- list, (x `mod` 2) - 1 == 0; x `div` 2 | x <- list, x `mod` 2 == 0]

--countbigfirst :: [(Int,Int)] -> Int
--countbigfirst list =
--    countbigfirstHelp(list, 0, 0)

--countbigfirstHelp :: [(Int,Int)] -> Int -> Int -> Int
--countbigfirstHelp list c t=
--    if c < length(list)
--    then if not null [(x,y) | (x,y) <- list, x > y]
--         then countbigfirstHelp(list, c+1, t+1)
--        else countbigfirstHelp(list, c+1, t+1)
--    else return t

--firstdif :: string -> string -> Char
--firstdif s1 s2 =
    


--firstnotsec 


--weirdseq 

--Gonna be honest, I thought the test was next week, started late after I saw the email and havent studied yet
--I, Paul Schmid, did not discuss this exam with anyone, or look things up on the internet