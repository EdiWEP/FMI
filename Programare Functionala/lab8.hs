import Data.List (nub, subsequences)
import Data.Maybe (fromJust)


type Nume = String
data Prop
  = Var Nume
  | F
  | T
  | Not Prop
  | Prop :|: Prop
  | Prop :&: Prop
  | Prop :->: Prop
  | Prop :<->: Prop
  deriving (Eq, Read)
infixr 2 :|:
infixr 3 :&:

p1 :: Prop
p1 = (Var "P" :|: Var "Q") :&: (Var "P" :&: Var "Q")

p2 :: Prop
p2 = let
        p = Var "P"
        q = Var "Q"
    in (p :|: q) :&: (Not p :&: Not q)

p3 :: Prop
p3 = let
        p = Var "P"
        q = Var "Q"
        r = Var "R"
    in (p :&: (q :|: r)) :&: ((Not p :|: Not q) :&: (Not p :|: Not r))

instance Show Prop where
    show (T) = "True"
    show (F) = "False"
    show (Var x) = x
    show (Not x) = "(~" ++ show x ++ ")"
    show (x :|: y) = "(" ++ show x ++ "|" ++ show y ++ ")"
    show (x :&: y) = "(" ++ show x ++ "&" ++ show y ++ ")"
    show (x :->: y) = "(" ++ show x ++ "->" ++ show y ++ ")"
    show (x :<->: y) = "(" ++ show x ++ "<->" ++ show y ++ ")"

test_ShowProp :: Bool
test_ShowProp =
    show (Not (Var "P") :&: Var "Q") == "((~P)&Q)"

type Env = [(Nume, Bool)]

impureLookup :: Eq a => a -> [(a,b)] -> b
impureLookup a = fromJust . lookup a

eval :: Prop -> Env -> Bool
eval T env = True 
eval F env = False
eval (Var name) env = impureLookup name env 
eval (Not p) env = not ( eval p env )
eval (p1 :|: p2) env = eval p1 env  || eval p2 env
eval (p1 :&: p2) env = eval p1 env  && eval p2 env
eval (p1 :->: p2) env 
    | not (eval p1 env) = True 
    | otherwise = eval p2 env
eval (p1 :<->: p2) env = eval p1 env == eval p2 env

test_eval = eval  (Var "P" :|: Var "Q") [("P", True), ("Q", False)] == True


variabile :: Prop -> [Nume]
variabile T = []
variabile F = []
variabile (Var k) = [k]
variabile (Not k) = nub (variabile k)
variabile (p1 :|: p2) = nub (variabile p1 ++ variabile p2)
variabile (p1 :&: p2) = nub (variabile p1 ++ variabile p2)
variabile (p1 :->: p2) = nub (variabile p1 ++ variabile p2)
variabile (p1 :<->: p2) = nub (variabile p1 ++ variabile p2)


test_variabile =
  variabile (Not (Var "P") :&: Var "Q") == ["P", "Q"]

envs :: [Nume] -> [Env]
envs names = map createEnv (subsequences names)
    where createEnv subseq = foldr (\x acc -> if x `elem` subseq then (x,True):acc else (x,False):acc) [] names

test_envs =
    envs ["P", "Q"]
    ==
    [ [ ("P",False)
      , ("Q",False)
      ]
    , [ ("P",False)
      , ("Q",True)
      ]
    , [ ("P",True)
      , ("Q",False)
      ]
    , [ ("P",True)
      , ("Q",True)
      ]
    ]

satisfiabila :: Prop -> Bool
satisfiabila prop = foldr (\env acc -> eval prop env || acc) False envirs
    where envirs = envs (variabile prop)

test_satisfiabila1 = satisfiabila (Not (Var "P") :&: Var "Q") == True
test_satisfiabila2 = satisfiabila (Not (Var "P") :&: Var "P") == False

valida :: Prop -> Bool
valida prop = not (satisfiabila (Not prop))

test_valida1 = valida (Not (Var "P") :&: Var "Q") == False
test_valida2 = valida (Not (Var "P") :|: Var "P") == True


echivalenta :: Prop -> Prop -> Bool
prop1 `echivalenta` prop2 = foldr(\env acc -> acc && eval prop1 env == eval prop2 env) True (envs (variabile prop1 ++ variabile prop2))

test_echivalenta1 =
  True
  ==
  (Var "P" :&: Var "Q") `echivalenta` (Not (Not (Var "P") :|: Not (Var "Q")))
test_echivalenta2 =
  False
  ==
  (Var "P") `echivalenta` (Var "Q")
test_echivalenta3 =
  True
  ==
  (Var "R" :|: Not (Var "R")) `echivalenta` (Var "Q" :|: Not (Var "Q"))
