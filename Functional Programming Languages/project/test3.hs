import System.IO
import Data.Char(toUpper)
import Data.List


mainFunc::Int -> String
mainFunc x
	|x == -1 = putStrLn this = "YOU WIN! CONGRATULATIONS!"
	|x == -2 =  = "YOU LOSE! SUCKER"
	|otherwise = putStrLn "fin"


printDescription::(Int, String, [(String, Int)]) -> String
--printDescription::room -> String
printDescription (_,x,_) = x

printOptions::(Int, String, [(String, Int)]) -> String
--printOptions::room -> String
printOptions (_,_,x) = (intercalate " " [a | (a,b) <- x])


--takes in allRooms and roomID, returns room
--keeps track of what room in
roomIn:: [(Int, String, [(String, Int)])] -> Int -> (Int, String, [(String, Int)])
--roomIn:: allRooms -> Int -> room
roomIn xs y = [ (a, b, c) |(a, b, c) <- xs, a == y]

roomOpt :: (Int, String, [(String, Int)]) -> [(String, Int)]
--roomOpt :: room -> [(String, Int)]
roomOpt (_,_,c) = c

this::[(Int, String, [(String, Int)])]
this = [(1, "stringb", [("stringc", 2)]), (2, "str", [("str3", 3)])]

a::(Int, String, [(String, Int)])
a = (1, "stringb", [("stringc", 2), ("more", 2), ("another", 3)])

b::String
b = "this"

t::[(String,Int)]
t = [("this", 1), ("second", 2), ("third", 3)]

y::[String]
y = ["this", "that", "those"]


--convertOpts::[(String, Int)] -> [(IO String, Int)]
--convertOpts xs = [

main :: IO ()
main = do 
	putStrLn "Type begin to start"
	thisa <- getLine 
	if thisa == "begin"
	then (mainFunc 0)
	else putStrLn "again"



