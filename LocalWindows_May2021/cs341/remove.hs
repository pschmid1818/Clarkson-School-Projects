remove :: Char -> [Char] -> [Char]
remove ch list 
 = [x | x <- list, x /= ch]