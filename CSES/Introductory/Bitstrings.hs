m :: Integer
m = 1000000007

solve :: Integer -> Integer
solve n
    | n == 0 = 1
    | even n = temp * temp `mod` m
    | otherwise = 2 * temp * temp `mod` m
        where temp = solve (n `div` 2)

main :: IO ()
main = getLine >>= (print . solve . read)