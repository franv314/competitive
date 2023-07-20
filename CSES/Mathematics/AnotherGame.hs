solveTC :: [Int] -> IO ()
solveTC stacks
    | all even stacks = putStrLn "second"
    | otherwise = putStrLn "first"

solve :: Int -> IO ()
solve 0 = return ()
solve n = getLine >> getLine >>= (solveTC . (map read) . words) >> solve (n - 1)

main :: IO ()
main = getLine >>= (solve . read)