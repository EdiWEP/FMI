import Data.List
import Distribution.Simple.Utils (xargs)
import GHC.Num.Backend.Selected (integer_powmod)


myInt = 55555555555555555555555555555555555555555555555555555555555

double :: Integer -> Integer
double x  
    | x>0 = x+x
    | x<0 = x*2
    | otherwise = 0 

triple :: Integer -> Integer 
triple x = double x + x


permutaLista :: [a] -> [[a]]
permutaLista = permutations 



maxim :: Integer -> Integer -> Integer 
maxim x y = 
    if (x>y)
        then x
        else y

maxim3 :: Integer -> Integer -> Integer -> Integer 
maxim3 x y z = maxim x ( maxim y z)

maxim3beta :: Integer -> Integer -> Integer -> Integer 
maxim3beta x y z = 
    if(x>y)
        then if(x>z)
            then x
            else z 
        else if(y>z)
            then y
            else z 


maxim3charlie :: Integer -> Integer -> Integer -> Integer
maxim3charlie x y z 
    | (x>y) = if(x>z) then x else z
    | (y>z) = y 
    | otherwise = z

maxim3delta :: Integer -> Integer -> Integer -> Integer 
maxim3delta x y z = 
    let 
        t =(maxim x y) 
    in (maxim t z)

maxim4 :: Integer -> Integer -> Integer -> Integer -> Integer 
maxim4 x y z t =
    let 
        a = maxim x y
        b = maxim z t
    in maxim a b 
 
testmaxim4 :: Integer -> Integer -> Integer -> Integer -> Bool
testmaxim4 x y z t =
    let 
        
        maxi = maxim4 x y z t
        ok = if(maxi >= x && maxi >= y || maxi >= z || maxi >= t)
            then 
                --putStrLn "Maxim Corect" 
                True
            else 
                --putStrLn "Maxim Incorect"
                False
    in ok


square :: Integer -> Integer 
square x = x*x

addSquares :: Integer -> Integer -> Integer 
addSquares x y = square x + square y


paritate :: Integer -> String 
paritate x = 
    if (mod x 2) == 1
        then "impar" 
        else "par"


factorial :: Integer -> Integer
factorial x
    | (x == 0) = 1
    | otherwise = x * factorial (x-1)

greaterThanDouble :: Integer -> Integer -> Bool 
greaterThanDouble x y = 
    if (x>double y) 
        then True 
        else False 




