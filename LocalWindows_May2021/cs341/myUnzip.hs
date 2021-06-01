myUnzip :: [(Int,Int)] -> ([Int],[Int])
myUnzip list = ([a | (a,_) <- list], [b | (_,b) <- list])