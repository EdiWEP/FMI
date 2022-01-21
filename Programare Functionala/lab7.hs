
data Fruct = Mar String Bool | Portocala String Int

ePortocalaDeSicilia :: Fruct -> Bool
ePortocalaDeSicilia (Portocala x _) = x `elem` ["Tarocco", "Moro", "Sanguinello"]
ePortocalaDeSicilia (Mar _ _) = False

nrFeliiSicilia :: [Fruct] -> Int
nrFeliiSicilia fructs =  sum (map (\(Portocala _ y) -> y) (filter ePortocalaDeSicilia fructs) )

isMar :: Fruct -> Bool
isMar (Mar _ _) = True
isMar (Portocala _ _) = False

nrMereViermi :: [Fruct] -> Int
nrMereViermi fructs = length ( filter (\(Mar _ y) -> y) (filter isMar fructs ) )

type NumeA = String
type Rasa = String
data Animal = Pisica NumeA | Caine NumeA Rasa
    deriving Show

vorbeste :: Animal -> String
vorbeste (Pisica _) = "Meow!"
vorbeste (Caine _ _) = "Woof!"

rasa :: Animal -> Maybe String
rasa (Pisica _) = Nothing
rasa (Caine _ r) = Just r


data Linie = L [Int]

data Matrice = M [Linie]

verifica :: Matrice -> Int -> Bool
verifica (M linii) k = foldr (\(L xs) acc -> acc && (sum xs == k) ) True linii

test_veri1 = verifica (M[L[1,2,3], L[4,5], L[2,3,6,8], L[8,5,3]]) 10 == False
test_verif2 = verifica (M[L[2,20,3], L[4,21], L[2,3,6,8,6], L[8,5,3,9]]) 25 == True

doarPozN :: Matrice -> Int -> Bool
doarPozN (M linii) k = foldr (\(L linie) acc -> acc && ( foldr (\x acc -> acc && (x > 0)) True linie) ) True ( filter (\(L xs) -> length xs == k) linii )

testPoz1 = doarPozN (M [L[1,2,3], L[4,5], L[2,3,6,8], L[8,5,3]]) 3 == True
testPoz2 = doarPozN (M [L[1,2,-3], L[4,5], L[2,3,6,8], L[8,5,3]]) 3 == False


corect :: Matrice -> Bool
corect (M linii) = let
     L primaLinie = head linii
     lungime = length primaLinie
     raspuns = foldr (\(L linie) acc -> acc && lungime == length linie ) True linii
     in raspuns
testcorect1 = corect (M[L[1,2,3], L[4,5], L[2,3,6,8], L[8,5,3]]) == False
testcorect2 = corect (M[L[1,2,3], L[4,5,8], L[3,6,8], L[8,5,3]]) == True

instance Show Linie where
     show (L []) = ""
     show (L linie) = foldl (\acc x -> acc ++ show x ++ " ") [] linie

instance Show Matrice where
     show (M linii) = foldl (\acc (L linie) -> acc ++ foldl (\acc x -> acc ++ show x ++ " ") [] linie ++ "\n") [] linii
