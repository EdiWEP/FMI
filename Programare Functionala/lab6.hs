import Data.Char
import Data.List
import Data.Tuple


-- 1.
rotate :: Int -> [Char] -> [Char]
rotate n list
    | n > leng || n < 0 = error "bad n"
    | otherwise =  (drop n list) ++ (take n list) 
    where leng = length list

-- 2.
-- functia prop_rotate testeaza daca functioneaza corect functia rotate
-- prin a roti sirul str, apoi a inversa rotirea prin (rotate l-m)
-- si a verifica daca rezultatul este echivalent cu sirul initial(fiindca asa ar trebui sa fie)
-- Evita eroarea prin a "trunchia" oarecum numarul dat k la un numar care este in modulo length str
-- `mod` returnand intotdeauna un nou k (m) pozitiv < length str
prop_rotate :: Int -> String -> Bool
prop_rotate k str = rotate (l - m) (rotate m str) == str
                        where l = length str
                              m = if l == 0 then 0 else k `mod` l

-- 3.
makeKey :: Int -> [(Char, Char)]
makeKey k = zip ['A'..'Z'] (rotate k ['A'..'Z']) 

-- 4.
lookUp :: Char -> [(Char, Char)] -> Char
lookUp chr tups 
    | length x > 0 = snd (head x) 
    | otherwise = chr 
    where x = filter (\(a,b) -> chr == a) tups

-- 5.
encipher :: Int -> Char -> Char
--encipher k chr = lookUp chr (makeKey k)
encipher k chr 
    | x `elem` ['A'..'Z'] && chr `elem` ['A'..'Z'] = x
    | x `elem` ['a'..'z'] && chr `elem` ['a'..'z'] = x 
    | otherwise = toEnum( fromEnum x -26) 
    where x = toEnum (fromEnum chr + (k`mod`26 )) ::Char


-- 6.
normalize :: String -> String
--normalize str = map (\x -> if x `elem` ['a'..'z'] then toUpper x else x) (filter isAlphaNum str)
normalize str = map toUpper (filter isAlphaNum str) 

-- 7.
encipherStr :: Int -> String -> String
encipherStr k str = map (encipher k) (normalize str)

-- 8.
reverseKey :: [(Char, Char)] -> [(Char, Char)]
reverseKey = map swap
--reverseKey = map (\(a,b) -> (b,a))

-- 9.
decipher :: Int -> Char -> Char
decipher k = encipher (26-k)  

decipherStr :: Int -> String -> String
decipherStr k str = map (\x -> if x `elem` ['A'..'Z'] then decipher k x else x) 
                                (filter (\x ->( x == ' ' || isAlphaNum x ) && x `notElem` ['a'..'z']) str) 
                        
