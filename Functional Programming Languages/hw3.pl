% CMPS112 Winter 2015 Homework 3 --
% Program: hw3.pl
% Authors:
% Justin Wong [jujwong@ucsc.edu]

father(al, bud).
father(al, kelly).
mother(peggy, kelly).
mother(peggy, bud).
mother(martha, peggy).

%8 grandma
grandma(X,Y):- mother(X,F), mother(F, Y).

%9 descendants
descendants(X, Y):-
	mother(X,Y); father(X,Y); grandma(X,Y).

% 10 siblings
siblings(X,Y):-mother(M,X),mother(M,Y), X \= Y.
siblings(X,Y):-father(F,X),father(F,Y), X \= Y.
	
%11 NFA Simulator
% The following facts describe a non-deterministic finite 
% automaton with four states q0,q1,q2 and q3 which accepts the 
% regular language "ab|aa*"

%    ASCII-ART for the NFA:
%
%    (q0)  ---a-->  (q1)  ---b-->  (q2*)
%     |
%     a
%     |
%     V  / --<-- \
%    (q3*)        a
%        \ -->-- 

% Transition Relation:
transition(q0,q1,a).
transition(q1,q2,b).
transition(q0,q3,a).
transition(q3,q3,a).

% accepting states
accepting(q2).
accepting(q3).

accepts(State, InputList):- 
   InputList = [],
   accepting(State).
accepts(State, InputList):-
   InputList = [H|T],
   transition(State, NewState, H),
   accepts(NewState, T).
   

	


