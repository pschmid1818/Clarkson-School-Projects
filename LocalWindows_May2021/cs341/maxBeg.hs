-- maxBeg :: [int] -> int
maxBeg list
 = if length list == 0
   then 0
   else if length list == 1
        then head list
        else max (head list) (head(tail list))