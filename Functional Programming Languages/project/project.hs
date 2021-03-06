allRooms::[room]
room::(Int, String, [(String, Int)])
--roomID, description, list of options, roomIDs



--looping function, where it prints then checks for userinput and prints description
mainFunc::Int -> String
mainFunc x
	|if x = -1 = "YOU WIN! CONGRATULATIONS!"
	|if x = -2 = "YOU LOSE! SUCKER"
	|otherwise = printDescription(roomIn allRooms x) ++ " " ++ printOptions(roomIn allRooms x)
	mainFunc(getRoom (roomOpt (roomIn allRooms x)))
	

--checks user input vs possible actions
getRoom::[(IO String, Int)] -> Int
getRoom xs = convertOpts(xs)
	head [b |(a,b) <- xs, a == userInput]
	where userInput <- getLine
--cases of wrong input

--printDescription::(Int, String, [(String, Int)]) -> String
printDescription::room -> String
printDescription (_,x,_) = x

--printOptions::(Int, String, [(String, Int)]) -> String
printOptions::room -> String
printOptions (_,_,x) = (intercalate " " [a | (a,b) <- x])


--takes in allRooms and roomID, returns room
--keeps track of what room in
roomIn:: [(Int, String, [(String, Int)])] -> Int -> (Int, String, [(String, Int)])
--roomIn:: allRooms -> Int -> room
roomIn xs y = head [ (a, b, c) |(a, b, c) <- xs, a == y]

--roomOpt :: (Int, String, [(String, Int)]) -> [(String, Int)]
roomOpt :: room -> [(String, Int)]
roomOpt (_,_,c) = c

getInput :: IO String
getInput <- getLine

convertOpts::[(String, Int)] -> [(IO String, Int)]
convertOpts xs = [

main:: ()
main = do 



