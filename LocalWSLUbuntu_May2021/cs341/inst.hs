import Data.Char
-- import Text.ParserCominators.Readp

instM :: Ord a => a -> [a] -> Maybe [a]
instM x [] = Just [x]
instM x (y:ys)
    | x == y = Nothing
    | x < y  = Just (x:y:ys)
    | x > y  = do
      zs <- instM x ys
      return (y:zs)

instAllListM :: Ord a => [a] -> Maybe [a]
instAllListM xs = foldl (\t x -> t >>= instM x) (Just []) xs

{-
instM :: Ord a => a -> [a] -> Maybe [a]
instM x [] = Just [x]
instM x (y:ys)
  | x == y     = Nothing
  | x < y      = Just (x:y:ys)
  | x > y      = do
    zs <- instM x ys
    return (y:zs)
    
instAllListM :: Ord a => [a] -> Maybe [a]
instAllListM xs = foldl (\t x  -> t >>= instM x) (Just []) xs
-}
