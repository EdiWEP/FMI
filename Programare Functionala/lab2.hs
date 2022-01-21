main = putStrLn "Hello, world!"



poly :: Double -> Double -> Double -> Double -> Double
poly a b c x = a*x^2 + b*x +c


eeny :: Int -> String
eeny a 
    | even a = "eeny"
    | otherwise = "neeny"


fizzbuzzGuards :: Int -> String
fizzbuzzGuards a 
    | a `mod` 15 == 0 = "FizzBuzz"
    | a `mod` 3 == 0 = "Fizz"
    | a `mod` 5 == 0 = "Buzz"
    | otherwise = ""

fizzbuzzIf :: Int -> String
fizzbuzzIf a = if (a `mod` 3 == 0) 
                    then 
                        "Fizz" ++ if ((a `mod` 5) == 0) then "Buzz" else ""
                        
                    else 
                        "" ++ if ((a `mod` 5) == 0) then "Buzz" else ""


tribonacciGuards :: Integer -> Integer
tribonacciGuards a
    | a < 3 = 1
    | a == 3 = 2
    | otherwise = tribonacciGuards (a-1) + tribonacciGuards (a-2) + tribonacciGuards (a-3)
    
                        
tribonacciPatterns :: Integer -> Integer
tribonacciPatterns 1 = 1
tribonacciPatterns 2 = 1
tribonacciPatterns 3 = 2
tribonacciPatterns a = tribonacciPatterns (a-1) + tribonacciPatterns (a-2) + tribonacciPatterns (a-3)


binomial :: Integer -> Integer -> Integer
binomial a 0 = 1
binomial 0 k = 0
binomial a b = binomial (a-1) b + binomial (a-1) (b-1)


verifL :: [Int]-> Bool
verifL xs = ((length xs) `mod` 2 == 0)   

takefinal :: [a] -> Int -> [a]
takefinal xs nr 
    | len < nr = xs
    | otherwise = drop (len - nr) xs
    where len = length xs

-- Pentru a merge ^ pe siruri de caractere putem scrie takefinal:: [a] -> Int -> [a]

remove :: [Int] -> Int -> [Int]
remove xs k = take (k-1) xs ++ drop k xs


myreplicate :: Int -> Int -> [Int]
myreplicate n y 
    | n == 0 = []
    | otherwise = y:t
    where t = myreplicate (n-1) y


sumImp :: [Int] -> Int
sumImp xs = let 
                xxs = [x | x <-xs, x `mod` 2 == 1]
            in sum xxs

sumImpRec :: [Int] -> Int
sumImpRec xs 
    | length xs == 0 = 0
    | otherwise = (if even (head xs) then 0 else head xs) + sumImpRec (tail xs)


totalLen :: [String] -> Int
totalLen xs 
    | length xs == 0 = 0
    | otherwise = (if length (head xs) > 0 && (head (head xs) == 'A') then (length (head xs)) else 0 ) + totalLen (tail xs)

