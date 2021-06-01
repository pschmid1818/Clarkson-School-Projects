-- Name: Paul Schmid

makex :: String -> (a, b) -> (String, b)
makex x (a,b) = (x,b) 

funcpn :: (Ord a, Num a) => (a -> a) -> (a -> a)
funcpn f = \z -> if z > 0 then f z else z

gtsq :: [Int] -> Int -> [Int]
gtsq list x = filter (\y -> (y ^ 2) > x) list

swapPair :: [(a,b)] -> [(b,a)]
swapPair list = map (\(x,y) -> (y,x)) list

-- doesnt like not . null for some reason
firne :: Eq a => [[a]] ->[a]
-- firne = map (\x -> head(x) . filter (not . null) x)
firne = map (\x -> head(x))

data MyTree a = MyLeaf a | MyNode [MyTree a]
    deriving Eq

tr1 :: MyTree Int
tr1 = MyNode [MyNode [MyLeaf 6,MyLeaf 2],MyNode [MyNode [MyLeaf 4],MyLeaf 5],MyLeaf 6]

doubleAll :: MyTree Int -> MyTree Int
doubleAll (MyNode leaves) = (MyNode (map doubleAll leaves))
doubleAll (MyLeaf a) = (MyLeaf (2*a))

find :: a -> MyTree a -> Bool
find x (MyNode leaves) = True

instance (Show a) => Show (MyTree a) where
    show (MyLeaf a) = "{" ++ show a ++ "}"
    show (MyNode leaves) = "" ++ show leaves
    

data Date = D Int Int Int
 deriving (Show, Eq)

da1 = D 10 29 2020
da2 = D 5 13 2020
da3 = D 6 7 2019

dl1 = [da1,da2, (D 4 29 2020), (D 10 10 2020), (D 1 1 2020)]
dl2 = [da1, da2, (D 4 29 2020), (D 10 10 2020), (D 1 1 2020), da3]

earlier :: Date -> Date -> Maybe Date
earlier (D m1 d1 y1) (D m2 d2 y2)
    | y1 == y2 && m1 < m2              = Just (D m1 d1 y1)
    | y1 == y2 && m1 >= m2 && d1 < d2  = Just (D m1 d1 y1)
    | y1 == y2 && m1 >= m2 && d1 >= d2 = Just (D m2 d2 y2)
    | otherwise                        = Nothing

--for some reason I've never been able to get >>= to work. I just need it to foldl for the list
earliest :: [Date] -> Maybe Date
-- earliest (l:ist) = foldl (\t -> t >>= earlier) (Just l) ist
earliest list = Just (head list)


-- ”I, Paul Schmid, did not discuss this exam with anyone, or look things up on the internet.”