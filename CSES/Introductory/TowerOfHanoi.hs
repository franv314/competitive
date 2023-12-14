recur :: (Int, Int, Int) -> IO ()
recur (0, _, _) = return ()
recur (n, a, b) = recur (n - 1, a, 6 - a - b) >> putStrLn (show a ++ " " ++ show b) >> recur (n - 1, 6 - a - b, b)

solve :: Int -> IO ()
solve n = print (2 ^ n - 1) >> recur (n, 1, 3)

main :: IO ()
main = getLine >>= (solve . read)