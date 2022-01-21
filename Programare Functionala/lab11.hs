import Data.List
import Data.Maybe (fromJust)


type Name = String

data  Value  =  VBool Bool
     |VInt Int
     |VFun (Value -> Value)
     |VError

data  Hask  = HTrue | HFalse
     |HIf Hask Hask Hask
     |HLit Int
     |Hask :==: Hask
     |Hask :+:  Hask
     |Hask :*: Hask
     |HVar Name
     |HLam Name Hask
     |Hask :$: Hask

infixl 7 :*:
infix 4 :==:
infixl 6 :+:
infixl 9 :$:

type  HEnv  =  [(Name, Value)]


instance Show Value where
    show (VInt x) = show x
    show (VBool b) = show b
    show (VFun f) = show "Can't show functions"
    show (VError ) = show "Can't show errors"
    


instance Eq Value where
    VInt x == VInt y = x == y
    VBool b == VBool k = b == k
    VError == VError = error "Can't compare errors"
    VFun f == VFun g = error "Can't compare functions"
    _ == _ = error "Can't compare different types"
  

addVints (VInt x) (VInt y) = VInt (x + y)
addVints _ _ = error "invalid addition"

multVints (VInt x) (VInt y) = VInt (x * y)
multVints _ _ = error "invalid multiplication"

hEval :: Hask -> HEnv -> Value
hEval HTrue env =  VBool True
hEval HFalse env =  VBool False
hEval (HIf c d e) env   = hif (hEval c env) (hEval d env) (hEval e env)
    where   hif (VBool b) v w  =  if b then v else w
            hif _ _ _ = error "invalid if"
hEval (HLit x) env = VInt x
hEval (x :==: y) env = VBool ((hEval x env) == (hEval y env))
hEval (x :+: y) env = addVints (hEval x env) (hEval y env)
hEval (x :*: y) env = multVints (hEval x env) (hEval y env)
hEval (HVar var) env = if ((lookup var env) == Nothing) then error "nu exista variabila" else fromJust(lookup var env)
hEval (HLam nume expr) env = VFun (\x -> hEval expr ((nume, x):env))
hEval (func :$: param ) env = lamb (hEval func env) (hEval param env)
                            where lamb (VFun f) x = f x 
                                  lamb _ _ = error "invalid function" 


run :: Hask -> String
run pg = show (hEval pg [("x",VInt 3), ("y",VInt 2)])


hask1 = (HVar "x") :+: (HVar "y")

hask2 = (HLit 3) :+: (HLit 4)

rez = run hask1
rez2 = run hask2
rez3 = run (hask1 :+: hask2) 

rez4 = run (hask1 :*: hask2)