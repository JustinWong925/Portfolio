import Data.List



this::[(Int, String, [(String, Int)])]
this = [(1, "stringb", [("stringc", 2)]), (2, "str", [("str3", 3)])]

a::(Int, String, [(String, Int)])
a = (1, "stringb", [("stringc", 2), ("more", 2), ("another", 3)])

b::String
b = "this"

t::[(String,Int)]
t = [("this", 1)]

mainFunc::Int -> String
mainFunc x
	|x < 0 = "YOU WIN! CONGRATULATIONS!"
	|x == 0 = "running again!"
	|otherwise = mainFunc(x - 1)



printOptions::(Int, String, [(String, Int)]) -> String
printOptions (_,_,x) = (intercalate " " [a | (a,b) <- x])

printDescription::(Int, String, [(String, Int)]) -> String
printDescription (_,x,_) = x


{-
getRoom::[(String,Int)] -> Int
getRoom xs = head [b |(a,b) <- xs, a == userInput]
-}


--takes in allRooms and roomID, returns room
--keeps track of what room in
roomIn :: [(Int, String, [(String, Int)])] -> Int -> (Int, String, [(String, Int)])
--roomIn:: allRooms -> Int -> room
roomIn xs y = head[(a, b, c) | (a, b, c) <- xs, a == y]

roomOpt :: (Int, String, [(String, Int)]) -> [(String, Int)]
roomOpt (_,_,c) = c

