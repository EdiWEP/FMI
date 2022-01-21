main = putStrLn "Hello, world!"

firstEl :: [(a,b)] -> [a]
firstEl = foldr (\x acc -> fst x:acc) []

firstElMap :: [(a,b)] -> [a]
firstElMap = map (\x -> fst x)

sumList :: [[Int]] -> [Int]
sumList = map sum 

prel2 :: [Int] -> [Int]
prel2 = map (\x -> if even x then x `div` 2 else x*2) 

findChar :: Char -> [[Char]] -> [[Char]]
findChar x = filter (x `elem`) 

squareList :: [Int] -> [Int]
squareList xs = map (^2) (filter odd xs) 

squareList2 :: [Int] -> [Int]
squareList2 xs = map (^2) (map fst (filter (\(a,b) -> odd b) ( zip xs [0..])) )

removeConsonants :: [[Char]] -> [[Char]]
removeConsonants = foldr (\y acc -> filter (\c -> c `elem` "aeiouAEIOU") y :acc) [] 

removeConsonantsBetter :: [[Char]] -> [[Char]]
removeConsonantsBetter = map (filter ( `elem` "aeiouAEIOU") ) 

myMap :: (a -> b) -> [a] -> [b]
myMap f [] = []
myMap f (h:t) = f h : myMap f t

myFilter :: (a -> Bool) -> [a] -> [a]
myFilter pred [] = []
myFilter pred (h:t) = if pred h then h:myFilter pred t else myFilter pred t 

sumSquareList :: [Int] -> Int
sumSquareList xs = sum $ squareList xs

allTrue :: [Bool] -> Bool 
allTrue xs = foldr (&&) True xs

rmChar :: Char -> String -> String
rmChar c = filter (/= c)

rmCharsRec :: String -> String -> String 
rmCharsRec [] sir = sir
rmCharsRec (h:t) sir = rmCharsRec t (rmChar h sir) 

rmCharsFold :: String -> String -> String 
rmCharsFold sir1 sir2 = foldr rmChar sir2 sir1