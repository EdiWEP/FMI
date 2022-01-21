import Data.Maybe;

data Expr = Const Int -- integer constant
          | Expr :+: Expr -- addition
          | Expr :*: Expr -- multiplication
           deriving Eq

data Operation = Add | Mult deriving (Eq, Show)

data Tree = Lf Int -- leaf
          | Node Operation Tree Tree -- branch
           deriving (Eq, Show)

instance Show Expr where
     show (Const x) = show x
     show (Const x :+: Const y) = show x ++ "+" ++ show y 
     show (Const x :*: Const y) = show x ++ "*" ++ show y 
     
evalExp :: Expr -> Int
evalExp (Const x) = x 
evalExp ( x :+:  y) = evalExp x + evalExp y 
evalExp ( x :*:  y) = evalExp x * evalExp y 


exp1 = ((Const 2 :*: Const 3) :+: (Const 0 :*: Const 5))
exp2 = (Const 2 :*: (Const 3 :+: Const 4))
exp3 = (Const 4 :+: (Const 3 :*: Const 3))
exp4 = (((Const 1 :*: Const 2) :*: (Const 3 :+: Const 1)) :*: Const 2)
test11 = evalExp exp1 == 6
test12 = evalExp exp2 == 14
test13 = evalExp exp3 == 13
test14 = evalExp exp4 == 16

evalArb :: Tree -> Int
evalArb (Lf x) = x
evalArb (Node Add x y) = evalArb x + evalArb y
evalArb (Node Mult x y) = evalArb x * evalArb y 

expToArb :: Expr -> Tree
expToArb (Const x) = Lf x
expToArb (x :+: y) = Node Add (expToArb x) (expToArb y)
expToArb (x :*: y) = Node Mult (expToArb x) (expToArb y)


arb1 = Node Add (Node Mult (Lf 2) (Lf 3)) (Node Mult (Lf 0)(Lf 5))
arb2 = Node Mult (Lf 2) (Node Add (Lf 3)(Lf 4))
arb3 = Node Add (Lf 4) (Node Mult (Lf 3)(Lf 3))
arb4 = Node Mult (Node Mult (Node Mult (Lf 1) (Lf 2)) (Node Add (Lf 3)(Lf 1))) (Lf 2)

test21 = evalArb arb1 == 6
test22 = evalArb arb2 == 14
test23 = evalArb arb3 == 13
test24 = evalArb arb4 == 16

class Collection c where
  empty :: c key value
  singleton :: key -> value -> c key value
  insert
      :: Ord key
      => key -> value -> c key value -> c key value
  lookupc :: Ord key => key -> c key value -> Maybe value
  delete :: Ord key => key -> c key value -> c key value
  keys :: c key value -> [key]
  keys c = [ k | (k,v) <- (toList c)]
  values :: c key value -> [value]
  values c = [ v | (k,v) <- (toList c)]
  toList :: c key value -> [(key, value)]
  fromList :: Ord key => [(key,value)] -> c key value
  fromList l = foldr (\x acc -> uncurry insert x acc) empty l 

newtype PairList k v 
  = PairList { getPairList :: [(k, v)] }

instance Collection PairList where 
    empty = PairList []
    singleton key val = PairList [(key, val)]
    insert key val c = if isNothing (lookupc key c ) then PairList ((key, val) : lista) 
                            else fromList ( map (\(k,v) -> if k == key then (k,val) else (k,v) ) lista )
        where lista = toList c
    lookupc _ (PairList []) = Nothing
    lookupc key c = if length gasit > 0 then Just (snd (head gasit)) else Nothing
        where gasit = filter (\(k,v) -> k == key) (toList c) 
    delete key c = fromList (foldr (\(k,v) acc -> if k == key then acc else (k,v):acc ) [] (toList c) ) 
    toList = getPairList 

data SearchTree key value
  = Empty
  | BNode
      (SearchTree key value) -- elemente cu cheia mai mica
      key                    -- cheia elementului
      (Maybe value)          -- valoarea elementului
      (SearchTree key value) -- elemente cu cheia mai mare

instance Collection SearchTree where 
    empty = Empty
    singleton key value = BNode Empty key (Just value) Empty
    --insert key val c = if isNothing (lookupc key c ) then fromList ((key, val) : toList c) else c
    insert k val (BNode left key value right) 
        | k == key = BNode left key (Just val) right  
        | k < key = BNode (insert k val left) key value right  
        | k > key = BNode left key value (insert k val right)   
    lookupc _ Empty = Nothing
    lookupc k (BNode left key value right) 
        | k == key = value 
        | k < key = lookupc k left 
        | k > key = lookupc k left 
    delete k (BNode left key value right) 
        | k == key = BNode left key Nothing right  
        | k < key = BNode (delete k left) key value right  
        | k > key = BNode left key value (delete k right)   
    toList Empty = []
    toList (BNode left key Nothing right) = toList left ++ toList right
    toList (BNode left key (Just value) right) = toList left ++ (key, value):toList right
