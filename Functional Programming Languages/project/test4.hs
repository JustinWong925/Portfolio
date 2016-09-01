main :: Int -> IO ()
main i = do
          | i > 2 = putStrLn ("This is greater than 2")
          | i < 2 = putStrLn ("This is less than 2")
          | otherwise = putStrLn("this is two")


