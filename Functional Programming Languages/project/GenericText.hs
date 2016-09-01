-- | Haskell Generic Text Adventure
-- | File Loading: Max Savage, Gabe de la Mora
-- | Adventure Printing/Looping: Rachael Lew, Justin Wong

import System.IO
import Data.List
import Data.Char
import Data.Functor


{- *************** NOTE ***************
       Because of the created data type Game (see line of code below):
       Changed the type declarations of 
            1) roomIn
			2) rom1
			3) mainFunc
			4) loop
	    So that they take in Game, rather than [(Int, String, [(String, Int)])]
		
			5) parse 
		Returns a Game
		
		This is causing some errors!
-}

data Game = Adventure [(Int, String, [(String, Int)])]

{- Prints out the description of the current room -}
printDescription::(Int, String, [(String, Int)]) -> String
printDescription (_,x,_) = x ++ "\n"


{- Prints the string associated with list of options -}
printOptions::(Int, String, [(String, Int)]) -> String
printOptions (_,_,x) = (intercalate "\n" [a | (a,b) <- x])


{- returns the room number if input matches an option -}
getRoom :: String -> [(String,Int)] -> Int
getRoom userInput [] = 0 
getRoom userInput xs = head [b |(a,b) <- xs, a == userInput]


{- takes in allRooms and roomID, returns room
   keeps track of what room in -}
roomIn:: Game -> Int -> (Int, String, [(String, Int)])
roomIn (Adventure xs) y = head [ (a, b, c) |(a, b, c) <- xs, a == y]


{- returns list of options, roomIDs -}
roomOpt :: (Int, String, [(String, Int)]) -> [(String, Int)]
roomOpt (_,_,c) = c


{-returns 1st room from list of all rooms -}
rom1 :: Game -> (Int, String, [(String, Int)])
rom1 (Adventure x) = head [(a,b,c) | (a,b,c) <- x]


{-Takes roomID and returns either description or the comments -}
mainFunc::Int -> Game -> String -- edited
mainFunc x (Adventure this)
	|x == 0 = "YOU WIN! GRATULATIONS!"
	|x == 99 = "YOU LOSE! SUCKER"
	|otherwise = printDescription(roomIn this x) ++ "\n" ++ "Options: " ++ "\n" ++ printOptions(roomIn this x)


{- checks the roomID with the end ints -}
endState :: Int -> Bool
endState i = if (i == 99 || i==0)
		then True
		else False


valid:: String -> [(String, Int)] -> Bool
valid userInput xs = if( length ([ [(a,b)] |(a,b) <- xs, a == userInput]) == 1)
			then True
			else False


{- Type "play" to begin the game
   First it will take in a text file and then parse its contents into the data structure we defined.
   Then it will print the description and options of the first room. It will take in user input 
   and use that to move along the rooms and call loop on the room number.
-}

play :: IO ()
play = do
	file <- readFile "test1.txt"
	let this = parse (lines file)
	let description = printDescription (rom1 this)
	putStrLn (description)
	let options = printOptions (rom1 this)
	putStrLn ("Options: " ++ "\n" ++ options ++ "\n" )
	getOpt <- getLine
	putStrLn ("\n")
	if(valid getOpt (roomOpt (roomIn this (1))) == True)
		then
			do
				let getRoomNumber = (getRoom getOpt (roomOpt (roomIn this (1))))
				putStrLn (mainFunc getRoomNumber this) -- edited
				if((endState getRoomNumber) == False)
					then
						loop getRoomNumber this
					else
						putStrLn ("")
		else
			do
		putStrLn ("Invalid option")
		play
            

{- Loop works by taking in the room number passed to it and running getRoomNumber over the roomID
   that was passed to it. It will check if the roomID is in the endState or not, if it is it will stop
   and print out either the congratulations for winning or taunt for losing, if it is not endState it
   will move rooms by looping through itself again.  
-}
loop :: Int -> Game -> IO ()
loop i (Adventure this) = do
	getOpt <- getLine
	putStrLn ("\n")
	if(valid getOpt (roomOpt (roomIn this (i))) == True)
		then
			do
				let getRoomNumber = (getRoom getOpt (roomOpt (roomIn this (i))))
				putStrLn (mainFunc getRoomNumber this ++ "\n")
				if((endState getRoomNumber) == False)
					then
						loop getRoomNumber this
					else
						putStrLn ("")
		else
			do
				putStrLn ("Invalid Option! Choose Again!" ++ "\n")
				putStrLn (printDescription(roomIn this (i)))
				putStrLn ("Options: " ++ printOptions(roomIn this (i)))
				loop i this

       
       
       



-- | Execute
--ourMain :: IO [(Int, String, [(String, Int)])]
--ourMain = do
--	file <- readFile "test1.txt"
--	let x = parse (lines file)
--	return (x)

-- | Typing and function stuff





-- | Pattern Matching based parser
parse :: [String] -> Game 
parse (x:xs)
	| x == [] = Adventure []
	| xs == [] = Adventure []
	| (drop 1 xs) == [] = Adventure []
	| all isDigit x == False = parse (drop 1 xs)
	| ((all isDigit x == False) && ((drop 1 xs) == [])) = Adventure []
	| all isDigit x == True = Adventure (((read x) :: Int), (xs !! 0), parseOptions (drop 1 xs)) : parse (drop 1 xs)
	| otherwise = Adventure []

parseOptions :: [String] -> [(String, Int)]
parseOptions (x:xs)
	| x == [] = []
	| xs == [] = []
	| (drop 1 xs) == [] = ((x, ((read (xs !! 0)) :: Int)):[])
	| all isDigit (xs !! 0) == True = ((x, ((read (xs !! 0)) :: Int)) : parseOptions (drop 1 xs))
	| otherwise = []

