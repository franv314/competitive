solve :: Int -> Int -> Int
solve m n
    | curr == 0 = 0
    | otherwise = curr + solve (m * 5) n
        where curr = n `div` m

main :: IO ()
main = getLine >>= (print . solve 5 . read)