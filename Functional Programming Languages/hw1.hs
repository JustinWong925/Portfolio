{------------------------------------------------
-- CMPS112 Winter 2015 Homework 1 --
Program: hw1.hs
Authors: 
Evan Hughes [eshughes@ucsc.edu]
Justin Wong [jujwong@ucsc.edu]

On this homework, we worked together for 3 hours
-------------------------------------------------}
-- (2)
citeAuthor :: String -> String -> String
citeAuthor firstname lastname = lastname ++ ", " ++ firstname

-- (3)
initials :: String -> String -> String
initials firstname lastname = [head firstname] ++ "." ++ [head lastname] ++ "."

-- (4)
title :: (String, String, Int) -> String
title (author, title, year) = title

-- (5)
citeBook :: (String, String, Int) -> String
citeBook (author,title,year) = title ++ " (" ++ author ++ ", " ++ show year ++ ")"

--(6)
bibliography_rec :: [(String, String, Int)] -> String
bibliography_rec [] = ""
bibliography_rec (x:xs) = citeBook x ++ "\n" ++ bibliography_rec xs 

--(7)
bibliography_fold :: [(String, String, Int)] -> String
bibliography_fold xs = foldl (\acc x -> acc ++ citeBook x ++ "\n") [] xs

-- (8)
--return the third element of a tuple, specific to the tuples used in this assignment
third :: (String, String, Int) -> Int
third (author,title,year) = year

averageYear :: [(String, String, Int)] -> Int
averageYear xs = year_sum `div` len
    where year_sum = sum year_list
          len = length year_list
          year_list = map (third) xs

-- (9)
--check_ref checks to see if a string starts with an opening bracket
check_ref :: String -> Bool
check_ref txt = [head txt] == "[" 

references :: String -> Int
references txt = length ref_list
    where ref_list = filter check_ref word_list
          word_list = words txt

-- (10)
{--------------------------------------------------------------------
bib_list is the same as bibliography_fold except that it makes a list
containing the citations instead of separating them by newlines
---------------------------------------------------------------------}
bib_list :: [(String, String, Int)] -> [String]
bib_list xs = reverse (foldl (\acc x -> (citeBook x):acc) [] xs)

{----------------------------------------------------------------
ref_replace takes a list of citations and a string, then checks
to see if the string is a reference. If it is, it replaces it 
with the corresponding citation.
-----------------------------------------------------------------}
ref_replace :: [String] -> String -> String
ref_replace cit ref = if (check_ref ref)
                      then cit !! ref_num
                      else ref
    where ref_num = read [(ref !! 1)] - 1

citeText :: [(String, String, Int)] -> String -> String
citeText books txt = unwords newtxt
    where newtxt = map (ref_replace bib) wordlist
          wordlist = words txt
          bib = bib_list books
