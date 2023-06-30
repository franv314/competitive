solve :: [Int] -> Int
solve = foldr lcm 1

loop :: Int -> Int -> IO ()
loop t b
    | t > b = return ()
    | otherwise = do
        getLine
        getLine
        a <- getLine
        putStrLn ("Case #" ++ show t ++ ": " ++ show (solve (map read (words a))))
        loop (t + 1) b 

main :: IO ()
main = getLine >>= (loop 1 . read)