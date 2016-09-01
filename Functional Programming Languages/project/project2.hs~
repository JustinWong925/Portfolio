{- Final Project: Generic Text Based Adventure Game
   Authors: Rachael Lew, Justin Wong, Max Savage, Gabe de La Mora
   CMPS 112: Comparative Programming Languages

-}

import Data.List

{- Example room -}
room::(Int, String, [(String, Int)])
room = (1, "room 1", [("win", 0), ("lose", 99), ("new", 2)])

{- example list -}
this::[(Int, String, [(String, Int)])]
this = [(1, "room 1", [("win", 0), ("lose", 99),("new", 2)]), (2, "This is room2, where dragons live and cause lots of fire to be spread throughout the world", [("win", 0), ("move foward to the next room", 3), ("back to the old room", 1)]), (3, "room3", [("win", 0), ("move", 4), ("back", 2)]), (4, "room4", [("room1", 1), ("room2", 2), ("back", 3)])]


{- Prints out the description of the current room -}
printDescription::(Int, String, [(String, Int)]) -> String
printDescription (_,x,_) = x ++ "\n"

{- Prints the string associated with list of options -}
printOptions::(Int, String, [(String, Int)]) -> String
printOptions (_,_,x) = (intercalate "\n" [a | (a,b) <- x])

{- returns te room number if input matches an option -}
getRoom :: String -> [(String,Int)] -> Int
getRoom userInput [] = 0 
getRoom userInput xs = head [b |(a,b) <- xs, a == userInput]

{- takes in allRooms and roomID, returns room
   keeps track of what room in -}
--roomIn:: allRooms -> Int -> room
roomIn:: [(Int, String, [(String, Int)])] -> Int -> (Int, String, [(String, Int)])
roomIn xs y = head [ (a, b, c) |(a, b, c) <- xs, a == y]

{- returns list of options, roomIDs -}
--roomOpt :: room -> [(String, Int)]
roomOpt :: (Int, String, [(String, Int)]) -> [(String, Int)]
roomOpt (_,_,c) = c

{-returns 1st room from list of all rooms -}
rom1 :: [(Int, String, [(String, Int)])] -> (Int, String, [(String, Int)])
rom1 x = head [(a,b,c) | (a,b,c) <- x]

{-Takes roomID and returns eiter description or the comments -}
mainFunc::Int -> String
mainFunc x
	|x == 0 = "YOU WIN! CONGRATULATIONS!"
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
          --------------------------------------------------------------------------------combine parsing -> change this to parsed list
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
                  putStrLn (mainFunc getRoomNumber)
                  if((endState getRoomNumber) == False)
                   then 
                    loop getRoomNumber
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

loop :: Int -> IO ()
loop i = do
            getOpt <- getLine
            putStrLn ("\n")
            if(valid getOpt (roomOpt (roomIn this (i))) == True)
               then
                do
                  let getRoomNumber = (getRoom getOpt (roomOpt (roomIn this (i))))
                  putStrLn (mainFunc getRoomNumber ++ "\n")
                  if((endState getRoomNumber) == False)
                   then 
                    loop getRoomNumber
                   else 
                    putStrLn ("")
               else
                do
                 putStrLn ("Invalid Option! Choose Again!" ++ "\n")
                 putStrLn (printDescription(roomIn this (i)))
                 putStrLn ("Options: " ++ printOptions(roomIn this (i)))
                 loop i

       
       
       
