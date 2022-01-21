
factori :: Int -> [Int]
factori x = [divizor | divizor <- [1..x], x `mod` divizor == 0]

prim :: Int -> Bool 
prim x =  2 == length (factori x)

numerePrime :: Int -> [Int]
numerePrime n = [prime | prime <- [2..n], prim prime]

myzip3 :: [a] -> [b] -> [c] -> [(a,b,c)]
myzip3 as bs cs = [(as !! index,bs !! index,cs !! index) | index <- [0..(min (min (length as) (length bs)) (length cs)) -1] ]

myzip3r :: [a] -> [b] -> [c] -> [(a,b,c)]
myzip3r [] bs cs = []
myzip3r as [] cs = []
myzip3r as bs [] = []
myzip3r as bs cs = (head as , head bs, head cs):myzip3 (tail as) (tail bs) (tail cs)

ordonataNat :: [Int] -> Bool 
ordonataNat [] = True 
ordonataNat [x] = True 
ordonataNat (x:xs) = and [ys | let as = zip (x:xs) [0..length (x:xs)], let bs  = zip  (x:xs) [0..length (x:xs)],  ys <- [fst c <= fst d | c <- as, d <- bs, snd c == snd d -1 ] ]

ordonataNatAltfel :: [Int] -> Bool
ordonataNatAltfel [] = True
ordonataNatAltfel [x] = True
ordonataNatAltfel (x:xs) = and [ a <= b | (a,b) <- zip (x:xs) xs]

ordonataNat1 :: [Int] -> Bool 
ordonataNat1 [] = True 
ordonataNat1 [x] = True
ordonataNat1 (x:xs) = x <= head xs && ordonataNat1 xs

ordonata :: [a] -> ( a -> a -> Bool) -> Bool 
ordonata [] operator = True 
ordonata [x] operator = True
ordonata (h:t) operator = and [a `operator` b | (a,b) <- zip (h:t) t ]

infixr 6 *<* 
(*<*) :: (Integer, Integer) -> (Integer, Integer) -> Bool 
(a,b) *<* (c,d) = (a < c) && (a < d) && (b > c) && (b > d)


compuneList :: (b -> c) -> [ ( a -> b) ] -> [ (a -> c ) ] 
compuneList f gs = [ f . g | g <- gs ]


aplicaList :: a -> [(a->b)] -> [b]
aplicaList arg fs = [f arg | f <- fs]