-- CMPS112 Winter 2015 Homework 3 --
--Program: hw3.hs
--Authors:
--Justin Wong [jujwong@ucsc.edu]

import Data.List
--Data Structure
data BST k v = Empty | Node k v (BST k v) (BST k v)

--1 Value at Root
val::BST k v -> Maybe v
val Empty = Nothing
val (Node k v l r) = Just v

--2 Number of Nodes
size::BST k v -> Int
size Empty = 0
size (Node k v l r) = 1 + size(l) + size(r)

--3 Write an ins function that inserts a value v using k as key. 
-- If the key is already used in the tree, it just updates the value,
-- otherwise it will add a new node while maintaining 
-- the order of the binary search tree.
ins::(Ord k) => k -> v -> BST k v -> BST k v
ins k v Empty = Node k v Empty Empty
ins k v (Node a b l r)
	|k == a = Node a v l r
	|k < a = Node a b (ins k v l) r
	|k > a = Node a b l (ins k v r)

--4 Make BST an instance of the Show type class. You will have to 
-- implement the show function such that the result every node of the tree
-- is shown as "(leftTree value rightTree)". This is an in-order traversal
instance (Show v) => Show (BST k v) where
	show Empty = "()"
	show (Node k v Empty Empty) =  "(" ++ show(v) ++ ")"
	show (Node k v left right) = "(" ++ show(left) ++ show(v) ++ show(right) ++ ")"
	
--5 Make JSON an instance of the Show type class. You will have to 
-- implement the show function such that the output looks like normal JSON.
data JSON = JStr String
	| JNum Double
	| JArr [JSON]
	| JObj [(String, JSON)]

jpair::(String, JSON) -> String
jpair (s, j) = "\"" ++ s ++ "\"" ++ ":" ++ show j 
	
instance Show JSON where
	show (JStr x) = "\"" ++ x ++ "\""
	show (JNum x) = show x
	show (JArr xs) = show xs
	show (JObj xs) = "{" ++ (intercalate "," (map jpair xs)) ++ "}"
	
	

--6 Make Double and lists of Json-things members of the type class Json. 
-- You will have to implement toJson and fromJson for each of these types.
-- Json is the typeclass and toJson/fromJson is the method
class Json a where
	toJson:: a -> JSON
	fromJson:: JSON -> a

instance Json Double where
	toJson = JNum
	fromJson (JNum x) = x
instance (Json a) => Json [a] where
    toJson xs = JArr(map toJson xs)
    fromJson (JArr xs) = map fromJson xs
	











