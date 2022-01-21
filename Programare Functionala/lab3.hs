import Data.Char

ePalindrom :: String -> Bool
ePalindrom str =  str == reverse str 

countVocale :: String -> Int
countVocale str 
    | length str == 0 = 0
    | (head str) `elem` vocals = 1 + countVocale (tail str)
    | otherwise = countVocale (tail str)
    where vocals = "aeiou"

nrVocale:: [String] -> Int
nrVocale lista 
    | length lista == 0 = 0
    | ePalindrom (head lista) = countVocale (head lista) + nrVocale (tail lista)
    | otherwise = nrVocale (tail lista)


insertNumber :: Int -> [Int] -> [Int]
insertNumber num lista 
    | null lista = []
    | even (head lista) = (head lista):num:insertNumber num (tail lista)
    | otherwise = (head lista):insertNumber num (tail lista)


divizori :: Int -> [Int]
divizori x = [y | y <- [1..x], x `mod` y == 0]


listadiv :: [Int] -> [[Int]]
listadiv xs = [divizori y | y <- xs]


inIntervalRec :: Int -> Int -> [Int] -> [Int]
inIntervalRec a b xs 
    | null xs = []
    | head xs `elem` [a..b] = (head xs):inIntervalRec a b(tail xs)
    | otherwise = inIntervalRec a b (tail xs) 


inIntervalComp :: Int -> Int -> [Int] -> [Int]
inIntervalComp a b xs = [y | y <- xs, y >= a && y <= b]


pozitiveRec :: [Int] -> Int 
pozitiveRec xs 
    | null xs = 0
    | head xs >= 0 = 1 + pozitiveRec (tail xs)
    | otherwise = pozitiveRec (tail xs)

pozitiveComp :: [Int] -> Int 
pozitiveComp xs = length [x | x <- xs, x >= 0]


impareHelper :: Int -> [Int] -> [Int]
impareHelper i xs 
    | null xs = []
    | odd (head xs) = i:impareHelper (i+1) (tail xs)
    | otherwise = impareHelper (i+1) (tail xs)


pozitiiImpareRec :: [Int] -> [Int]
pozitiiImpareRec xs = impareHelper 0 xs


pozitiiImpareComp :: [Int] -> [Int]
pozitiiImpareComp xs = [ b | (a,b) <- zip xs [0..length xs -1], odd a]



multDigitsRec :: [Char] -> Int 
multDigitsRec str 
    | null str = 1
    | isDigit(head str) = digitToInt (head str) * multDigitsRec (tail str)
    | otherwise = multDigitsRec (tail str)


multDigitsComp :: [Char] -> Int 
multDigitsComp str 
    | null xs = 1
    | otherwise = product xs
    where xs = [digitToInt x | x <- str, isDigit x]